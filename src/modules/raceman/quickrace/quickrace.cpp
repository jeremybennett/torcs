/***************************************************************************

    file                 : quickrace.cpp
    created              : Sun Jan 30 22:42:04 CET 2000
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

#include "qracemain.h"

#ifdef _WIN32
BOOL WINAPI DllEntryPoint (HINSTANCE hDLL, DWORD dwReason, LPVOID Reserved)
{
    return TRUE;
}
#endif

tRmInfo *RmInfo;

/***************************************************************/
/* BACK TO RACE HOOK */

static void	*BackToRaceHookHandle = 0;

static void
BackToRaceHookActivate(void * /* dummy */)
{
    RmInfo->_reState = RE_STATE_RACE;
    GfuiScreenActivate(RmInfo->_reGameScreen);
}

static void *
qrBackToRaceHookInit(void)
{
    if (BackToRaceHookHandle) {
	return BackToRaceHookHandle;
    }

    BackToRaceHookHandle = GfuiHookCreate(0, BackToRaceHookActivate);

    return BackToRaceHookHandle;
}

void
qrBackToRaceHookShutdown(void)
{
    if (BackToRaceHookHandle) {
	GfuiHookRelease(BackToRaceHookHandle);
	BackToRaceHookHandle = 0;
    }
}

/* Run state from Race Engine */
static int
runState(tRmInfo *rmInfo)
{
    switch (rmInfo->_reState) {
    case RE_STATE_CONFIG:
	RmInfo = rmInfo;
	GfOut("QuickRace runState: RE_STATE_CONFIG\n");
	qrConfigInit();
	return RM_ASYNC | RM_NEXT_STEP;	/* Race engine will be called back later */

    case RE_STATE_EVENT_INIT:
	GfOut("QuickRace runState: RE_STATE_EVENT_INIT\n");
	return RM_SYNC | RM_NEXT_STEP;

    case RE_STATE_PRE_RACE:
	GfOut("QuickRace runState: RE_STATE_PRE_RACE\n");
	{
	    tdble	dist;

	    dist = GfParmGetNum(rmInfo->params, RM_SECT_RACE, RM_ATTR_DISTANCE, (char*)NULL, 0);
	    if (dist== 0.0) {
		rmInfo->s->_totLaps = (int)GfParmGetNum(rmInfo->params, RM_SECT_RACE, RM_ATTR_LAPS, (char*)NULL, 30);
	    } else {
		rmInfo->s->_totLaps = ((int)(dist / rmInfo->track->length)) + 1;
	    }
	    rmInfo->s->_raceType = RM_TYPE_RACE;
	    rmInfo->s->_maxDammage = (int)GfParmGetNum(rmInfo->params, RM_SECT_RACE, RM_ATTR_MAX_DMG, (char*)NULL, 10000);
	}
	return RM_SYNC | RM_NEXT_STEP;
	
    case RE_STATE_RACE:
	return RM_ASYNC /* | RM_END_RACE */;

    case RE_STATE_RACE_END:
	GfOut("QuickRace runState: RE_STATE_RACE_END\n");
	if (rmInfo->s->_raceState != RM_RACE_ENDED) {
	    RmConfirmScreen("End Race ?",
			    "Yes", "Back to Main Menu", rmInfo->_reGameScreen,
			    "No", "Return to Race", qrBackToRaceHookInit(),
			    1);
	    return RM_ASYNC | RM_NEXT_STEP;	    
	}
	return RM_SYNC | RM_NEXT_STEP;

    case RE_STATE_POST_RACE:
	GfOut("QuickRace runState: RE_STATE_POST_RACE\n");
	RmShowResults(rmInfo->_reGameScreen, rmInfo);
	return RM_ASYNC | RM_NEXT_STEP /* | RM_NEXT_RACE */;

    default:
	return RM_SYNC | RM_NEXT_STEP;
    }
    rmInfo->_reState = RE_STATE_SHUTDOWN;
    return RM_SYNC;
}


/*
 * Function
 *	qraceInit
 *
 * Description
 *	init the menus
 *
 * Parameters
 *	
 *
 * Return
 *	
 *
 * Remarks
 *	
 */
static int
qraceInit(int index, void *p)
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
quickrace(tModInfo *modInfo)
{
    modInfo->name = "Quick Race";	/* name of the module (short) */
    modInfo->desc = "Race Without practice nor qualification sessions";	/* description of the module (can be long) */
    modInfo->fctInit = qraceInit;	/* init function */
    modInfo->gfId = 0;			/* always loaded  */
    modInfo->index = 0;
    modInfo->prio = 10;			/* First */
    modInfo->magic = RM_MAGIC;
    
    return 0;
}


