/***************************************************************************

    file        : racestate.cpp
    created     : Sat Nov 16 12:00:42 CET 2002
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

/* The Race Engine State Automaton */

#include <stdlib.h>
#include <stdio.h>
#include <tgf.h>
#include <raceman.h>
#include <racemantools.h>

#include "racemain.h"
#include "raceinit.h"
#include "raceengine.h"
#include "racegl.h"

#include "racestate.h"

static void *mainMenu;

/* State Automaton Init */
void
ReStateInit(void *prevMenu)
{
    mainMenu = prevMenu;
}


/* State Automaton Management */
void
ReStateManage(void)
{
    int mode = RM_SYNC;
    
    do {
	switch (ReInfo->_reState) {
	case RE_STATE_CONFIG:	/* raceman */
	    GfOut("RaceEngine: state = RE_STATE_CONFIG\n");
	    mode = ReInfo->_reRacemanItf.runState(ReInfo);
	    if (mode & RM_NEXT_STEP) {
		ReInfo->_reState = RE_STATE_EVENT_INIT;
	    }
	    break;

	case RE_STATE_EVENT_INIT: /* raceman */
	    GfOut("RaceEngine: state = RE_STATE_EVENT_INIT\n");
	    mode = ReInfo->_reRacemanItf.runState(ReInfo);
	    if (mode & RM_NEXT_STEP) {
		ReInfo->_reState = RE_STATE_INT_TRACK_INIT;
	    }
	    break;

	case RE_STATE_INT_TRACK_INIT: /* internal */
	    GfOut("RaceEngine: state = RE_STATE_INT_TRACK_INIT\n");
	    RmLoadingScreenStart(ReInfo->_reName, "data/img/splash-qrloading.png");
	    RmInitTrack(ReInfo);
	    RmLoadingScreenSetText("Loading Track 3D Description...");
	    ReInfo->_reGraphicItf.inittrack(ReInfo->track);
	    ReInfo->_reState = RE_STATE_PRE_RACE;
	    break;

	case RE_STATE_PRE_RACE:	/* raceman */
	    GfOut("RaceEngine: state = RE_STATE_PRE_RACE\n");
	    ReRaceCleanDrivers();
	    mode = ReInfo->_reRacemanItf.runState(ReInfo);
	    if (mode & RM_NEXT_STEP) {
		ReInfo->_reState = RE_STATE_INT_CARS_INIT;
	    }
	    break;

	case RE_STATE_INT_CARS_INIT: /* internal */
	    GfOut("RaceEngine: state = RE_STATE_INT_CARS_INIT\n");
	    RmLoadingScreenStart(ReInfo->_reName, "data/img/splash-qrloading.png");
	    mode = ReRacePrepare();
	    if (mode & RM_NEXT_STEP) {
		ReInfo->_reState = RE_STATE_RACE_START;
	    }
	    break;

	case RE_STATE_RACE_START:
	    mode = ReInfo->_reRacemanItf.runState(ReInfo);
	    if (mode & RM_NEXT_STEP) {
		ReInfo->_reState = RE_STATE_RACE;
	    }
	    break;

	case RE_STATE_RACE:
	    ReUpdate();
	    mode = ReInfo->_reRacemanItf.runState(ReInfo);
	    if ((mode & RM_END_RACE) || (ReInfo->s->_raceState == RM_RACE_ENDED)) {
		ReInfo->_reState = RE_STATE_RACE_END;
	    }
	    break;

	case RE_STATE_RACE_END:
	    mode = ReInfo->_reRacemanItf.runState(ReInfo);
	    if (mode & RM_NEXT_STEP) {
		ReInfo->_reState = RE_STATE_INT_RACE_END;
	    } else if (mode & RM_CONTINUE_RACE) {
		ReInfo->_reState = RE_STATE_RACE;
	    }
	    break;

	case RE_STATE_INT_RACE_END: /* internal */
	    GfOut("RaceEngine: state = RE_STATE_INT_CARS_SHUTDOWN\n");
	    mode = ReRaceEnd();
	    if (mode & RM_NEXT_STEP) {
		ReInfo->_reState = RE_STATE_POST_RACE;
	    }
	    break;

	case RE_STATE_POST_RACE: /* raceman */
	    GfOut("RaceEngine: state = RE_STATE_POST_RACE\n");
	    mode = ReInfo->_reRacemanItf.runState(ReInfo);
	    if (mode & RM_NEXT_STEP) {
		ReInfo->_reState = RE_STATE_INT_TRACK_SHUTDOWN;
	    } else if (mode & RM_NEXT_RACE) {
		ReInfo->_reState = RE_STATE_PRE_RACE;
	    }
	    break;

	case RE_STATE_INT_TRACK_SHUTDOWN: /* internal */
	    GfOut("RaceEngine: state = RE_STATE_INT_TRACK_SHUTDOWN\n");
	    ReInfo->_reState = RE_STATE_EVENT_SHUTDOWN;
	    mode = RM_SYNC;
	    break;

	case RE_STATE_EVENT_SHUTDOWN: /* raceman */
	    GfOut("RaceEngine: state = RE_STATE_EVENT_SHUTDOWN\n");
	    mode = ReInfo->_reRacemanItf.runState(ReInfo);
	    if (mode & RM_NEXT_STEP) {
		ReInfo->_reState = RE_STATE_SHUTDOWN;
	    } else if (mode & RM_NEXT_EVENT) {
		ReInfo->_reState = RE_STATE_EVENT_INIT;
	    }
	    break;

	case RE_STATE_SHUTDOWN:
	case RE_STATE_ERROR:
	    GfOut("RaceEngine: state = RE_STATE_SHUTDOWN\n");
	    ReShutdown(0);
	    GfuiScreenActivate(mainMenu);
	    return;

	case RE_STATE_EXIT:
	    exit (0);		/* brutal isn't it ? */
	    break;
	}
    } while ((mode & (RM_SYNC | RM_QUIT)) == RM_SYNC);
    if (mode & RM_QUIT) {
	exit (0);		/* brutal isn't it ? */
    }
    if (mode & RM_ACTIVGAMESCR) {
	GfuiScreenActivate(ReInfo->_reGameScreen);
    }
}

/* Change and Execute a New State  */
void
ReStateApply(void *state)
{
    ReInfo->_reState = (int)state;
    ReStateManage();
}
