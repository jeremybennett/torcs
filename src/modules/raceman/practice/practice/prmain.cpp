/***************************************************************************

    file                 : prmain.cpp
    created              : Sun Jan 30 22:53:53 CET 2000
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
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <osspec.h>

#include <raceman.h>
#include <practicectrl.h>

#include "practice.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

static tSimItf	SimItf;
static double	curTime = 0;
static double	lastTime = 0;
static double   timeMult = 1.0;
static tCarElt	*TheCarList = (tCarElt*)NULL;

static void	*pracecfg = NULL;
tModList	*pracemodlist = (tModList*)NULL;
tTrackItf	prTrackItf = {0};
tTrack		*prTheTrack = (tTrack*)NULL;
tGraphicItf     prGraphicItf;
tSituation 	prTheSituation;
int		prRunning; /* flag to manage the simulation */
int		prKeyPressed = 0;

tRmInfo		*prRaceInfo = (tRmInfo*)NULL;

tprCarInfo	*prCarInfo;

static const tdble dtmax = RCM_MAX_DT_SIMU;

static void prPreStart(void);
static tRingListHead prCurResults = {(tRingList*)&prCurResults, (tRingList*)&prCurResults}; /* empty */

int prShowRace = 1;

static double	prBonusTime;	/* time allowed after finish */

