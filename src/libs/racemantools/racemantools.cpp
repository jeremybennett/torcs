/***************************************************************************
                       racemantools.cpp -- Tools for race managers                               
                             -------------------                                         
    created              : Mon Aug 16 21:47:17 CEST 1999
    copyright            : (C) 1999 by Eric Espie                         
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
    		This is a set of tools useful for race managers.
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

#ifdef DMALLOC
#include "dmalloc.h"
#endif

static void initStartingGrid(tRmInfo *raceInfo);
static void initPits(tRmInfo *raceInfo);

/** Dump the track segments on screen
    @param	track	track to dump
    @param	verbose	if set to 1 all the segments are described (long)
 */
void
RmDumpTrack(tTrack *track, int verbose)
{
    char	buf[256];
    int		i;
    tTrackSeg	*seg;
#ifdef DEBUG
    char	*stype[4] = { "", "RGT", "LFT", "STR" }; 
#endif

    RmLoadingScreenSetText("Loading Track Geometry...");
    sprintf(buf, ">>> Track Name    %s", track->name);
    RmLoadingScreenSetText(buf);
    sprintf(buf, ">>> Track Length  %.2f m", track->length);
    RmLoadingScreenSetText(buf);
    sprintf(buf, ">>> Track Width   %.2f m", track->width);
    RmLoadingScreenSetText(buf);

    GfOut("++++++++++++ Track ++++++++++++\n");
    GfOut("name     = %s\n", track->name);
    GfOut("author   = %s\n", track->author);
    GfOut("filename = %s\n", track->filename);
    GfOut("nseg     = %d\n", track->nseg);
    GfOut("version  = %d\n", track->version);
    GfOut("length   = %f\n", track->length);
    GfOut("width    = %f\n", track->width);
    GfOut("XSize    = %f\n", track->max.x);
    GfOut("YSize    = %f\n", track->max.y);
    GfOut("ZSize    = %f\n", track->max.z);
    switch (track->pits.type) {
    case TR_PIT_NONE:
	GfOut("Pits     = none\n");
	break;
    case TR_PIT_ON_TRACK_SIDE:
	GfOut("Pits     = present on track side\n");
	break;
    case TR_PIT_ON_SEPARATE_PATH:
	GfOut("Pits     = present on separate path\n");
	break;
    }
    if (verbose) {
	for (i = 0, seg = track->seg->next; i < track->nseg; i++, seg = seg->next) {
	    GfOut("	segment %d -------------- \n", seg->id);
#ifdef DEBUG
	    GfOut("        type    %s\n", stype[seg->type]);
#endif
	    GfOut("        length  %f\n", seg->length);
	    GfOut("	radius  %f\n", seg->radius);
	    GfOut("	arc	%f   Zs %f   Ze %f   Zcs %f\n", RAD2DEG(seg->arc), 
		   RAD2DEG(seg->angle[TR_ZS]), 
		   RAD2DEG(seg->angle[TR_ZE]), 
		   RAD2DEG(seg->angle[TR_CS]));
	    GfOut("	Za	%f\n", RAD2DEG(seg->angle[TR_ZS]));
	    GfOut("	vertices: %-8.8f %-8.8f %-8.8f ++++ ",
		   seg->vertex[TR_SR].x,
		   seg->vertex[TR_SR].y,
		   seg->vertex[TR_SR].z);
	    GfOut("%-8.8f %-8.8f %-8.8f\n",
		   seg->vertex[TR_SL].x,
		   seg->vertex[TR_SL].y,
		   seg->vertex[TR_SL].z);
	    GfOut("	vertices: %-8.8f %-8.8f %-8.8f ++++ ",
		   seg->vertex[TR_ER].x,
		   seg->vertex[TR_ER].y,
		   seg->vertex[TR_ER].z);
	    GfOut("%-8.8f %-8.8f %-8.8f\n",
		   seg->vertex[TR_EL].x,
		   seg->vertex[TR_EL].y,
		   seg->vertex[TR_EL].z);
	    GfOut("	prev    %d\n", seg->prev->id);
	    GfOut("	next    %d\n", seg->next->id);
	}
	GfOut("From Last To First\n");
	GfOut("Dx = %-8.8f  Dy = %-8.8f Dz = %-8.8f\n",
	       track->seg->next->vertex[TR_SR].x - track->seg->vertex[TR_ER].x,
	       track->seg->next->vertex[TR_SR].y - track->seg->vertex[TR_ER].y,
	       track->seg->next->vertex[TR_SR].z - track->seg->vertex[TR_ER].z);
	
    }
}


