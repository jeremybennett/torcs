/***************************************************************************

    file                 : qracemain.cpp
    created              : Sun Jan 30 22:41:27 CET 2000
    copyright            : (C) 2000 by Eric Espie
    email                : torcs@free.fr
    version              : $Id$

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <osspec.h>
#include <racemantools.h>
#include <robottools.h>

#include "qracegl.h"
#include "qracemain.h"

static tSimItf	SimItf;
static double	curTime = 0;
static double	lastTime = 0;
static double   timeMult = 1.0;
static double 	msgDisp = -1.0;
static tCarElt	*TheCarList = (tCarElt*)NULL;

static void	*qracecfg = NULL;
tModList	*qracemodlist = (tModList*)NULL;
tTrackItf	qrTrackItf;
tTrack		*qrTheTrack = (tTrack*)NULL;
tGraphicItf     qrGraphicItf;
tSituation 	qrTheSituation;
int		qrRunning; /* flag to manage the simulation */
int		qrKeyPressed = 0;

tRmInfo		*qrRaceInfo = (tRmInfo*)NULL;
tqrCarInfo	*qrCarInfo;

static const double dtmax = RCM_MAX_DT_SIMU;
static char	buf[256];

static void qrPreStart(void);


void
qrLoadTrackModule(void)
{
    char	*trackdllname;
    char	key[256];

    qracecfg = GfParmReadFile(QRACE_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    trackdllname   = GfParmGetStr(qracecfg, "Modules", "track", "");
    sprintf(key, "modules/track/%s.%s", trackdllname, DLLEXT);
    if (GfModLoad(TRK_IDENT, key, &qracemodlist)) return;
    qracemodlist->modInfo->fctInit(qracemodlist->modInfo->index, &qrTrackItf);
}


/*
 * Function
 *	qraceRun
 *
 * Description
 *	Called when the player select quick race
 *
 * Parameters
 *	none
 *
 * Return
 *	none
 *
 * Remarks
 *	
 */
void
qraceRun(void *dummy)
{
    char	*simudllname;
    char	*graphicdllname;
    int 	i;
    char	key[256];
    tModInfo	*curModInfo;
    tRobotItf	*robot;
    tdble	dist;

    curTime = lastTime = 0;
    RmLoadingScreenStart("Quick Race Loading", "data/img/splash-qrloading.png");
    RmLoadingScreenSetText("Race Configuration...");

    memset(&qrTheSituation, 0, sizeof(qrTheSituation));
    
    qracecfg = GfParmReadFile(QRACE_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    dist = GfParmGetNum(qracecfg, RM_SECT_RACE, RM_ATTR_DISTANCE, (char*)NULL, 0);
    if (dist== 0.0) {
	qrTheSituation._totLaps = (int)GfParmGetNum(qracecfg, RM_SECT_RACE, RM_ATTR_LAPS, (char*)NULL, 30);
    } else {
	qrTheSituation._totLaps = ((int)(dist / qrTheTrack->length)) + 1;
    }
    qrTheSituation._raceType = RM_TYPE_RACE;
    qrTheSituation._maxDammage = (int)GfParmGetNum(qracecfg, RM_SECT_RACE, RM_ATTR_MAX_DMG, (char*)NULL, 10000);
    
    simudllname    = GfParmGetStr(qracecfg, "Modules", "simu", "");
    graphicdllname = GfParmGetStr(qracecfg, "Modules", "graphic", "");

    RmLoadingScreenSetText("Loading Simulation Engine...");
    sprintf(key, "modules/simu/%s.%s", simudllname, DLLEXT);
    if (GfModLoad(SIM_IDENT, key, &qracemodlist)) return;
    qracemodlist->modInfo->fctInit(qracemodlist->modInfo->index, &SimItf);

    RmLoadingScreenSetText("Loading Graphic Engine...");
    sprintf(key, "modules/graphic/%s.%s", graphicdllname, DLLEXT);
    if (GfModLoad(GRX_IDENT, key, &qracemodlist)) return;
    curModInfo = qracemodlist->modInfo;
    curModInfo->fctInit(curModInfo->index, &qrGraphicItf);

    RmLoadingScreenSetText("Initializing Race Information...");
    qrRaceInfo = (tRmInfo*)calloc(1, sizeof(tRmInfo));
    qrRaceInfo->s = &qrTheSituation;
    qrRaceInfo->track = qrTheTrack;
    qrRaceInfo->simItf = &SimItf;
    qrRaceInfo->params = qracecfg;
    qrRaceInfo->modList = &qracemodlist;

    RmLoadingScreenSetText("Initializing the drivers...");
    if (RmInitCars(qrRaceInfo)) {
	GfParmWriteFile(QRACE_CFG, qracecfg, "quick race", GFPARM_PARAMETER, "../../dtd/params.dtd");
	GfParmReleaseHandle(qracecfg);
	qrTrackItf.trkShutdown();
	GfModUnloadList(&qracemodlist);
	qracemodlist = (tModList*)NULL;
	GfuiScreenReplace(qrMainMenuHandle);
	return;
    }
    

    TheCarList = qrRaceInfo->carList;
    
    qrCarInfo = (tqrCarInfo*)calloc(qrTheSituation._ncars, sizeof(tqrCarInfo));
    qrRunning = 0;    

    RmLoadingScreenSetText("Loading Track 3D Description...");
    qrGraphicItf.inittrack(qrTheTrack);
    RmLoadingScreenSetText("Loading Cars 3D Objects...");
    qrGraphicItf.initcars(&qrTheSituation);

    
    for (i = 0; i < qrTheSituation._ncars; i++) {
	sprintf(buf, "Initializing Driver %s...", qrTheSituation.cars[i]->_name);
	RmLoadingScreenSetText(buf);
	robot = qrTheSituation.cars[i]->robot;
	robot->rbNewRace(robot->index, qrTheSituation.cars[i], &qrTheSituation);
    }
    SimItf.update(&qrTheSituation, dtmax, -1);
    for (i = 0; i < qrTheSituation._ncars; i++) {
	qrCarInfo[i].prevTrkPos = qrTheSituation.cars[i]->_trkPos;
    }

    if (RmInitResults(qrRaceInfo)) {
	return;
    }

    RmLoadingScreenSetText("Running Prestart...");
    qrPreStart();

    RmLoadingScreenSetText("Ready.");
    qraceglRun();
    
    return;
}

void
qrShutdown(void)
{
    int i;
    tRobotItf *robot;
    
    qrStop();
    GfParmWriteFile(QRACE_CFG, qracecfg, "quick race", GFPARM_PARAMETER, "../../dtd/params.dtd");
    GfParmReleaseHandle(qracecfg);
    qraceglShutdown();
    RmSaveResults(qrRaceInfo);
    qrResults(qrMainMenuHandle);
    for (i = 0; i < qrTheSituation._ncars; i++) {
	robot = qrTheSituation.cars[i]->robot;
	if (robot->rbShutdown) {
	    robot->rbShutdown(robot->index);
	}
	GfParmReleaseHandle(qrTheSituation.cars[i]->_paramsHandle);
	free(qrTheSituation.cars[i]->_modName);
    }
    free(qrCarInfo);
    qrTrackItf.trkShutdown();
    SimItf.shutdown();
    qrGraphicItf.shutdowncars(); 
    GfModUnloadList(&qracemodlist);
    qracemodlist = (tModList*)NULL;
    RmShutdownResults(qrRaceInfo);
    curTime = GfTimeClock();
}

static void
qrUpdtPitTime(tCarElt *car)
{
    tqrCarInfo *info = &(qrCarInfo[car->index]);

    info->totalPitTime = 2.0 + car->pitcmd->fuel / 8.0 + (tdble)(car->pitcmd->repair) * 0.007;
    car->_scheduledEventTime = qrTheSituation.currentTime + info->totalPitTime;
    SimItf.reconfig(car);    
}


static void
qrUpdtPitCmd(void *pvcar)
{
    tCarElt *car = (tCarElt*)pvcar;
    
    qrUpdtPitTime(car);
    qrStart(); /* resynchro */
    GfuiScreenActivate(qrHandle);
}

static void
qrRaceMsgUpdate(void)
{
    if (curTime > msgDisp) {
	qrSetRaceMsg("");
    }
}

static void
qrRaceMsgSet(char *msg, double life)
{
    qrSetRaceMsg(msg);
    msgDisp = curTime + life;
}


static void
qrManage(tCarElt *car)
{
    int i, evnb, pitok;
    tTrackSeg *sseg;
    tdble wseg;
    static float color[] = {0.0, 0.0, 1.0, 1.0};
    
    tqrCarInfo *info = &(qrCarInfo[car->index]);

    if (car->_speed_x > car->_topSpeed) {
	car->_topSpeed = car->_speed_x;
    }

    /* PIT STOP */
    if (car->ctrl->raceCmd & RM_CMD_PIT_ASKED) {
	car->ctrl->msg[3] = "Can Pit";
	memcpy(car->ctrl->msgColor, color, sizeof(car->ctrl->msgColor));
    }
    
    if (car->_state & RM_CAR_STATE_PIT) {
	car->ctrl->raceCmd &= ~RM_CMD_PIT_ASKED; /* clear the flag */
	if (car->_scheduledEventTime < qrTheSituation.currentTime) {
	    car->_state &= ~RM_CAR_STATE_PIT;
	    sprintf(buf, "%s pit stop %.1fs", car->_name, info->totalPitTime);
	    qrRaceMsgSet(buf, 5);
	} else {
	    car->ctrl->msg[2] = "In Pits";
	    memcpy(car->ctrl->msgColor, color, sizeof(car->ctrl->msgColor));
	    if (car == qrTheSituation.cars[qrTheSituation.current]) {
		sprintf(buf, "%s in pits %.1fs", car->_name, qrTheSituation.currentTime - info->startPitTime);
		qrRaceMsgSet(buf, .1);
	    }
	}
    } else if ((car->_pit) && (car->ctrl->raceCmd & RM_CMD_PIT_ASKED)) {
	tdble lgFromStart = car->_trkPos.seg->lgfromstart;
	
	switch (car->_trkPos.seg->type) {
	case TR_STR:
	    lgFromStart += car->_trkPos.toStart;
	    break;
	default:
	    lgFromStart += car->_trkPos.toStart * car->_trkPos.seg->radius;
	    break;
	}
	if ((lgFromStart > car->_pit->lmin) && (lgFromStart < car->_pit->lmax)) {
	    pitok = 0;
	    if (qrTheTrack->pits.side == TR_RGT) {
		sseg = car->_trkPos.seg->rside;
		wseg = RtTrackGetWidth(sseg, car->_trkPos.toStart);
		if (sseg->rside) {
		    sseg = sseg->rside;
		    wseg += RtTrackGetWidth(sseg, car->_trkPos.toStart);
		}
		if (((car->_trkPos.toRight + wseg) <
		     (qrTheTrack->pits.width - car->_dimension_y / 2.0)) &&
		    (fabs(car->_speed_x) < 1.0) &&
		    (fabs(car->_speed_y) < 1.0)) {
		    pitok = 1;
		}
	    } else {
		sseg = car->_trkPos.seg->lside;
		wseg = RtTrackGetWidth(sseg, car->_trkPos.toStart);
		if (sseg->lside) {
		    sseg = sseg->lside;
		    wseg += RtTrackGetWidth(sseg, car->_trkPos.toStart);
		}
		if (((car->_trkPos.toLeft + wseg) <
		     (qrTheTrack->pits.width - car->_dimension_y / 2.0)) &&
		    (fabs(car->_speed_x) < 1.0) &&
		    (fabs(car->_speed_y) < 1.0)) {
		    pitok = 1;
		}
	    }
	    if (pitok) {
		car->_state |= RM_CAR_STATE_PIT;
		car->_event |= RM_EVENT_PIT_STOP;
		info->startPitTime = qrTheSituation.currentTime;
		sprintf(buf, "%s in pits", car->_name);
		qrRaceMsgSet(buf, 5);
		if (car->robot->rbPitCmd(car->robot->index, car, &qrTheSituation) == ROB_PIT_MENU) {
		    /* the pit cmd is modified by menu */
		    qrStop();
		    RmPitMenuStart(car, (void*)car, qrUpdtPitCmd);
		} else {
		    qrUpdtPitTime(car);
		}
	    }
	}
    }
    
    /* Start Line Crossing */
    if (info->prevTrkPos.seg != car->_trkPos.seg) {
	if ((info->prevTrkPos.seg->raceInfo & TR_LAST) && (car->_trkPos.seg->raceInfo & TR_START)) {
	    if (info->lapFlag == 0) {
		if ((car->_state & RM_CAR_STATE_FINISH) == 0) {
		    car->_laps++;
		    car->_remainingLaps--;
		    if (car->_laps > 1) {
			car->_lastLapTime = qrTheSituation.currentTime - info->sTime;
			car->_curTime += car->_lastLapTime;
			if (car->_bestLapTime != 0) {
			    car->_deltaBestLapTime = car->_lastLapTime - car->_bestLapTime;
			}
			if ((car->_lastLapTime < car->_bestLapTime) || (car->_bestLapTime == 0)) {
			    car->_bestLapTime = car->_lastLapTime;
			}
			if (car->_pos != 1) {
			    car->_timeBehindLeader = car->_curTime - qrTheSituation.cars[0]->_curTime;
			    car->_lapsBehindLeader = qrTheSituation.cars[0]->_laps - car->_laps;
			    car->_timeBehindPrev = car->_curTime - qrTheSituation.cars[car->_pos - 2]->_curTime;
			    qrTheSituation.cars[car->_pos - 2]->_timeBeforeNext = car->_timeBehindPrev;
			} else {
			    car->_timeBehindLeader = 0;
			    car->_lapsBehindLeader = 0;
			    car->_timeBehindPrev = 0;
			}
			info->sTime = qrTheSituation.currentTime;
			/* results history */
			evnb = qrTheSituation._ncars * (car->_laps - 2) + car->_startRank;
			qrRaceInfo->lapInfo[evnb].pos = car->_pos;
			qrRaceInfo->lapInfo[evnb].event = car->_event;
			qrRaceInfo->lapInfo[evnb].lapsBehind = car->_lapsBehindLeader;
			car->_event = 0;
			qrRaceInfo->lapInfo[evnb].lapTime = car->_lastLapTime;
		    }
		    if ((car->_remainingLaps < 0) || (qrTheSituation._raceState == RM_RACE_FINISHING)) {
			car->_state |= RM_CAR_STATE_FINISH;
			qrTheSituation._raceState = RM_RACE_FINISHING;
			switch (car->_pos) {
			case 1:
			    sprintf(buf, "%s Finished 1st", car->_name);
			    break;
			case 2:
			    sprintf(buf, "%s Finished 2nd", car->_name);
			    break;
			case 3:
			    sprintf(buf, "%s Finished 3rd", car->_name);
			    break;
			default:
			    sprintf(buf, "%s Finished %dth", car->_name, car->_pos);
			    break;
			}
			qrRaceMsgSet(buf, 5);
		    }
		} else {
		    /* prevent infinite looping of cars around track, allow one lap after finish for the first car */
		    for (i = 0; i < qrTheSituation._ncars; i++) {
			qrTheSituation.cars[i]->_state |= RM_CAR_STATE_FINISH;
		    }
		    return;
		}
	    } else {
		info->lapFlag--;
	    }
	}
	if ((info->prevTrkPos.seg->raceInfo & TR_START) && (car->_trkPos.seg->raceInfo & TR_LAST)) {
	    /* going backward through the start line */
	    info->lapFlag++;
	}
    }
    info->prevTrkPos = car->_trkPos;
    car->_curLapTime = qrTheSituation.currentTime - info->sTime;
    car->_distFromStartLine = car->_trkPos.seg->lgfromstart +
	(car->_trkPos.seg->type == TR_STR ? car->_trkPos.toStart : car->_trkPos.toStart * car->_trkPos.seg->radius);
    car->_distRaced = (car->_laps - 1) * qrTheTrack->length + car->_distFromStartLine;
    
}

static void 
qrSortCars(void)
{
    int		i,j;
    tCarElt	*car;
    int		allfinish;
    
    if ((qrTheSituation.cars[0]->_state & RM_CAR_STATE_FINISH) == 0) {
	allfinish = 0;
    } else {
	allfinish = 1;
    }
    
    for (i = 1; i < qrTheSituation._ncars; i++) {
	j = i;
	while (j > 0) {
	    if ((qrTheSituation.cars[j]->_state & RM_CAR_STATE_FINISH) == 0) {
		allfinish = 0;
		if (qrTheSituation.cars[j]->_distRaced > qrTheSituation.cars[j-1]->_distRaced) {
		    car = qrTheSituation.cars[j];
		    qrTheSituation.cars[j] = qrTheSituation.cars[j-1];
		    qrTheSituation.cars[j-1] = car;
		    if (qrTheSituation.current == j) {
			qrTheSituation.current = j-1;
		    } else if (qrTheSituation.current == j-1) {
			qrTheSituation.current = j;
		    }
		    qrTheSituation.cars[j]->_pos = j+1;
		    qrTheSituation.cars[j-1]->_pos = j;
		    j--;
		    continue;
		}
	    }
	    j = 0;
	}
    }
    if (allfinish) {
	qrShutdown();
    }
}

static void
qrPreStart(void)
{
    int i,j;
    for (i = 0; i < qrTheSituation._ncars; i++) {
	memset(qrTheSituation.cars[i]->ctrl, 0, sizeof(tCarCtrl));
	qrTheSituation.cars[i]->ctrl->brakeCmd = 1.0;
	qrTheSituation.cars[i]->ctrl->accelCmd = 0.0;
	qrTheSituation.cars[i]->ctrl->gear = 0;
    }    
    for (j = 0; j < ((int)(1.0 / dtmax)); j++) {
	SimItf.update(&qrTheSituation, dtmax, -1);
    }
}


void
qrOneStep(void *telem)
{
    int i;
    tRobotItf *robot;

    curTime += dtmax * timeMult;
    qrTheSituation.currentTime += dtmax;
    
    if ((qrTheSituation.currentTime - lastTime) >= RCM_MAX_DT_ROBOTS) {
	qrTheSituation.deltaTime = qrTheSituation.currentTime - lastTime;
	for (i = 0; i < qrTheSituation._ncars; i++) {
	    if ((qrTheSituation.cars[i]->_state & RM_CAR_STATE_NO_SIMU) == 0) {
		robot = qrTheSituation.cars[i]->robot;
		robot->rbDrive(robot->index, qrTheSituation.cars[i], &qrTheSituation);
	    }
	}
	lastTime = qrTheSituation.currentTime;
	qrKeyPressed = 0;
    }

    qrTheSituation.deltaTime = dtmax;

    if (telem) {
	SimItf.update(&qrTheSituation, dtmax, qrTheSituation.cars[qrTheSituation.current]->index);
    } else {
	SimItf.update(&qrTheSituation, dtmax, -1);
    }
    for (i = 0; i < qrTheSituation._ncars; i++) {
	qrManage(qrTheSituation.cars[i]);
    }

    qrRaceMsgUpdate();
    qrSortCars();
}

void
qrStart(void)
{
    qrRunning = 1;
    curTime = GfTimeClock() - dtmax;
}

void
qrStop(void)
{
    qrRunning = 0;
}


void
qrUpdate(void)
{
    double t = GfTimeClock();

    while (qrRunning && ((t - curTime) > dtmax)) {
	qrOneStep(NULL);
    }
}

void
qrNextCar(void *dummy)
{
    qrTheSituation.current++;
    if (qrTheSituation.current == qrTheSituation._ncars) {
	qrTheSituation.current--;
    }
    GfParmSetStr(qracecfg, RM_SECT_DRIVERS, RM_ATTR_FOCUSED,
		 qrTheSituation.cars[qrTheSituation.current]->_modName);
    GfParmSetNum(qracecfg, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, (char*)NULL,
		 (tdble)(qrTheSituation.cars[qrTheSituation.current]->_driverIndex));
    qrTheSituation.cars[qrTheSituation.current]->priv->collision = 0;
}

void
qrPrevCar(void *dummy)
{
    qrTheSituation.current--;
    if (qrTheSituation.current < 0) {
	qrTheSituation.current = 0;
    }
    GfParmSetStr(qracecfg, RM_SECT_DRIVERS, RM_ATTR_FOCUSED,
		 qrTheSituation.cars[qrTheSituation.current]->_modName);
    GfParmSetNum(qracecfg, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, (char*)NULL,
		 (tdble)(qrTheSituation.cars[qrTheSituation.current]->_driverIndex));
    qrTheSituation.cars[qrTheSituation.current]->priv->collision = 0;
}

void
qrTimeMod (void *vcmd)
{
    switch ((int)vcmd) {
    case 0:
	timeMult *= 2.0;
	if (timeMult > 64.0) {
	    timeMult = 64.0;
	}
	break;
    case 1:
	timeMult *= 0.5;
	if (timeMult < 0.25) {
	    timeMult = 0.25;
	}
	break;
    case 2:
    default:
	timeMult = 1.0;
	break;
    }
    sprintf(buf, "Time x%.2f", 1.0 / timeMult);
    qrRaceMsgSet(buf, 5);
}
