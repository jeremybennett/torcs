/***************************************************************************

    file        : racegl.cpp
    created     : Sat Nov 16 18:22:00 CET 2002
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

#include "racemain.h"
#include "raceinit.h"
#include "racestate.h"
#include "raceengine.h"

#include "racegl.h"

static void	*reScreenHandle = 0;
static void	*reHookHandle = 0;
static int	rePauseId;
static int	reMsgId;
static int	reBigMsgId;

static void
reDisplay(void)
{
    ReStateManage();
}

static void
reScreenActivate(void * /* dummy */)
{
    glutDisplayFunc(reDisplay);

    if ((ReInfo->s->_raceState & RM_RACE_PAUSED) == 0) {
	ReStart(); 			/* resynchro */
    }
    glutPostRedisplay();	/* Ensure that 100% of the CPU is used ;-) */
}

static void
ReBoardInfo(void *vboard)
{
    if (ReInfo->s->_raceState & RM_RACE_PAUSED) {
	ReInfo->s->_raceState &= ~RM_RACE_PAUSED;
	ReStart();
	GfuiVisiblilitySet(reScreenHandle, rePauseId, 0);
    } else {
	ReInfo->s->_raceState |= RM_RACE_PAUSED;
	ReStop();
	GfuiVisiblilitySet(reScreenHandle, rePauseId, 1);
    }
}

static void
reSkipPreStart(void * /* dummy */)
{
    if (ReInfo->s->currentTime < 0) {
	ReInfo->s->currentTime = - RCM_MAX_DT_SIMU;
	ReInfo->_reLastTime = 0;
    }
}


static void
reAddKeys(void)
{
    GfuiAddSKey(reScreenHandle, GLUT_KEY_F1,   "Help", reScreenHandle, GfuiHelpScreen);
    GfuiAddSKey(reScreenHandle, GLUT_KEY_PAGE_UP, "Select Previous Car", (void*)0, RePrevCar);
    GfuiAddSKey(reScreenHandle, GLUT_KEY_PAGE_DOWN, "Select Next Car", (void*)0, ReNextCar);


    GfuiAddKey(reScreenHandle, '-', "Slow Time",       (void*)0, ReTimeMod);
    GfuiAddKey(reScreenHandle, '+', "Accelerate Time", (void*)1, ReTimeMod);
    GfuiAddKey(reScreenHandle, '.', "Real Time",       (void*)2, ReTimeMod);
    GfuiAddKey(reScreenHandle, 'p', "Pause Race",      (void*)0, ReBoardInfo);
    GfuiAddKey(reScreenHandle, 27, "Stop Current Race", (void*)RE_STATE_RACE_STOP, ReStateApply);
    GfuiAddKey(reScreenHandle, 'q', "Exit of TORCS",   (void*)RE_STATE_EXIT, ReStateApply);
    GfuiAddKey(reScreenHandle, ' ', "One Step Debug",  (void*)0, reSkipPreStart);
    GfuiAddSKey(reScreenHandle, GLUT_KEY_F12,   "Screen Shot", NULL, GfuiScreenShot);
    
}


void
ReSetRaceMsg(char *msg)
{
    static char *curMsg = 0;
    
    if (curMsg) free(curMsg);
    if (msg) {
	curMsg = strdup(msg);
	GfuiLabelSetText(reScreenHandle, reMsgId, curMsg);
    } else {
	curMsg = 0;
	GfuiLabelSetText(reScreenHandle, reMsgId, "");
    }
}

void
ReSetRaceBigMsg(char *msg)
{
    static char *curMsg = 0;
    
    if (curMsg) free(curMsg);
    if (msg) {
	curMsg = strdup(msg);
	GfuiLabelSetText(reScreenHandle, reBigMsgId, curMsg);
    } else {
	curMsg = 0;
	GfuiLabelSetText(reScreenHandle, reBigMsgId, "");
    }
}

void *
ReScreenInit(void)
{
    static float bgcolor[4] = {0.0, 0.0, 0.0, 0.0};
    static float fgcolor2[4] = {1.0, 0.0, 0.0, 1.0};
    
    ReScreenShutdown();

    reScreenHandle = GfuiScreenCreateEx(bgcolor, 0, reScreenActivate, 0, 0, 0);

    reAddKeys();

    reMsgId = GfuiLabelCreateEx(reScreenHandle,
				"",
				fgcolor2,
				GFUI_FONT_MEDIUM,
				320,
				440,
				GFUI_ALIGN_HC_VB,
				32);

    rePauseId = GfuiLabelCreateEx(reScreenHandle,
				  "P A U S E",
				  fgcolor2,
				  GFUI_FONT_BIG,
				  320,
				  400,
				  GFUI_ALIGN_HC_VB,
				  0);

    reBigMsgId = GfuiLabelCreateEx(reScreenHandle,
				   "",
				   fgcolor2,
				   GFUI_FONT_BIG,
				   320,
				   360,
				   GFUI_ALIGN_HC_VB,
				   32);

    GfuiVisiblilitySet(reScreenHandle, rePauseId, 0);

    return reScreenHandle;
}


void
ReScreenShutdown(void)
{
    if (reScreenHandle) {
	GfuiScreenRelease(reScreenHandle);
	reScreenHandle = 0;
    }
}


static void
reHookActivate(void * /* dummy */)
{
    ReStateManage();
}

void *
ReHookInit(void)
{
    if (reHookHandle) {
	return reHookHandle;
    }
    
    reHookHandle = GfuiHookCreate(0, reHookActivate);

    return reHookHandle;
}


void
ReHookShutdown(void)
{
    if (reHookHandle) {
	GfuiHookRelease(reHookHandle);
	reHookHandle = 0;
    }
}
