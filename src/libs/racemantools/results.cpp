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
}

int
RmInitResults(tRmInfo *rmInfo)
{
    int nblap = rmInfo->s->_totLaps + 1;
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
#ifndef WIN32
    int		*index;
    tCarElt	**cars;
    int		nb, i, max, ncars;
    char	buf[1024];
    FILE	*fout;
    FILE	*fcmd;
    char	*filename = "res";
    int		pos;

    GfOut("Saving Results\n");

    index = (int*)malloc(rmInfo->s->_ncars * sizeof(int *));
    cars = rmInfo->s->cars;

    ncars = max = rmInfo->s->_ncars;
    for (i = 0; i < max; i++) {
	index[cars[i]->_startRank] = i;
    }

    sprintf(buf, "results/%s.cmd", filename);
    fcmd = fopen(buf, "w");
    if (fcmd == NULL) {
	GfTrace("Error while openning %s\n", buf);
	return;
    }
    fprintf(fcmd, "#!/bin/sh\n");
    fprintf(fcmd, "gnuplot -persist > results/%s.png <<!!\n", filename);
    fprintf(fcmd, "#   set grid\n");
    fprintf(fcmd, "    set nokey\n");
    fprintf(fcmd, "    set title \"Race Positions Lap by Lap\"\n");
    fprintf(fcmd, "    set xlabel \"Laps\"\n");
    fprintf(fcmd, "    set ylabel \"Drivers\"\n");
    fprintf(fcmd, "    set y2label \"Positions\"\n");
    fprintf(fcmd, "    set yrange [* : *] reverse\n");
    fprintf(fcmd, "    set y2range [* : *] reverse\n");
    fprintf(fcmd, "    set size 2.5,1.5\n");
    fprintf(fcmd, "    set terminal png color\n");
    fprintf(fcmd, "    set data style lines\n");
    fprintf(fcmd, "    set xtics border 1\n");
    fprintf(fcmd, "    set y2tics border mirror 1\n");
    fprintf(fcmd, "    set ytics border (\"%s\" 1", cars[index[0]]->_name);
    for (i = 1; i < max; i++) {
	fprintf(fcmd, ", \"%s\" %d", cars[index[i]]->_name, i + 1);
    }
    fprintf(fcmd, ")\n");    

    fprintf(fcmd, "plot 'results/%s.dat' using 2", filename);
    for (i = 1; i < max; i++) {
	fprintf(fcmd, ", '' using %d", i + 2);
    }
    fprintf(fcmd, "\n");
    fprintf(fcmd, "!!\n");
    fclose(fcmd);
    
    sprintf(buf, "results/%s.dat", filename);
    fout = fopen(buf, "w");
    if (fout == NULL) {
	GfTrace("Error while openning %s\n", buf);
	return;
    }
    fprintf(fout, "0 ");
    for (i = 0; i < max; i++) {
	fprintf(fout, "%d ", cars[index[i]]->_startRank + 1);
    }
    fprintf(fout, "\n");
    for (nb = 0; nb < rmInfo->s->_totLaps + 1; nb++) {
	fprintf(fout, "%d ", nb + 1);
	for (i = 0; i < max; i++) {
	    pos = rmInfo->lapInfo[ncars * nb + i].pos;
	    if (pos == 0) {
		fprintf(fout, "- ");
	    } else {
		fprintf(fout, "%d ", pos);
	    }
	}
	fprintf(fout, "\n");
    }
    fclose(fout);
    sprintf(buf, "sh results/%s.cmd", filename);
    system(buf);

    free (index);
#endif
}