/** Initialize the cars for a race manager.
    The car are positionned on the starting grid.
    @param	raceInfo	the tRmInfo structure with track, simItf already stored.
    @return	0 Ok
		-1 Error
 */
int
RmInitCars(tRmInfo *raceInfo)
{
    int		nCars;
    int		index;
    int		i, j;
    char	*cardllname;
    int		robotIdx;
    tModInfo	*curModInfo;
    tRobotItf	*curRobot;
    char	buf[256];
    char	path[256];
    void	*handle;
    char	*category;
    void	*cathdle;
    void	*carhdle;
    void	*robhdle;
    tCarElt	*elt;
    char	*focused;
    int		focusedIdx;
    
    /* Get the number of cars racing */
    nCars = (int)GfParmGetNum(raceInfo->params, RM_SECT_DRIVERS, RM_ATTR_NDRIVERS, (char*)NULL, 0);
    GfOut("loading %d cars\n", nCars);

    raceInfo->carList = (tCarElt*)calloc(nCars, sizeof(tCarElt));
    raceInfo->s->current = -1;
    focused = GfParmGetStr(raceInfo->params, RM_SECT_DRIVERS, RM_ATTR_FOCUSED, "");
    focusedIdx = (int)GfParmGetNum(raceInfo->params, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, NULL, 0);
    index = 0;
    for (i = 1; i < nCars+1; i++) {
	/* Get Shared library name */
	sprintf(path, "%s/%s/%d", RM_SECT_DRIVERS, RM_LIST_DRIVERS, i);
	cardllname = GfParmGetStr(raceInfo->params, path, RM_ATTR_MODULE, "");
	robotIdx = (int)GfParmGetNum(raceInfo->params, path, RM_ATTR_IDX, (char*)NULL, 0);
	if ((strcmp(focused, cardllname) == 0) && (focusedIdx == robotIdx)) {
	    raceInfo->s->current = i-1;
	}
	sprintf(path, "drivers/%s/%s.%s", cardllname, cardllname, DLLEXT);
	/* load the robot shared library */
	if (GfModLoad(CAR_IDENT, path, raceInfo->modList)) {
	    GfTrace("Pb with loading %s driver\n", path);
	    break;
	}
	/* search for corresponding index */
	for (j = 0; j < MAX_MOD_ITF; j++) {
	    if ((*(raceInfo->modList))->modInfo[j].index == robotIdx) {
		/* good robot found */
		curModInfo = &((*(raceInfo->modList))->modInfo[j]);
		sprintf(buf, "Loading Driver %s...", curModInfo->name);
		RmLoadingScreenSetText(buf);
		GfOut("Driver's name: %s\n", curModInfo->name);
		/* retrieve the robot interface (function pointers) */
		curRobot = (tRobotItf*)calloc(1, sizeof(tRobotItf));
		curModInfo->fctInit(robotIdx, (void*)(curRobot));
		sprintf(buf, "drivers/%s/%s.xml", cardllname, cardllname);
		robhdle = GfParmReadFile(buf, GFPARM_RMODE_STD);
		if (robhdle != NULL) {
		    elt = &(raceInfo->carList[index]);
		    
		    elt->index = index;
		    elt->robot = curRobot;
		    elt->info = (tInitCar*)calloc(1, sizeof(tInitCar));
		    elt->pub  = (tPublicCar*)calloc(1, sizeof(tPublicCar));
		    elt->race = (tCarRaceInfo*)calloc(1, sizeof(tCarRaceInfo));
		    elt->priv = (tPrivCar*)calloc(1, sizeof(tPrivCar));
		    elt->ctrl = (tCarCtrl*)calloc(1, sizeof(tCarCtrl));
		    elt->pitcmd = (tCarPitCmd*)calloc(1, sizeof(tCarPitCmd));
		    elt->_paramsHandle = robhdle;
		    elt->_driverIndex = robotIdx;
		    elt->_modName = strdup(cardllname);

		    sprintf(path, "%s/%s/%d", ROB_SECT_ROBOTS, ROB_LIST_INDEX, robotIdx);
		    elt->_name       = GfParmGetStr(robhdle, path, ROB_ATTR_NAME, "<none>");
		    elt->_carName    = GfParmGetStr(robhdle, path, ROB_ATTR_CAR, "");
		    elt->_raceNumber = (int)GfParmGetNum(robhdle, path, ROB_ATTR_RACENUM, (char*)NULL, 0);
		    elt->_startRank  = index;
		    elt->_pos        = index+1;
		    elt->_remainingLaps = raceInfo->s->_totLaps;

		    curRobot->rbNewTrack(robotIdx, raceInfo->track, &handle, raceInfo->s);
		    /* handle contains the drivers modifications to the car */
		    /* Read Car model specifications */
		    sprintf(buf, "cars/%s/%s.xml", elt->_carName, elt->_carName);
		    GfOut("Car Specification: %s\n", buf);
		    carhdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
		    category = GfParmGetStr(carhdle, SECT_CAR, PRM_CATEGORY, NULL);
		    if (category != 0) {
			/* Read Car Category specifications */
			sprintf(buf, "categories/%s.xml", category);
			GfOut("Category Specification: %s\n", buf);
			cathdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
			if (GfParmCheckHandle(cathdle, carhdle)) {
			    GfTrace("Car %s not in Category %s (driver %s) !!!\n", elt->_carName, category, elt->_name);
			    break;
			}
			carhdle = GfParmMergeHandles(cathdle, carhdle,
						     GFPARM_MMODE_SRC | GFPARM_MMODE_DST | GFPARM_MMODE_RELSRC | GFPARM_MMODE_RELDST);
			//GfParmWriteFile("merge.xml", carhdle, "merged", GFPARM_TEMPLATE, "config/params.dtd");
			if (handle != NULL) {
			    if (GfParmCheckHandle(carhdle, handle)) {
				GfTrace("Bad Car parameters for driver %s\n", elt->_name);
				break;
			    }
			    handle = GfParmMergeHandles(carhdle, handle,
							GFPARM_MMODE_SRC | GFPARM_MMODE_DST | GFPARM_MMODE_RELSRC | GFPARM_MMODE_RELDST);
			} else {
			    handle = carhdle;
			}
			elt->_carHandle = handle;
			//GfParmWriteFile("toto.xml", handle, "toto", GFPARM_PARAMETER, "toto.dtd");
		    } else {
			GfTrace("Bad Car category for driver %s\n", elt->_name);
			break;
		    }
		    index ++;
		} else {
		    GfTrace("Pb No description file for driver %s\n", cardllname);
		}
    
		break;
	    }
	}
    }
    nCars = index; /* real number of cars */
    if (nCars == 0) {
	GfTrace("No driver for that race...\n");
	return -1;
    } else {
	GfOut("%d drivers ready to race\n", nCars);
    }
    
    raceInfo->s->currentTime = 0;
    raceInfo->s->deltaTime = GfParmGetNum(raceInfo->params, RM_SECT_SIMUL, RM_ATTR_TIMESTEP, (char*)NULL, 0.01);
    raceInfo->s->_ncars = nCars;
    if ((raceInfo->s->current > nCars-1) || (raceInfo->s->current < 0)) {
	raceInfo->s->current = 0;
    }
    raceInfo->s->cars = (tCarElt **)calloc(nCars, sizeof(tCarElt *));
    for (i = 0; i < nCars; i++) {
	raceInfo->s->cars[i] = &(raceInfo->carList[i]);
    }

    raceInfo->simItf->init(nCars);

    initStartingGrid(raceInfo);

    initPits(raceInfo);
    
    return 0;
}

