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

static int	rmSaveId;
static void	*rmScrHdle = NULL;

/** Display the Practice session results.
    @param	prevHdle	Handle to return to.
    @param	trackname	Current track.
    @param	reshead		Result list.
    @return	None.
    @ingroup	racemantools
 */
void
RmPracticeResults(void *prevHdle, char *trackname, tRingListHead *reshead)
{
#if 0
    void	*hdle;
    int		x1, x2, x3, x4, x5, x6;
    int		y;
    char	buf[256];
    char	*s;
    static float	fgcolor[4] = {1.0, 0.0, 1.0, 1.0};
    tPractResults	*curRes;
    int		laps = 0;
    tdble	bestTopSpd = 0;
    tdble	avgTopSpd = 0;
    tdble	bestMinSpd = 0;
    tdble	avgMinSpd = 0;
    tdble	bestAvgSpd = 0;
    tdble	avgAvgSpd = 0;
    double	bestLapTime = 100000;
    double	totalTime = 0;
    tdble	bestfuel = 100000;
    tdble	totalFuel = 0;
    
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
	    laps++;
	    sprintf(buf, "%d", curRes->lap);
	    GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x1, y, GFUI_ALIGN_HL_VB, 0);
	    s = GfTime2Str(curRes->lapTime, 0);
	    totalTime += curRes->lapTime;
	    if (curRes->lapTime == bestLapTime) {
		GfuiLabelCreateEx(hdle, s, fgcolor, GFUI_FONT_MEDIUM_C, x2, y, GFUI_ALIGN_HL_VB, 0);
	    } else {
		GfuiLabelCreate(hdle, s, GFUI_FONT_MEDIUM_C, x2, y, GFUI_ALIGN_HL_VB, 0);
	    }
	    sprintf(buf, "%.2f", curRes->topSpeed * 3.6);
	    avgTopSpd += curRes->topSpeed;
	    if (curRes->topSpeed == bestTopSpd) {
		GfuiLabelCreateEx(hdle, buf, fgcolor, GFUI_FONT_MEDIUM_C, x3, y, GFUI_ALIGN_HL_VB, 0);
	    } else {
		GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x3, y, GFUI_ALIGN_HL_VB, 0);
	    }
	    sprintf(buf, "%.2f", curRes->bottomSpeed * 3.6);
	    avgMinSpd += curRes->bottomSpeed;
	    if (curRes->bottomSpeed == bestMinSpd) {
		GfuiLabelCreateEx(hdle, buf, fgcolor, GFUI_FONT_MEDIUM_C, x4, y, GFUI_ALIGN_HL_VB, 0);
	    } else {
		GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x4, y, GFUI_ALIGN_HL_VB, 0);
	    }
	    sprintf(buf, "%.2f", curRes->speedAvg * 3.6);
	    avgAvgSpd += curRes->speedAvg;
	    if (curRes->speedAvg == bestAvgSpd) {
		GfuiLabelCreateEx(hdle, buf, fgcolor, GFUI_FONT_MEDIUM_C, x5, y, GFUI_ALIGN_HL_VB, 0);
	    } else {
		GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x5, y, GFUI_ALIGN_HL_VB, 0);
	    }
	    sprintf(buf, "%.2f", curRes->fuel);
	    totalFuel += curRes->fuel;
	    if (curRes->fuel == bestfuel) {
		GfuiLabelCreateEx(hdle, buf, fgcolor, GFUI_FONT_MEDIUM_C, x6, y, GFUI_ALIGN_HL_VB, 0);
	    } else {
		GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x6, y, GFUI_ALIGN_HL_VB, 0);
	    }
	    y -= 15;

	    curRes = (tPractResults*)GfRlstGetNext(reshead, (tRingList*)curRes);
	} while (curRes != NULL);
	y -= 5;
	GfuiLabelCreate(hdle, "Total:", GFUI_FONT_MEDIUM_C, x1, y, GFUI_ALIGN_HL_VB, 0);
	s = GfTime2Str(totalTime, 0);
	GfuiLabelCreate(hdle, s, GFUI_FONT_MEDIUM_C, x2, y, GFUI_ALIGN_HL_VB, 0);
	sprintf(buf, "%.2f", avgTopSpd / (tdble)laps * 3.6);
	GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x3, y, GFUI_ALIGN_HL_VB, 0);
	sprintf(buf, "%.2f", avgMinSpd / (tdble)laps * 3.6);
	GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x4, y, GFUI_ALIGN_HL_VB, 0);
	sprintf(buf, "%.2f", avgAvgSpd / (tdble)laps * 3.6);
	GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x5, y, GFUI_ALIGN_HL_VB, 0);
	sprintf(buf, "%.2f", totalFuel);
	GfuiLabelCreate(hdle, buf, GFUI_FONT_MEDIUM_C, x6, y, GFUI_ALIGN_HL_VB, 0);
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
		     GfuiScreenReplace,
		     NULL,
		     (tfuiCallback)NULL,
		     (tfuiCallback)NULL);

    GfuiAddKey(hdle, (unsigned char)27, "", prevHdle, GfuiScreenReplace);
    GfuiAddKey(hdle, (unsigned char)13, "", prevHdle, GfuiScreenReplace);
    GfuiAddSKey(hdle, GLUT_KEY_F12, "Take a Screen Shot", NULL, GfuiScreenShot);

    GfuiScreenActivate(hdle);