void
prLoadTrackModule(void)
{
    char	*trackdllname;
    char	key[256];

    pracecfg = GfParmReadFile(PRACTICE_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    trackdllname   = GfParmGetStr(pracecfg, "Modules", "track", "");
    sprintf(key, "modules/track/%s.%s", trackdllname, DLLEXT);
    if (GfModLoad(TRK_IDENT, key, &pracemodlist)) return;
    pracemodlist->modInfo->fctInit(pracemodlist->modInfo->index, &prTrackItf);
}



void
prRun(void)
{
    char	*simudllname;
    char	*graphicdllname;
    int 	i;
    char	key[256];
    tModInfo	*curModInfo;
    tRobotItf	*robot;
    char	*trackName;
    char	*catName;
    char	buf[256];
    tRingList	*lm;
    char	*name;
    tdble	dist;

    curTime = lastTime = 0;
    RmLoadingScreenStart("Practice Loading", "data/img/splash-qrloading.png");
    RmLoadingScreenSetText("Race Configuration...");

    while ((lm = GfRlstUnlinkFirst(&prCurResults)) != NULL) free(lm);
    if (prTrackItf.trkBuild == NULL) {
	prLoadTrackModule();
    }
    
    prBonusTime = 0;

    memset(&prTheSituation, 0, sizeof(prTheSituation));
    
    pracecfg = GfParmReadFile(PRACTICE_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    trackName = GfParmGetStr(pracecfg, "Race/Track", "name", "");
    catName = GfParmGetStr(pracecfg, "Race/Track", "category", "");

    GfOut("track name = %s  category = %s\n", trackName, catName);
    sprintf(buf, "tracks/%s/%s/%s.%s", catName, trackName, trackName, TRKEXT);
    
    prTheTrack = prTrackItf.trkBuild(buf);
    dist = GfParmGetNum(pracecfg, RM_SECT_RACE, RM_ATTR_DISTANCE, (char*)NULL, 0);
    if (dist== 0.0) {
	prTheSituation._totLaps = (int)GfParmGetNum(pracecfg, RM_SECT_RACE, RM_ATTR_LAPS, (char*)NULL, 30);
    } else {
	prTheSituation._totLaps = ((int)(dist / prTheTrack->length)) + 1;
    }
    if (prTheSituation._totLaps > 20) {
	prTheSituation._totLaps = 20;
    }
    
    prTheSituation._raceType = RM_TYPE_PRACTICE;
    
    simudllname    = GfParmGetStr(pracecfg, "Modules", "simu", "");
    graphicdllname = GfParmGetStr(pracecfg, "Modules", "graphic", "");
    name = GfParmGetStr(pracecfg, RM_SECT_RACE, RM_ATTR_SHOW_RACE, "yes");
    if (strcmp(name, "yes") == 0) {
	prShowRace = 1;
    } else {
	prShowRace = 0;
    }

    RmLoadingScreenSetText("Loading Simulation Engine...");
    sprintf(key, "modules/simu/%s.%s", simudllname, DLLEXT);
    if (GfModLoad(SIM_IDENT, key, &pracemodlist)) return;
    pracemodlist->modInfo->fctInit(pracemodlist->modInfo->index, &SimItf);

    RmLoadingScreenSetText("Loading Graphic Engine...");
    sprintf(key, "modules/graphic/%s.%s", graphicdllname, DLLEXT);
    if (GfModLoad(GRX_IDENT, key, &pracemodlist)) return;
    curModInfo = pracemodlist->modInfo;
    curModInfo->fctInit(curModInfo->index, &prGraphicItf);

    RmLoadingScreenSetText("Initializing Race Information...");
    prRaceInfo = (tRmInfo*)calloc(1, sizeof(tRmInfo));
    prRaceInfo->s = &prTheSituation;
    prRaceInfo->track = prTheTrack;
    prRaceInfo->simItf = &SimItf;
    prRaceInfo->params = pracecfg;
    prRaceInfo->modList = &pracemodlist;
    
    RmLoadingScreenSetText("Initializing the driver...");
    RmInitCars(prRaceInfo);
    TheCarList = prRaceInfo->carList;
    
    prCarInfo = (tprCarInfo*)calloc(prTheSituation._ncars, sizeof(tprCarInfo));
    prRunning = 0;    

    if (prShowRace) {
	RmLoadingScreenSetText("Loading Track 3D Description...");
	prGraphicItf.inittrack(prTheTrack);
	RmLoadingScreenSetText("Loading Cars 3D Objects...");
	prGraphicItf.initcars(&prTheSituation);
    }
    

    RmLoadingScreenSetText("Initializing the driver...");
    for (i = 0; i < prTheSituation._ncars; i++) {
	robot = prTheSituation.cars[i]->robot;
	robot->rbNewRace(robot->index, prTheSituation.cars[i], &prTheSituation);
    }
    SimItf.update(&prTheSituation, dtmax, -1);
    for (i = 0; i < prTheSituation._ncars; i++) {
	prCarInfo[i].prevTrkPos = prTheSituation.cars[i]->_trkPos;
    }

    RmLoadingScreenSetText("Running Prestart...");
    prPreStart();

    RmLoadingScreenSetText("Ready.");
    praceglRun();
    
    return;
}

void
prShutdown(void)
{
    int i;
    tRobotItf *robot;
    
    GfParmWriteFile(PRACTICE_CFG, pracecfg, "practice", GFPARM_PARAMETER, "../../dtd/params.dtd");
    GfParmReleaseHandle(pracecfg);
    praceglShutdown();
    for (i = 0; i < prTheSituation._ncars; i++) {
	robot = prTheSituation.cars[i]->robot;
	if (robot->rbShutdown) {
	    robot->rbShutdown(robot->index);
	}
	GfParmReleaseHandle(prTheSituation.cars[i]->_paramsHandle);
	free(prTheSituation.cars[i]->_modName);
    }
    free(prCarInfo);
    prTrackItf.trkShutdown();
    SimItf.shutdown();
    GfModUnloadList(&pracemodlist);
    pracemodlist = (tModList*)NULL;
    prCtrlItf->results(&prCurResults);
    prTrackItf.trkBuild = NULL;
}


static int
prManage(tCarElt *car, int dispRes)
{
    tPractResults *curRes;
    char bufRes[1024];
    char *s;
    
    tprCarInfo *info = &(prCarInfo[car->index]);

    if (car->_speed_x > car->_topSpeed) {
	car->_topSpeed = car->_speed_x;
    }

    if (car->_speed_x > info->topSpd) info->topSpd = car->_speed_x;
    if (car->_speed_x < info->botSpd) info->botSpd = car->_speed_x;
    if ((car->_speed_x < 0.1) && (car->_fuel == 0)) {
	return 1;
    }
    
    if (prBonusTime) {
	if (prBonusTime < prTheSituation.currentTime) {
	    return 1;
	} else {
	    return 0;
	}
    }
    if (info->prevTrkPos.seg != car->_trkPos.seg) {
	if ((info->prevTrkPos.seg->raceInfo &TR_LAST) && (car->_trkPos.seg->raceInfo & TR_START)) {
	    if (info->lapFlag == 0) {
		/* new lap */
		car->_laps++;
		car->_remainingLaps--;
		if (car->_laps > 1) {
		    car->_lastLapTime = prTheSituation.currentTime - info->sTime;
		    car->_curTime += car->_lastLapTime;
		    if (car->_bestLapTime != 0) {
			car->_deltaBestLapTime = car->_lastLapTime - car->_bestLapTime;
		    }
		    if ((car->_lastLapTime < car->_bestLapTime) || (car->_bestLapTime == 0)) {
			car->_bestLapTime = car->_lastLapTime;
		    }
		    info->sTime = prTheSituation.currentTime;
		    curRes = (tPractResults*)malloc(sizeof(tPractResults));
		    curRes->lap = car->_laps - 1;
		    curRes->lapTime = car->_lastLapTime;
		    curRes->topSpeed = info->topSpd;
		    info->topSpd = car->_speed_x;
		    curRes->bottomSpeed = info->botSpd;
		    info->botSpd = car->_speed_x;
		    curRes->speedAvg = prTheTrack->length / curRes->lapTime;
		    curRes->fuel = info->fuel - car->_fuel;
		    info->fuel = car->_fuel;
		    GfRlstAddLast(&prCurResults, (tRingList*)curRes);
		    if (dispRes) {
			s = GfTime2Str(curRes->lapTime, 0);
			sprintf(bufRes,"lap: %2d   time: %s  top spd: %.2f    min spd: %.2f    dammage: %d", 
				curRes->lap, s, curRes->topSpeed * 3.6, curRes->bottomSpeed * 3.6, car->_dammage);
			RmLoadingScreenSetText(bufRes);
		    }
		} else {
		    /* first lap starting */
		    info->sTime = prTheSituation.currentTime;
		    info->topSpd = car->_speed_x;
		    info->botSpd = car->_speed_x;
		    info->fuel = car->_fuel;
		}
		if (car->_remainingLaps < 0) {
		    prBonusTime = prTheSituation.currentTime + 5.0;
		    return 0;
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
    car->_curLapTime = prTheSituation.currentTime - info->sTime;
    car->_distRaced = (car->_laps - 1) * prTheTrack->length + car->_trkPos.seg->lgfromstart + 
	(car->_trkPos.seg->type == TR_STR ? car->_trkPos.toStart : car->_trkPos.toStart * car->_trkPos.seg->radius);

    return 0;
}


static void
prPreStart(void)
{
    int i,j;
    for (j = 0; j < ((int)(1.0 / dtmax)); j++) {
	for (i = 0; i < prTheSituation._ncars; i++) {
	    memset(prTheSituation.cars[i]->ctrl, 0, sizeof(tCarCtrl));
	    prTheSituation.cars[i]->ctrl->brakeCmd = 1.0;
	}
	SimItf.update(&prTheSituation, dtmax, -1);
    }
}


void
prStart(void)
{
    prRunning = 1;
    curTime = GfTimeClock() - dtmax;
}

void
prStop(void)
{
    prRunning = 0;
}


void
prUpdate(void)
{
    int i;
    tRobotItf *robot;

    double t = GfTimeClock();

    if (prRunning) {
	while ((t - curTime) > dtmax) {
	    curTime += dtmax * timeMult;
	    prTheSituation.currentTime += dtmax;
	    if ((prTheSituation.currentTime - lastTime) >= RCM_MAX_DT_ROBOTS) {
		prTheSituation.deltaTime = prTheSituation.currentTime - lastTime;
		for (i = 0; i < prTheSituation._ncars; i++) {
		    robot = prTheSituation.cars[i]->robot;
		    robot->rbDrive(robot->index, prTheSituation.cars[i], &prTheSituation);
		}
		lastTime = prTheSituation.currentTime;
		prKeyPressed = 0;
	    }
	    prTheSituation.deltaTime = dtmax;
	    SimItf.update(&prTheSituation, dtmax, -1);
	    for (i = 0; i < prTheSituation._ncars; i++) {
		if (prManage(prTheSituation.cars[i], 0)) {
		    prShutdown();
		    return;
		}
	    }
	}
    }
}

void
prUpdateBlind(void)
{
    int i;
    tRobotItf *robot;

    lastTime = 0;
    curTime = 0;

    while (1) {
	curTime += dtmax;
	prTheSituation.currentTime += dtmax;
	if ((prTheSituation.currentTime - lastTime) >= RCM_MAX_DT_ROBOTS) {
	    prTheSituation.deltaTime = prTheSituation.currentTime - lastTime;
	    for (i = 0; i < prTheSituation._ncars; i++) {
		robot = prTheSituation.cars[i]->robot;
		robot->rbDrive(robot->index, prTheSituation.cars[i], &prTheSituation);
	    }
	    prKeyPressed = 0;
	    lastTime = prTheSituation.currentTime;
	}
	prTheSituation.deltaTime = dtmax;
	SimItf.update(&prTheSituation, dtmax, -1);
	for (i = 0; i < prTheSituation._ncars; i++) {
	    if (prManage(prTheSituation.cars[i], 1)) {
		prShutdown();
		return;
	    }
	}
    }
}

void
prTimeMod (void *vcmd)
{
    switch ((int)vcmd) {
    case 0:
	timeMult *= 2.0;
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
}