/*
 * Function
 *	initStartingGrid
 *
 * Description
 *	Place the cars on the starting grid
 *
 * Parameters
 *	Race Information structure initialized
 *
 * Return
 *	none
 */
static void
initStartingGrid(tRmInfo *raceInfo)
{
    int		i;
    tTrackSeg	*curseg;
    int		rows;
    tdble	a, b, wi2;
    tdble	d1, d2,d3;
    tdble	startpos, tr, ts;
    tdble	speedInit;
    tdble	heightInit;
    tCarElt	*car;
    void	*trHdle;
    char	*pole;

    trHdle = GfParmReadFile(raceInfo->track->filename, GFPARM_RMODE_STD);
    
    RmDumpTrack(raceInfo->track, 0);
    curseg = raceInfo->track->seg->next;
    while (curseg->type == TR_STR) {
	curseg = curseg->next;
    }
    if (curseg->type == TR_LFT) {
	pole = GfParmGetStr(raceInfo->params, RM_SECT_STARTINGGRID, RM_ATTR_POLE, "left");
    } else {
	pole = GfParmGetStr(raceInfo->params, RM_SECT_STARTINGGRID, RM_ATTR_POLE, "right");
    }
    pole = GfParmGetStr(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_POLE, pole);
    
    if (strcmp(pole, "left") == 0) {
	a = raceInfo->track->width;
	b = -a;
    } else {
	a = 0;
	b = raceInfo->track->width;
    }
    wi2 = raceInfo->track->width * 0.5;

    rows = (int)GfParmGetNum(raceInfo->params, RM_SECT_STARTINGGRID, RM_ATTR_ROWS, (char*)NULL, 2);
    rows = (int)GfParmGetNum(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_ROWS, (char*)NULL, rows);
    d1 = GfParmGetNum(raceInfo->params, RM_SECT_STARTINGGRID, RM_ATTR_TOSTART, (char*)NULL, 10);
    d1 = GfParmGetNum(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_TOSTART, (char*)NULL, d1);
    d2 = GfParmGetNum(raceInfo->params, RM_SECT_STARTINGGRID, RM_ATTR_COLDIST, (char*)NULL, 10);
    d2 = GfParmGetNum(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_COLDIST, (char*)NULL, d2);
    d3 = GfParmGetNum(raceInfo->params, RM_SECT_STARTINGGRID, RM_ATTR_COLOFFSET, (char*)NULL, 5);
    d3 = GfParmGetNum(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_COLOFFSET, (char*)NULL, d3);
    speedInit = GfParmGetNum(raceInfo->params, RM_SECT_STARTINGGRID, RM_ATTR_INITSPEED, (char*)NULL, 0.0);
    heightInit = GfParmGetNum(raceInfo->params, RM_SECT_STARTINGGRID, RM_ATTR_INITHEIGHT, (char*)NULL, 1.0);
    heightInit = GfParmGetNum(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_INITHEIGHT, (char*)NULL, heightInit);

    if (rows < 1) {
	rows = 1;
    }
    for (i = 0; i < raceInfo->s->_ncars; i++) {
	car = &(raceInfo->carList[i]);
	car->_speed_x = speedInit;
	startpos = raceInfo->track->length - (d1 + (i / rows) * d2 + (i % rows) * d3);
	tr = a + b * ((i % rows) + 1) / (rows + 1);
	curseg = raceInfo->track->seg;  /* last segment */
	while (startpos < curseg->lgfromstart) {
	    curseg = curseg->prev;
	}
	ts = startpos - curseg->lgfromstart;
	car->_trkPos.seg = curseg;
	car->_trkPos.toRight = tr;
	switch (curseg->type) {
	case TR_STR:
	    car->_trkPos.toStart = ts;
	    RtTrackLocal2Global(&(car->_trkPos), &(car->_pos_X), &(car->_pos_Y), TR_TORIGHT);
	    car->_yaw = curseg->angle[TR_ZS];
	    break;
	case TR_RGT:
	    car->_trkPos.toStart = ts / curseg->radius;
	    RtTrackLocal2Global(&(car->_trkPos), &(car->_pos_X), &(car->_pos_Y), TR_TORIGHT);
	    car->_yaw = curseg->angle[TR_ZS] - car->_trkPos.toStart;
	    break;
	case TR_LFT:
	    car->_trkPos.toStart = ts / curseg->radius;
	    RtTrackLocal2Global(&(car->_trkPos), &(car->_pos_X), &(car->_pos_Y), TR_TORIGHT);
	    car->_yaw = curseg->angle[TR_ZS] + car->_trkPos.toStart;
	    break;
	}
	car->_pos_Z = RtTrackHeightL(&(car->_trkPos)) + heightInit;

	NORM0_2PI(car->_yaw);
	raceInfo->simItf->config(car);
    }
}


