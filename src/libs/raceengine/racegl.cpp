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

static float bgcolor[4] = {0.0, 0.0, 0.0, 0.0};
static float red[4] = {1.0, 0.0, 0.0, 1.0};
static float white[4] = {1.0, 1.0, 1.0, 1.0};

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
    glutPostRedisplay();
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
    GfuiAddSKey(reScreenHandle, GLUT_KEY_F1,        "Help", reScreenHandle, GfuiHelpScreen);
    GfuiAddSKey(reScreenHandle, GLUT_KEY_PAGE_UP,   "Select Previous Car", (void*)0, RePrevCar);
    GfuiAddSKey(reScreenHandle, GLUT_KEY_PAGE_DOWN, "Select Next Car", (void*)0, ReNextCar);
    GfuiAddSKey(reScreenHandle, GLUT_KEY_F12,       "Screen Shot", NULL, GfuiScreenShot);


    GfuiAddKey(reScreenHandle, '-', "Slow Time",         (void*)0, ReTimeMod);
    GfuiAddKey(reScreenHandle, '+', "Accelerate Time",   (void*)1, ReTimeMod);
    GfuiAddKey(reScreenHandle, '.', "Real Time",         (void*)2, ReTimeMod);
    GfuiAddKey(reScreenHandle, 'p', "Pause Race",        (void*)0, ReBoardInfo);
    GfuiAddKey(reScreenHandle, 27,  "Stop Current Race", (void*)RE_STATE_RACE_STOP, ReStateApply);
    GfuiAddKey(reScreenHandle, 'q', "Exit of TORCS",     (void*)RE_STATE_EXIT, ReStateApply);
    GfuiAddKey(reScreenHandle, ' ', "Skip Pre Start",    (void*)0, reSkipPreStart);
    
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
    
    ReScreenShutdown();

    reScreenHandle = GfuiScreenCreateEx(bgcolor, 0, reScreenActivate, 0, 0, 0);

    reAddKeys();

    reMsgId = GfuiLabelCreateEx(reScreenHandle,
				"",
				red,
				GFUI_FONT_MEDIUM,
				320,
				440,
				GFUI_ALIGN_HC_VB,
				32);

    rePauseId = GfuiLabelCreateEx(reScreenHandle,
				  "P A U S E",
				  red,
				  GFUI_FONT_BIG,
				  320,
				  400,
				  GFUI_ALIGN_HC_VB,
				  0);

    reBigMsgId = GfuiLabelCreateEx(reScreenHandle,
				   "",
				   red,
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

/**************************************************************************/

/*
 * Result only screen
 */
#define LINES	21

static void	*reResScreenHdle = 0;
static int	reResTitleId;
static int	reResMsgId[LINES];
static char	*reResMsg[LINES];
static int	reCurLine;

static void
reAddResKeys(void)
{
    GfuiAddSKey(reResScreenHdle, GLUT_KEY_F1,  "Help", reScreenHandle, GfuiHelpScreen);
    GfuiAddSKey(reResScreenHdle, GLUT_KEY_F12, "Screen Shot", NULL, GfuiScreenShot);

    GfuiAddKey(reResScreenHdle, 27,  "Stop Current Race", (void*)RE_STATE_RACE_STOP, ReStateApply);
    GfuiAddKey(reResScreenHdle, 'q', "Exit of TORCS",     (void*)RE_STATE_EXIT, ReStateApply);
}

static void
reResScreenActivate(void * /* dummy */)
{
    glutDisplayFunc(reDisplay);
    GfuiDisplay();
    glutPostRedisplay();
}


static void
reContDisplay(void)
{
    GfuiDisplay();
    glutPostRedisplay();
}


static void
reResCont(void * /* dummy */)
{
    ReStateManage();
}

static void
reResScreenShutdown(void * /* dummy */)
{
    int		i;

    for (i = 1; i < LINES; i++) {
	FREEZ(reResMsg[i]);
    }
}

void *
ReResScreenInit(void)
{
    int		i;
    int		y, dy;
    char	*img;
    static char	*title[3] = {"Practice", "Qualifications", "Race"};

    if (reResScreenHdle) {
	GfuiScreenRelease(reResScreenHdle);
	reResScreenHdle = 0;
    }

    reResScreenHdle = GfuiScreenCreateEx(bgcolor, 0, reResScreenActivate, 0, reResScreenShutdown, 0);

    GfuiTitleCreate(reResScreenHdle, title[ReInfo->s->_raceType], strlen(title[ReInfo->s->_raceType]));

    img = GfParmGetStr(ReInfo->params, RM_SECT_HEADER, RM_ATTR_RUNIMG, 0);
    if (img) {
	GfuiScreenAddBgImg(reResScreenHdle, img);
    }
    
    reAddResKeys();

    reResTitleId = GfuiLabelCreateEx(reResScreenHdle,
				     "",
				     red,
				     GFUI_FONT_MEDIUM,
				     320, 420,
				     GFUI_ALIGN_HC_VB, 32);

    y = 400;
    dy = 378 / LINES;
    for (i = 0; i < LINES; i++) {
	FREEZ(reResMsg[i]);
	reResMsgId[i] = GfuiLabelCreateEx(reResScreenHdle,
					  "",
					  white,
					  GFUI_FONT_MEDIUM_C,
					  20, y, 
					  GFUI_ALIGN_HL_VB, 100);
	y -= dy;
    }

    reCurLine = 0;
    return reResScreenHdle;
}

void
ReResScreenSetTitle(char *title)
{
    if (reResScreenHdle) {
	GfuiLabelSetText(reResScreenHdle, reResTitleId, title);
    }
}

void
ReResScreenAddText(char *text)
{
    int		i;

    if (reCurLine == LINES) {
	free(reResMsg[0]);
	for (i = 1; i < LINES; i++) {
	    reResMsg[i - 1] = reResMsg[i];
	    GfuiLabelSetText(reResScreenHdle, reResMsgId[i - 1], reResMsg[i]);
	}
	reCurLine--;
    }
    reResMsg[reCurLine] = strdup(text);
    GfuiLabelSetText(reResScreenHdle, reResMsgId[reCurLine], reResMsg[reCurLine]);
    reCurLine++;
}

void
ReResScreenSetText(char *text, int line)
{
    if (line < LINES) {
	FREEZ(reResMsg[line]);
	reResMsg[line] = strdup(text);
	GfuiLabelSetText(reResScreenHdle, reResMsgId[line], reResMsg[line]);
    }
}


void
ReResScreenRemoveText(int line)
{
    if (line < LINES) {
	FREEZ(reResMsg[line]);
	GfuiLabelSetText(reResScreenHdle, reResMsgId[line], "");
    }
}

void
ReResShowCont(void)
{

    GfuiButtonCreate(reResScreenHdle,
		     "Continue",
		     GFUI_FONT_LARGE,
		     320, 15, GFUI_BTNSZ,
		     GFUI_ALIGN_HC_VB,
		     0, 0, reResCont,
		     NULL, (tfuiCallback)NULL,
		     (tfuiCallback)NULL);
    GfuiAddKey(reResScreenHdle, 13,  "Continue", 0, reResCont);
    GfuiAddKey(reResScreenHdle, 27,  "Continue", 0, reResCont);

    glutDisplayFunc(reContDisplay);
    glutPostRedisplay();
}
