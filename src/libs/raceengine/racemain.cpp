/***************************************************************************

    file        : racemain.cpp
    created     : Sat Nov 16 12:13:31 CET 2002
    copyright   : (C) 2002 by Eric Espié                        
    email       : eric.espie@torcs.org   
    version     : $Id$                                  

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/** @file   
    		
    @author	<a href=mailto:eric.espie@torcs.org>Eric Espie</a>
    @version	$Id$
*/

#include <stdlib.h>
#include <stdio.h>
#include <tgf.h>
#include <raceman.h>
#include <robot.h>
#include <racemantools.h>

#include "raceengine.h"
#include "raceinit.h"
#include "racegl.h"
#include "raceresults.h"
#include "racestate.h"

#include "racemain.h"

static char buf[1024];
static char path[1024];
static char path2[1024];


int
ReRaceEventInit(void)
{
    RmLoadingScreenStart(ReInfo->_reName, "data/img/splash-qrloading.png");
    ReInitTrack();
    RmLoadingScreenSetText("Loading Track 3D Description...");
    ReInfo->_reGraphicItf.inittrack(ReInfo->track);
    ReInitResults();

    return RM_SYNC | RM_NEXT_STEP;
}


int
RePreRace(void)
{
    tdble	dist;
    char	*raceName;
    char	*raceType;
    void	*params = ReInfo->params;
    void	*results = ReInfo->results;
    
    ReInfo->_reRaceName = raceName = ReGetCurrentRaceName();
    if (!raceName) {
	return RM_QUIT;
    }
    dist = GfParmGetNum(params, raceName, RM_ATTR_DISTANCE, (char*)NULL, 0);
    if (dist == 0.0) {
	ReInfo->s->_totLaps = (int)GfParmGetNum(params, raceName, RM_ATTR_LAPS, (char*)NULL, 30);
    } else {
	ReInfo->s->_totLaps = ((int)(dist / ReInfo->track->length)) + 1;
    }
    ReInfo->s->_maxDammage = (int)GfParmGetNum(params, raceName, RM_ATTR_MAX_DMG, (char*)NULL, 10000);

    raceType = GfParmGetStr(params, raceName, RM_ATTR_TYPE, RM_VAL_RACE);
    if (!strcmp(raceType, RM_VAL_RACE)) {
	ReInfo->s->_raceType = RM_TYPE_RACE;
    } else if (!strcmp(raceType, RM_VAL_QUALIF)) {
	ReInfo->s->_raceType = RM_TYPE_QUALIF;
    } else if (!strcmp(raceType, RM_VAL_PRACTICE)) {
	ReInfo->s->_raceType = RM_TYPE_PRACTICE;
    }

    /* Cleanup results */
    sprintf(path, "%s/%s", RE_SECT_RESULTS, raceName);
    GfParmListClean(results, path);

    return RM_SYNC | RM_NEXT_STEP;
}

