/***************************************************************************

    file                 : pracegl.cpp
    created              : Sun Jan 30 22:40:58 CET 2000
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


#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include <graphic.h>
#include <telemetry.h>
#include <robot.h>
#include <tgf.h>

#include "practice.h"

static int BoardFl = 1;
static int FpsFl = 1;
static int RunFl = 0;

static void *prHandle;
static int prPauseId;

static void
prQuit(void *vflag)
{
    switch ((int)vflag) {
    case 0:
	exit(0);
	break;
    case 1:
	prShutdown();
	break;
    }
}

static void
prBoardInfo(void *vboard)
{
    RunFl = 1 - RunFl;
    if (RunFl) {
	prStart();
	GfuiVisiblilitySet(prHandle, prPauseId, 0);
    } else {
	prStop();
	GfuiVisiblilitySet(prHandle, prPauseId, 1);
    }
}

static void
prAddKeys(void)
{
    GfuiAddSKey(prHandle, GLUT_KEY_F1, "Help", prHandle, GfuiHelpScreen);

    GfuiAddKey(prHandle, 'p', "Pause Race",       (void*)0, prBoardInfo);
    GfuiAddKey(prHandle,  27, "End Current Race", (void*)1, prQuit);
    GfuiAddKey(prHandle, 'q', "Exit TORCS",       (void*)0, prQuit);
    GfuiAddSKey(prHandle, GLUT_KEY_F12, "Screen Shot", NULL, GfuiScreenShot);
}    


static void
prIdle(void)
{
    prGraphicItf.refresh(&prTheSituation);
    GfuiDisplay();
    prUpdate();
    glutPostRedisplay();
}

void
prActivate(void *dummy)
{
    if (prShowRace) {
	glutDisplayFunc(prIdle);
	glClearColor(prTheTrack->graphic.bgColor[0], prTheTrack->graphic.bgColor[1], prTheTrack->graphic.bgColor[2], 1.0);
	if (RunFl) {
	    prStart();
	}
    } else {
	RmLoadingScreenStart("Practice", "data/img/splash-qrloading.png");
	prUpdateBlind();
    }
}

void
praceglRun(void)
{
    RunFl = 0;
    BoardFl = 1;
    FpsFl = 1;
    static float bgcolor[4] = {0.0, 0.0, 0.0, 0.0};
    static float fgcolor2[4] = {1.0, 0.0, 0.0, 1.0};
    int sw, sh, vw, vh;

    prHandle = GfuiScreenCreateEx(bgcolor, NULL, prActivate, NULL, (tfuiCallback)NULL, 0);
    prAddKeys();

    prPauseId = GfuiLabelCreateEx(prHandle,
			       "P A U S E",
			       fgcolor2,
			       GFUI_FONT_BIG,
			       320,
			       400,
			       GFUI_ALIGN_HC_VB,
			       9);
    
    GfScrGetSize(&sw, &sh, &vw, &vh);
    prGraphicItf.initview((sw-vw)/2, (sh-vh)/2, vw, vh, GR_VIEW_STD, prHandle);

    prBoardInfo(0);

    GfuiScreenActivate(prHandle);
}

void
praceglShutdown(void)
{
    glutIdleFunc((void(*)(void))NULL);
    glutKeyboardFunc((void(*)(unsigned char,int,int))NULL);
    glutSpecialFunc((void(*)(int,int,int))NULL);
    glutDisplayFunc(GfuiDisplayNothing);
    GfuiScreenRelease(prHandle);
}
