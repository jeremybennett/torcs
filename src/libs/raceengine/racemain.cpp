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
    int		i;
    int		nCars;
    tdble	dist;
    char	*raceName;
    char	*raceType;
    char	*gridType;
    void	*params = ReInfo->params;
    
    raceName = ReGetCurrentRaceName();
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

    ReInfo->_reCarInfo = (tReCarInfo*)calloc(GfParmGetEltNb(params, RM_SECT_DRIVERS), sizeof(tReCarInfo));

    raceType = GfParmGetStr(params, raceName, RM_ATTR_TYPE, RM_VAL_RACE);
    if (!strcmp(raceType, RM_VAL_RACE)) {
	ReInfo->s->_raceType = RM_TYPE_RACE;
    } else if (!strcmp(raceType, RM_VAL_QUALIF)) {
	ReInfo->s->_raceType = RM_TYPE_QUALIF;
    } else if (!strcmp(raceType, RM_VAL_PRACTICE)) {
	ReInfo->s->_raceType = RM_TYPE_PRACTICE;
    }

    /* Drivers starting order */
    gridType = GfParmGetStr(params, raceName, RM_ATTR_START_ORDER, RM_VAL_DRV_LIST_ORDER);
    if (!strcmp(gridType, RM_VAL_DRV_LIST_ORDER)) {
	/* Starting grid in the drivers list order */
	GfParmListClean(params, RM_SECT_DRIVERS_RACING);
	nCars = GfParmGetEltNb(params, RM_SECT_DRIVERS);
	for (i = 1; i < nCars + 1; i++) {
	    sprintf(path, "%s/%d", RM_SECT_DRIVERS, i);
	    sprintf(path2, "%s/%d", RM_SECT_DRIVERS_RACING, i);
	    GfParmSetStr(params, path2, RM_ATTR_MODULE, GfParmGetStr(params, path, RM_ATTR_MODULE, ""));
	    GfParmSetNum(params, path2, RM_ATTR_IDX, NULL, GfParmGetNum(params, path, RM_ATTR_IDX, NULL, 0));
	}
    }

    return RM_SYNC | RM_NEXT_STEP;
}

/* return state mode */
int
ReRaceStart(void)
{
    int		i, j;
    int		sw, sh, vw, vh;
    int		foundHuman;
    char	*dllname;
    char	key[256];
    char	*raceName;
    tRobotItf	*robot;
    tReCarInfo	*carInfo = ReInfo->_reCarInfo;;
    tSituation	*s = ReInfo->s;
    void	*params = ReInfo->params;


    RmLoadingScreenStart(ReInfo->_reName, "data/img/splash-qrloading.png");

    GfOut("Loading Simulation Engine...\n");
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

    RmLoadingScreenSetText("Loading Cars 3D Objects...");
    ReInfo->_reGraphicItf.initcars(s);

    RmLoadingScreenSetText("Ready.");

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
	raceName = ReGetCurrentRaceName();
	if (!strcmp(GfParmGetStr(params, raceName, RM_ATTR_DISPMODE, RM_VAL_VISIBLE), RM_VAL_INVISIBLE)) {
	    ReInfo->_displayMode = RM_DISP_MODE_NONE;
	    ReInfo->_reGameScreen = ReResScreenInit();
	    sprintf(buf, "%s on %s", s->cars[0]->_name, ReInfo->track->name);
	    ReResScreenSetTitle(buf);
	}
    }
    
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
    char	*raceName;
    void	*params = ReInfo->params;

    raceName = ReGetCurrentRaceName();
    if (!raceName) {
	return RM_QUIT;
    }

    if (!strcmp(GfParmGetStr(params, raceName, RM_ATTR_ALLOW_RESTART, RM_VAL_NO), RM_VAL_NO)) {
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
    ReRaceCleanup();

    return ReDisplayResults();
}


int
RePostRace(void)
{
    return RM_SYNC | RM_NEXT_STEP;
}


