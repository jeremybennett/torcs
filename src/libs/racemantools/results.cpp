/***************************************************************************

    file                 : results.cpp
    created              : Fri Apr 14 22:36:36 CEST 2000
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

/** @file
    		This is a set of tools useful for race managers to display results.
    @ingroup	racemantools
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
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
#include <racemantools.h>
#include <robottools.h>
#include <robot.h>


/** Display the Practice session results.
    @param	prevHdle	Handle to return to.
    @param	trackname	Current track.
    @param	res		Result list.
    @return	None.
 */
void
RmPracticeResults(void *prevHdle, char *trackname, tRingListHead *reshead)
{
    void	*hdle;
    int		x1, x2, x3, x4, x5, x6;
    int		y;
    char	buf[256];
    char	*s;
    static float	fgcolor[4] = {1.0, 0.0, 1.0, 1.0};
    tPractResults	*curRes;
    tdble	bestTopSpd = 0;
    tdble	bestMinSpd = 0;
    tdble	bestAvgSpd = 0;
    tdble	bestLapTime = 100000;
    tdble	bestfuel = 100000;
    
    hdle = GfuiScreenCreate();
    sprintf(buf, "Results");
    GfuiTitleCreate(hdle, buf, strlen(buf));
    GfuiLabelCreate(hdle, trackname, GFUI_FONT_LARGE,
		 320, 420, GFUI_ALIGN_HC_VB, 0);
    GfuiScreenAddBgImg(hdle, "data/img/splash-result.png");

    
    x1 = 5;
    x2 = x1 + 50;
    x3 = x2 + 100;
    x4 = x3 + 80;
    x5 = x4 + 80;
    x6 = x5 + 80;
    
    y = 400;
    GfuiLabelCreateEx(hdle, "Lap",     fgcolor, GFUI_FONT_LARGE_C, x1, y, GFUI_ALIGN_HL_VB, 0);
    GfuiLabelCreateEx(hdle, "Time",    fgcolor, GFUI_FONT_LARGE_C, x2, y, GFUI_ALIGN_HL_VB, 0);
    GfuiLabelCreateEx(hdle, "Top Spd", fgcolor, GFUI_FONT_LARGE_C, x3, y, GFUI_ALIGN_HL_VB, 0);
    GfuiLabelCreateEx(hdle, "Min Spd", fgcolor, GFUI_FONT_LARGE_C, x4, y, GFUI_ALIGN_HL_VB, 0);
    GfuiLabelCreateEx(hdle, "Avg Spd", fgcolor, GFUI_FONT_LARGE_C, x5, y, GFUI_ALIGN_HL_VB, 0);
    GfuiLabelCreateEx(hdle, "Fuel",    fgcolor, GFUI_FONT_LARGE_C, x6, y, GFUI_ALIGN_HL_VB, 0);
    y -= 20;

    curRes = (tPractResults*)GfRlstGetFirst(reshead);
    if (curRes != NULL) {
	do {
	    if (bestTopSpd < curRes->topSpeed) bestTopSpd = curRes->topSpeed;
	    if (bestMinSpd < curRes->bottomSpeed) bestMinSpd = curRes->bottomSpeed;
	    if (bestAvgSpd < curRes->speedAvg) bestAvgSpd = curRes->speedAvg;
	    if (bestLapTime > curRes->lapTime) bestLapTime = curRes->lapTime;
	    if (bestfuel > curRes->fuel) bestfuel = curRes->fuel;
	    curRes = (tPractResults*)GfRlstGetNext(reshead, (tRingList*)curRes);
	} while (curRes != NULL);

	curRes = (tPractResults*)GfRlstGetFirst(reshead);
	do {
	    
	    sprintf(buf, "%d", curRes->lap);
	    GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x1, y, GFUI_ALIGN_HL_VB, 0);
	    s = GfTime2Str(curRes->lapTime, 0);
	    if (curRes->lapTime == bestLapTime) {
		GfuiLabelCreateEx(hdle, s, fgcolor, GFUI_FONT_MEDIUM_C, x2, y, GFUI_ALIGN_HL_VB, 0);
	    } else {
		GfuiLabelCreate(hdle, s, GFUI_FONT_MEDIUM_C, x2, y, GFUI_ALIGN_HL_VB, 0);
	    }
	    sprintf(buf, "%.2f", curRes->topSpeed * 3.6);
	    if (curRes->topSpeed == bestTopSpd) {
		GfuiLabelCreateEx(hdle, buf, fgcolor, GFUI_FONT_MEDIUM_C, x3, y, GFUI_ALIGN_HL_VB, 0);
	    } else {
		GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x3, y, GFUI_ALIGN_HL_VB, 0);
	    }
	    sprintf(buf, "%.2f", curRes->bottomSpeed * 3.6);
	    if (curRes->bottomSpeed == bestMinSpd) {
		GfuiLabelCreateEx(hdle, buf, fgcolor, GFUI_FONT_MEDIUM_C, x4, y, GFUI_ALIGN_HL_VB, 0);
	    } else {
		GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x4, y, GFUI_ALIGN_HL_VB, 0);
	    }
	    sprintf(buf, "%.2f", curRes->speedAvg * 3.6);
	    if (curRes->speedAvg == bestAvgSpd) {
		GfuiLabelCreateEx(hdle, buf, fgcolor, GFUI_FONT_MEDIUM_C, x5, y, GFUI_ALIGN_HL_VB, 0);
	    } else {
		GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x5, y, GFUI_ALIGN_HL_VB, 0);
	    }
	    sprintf(buf, "%.2f", curRes->fuel);
	    if (curRes->fuel == bestfuel) {
		GfuiLabelCreateEx(hdle, buf, fgcolor, GFUI_FONT_MEDIUM_C, x6, y, GFUI_ALIGN_HL_VB, 0);
	    } else {
		GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x6, y, GFUI_ALIGN_HL_VB, 0);
	    }
	    y -= 15;

	    curRes = (tPractResults*)GfRlstGetNext(reshead, (tRingList*)curRes);
	} while (curRes != NULL);
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

int
RmInitResults(tRmInfo *rmInfo)
{
    int nblap = rmInfo->s->_totLaps;
    int nbdrv = rmInfo->s->_ncars;

    rmInfo->lapInfo = (tDrvLapInfo*)calloc(nbdrv * nblap, sizeof(tDrvLapInfo));
    if (rmInfo->lapInfo == NULL) {
	return -1;
    }

    return 0;
}

void
RmShutdownResults(tRmInfo *rmInfo)
{
    if (rmInfo->lapInfo) {
	free(rmInfo->lapInfo);
	rmInfo->lapInfo = NULL;
    }
}


void
RmSaveResults(tRmInfo *rmInfo)
{
    char	buf[256];
    int		*index;
    tCarElt	**cars;
    int i;

    index = (int*)malloc(rmInfo->s->_ncars);
    cars = rmInfo->s->cars;

    for (i = 0; i < rmInfo->s->_ncars; i++) {
	index[cars[i]->_startRank] = i;
    }
    
    
}
