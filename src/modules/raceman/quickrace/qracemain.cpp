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

#include <tgf.h>
#include <osspec.h>
#include <racemantools.h>
#include <robottools.h>

#include "qracegl.h"
#include "qracemain.h"



static tSimItf	SimItf;
static double	curTime;
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

static const double dtmax = 0.005;

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
    char	buf[256];
    char	key[256];
    tModInfo	*curModInfo;
    tRobotItf	*robot;
	
    RmLoadingScreenStart("Quick Race Loading", "data/img/splash-qrloading.png");
    RmLoadingScreenSetText("Race Configuration...");

    memset(&qrTheSituation, 0, sizeof(qrTheSituation));
    
    qracecfg = GfParmReadFile(QRACE_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    qrTheSituation._totLaps = (int)GfParmGetNum(qracecfg, "Race", "laps", (char*)NULL, 30);
    qrTheSituation._raceType = RM_TYPE_RACE;
    qrTheSituation._maxDammage = (int)GfParmGetNum(qracecfg, "Race", RM_ATTR_MAX_DMG, (char*)NULL, 10000);
    
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
	GfuiScreenActivate(qrMainMenuHandle);
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
    qrResults(qrMainMenuHandle);
    for (i = 0; i < qrTheSituation._ncars; i++) {
	robot = qrTheSituation.cars[i]->robot;
	if (robot->rbShutdown) robot->rbShutdown();
	GfParmReleaseHandle(qrTheSituation.cars[i]->_paramsHandle);
	free(qrTheSituation.cars[i]->_modName);
    }
    free(qrCarInfo);
    qrTrackItf.trkShutdown();
    SimItf.shutdown();
    GfModUnloadList(&qracemodlist);
    qracemodlist = (tModList*)NULL;
    curTime = GfTimeClock();
}

static void
qrUpdtPitTime(tCarElt *car)
{
    car->_scheduledEventTime = qrTheSituation.currentTime + 5.0 + car->pitcmd->fuel / 8.0 + (tdble)(car->pitcmd->repair) * 0.015;
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
qrManage(tCarElt *car)
{
    int i;
    
    tqrCarInfo *info = &(qrCarInfo[car->index]);

    if (car->_speed_x > car->_topSpeed) {
	car->_topSpeed = car->_speed_x;
    }

    /* PIT STOP */
    if (car->_state & RM_CAR_STATE_PIT) {
	if (car->_scheduledEventTime < qrTheSituation.currentTime) {
	    car->_state &= ~RM_CAR_STATE_PIT;
	}
    } else if ((car->_pit) && (car->ctrl->raceCmd == RM_CMD_PIT_ASKED) &&
	       (car->_trkPos.seg == car->_pit->pos.seg) && 
	       (car->_trkPos.toStart > (car->_pit->pos.toStart - qrTheTrack->pits.len / 2.0 + car->_dimension_x/2.0)) &&
	       (car->_trkPos.toStart < (car->_pit->pos.toStart + qrTheTrack->pits.len / 2.0 - car->_dimension_x/2.0))) {
	if (((qrTheTrack->pits.side == TR_RGT) &&
	     ((car->_trkPos.toRight + RtTrackGetWidth(car->_trkPos.seg->rside, car->_trkPos.toStart) <
	       (qrTheTrack->pits.width - car->_dimension_y / 2.0)) &&
	      (fabs(car->_speed_x) < 0.1) &&
	      (fabs(car->_speed_y) < 0.1))) ||
	    ((qrTheTrack->pits.side != TR_RGT) && 
	     ((car->_trkPos.toLeft + RtTrackGetWidth(car->_trkPos.seg->lside, car->_trkPos.toStart) <
	       (qrTheTrack->pits.width - car->_dimension_y / 2.0)) &&
	      (fabs(car->_speed_x) < 0.1) &&
	      (fabs(car->_speed_y) < 0.1)))) {
	    car->_state |= RM_CAR_STATE_PIT;
	    if (car->robot->rbPitCmd(car->robot->index, car, &qrTheSituation) == ROB_PIT_MENU) {
		/* the pit cmd is modified by menu */
		qrStop();
		RmPitMenuStart(car, (void*)car, qrUpdtPitCmd);
	    }
	    qrUpdtPitTime(car);
	}
    }

    /* Start Line Crossing */
    if (info->prevTrkPos.seg != car->_trkPos.seg) {
	if ((info->prevTrkPos.seg->raceInfo == TR_LAST) && (car->_trkPos.seg->raceInfo == TR_START)) {
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
		    }
		    if ((car->_remainingLaps < 0) || (qrTheSituation._raceState == RM_RACE_FINISHING)) {
			car->_state |= RM_CAR_STATE_FINISH;
			qrTheSituation._raceState = RM_RACE_FINISHING;
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
	if ((info->prevTrkPos.seg->raceInfo == TR_START) && (car->_trkPos.seg->raceInfo == TR_LAST)) {
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
    for (j = 0; j < 200; j++) {
	SimItf.update(&qrTheSituation, dtmax, -1);
    }
}


void
qrOneStep(void *telem)
{
    int i;
    tRobotItf *robot;
    
    qrTheSituation.deltaTime = 2 * dtmax;
    for (i = 0; i < qrTheSituation._ncars; i++) {
	if ((qrTheSituation.cars[i]->_state & RM_CAR_STATE_NO_SIMU) == 0) {
	    robot = qrTheSituation.cars[i]->robot;
	    robot->rbDrive(robot->index, qrTheSituation.cars[i], &qrTheSituation);
	}
    }
    qrTheSituation.deltaTime = dtmax;
    if (telem) {
	SimItf.update(&qrTheSituation, dtmax, qrTheSituation.cars[qrTheSituation.current]->index);
	SimItf.update(&qrTheSituation, dtmax, qrTheSituation.cars[qrTheSituation.current]->index);
    } else {
	SimItf.update(&qrTheSituation, dtmax, -1);
	SimItf.update(&qrTheSituation, dtmax, -1);
    }
    for (i = 0; i < qrTheSituation._ncars; i++) {
	qrManage(qrTheSituation.cars[i]);
    }
    qrTheSituation.currentTime += 2*dtmax;
    qrKeyPressed = 0;
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

    while (qrRunning && ((t - curTime) > (2*dtmax))) {
	qrOneStep(NULL);
	curTime += 2*dtmax;
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