#endif
}

void
rmSaveRes(void *vInfo)
{
    tRmInfo *info = (tRmInfo *)vInfo;

    GfParmWriteFile(0, info->results, "Results", GFPARM_PARAMETER, "../config/params.dtd");

    GfuiVisiblilitySet(rmScrHdle, rmSaveId, GFUI_INVISIBLE);
}


/* Not more that 21 cars... */
void
RmShowResults(void *prevHdle, tRmInfo *info, char *race)
{
    void		*results = info->results;
    int			i;
    int			x1, x2, x3, x4, x5, x6, x7, x8;
    int			dlap;
    int			y;
    static char		buf[256];
    static char		path[1024];
    char		*str;
    static float	fgcolor[4] = {1.0, 0.0, 1.0, 1.0};
    int			laps, totLaps;
    tdble		refTime;
    int			nbCars;
    
    rmScrHdle = GfuiScreenCreate();
    sprintf(buf, "Race Results");
    GfuiTitleCreate(rmScrHdle, buf, strlen(buf));
    sprintf(buf, "%s", info->track->name);
    GfuiLabelCreate(rmScrHdle, buf, GFUI_FONT_LARGE,
		    320, 420, GFUI_ALIGN_HC_VB, 0);
    GfuiScreenAddBgImg(rmScrHdle, "data/img/splash-result.png");
    
    x1 = 30;
    x2 = 60;
    x3 = 240;
    x4 = 330;
    x5 = 360;
    x6 = 420;
    x7 = 510;
    x8 = 595;
    
    y = 400;
    GfuiLabelCreateEx(rmScrHdle, "Rank",      fgcolor, GFUI_FONT_LARGE_C, x1, y, GFUI_ALIGN_HC_VB, 0);
    GfuiLabelCreateEx(rmScrHdle, "Driver",    fgcolor, GFUI_FONT_LARGE_C, x2+10, y, GFUI_ALIGN_HL_VB, 0);
    GfuiLabelCreateEx(rmScrHdle, "Total",     fgcolor, GFUI_FONT_LARGE_C, x3, y, GFUI_ALIGN_HR_VB, 0);
    GfuiLabelCreateEx(rmScrHdle, "Best",      fgcolor, GFUI_FONT_LARGE_C, x4, y, GFUI_ALIGN_HR_VB, 0);
    GfuiLabelCreateEx(rmScrHdle, "Laps",      fgcolor, GFUI_FONT_LARGE_C, x5, y, GFUI_ALIGN_HC_VB, 0);
    GfuiLabelCreateEx(rmScrHdle, "Top Spd",   fgcolor, GFUI_FONT_LARGE_C, x6, y, GFUI_ALIGN_HC_VB, 0);
    GfuiLabelCreateEx(rmScrHdle, "Dammages",  fgcolor, GFUI_FONT_LARGE_C, x7, y, GFUI_ALIGN_HC_VB, 0);
    GfuiLabelCreateEx(rmScrHdle, "Pit Stops", fgcolor, GFUI_FONT_LARGE_C, x8, y, GFUI_ALIGN_HC_VB, 0);
    y -= 20;
    
    sprintf(path, "%s/%s", RE_SECT_RESULTS, race);
    totLaps = (int)GfParmGetNum(results, path, RE_ATTR_LAPS, NULL, 0);
    sprintf(path, "%s/%s/%s/%d", RE_SECT_RESULTS, race, RE_SECT_RANK, 1);
    refTime = GfParmGetNum(results, path, RE_ATTR_TIME, NULL, 0);
    sprintf(path, "%s/%s/%s", RE_SECT_RESULTS, race, RE_SECT_RANK);
    nbCars = (int)GfParmGetEltNb(results, path);
    for (i = 0; i < nbCars; i++) {
	sprintf(path, "%s/%s/%s/%d", RE_SECT_RESULTS, race, RE_SECT_RANK, i + 1);
	laps = (int)GfParmGetNum(results, path, RE_ATTR_LAPS, NULL, 0);

	sprintf(buf, "%d", i+1);
	GfuiLabelCreate(rmScrHdle, buf, GFUI_FONT_MEDIUM_C,
			x1, y, GFUI_ALIGN_HC_VB, 0);

	GfuiLabelCreate(rmScrHdle, GfParmGetStr(results, path, RE_ATTR_NAME, ""), GFUI_FONT_MEDIUM_C,
			x2, y, GFUI_ALIGN_HL_VB, 0);

	if (laps == totLaps) {
	    if (i == 0) {
		str = GfTime2Str(GfParmGetNum(results, path, RE_ATTR_TIME, NULL, 0), 0);
	    } else {
		str = GfTime2Str(GfParmGetNum(results, path, RE_ATTR_TIME, NULL, 0) - refTime, 1);
	    }
	} else {
	    dlap = totLaps - laps;
	    if (dlap == 1) {
		sprintf(buf,"+1 Lap");
	    } else {
		sprintf(buf,"+%d Laps", dlap);
	    }
	    str = buf;
	}
	GfuiLabelCreate(rmScrHdle, str, GFUI_FONT_MEDIUM_C,
			x3, y, GFUI_ALIGN_HR_VB, 0);
	

	str = GfTime2Str(GfParmGetNum(results, path, RE_ATTR_BEST_LAP_TIME, NULL, 0), 0);
	GfuiLabelCreate(rmScrHdle, str, GFUI_FONT_MEDIUM_C,
			x4, y, GFUI_ALIGN_HR_VB, 0);

	sprintf(buf, "%d", laps);
	GfuiLabelCreate(rmScrHdle, buf, GFUI_FONT_MEDIUM_C,
			x5, y, GFUI_ALIGN_HC_VB, 0);

	sprintf(buf, "%d", (int)(GfParmGetNum(results, path, RE_ATTR_TOP_SPEED, NULL, 0) * 3.6));
	GfuiLabelCreate(rmScrHdle, buf, GFUI_FONT_MEDIUM_C,
			x6, y, GFUI_ALIGN_HC_VB, 0);

	sprintf(buf, "%d", (int)(GfParmGetNum(results, path, RE_ATTR_DAMMAGES, NULL, 0)));
	GfuiLabelCreate(rmScrHdle, buf, GFUI_FONT_MEDIUM_C,
			x7, y, GFUI_ALIGN_HC_VB, 0);

	sprintf(buf, "%d", (int)(GfParmGetNum(results, path, RE_ATTR_NB_PIT_STOPS, NULL, 0)));
	GfuiLabelCreate(rmScrHdle, buf, GFUI_FONT_MEDIUM_C,
			x8, y, GFUI_ALIGN_HC_VB, 0);
	y -= 15;
    }

    GfuiButtonCreate(rmScrHdle,
		     "Continue",
		     GFUI_FONT_LARGE,
		     210,
		     40,
		     150,
		     GFUI_ALIGN_HC_VB,
		     0,
		     prevHdle,
		     GfuiScreenReplace,
		     NULL,
		     (tfuiCallback)NULL,
		     (tfuiCallback)NULL);

    rmSaveId = GfuiButtonCreate(rmScrHdle,
				"Save",
				GFUI_FONT_LARGE,
				430,
				40,
				150,
				GFUI_ALIGN_HC_VB,
				0,
				info,
				rmSaveRes,
				NULL,
				(tfuiCallback)NULL,
				(tfuiCallback)NULL);

    GfuiAddKey(rmScrHdle, (unsigned char)27, "", prevHdle, GfuiScreenReplace);
    GfuiAddKey(rmScrHdle, (unsigned char)13, "", prevHdle, GfuiScreenReplace);
    GfuiAddSKey(rmScrHdle, GLUT_KEY_F12, "Take a Screen Shot", NULL, GfuiScreenShot);

    GfuiScreenActivate(rmScrHdle);
}

