/***************************************************************************

    file                 : qracegl.cpp
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
#include <string.h>
#include <GL/glut.h>

#include <graphic.h>
#include <telemetry.h>
#include <robot.h>
#include <tgf.h>
#include "qracemain.h"
#include "qracegl.h"

static int BoardFl = 1;
static int FpsFl = 1;
static int RunFl = 1;

void *qrHandle;
static int qrPauseId;

static void
qrQuit(void *vflag)
{
    switch ((int)vflag) {
    case 0:
	exit(0);
	break;
    case 1:
	qrShutdown();
	break;
    }
}

static void
qrBoardInfo(void *vboard)
{
    RunFl = 1 - RunFl;
    if (RunFl) {
	qrTheSituation._raceState &= ~RM_RACE_PAUSED;
	qrStart();
	GfuiVisiblilitySet(qrHandle, qrPauseId, 0);
    } else {
	qrTheSituation._raceState |= RM_RACE_PAUSED;
	qrStop();
	GfuiVisiblilitySet(qrHandle, qrPauseId, 1);
    }
}

static void
qrAddKeys(void)
{
    GfuiAddSKey(qrHandle, GLUT_KEY_F1,   "Help", qrHandle, GfuiHelpScreen);
    GfuiAddSKey(qrHandle, GLUT_KEY_PAGE_UP, "Select Previous Car", (void*)0, qrPrevCar);
    GfuiAddSKey(qrHandle, GLUT_KEY_PAGE_DOWN, "Select Next Car", (void*)0, qrNextCar);


    GfuiAddKey(qrHandle, 'p', "Pause Race", (void*)0, qrBoardInfo);
    GfuiAddKey(qrHandle, 27, "End Current Race", (void*)1, qrQuit);
    GfuiAddKey(qrHandle, 'q', "Exit of TORCS", (void*)0, qrQuit);
    GfuiAddKey(qrHandle, ' ', "One Step Debug", (void*)1, qrOneStep);
    GfuiAddSKey(qrHandle, GLUT_KEY_F12,   "Screen Shot", NULL, GfuiScreenShot);
    
}

static void
Idle(void)
{
    qrGraphicItf.refresh(&qrTheSituation);
    GfuiDisplay();
    qrUpdate();
    glutPostRedisplay();
}

void
qrActivate(void *dummy)
{
    //glutIdleFunc(Idle);
    glClearColor(qrTheTrack->graphic.bgColor[0], qrTheTrack->graphic.bgColor[1], qrTheTrack->graphic.bgColor[2], 1.0);
    glutDisplayFunc(Idle);
    if (RunFl) {
	qrStart(); /* resynchro */
    }
}

void
qraceglRun(void)
{
    RunFl = 0;
    BoardFl = 1;
    FpsFl = 1;
    static float bgcolor[4] = {0.0, 0.0, 0.0, 0.0};
    static float fgcolor2[4] = {1.0, 0.0, 0.0, 1.0};
    int sw, sh, vw, vh;
    
    qrTheSituation._raceState |= RM_RACE_PAUSED;
    qrHandle = GfuiScreenCreateEx(bgcolor, NULL, qrActivate, NULL, (tfuiCallback)NULL, 0);


    qrAddKeys();

/*     GfuiLabelCreate(qrHandle, */
/* 		 qrTheTrack->name, */
/* 		 GFUI_FONT_LARGE, */
/* 		 320, */
/* 		 440, */
/* 		 GFUI_ALIGN_HC_VB, */
/* 		 strlen(qrTheTrack->name)); */

    qrPauseId = GfuiLabelCreateEx(qrHandle,
			       "P A U S E",
			       fgcolor2,
			       GFUI_FONT_BIG,
			       320,
			       400,
			       GFUI_ALIGN_HC_VB,
			       0);
    GfScrGetSize(&sw, &sh, &vw, &vh);
    qrGraphicItf.initview((sw-vw)/2, (sh-vh)/2, vw, vh, GR_VIEW_STD, qrHandle);

    GfuiScreenActivate(qrHandle);
}