/* return state mode */
int
ReRaceStart(void)
{
    int		i, j;
    int		sw, sh, vw, vh;
    int		foundHuman;
    int		nCars;
    int		maxCars;
    char	*prevRaceName;
    char	*dllname;
    char	key[256];
    char	*gridType;
    tRobotItf	*robot;
    tReCarInfo	*carInfo;
    tSituation	*s = ReInfo->s;
    char	*raceName = ReInfo->_reRaceName;
    void	*params = ReInfo->params;
    void	*results = ReInfo->results;


    FREEZ(ReInfo->_reCarInfo);
    carInfo = ReInfo->_reCarInfo = (tReCarInfo*)calloc(GfParmGetEltNb(params, RM_SECT_DRIVERS), sizeof(tReCarInfo));

    /* Drivers starting order */
    GfParmListClean(params, RM_SECT_DRIVERS_RACING);
    if (ReInfo->s->_raceType == RM_TYPE_QUALIF) {
	i = (int)GfParmGetNum(params, RM_SECT_DRIVERS, RM_ATTR_CUR_DRIVER, NULL, 1);
	if (i == 1) {
	    RmLoadingScreenStart(ReInfo->_reName, "data/img/splash-qrloading.png");
	    RmLoadingScreenSetText("Preparing Starting Grid...");
	} else {
	    RmShutdownLoadingScreen();
	}

	sprintf(path, "%s/%d", RM_SECT_DRIVERS, i);
	sprintf(path2, "%s/%d", RM_SECT_DRIVERS_RACING, 1);
	GfParmSetStr(params, path2, RM_ATTR_MODULE, GfParmGetStr(params, path, RM_ATTR_MODULE, ""));
	GfParmSetNum(params, path2, RM_ATTR_IDX, NULL, GfParmGetNum(params, path, RM_ATTR_IDX, NULL, 0));
    } else {

	RmLoadingScreenStart(ReInfo->_reName, "data/img/splash-qrloading.png");
	RmLoadingScreenSetText("Preparing Starting Grid...");

	gridType = GfParmGetStr(params, raceName, RM_ATTR_START_ORDER, RM_VAL_DRV_LIST_ORDER);
	if (!strcmp(gridType, RM_VAL_DRV_LIST_ORDER)) {
	    /* Starting grid in the drivers list order */
	    nCars = GfParmGetEltNb(params, RM_SECT_DRIVERS);
	    maxCars = (int)GfParmGetNum(params, raceName, RM_ATTR_MAX_DRV, NULL, 100);
	    nCars = MIN(nCars, maxCars);
	    for (i = 1; i < nCars + 1; i++) {
		sprintf(path, "%s/%d", RM_SECT_DRIVERS, i);
		sprintf(path2, "%s/%d", RM_SECT_DRIVERS_RACING, i);
		GfParmSetStr(params, path2, RM_ATTR_MODULE, GfParmGetStr(params, path, RM_ATTR_MODULE, ""));
		GfParmSetNum(params, path2, RM_ATTR_IDX, NULL, GfParmGetNum(params, path, RM_ATTR_IDX, NULL, 0));
	    }
	} else if (!strcmp(gridType, RM_VAL_LAST_RACE_ORDER)) {
	    /* Starting grid in the arrival of the previous race */
	    nCars = GfParmGetEltNb(params, RM_SECT_DRIVERS);
	    maxCars = (int)GfParmGetNum(params, raceName, RM_ATTR_MAX_DRV, NULL, 100);
	    nCars = MIN(nCars, maxCars);
	    prevRaceName = ReGetPrevRaceName();
	    if (!prevRaceName) {
		return RM_QUIT;
	    }
	    for (i = 1; i < nCars + 1; i++) {
		sprintf(path, "%s/%s/%s/%d", RE_SECT_RESULTS, prevRaceName, RE_SECT_RANK, i);
		sprintf(path2, "%s/%d", RM_SECT_DRIVERS_RACING, i);
		GfParmSetStr(params, path2, RM_ATTR_MODULE, GfParmGetStr(results, path, RE_ATTR_MODULE, ""));
		GfParmSetNum(params, path2, RM_ATTR_IDX, NULL, GfParmGetNum(results, path, RE_ATTR_IDX, NULL, 0));
	    }
	}
    }
    
    RmLoadingScreenSetText("Loading Simulation Engine...");
    dllname = GfParmGetStr(ReInfo->_reParam, "Modules", "simu", "");
    sprintf(key, "modules/simu/%s.%s", dllname, DLLEXT);
    if (GfModLoad(0, key, &ReRaceModList)) return RM_QUIT;
    ReRaceModList->modInfo->fctInit(ReRaceModList->modInfo->index, &ReInfo->_reSimItf);

    
    if (ReInitCars()) {
	return RM_QUIT;
    }

    for (i = 0; i < s->_ncars; i++) {
	sprintf(buf, "Initializing Driver %s...", s->cars[i]->_name);
	RmLoadingScreenSetText(buf);
	robot = s->cars[i]->robot;
	robot->rbNewRace(robot->index, s->cars[i], s);
    }
    
    ReInfo->_reSimItf.update(s, RCM_MAX_DT_SIMU, -1);
    for (i = 0; i < s->_ncars; i++) {
	carInfo[i].prevTrkPos = s->cars[i]->_trkPos;
    }

    RmLoadingScreenSetText("Running Prestart...");
    for (i = 0; i < s->_ncars; i++) {
	memset(&(s->cars[i]->ctrl), 0, sizeof(tCarCtrl));
	s->cars[i]->ctrl.brakeCmd = 1.0;
    }    
    for (j = 0; j < ((int)(1.0 / RCM_MAX_DT_SIMU)); j++) {
	ReInfo->_reSimItf.update(s, RCM_MAX_DT_SIMU, -1);
    }

    /* Blind mode or not */
    ReInfo->_displayMode = RM_DISP_MODE_NORMAL;
    ReInfo->_reGameScreen = ReScreenInit();
    foundHuman = 0;
    for (i = 0; i < s->_ncars; i++) {
	if (s->cars[i]->_driverType == RM_DRV_HUMAN) {
	    foundHuman = 1;
	    break;
	}
    }
    if (!foundHuman) {
	if (!strcmp(GfParmGetStr(params, ReInfo->_reRaceName, RM_ATTR_DISPMODE, RM_VAL_VISIBLE), RM_VAL_INVISIBLE)) {
	    ReInfo->_displayMode = RM_DISP_MODE_NONE;
	    ReInfo->_reGameScreen = ReResScreenInit();
	    if (ReInfo->s->_raceType == RM_TYPE_QUALIF) {
		ReUpdateQualifCurRes(s->cars[0]);
	    } else {
		sprintf(buf, "%s on %s", s->cars[0]->_name, ReInfo->track->name);
		ReResScreenSetTitle(buf);
	    }
	}
    }

    if (ReInfo->_displayMode == RM_DISP_MODE_NORMAL) {
	RmLoadingScreenSetText("Loading Cars 3D Objects...");
	ReInfo->_reGraphicItf.initcars(s);
    }
    
    RmLoadingScreenSetText("Ready.");
    
    ReInfo->_reTimeMult = 1.0;
    ReInfo->_reLastTime = 0.0;
    ReInfo->s->currentTime = -2.0;
    ReInfo->s->deltaTime = RCM_MAX_DT_SIMU;
   
    ReInfo->s->_raceState = RM_RACE_STARTING;

    GfScrGetSize(&sw, &sh, &vw, &vh);
    ReInfo->_reGraphicItf.initview((sw-vw)/2, (sh-vh)/2, vw, vh, GR_VIEW_STD, ReInfo->_reGameScreen);

    GfuiScreenActivate(ReInfo->_reGameScreen);

    return RM_SYNC | RM_NEXT_STEP;
}