static void initPits(tRmInfo *raceInfo)
{
    tTrackPitInfo	*pits;
    tTrackSeg		*curMainSeg;
    tTrackSeg		*curPitSeg = NULL;
    tdble		toStart = 0.0;
    tdble		offset = 0.0;
    tTrkLocPos		curPos;
    int			changeSeg;
    int			i;
    
    switch (raceInfo->track->pits.type) {
    case TR_PIT_ON_TRACK_SIDE:
	pits = &(raceInfo->track->pits);
	pits->driversPits = (tTrackOwnPit*)calloc(pits->nMaxPits, sizeof(tTrackOwnPit));
	pits->driversPitsNb = raceInfo->s->_ncars;
	curPos.type = TR_LPOS_MAIN;
	curMainSeg = pits->pitStart->prev;
	changeSeg = 1;
	toStart = 0;
	i =  0;
	while (i < pits->nMaxPits) {
	    if (changeSeg) {
		changeSeg = 0;
		offset = 0;
		curMainSeg = curMainSeg->next;
		switch (pits->side) {
		case TR_RGT:
		    curPitSeg = curMainSeg->rside;
		    if (curPitSeg->rside) {
			offset = curPitSeg->width;
			curPitSeg = curPitSeg->rside;
		    }
		    break;
		case TR_LFT:
		    curPitSeg = curMainSeg->lside;
		    if (curPitSeg->lside) {
			offset = curPitSeg->width;
			curPitSeg = curPitSeg->lside;
		    }
		    break;
		}
		curPos.seg = curMainSeg;
		if (toStart >= curMainSeg->length) {
		    toStart -= curMainSeg->length;
		    changeSeg = 1;
		    continue;
		}
	    }
	    curPos.toStart = toStart + pits->len / 2.0;
	    switch (pits->side) {
	    case TR_RGT:
		curPos.toRight  = -offset - RtTrackGetWidth(curPitSeg, toStart) + pits->width / 2.0;
		curPos.toLeft   = curMainSeg->width - curPos.toRight;
		curPos.toMiddle = curMainSeg->width / 2.0 - curPos.toRight;
		break;
	    case TR_LFT:
		curPos.toLeft   = -offset - RtTrackGetWidth(curPitSeg, toStart) + pits->width / 2.0;
		curPos.toRight  = curMainSeg->width - curPos.toLeft;
		curPos.toMiddle = curMainSeg->width / 2.0 - curPos.toLeft;
		break;
	    }
	    pits->driversPits[i].pos = curPos;
	    if (i < raceInfo->s->_ncars) {
		pits->driversPits[i].car = &(raceInfo->carList[i]);
		raceInfo->carList[i]._pit = &(pits->driversPits[i]);
	    }
	    
	    toStart += pits->len;
	    if (toStart >= curMainSeg->length) {
		toStart -= curMainSeg->length;
		changeSeg = 1;
	    }
	    i++;
	}
	break;
    case TR_PIT_ON_SEPARATE_PATH:
	break;
    case TR_PIT_NONE:
	break;	
    }
    
}