void
qrResults(void *prevHdle)
{
    int		i;
    tCarElt	*car;
    void	*hdle;
    int		x1, x2, x3, x4, x5, x6;
    int		dlap;
    int		y;
    char	buf[256];
    char	*s;
    static float	fgcolor[4] = {1.0, 0.0, 1.0, 1.0};
    
    hdle = GfuiScreenCreate();
    sprintf(buf, "Race Results");
    GfuiTitleCreate(hdle, buf, strlen(buf));
    sprintf(buf, "%s", qrTheTrack->name);
    GfuiLabelCreate(hdle, buf, GFUI_FONT_LARGE,
		    320, 420, GFUI_ALIGN_HC_VB, 0);
    GfuiScreenAddBgImg(hdle, "data/img/splash-result.png");
    
    x1 = 80;
    x2 = 110;
    x3 = 290;
    x4 = 380;
    x5 = 410;
    x6 = 470;
    
    y = 400;
    GfuiLabelCreateEx(hdle, "Rank", fgcolor, GFUI_FONT_LARGE_C, x1, y, GFUI_ALIGN_HC_VB, 0);
    GfuiLabelCreateEx(hdle, "Driver", fgcolor, GFUI_FONT_LARGE_C, x2+10, y, GFUI_ALIGN_HL_VB, 0);
    GfuiLabelCreateEx(hdle, "Total", fgcolor, GFUI_FONT_LARGE_C, x3, y, GFUI_ALIGN_HR_VB, 0);
    GfuiLabelCreateEx(hdle, "Best", fgcolor, GFUI_FONT_LARGE_C, x4, y, GFUI_ALIGN_HR_VB, 0);
    GfuiLabelCreateEx(hdle, "Laps", fgcolor, GFUI_FONT_LARGE_C, x5, y, GFUI_ALIGN_HC_VB, 0);
    GfuiLabelCreateEx(hdle, "Top Spd", fgcolor, GFUI_FONT_LARGE_C, x6, y, GFUI_ALIGN_HC_VB, 0);
    y -= 20;
    
    for (i = 0; i < qrTheSituation._ncars; i++) {
	car = qrTheSituation.cars[i];
	if (car->_laps > qrTheSituation._totLaps) car->_laps = qrTheSituation._totLaps + 1;

	sprintf(buf, "%d", i+1);
	GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C,
			x1, y, GFUI_ALIGN_HC_VB, 0);

	GfuiLabelCreate(hdle, car->_name, GFUI_FONT_MEDIUM_C,
			x2, y, GFUI_ALIGN_HL_VB, 0);

	if (car->_laps == qrTheSituation.cars[0]->_laps) {
	    if (i == 0) {
		s = GfTime2Str(car->_curTime, 0);
	    } else {
		s = GfTime2Str(car->_curTime - qrTheSituation.cars[0]->_curTime, 1);
	    }
	} else {
	    dlap = qrTheSituation.cars[0]->_laps - car->_laps;
	    if (dlap == 1) {
		sprintf(buf,"+1 Lap");
	    } else {
		sprintf(buf,"+%d Laps", qrTheSituation.cars[0]->_laps - car->_laps);
	    }
	    s = buf;
	}
	GfuiLabelCreate(hdle, s, GFUI_FONT_MEDIUM_C,
			x3, y, GFUI_ALIGN_HR_VB, 0);
	

	s = GfTime2Str(car->_bestLapTime, 0);
	GfuiLabelCreate(hdle, s, GFUI_FONT_MEDIUM_C,
			x4, y, GFUI_ALIGN_HR_VB, 0);

	sprintf(buf, "%d", car->_laps-1);
	GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C,
			x5, y, GFUI_ALIGN_HC_VB, 0);

	sprintf(buf, "%d", (int)(car->_topSpeed * 3.6));
	GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C,
			x6, y, GFUI_ALIGN_HC_VB, 0);
	y -= 15;
    }

    GfuiButtonCreate(hdle,
		  "Continue",
		  GFUI_FONT_LARGE,
		  320,
		  40,
		  GFUI_BTNSZ,
		  GFUI_ALIGN_HC_VB,
		  0,
		  prevHdle,
		  GfuiScreenActivate,
		  NULL,
		  (tfuiCallback)NULL,
		  (tfuiCallback)NULL);

    GfuiAddKey(hdle, (unsigned char)27, "", prevHdle, GfuiScreenActivate);
    GfuiAddKey(hdle, (unsigned char)13, "", prevHdle, GfuiScreenActivate);
    GfuiAddSKey(hdle, GLUT_KEY_F12, "Take a Screen Shot", NULL, GfuiScreenShot);

    GfuiScreenActivate(hdle);
}

void
qraceglShutdown(void)
{
    glutIdleFunc((void(*)(void))NULL);
    glutKeyboardFunc((void(*)(unsigned char,int,int))NULL);
    glutSpecialFunc((void(*)(int,int,int))NULL);
    glutDisplayFunc(GfuiDisplayNothing);
    if (qrHandle) {
	GfuiScreenRelease(qrHandle);
    }
}
