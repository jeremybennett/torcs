/***************************************************************************

    file        : simplerace.cpp
    created     : Sat Nov 16 17:37:16 CET 2002
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
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <osspec.h>
#include <raceman.h>
#include <racemantools.h>

#include "simpleconfig.h"
#include "simplehook.h"

#include "simplerace.h"

tRmInfo *RmInfo = 0;

static int srQualLaps;
static int srEventProgress;

#define SR_QUALIFS	1
#define SR_RACE		2

#ifdef _WIN32
BOOL WINAPI DllEntryPoint (HINSTANCE hDLL, DWORD dwReason, LPVOID Reserved)
{
    return TRUE;
}
#endif

static void
eventInit(tRmInfo *rmInfo)
{
    srQualLaps = (int)GfParmGetNum(rmInfo->params, RM_SECT_RACE, RM_ATTR_QUAL_LAPS, (char*)NULL, 0);

    if (srQualLaps) {
	srEventProgress = SR_QUALIFS;
	
    } else {
	srEventProgress = SR_RACE;
    }
}

static void
preRace(tRmInfo *rmInfo)
{
    tdble	dist;
    void	*params = rmInfo->params;

    switch (srEventProgress) {
    case SR_QUALIFS:
	rmInfo->s->_totLaps = srQualLaps;
	rmInfo->s->_raceType = RM_TYPE_QUALIF;
	rmInfo->s->_maxDammage = (int)GfParmGetNum(params, RM_SECT_QUALIF, RM_ATTR_MAX_DMG, (char*)NULL, 10000);
	break;

    case SR_RACE:
	dist = GfParmGetNum(params, RM_SECT_RACE, RM_ATTR_DISTANCE, (char*)NULL, 0);
	if (dist== 0.0) {
	    rmInfo->s->_totLaps = (int)GfParmGetNum(rmInfo->params, RM_SECT_RACE, RM_ATTR_LAPS, (char*)NULL, 30);
	} else {
	    rmInfo->s->_totLaps = ((int)(dist / rmInfo->track->length)) + 1;
	}
	rmInfo->s->_raceType = RM_TYPE_RACE;
	rmInfo->s->_maxDammage = (int)GfParmGetNum(params, RM_SECT_RACE, RM_ATTR_MAX_DMG, (char*)NULL, 10000);
	break;
    }
}

static void
postRace(tRmInfo *rmInfo)
{
    switch (srEventProgress) {
    case SR_QUALIFS:
	break;

    case SR_RACE:
	RmShowResults(SrRaceAgainHookInit(), rmInfo, RE_SECT_FINAL);
	break;
    }
}

/* Run state from Race Engine */
static int
runState(tRmInfo *rmInfo)
{
    switch (rmInfo->_reState) {
    case RE_STATE_CONFIG:
	RmInfo = rmInfo;
	GfOut("SimpleRace runState: RE_STATE_CONFIG\n");
	SrConfigInit();
	return RM_ASYNC | RM_NEXT_STEP;	/* Race engine will be called back later */

    case RE_STATE_EVENT_INIT:
	GfOut("SimpleRace runState: RE_STATE_EVENT_INIT\n");
	eventInit(rmInfo);
	return RM_SYNC | RM_NEXT_STEP;

    case RE_STATE_PRE_RACE:
	GfOut("SimpleRace runState: RE_STATE_PRE_RACE\n");
	preRace(rmInfo);
	return RM_SYNC | RM_NEXT_STEP;

    case RE_STATE_RACE_START:
	GfOut("SimpleRace runState: RE_STATE_RACE_START\n");
	return RM_SYNC | RM_NEXT_STEP;
	
    case RE_STATE_RACE:
	return RM_ASYNC /* | RM_END_RACE */;

    case RE_STATE_RACE_END:
	GfOut("SimpleRace runState: RE_STATE_RACE_END\n");
	if (rmInfo->s->_raceState != RM_RACE_ENDED) {
	    RmConfirmScreen("End Race ?",
			    "Yes", "Back to Main Menu", rmInfo->_reGameScreen,
			    "No", "Return to Race", SrBackToRaceHookInit(),
			    1);
	    return RM_ASYNC | RM_NEXT_STEP;	    
	}
	return RM_SYNC | RM_NEXT_STEP;

    case RE_STATE_POST_RACE:
	GfOut("SimpleRace runState: RE_STATE_POST_RACE\n");
	postRace(rmInfo);
	return RM_ASYNC | RM_NEXT_STEP /* | RM_NEXT_RACE */;

    case RE_STATE_EVENT_SHUTDOWN:
	GfOut("SimpleRace runState: RE_STATE_EVENT_SHUTDOWN\n");
	return RM_SYNC | RM_NEXT_STEP /* | RM_NEXT_EVENT */;

    default:
	return RM_SYNC | RM_NEXT_STEP;
    }
    rmInfo->_reState = RE_STATE_SHUTDOWN;
    return RM_SYNC;
}


static int
raceInit(int index, void *p)
{
    tRacemanItf *itf = (tRacemanItf*)p;
    
    itf->runState = runState;
    
    return 0;
}


/*
 * Function
 *	quickrace
 *
 * Description
 *	Entry point of the module
 *
 * Parameters
 *	pointer on info structure
 *
 * Return
 *	0 if ok
 *     -1 if error
 */
extern "C" int
simplerace(tModInfo *modInfo)
{
    modInfo->name  = "Simple Race";	/* name of the module (short) */
    modInfo->desc  = "Simple Race day event";	/* description of the module (can be long) */
    modInfo->fctInit = raceInit;	/* init function */
    modInfo->gfId  = 0;			/* always loaded  */
    modInfo->index = 0;
    modInfo->prio  = 20;		/* Second */
    modInfo->magic = RM_MAGIC;
    
    return 0;
}