/***************************************************************/
/* BACK TO RACE HOOK */

static void	*BackToRaceHookHandle = 0;

static void
BackToRaceHookActivate(void * /* dummy */)
{
    ReInfo->_reState = RE_STATE_RACE;
    GfuiScreenActivate(ReInfo->_reGameScreen);
}

static void *
BackToRaceHookInit(void)
{
    if (BackToRaceHookHandle) {
	return BackToRaceHookHandle;
    }

    BackToRaceHookHandle = GfuiHookCreate(0, BackToRaceHookActivate);

    return BackToRaceHookHandle;
}

/***************************************************************/
/* RESTART RACE HOOK */

static void	*RestartRaceHookHandle = 0;

static void
RestartRaceHookActivate(void * /* dummy */)
{
    ReRaceCleanup();
    ReInfo->_reState = RE_STATE_PRE_RACE;
    GfuiScreenActivate(ReInfo->_reGameScreen);
}

static void *
RestartRaceHookInit(void)
{
    if (RestartRaceHookHandle) {
	return RestartRaceHookHandle;
    }

    RestartRaceHookHandle = GfuiHookCreate(0, RestartRaceHookActivate);

    return RestartRaceHookHandle;
}

int
ReRaceStop(void)
{
    void	*params = ReInfo->params;

    if (!strcmp(GfParmGetStr(params, ReInfo->_reRaceName, RM_ATTR_ALLOW_RESTART, RM_VAL_NO), RM_VAL_NO)) {
	RmTwoStateScreen("Race Stopped",
			 "Abandon Race", "Abort current race", ReInfo->_reGameScreen,
			 "Resume Race", "Return to Race", BackToRaceHookInit());
    } else {
	RmTriStateScreen("Race Stopped",
			 "Restart Race", "Restart the current race", RestartRaceHookInit(),
			 "Abandon Race", "Abort current race", ReInfo->_reGameScreen,
			 "Resume Race", "Return to Race", BackToRaceHookInit());
    }
    return RM_ASYNC | RM_NEXT_STEP;	    
}


int
ReRaceEnd(void)
{
    int		curDrvIdx;
    void	*params = ReInfo->params;

    ReRaceCleanup();

    if (ReInfo->s->_raceType == RM_TYPE_QUALIF) {
	curDrvIdx = (int)GfParmGetNum(params, RM_SECT_DRIVERS, RM_ATTR_CUR_DRIVER, NULL, 1);
	curDrvIdx++;
	if (curDrvIdx > GfParmGetEltNb(params, RM_SECT_DRIVERS)) {
	    GfParmSetNum(params, RM_SECT_DRIVERS, RM_ATTR_CUR_DRIVER, NULL, 1);
	    return ReDisplayResults();
	}
	GfParmSetNum(params, RM_SECT_DRIVERS, RM_ATTR_CUR_DRIVER, NULL, curDrvIdx);
	return RM_SYNC | RM_NEXT_RACE;
    }
    
    return ReDisplayResults();
}


int
RePostRace(void)
{
    int		curRaceIdx;
    void	*params = ReInfo->params;

    curRaceIdx = (int)GfParmGetNum(params, RM_SECT_RACES, RM_ATTR_CUR_RACE, NULL, 1);
    if (curRaceIdx < GfParmGetEltNb(params, RM_SECT_RACES)) {
	curRaceIdx++;
	GfParmSetNum(params, RM_SECT_RACES, RM_ATTR_CUR_RACE, NULL, curRaceIdx);
	return RM_SYNC | RM_NEXT_RACE;
    }
    
    GfParmSetNum(params, RM_SECT_RACES, RM_ATTR_CUR_RACE, NULL, 1);
    return RM_SYNC | RM_NEXT_STEP;
}


int
ReEventShutdown(void)
{
    ReInfo->_reGraphicItf.shutdowntrack();
    return RM_SYNC | RM_NEXT_STEP;
}

