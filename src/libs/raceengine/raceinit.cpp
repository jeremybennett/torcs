/***************************************************************************

    file        : raceinit.cpp
    created     : Sat Nov 16 10:34:35 CET 2002
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


/* Race initialization routines */

#include <stdlib.h>
#include <stdio.h>
#include <tgf.h>
#include <raceman.h>
#include <robot.h>
#include <racemantools.h>
#include <robottools.h>

#include "raceengine.h"
#include "racemain.h"
#include "racestate.h"
#include "racegl.h"
#include "raceresults.h"

#include "raceinit.h"

static char *level_str[] = { ROB_VAL_ROOKIE, ROB_VAL_AMATEUR, ROB_VAL_SEMI_PRO, ROB_VAL_PRO };

static tModList *reEventModList = 0;
tModList *ReRaceModList = 0;
static char buf[1024];
static char path[1024];

typedef struct 
{
    int		index;
    tModList	*curmod;
} tMainMod;

/* Race Engine Initialization */
void
ReInit(void)
{
    char	*dllname;
    char	key[256];

    ReShutdown();

    ReInfo = (tRmInfo *)calloc(1, sizeof(tRmInfo));
    ReInfo->s = (tSituation *)calloc(1, sizeof(tSituation));
    ReInfo->modList = &ReRaceModList;
    ReInfo->_reParam = GfParmReadFile(RACE_ENG_CFG, GFPARM_RMODE_REREAD | GFPARM_RMODE_CREAT);

    GfOut("Loading Track Loader...\n");
    dllname = GfParmGetStr(ReInfo->_reParam, "Modules", "track", "");
    sprintf(key, "modules/track/%s.%s", dllname, DLLEXT);
    if (GfModLoad(0, key, &reEventModList)) return;
    reEventModList->modInfo->fctInit(reEventModList->modInfo->index, &ReInfo->_reTrackItf);

    GfOut("Loading Graphic Engine...\n");
    dllname = GfParmGetStr(ReInfo->_reParam, "Modules", "graphic", "");
    sprintf(key, "modules/graphic/%s.%s", dllname, DLLEXT);
    if (GfModLoad(0, key, &reEventModList)) return;
    reEventModList->modInfo->fctInit(reEventModList->modInfo->index, &ReInfo->_reGraphicItf);

    ReInfo->_reGameScreen = ReHookInit();
}

/* Race Engine Exit */
void
ReShutdown(void)
{
    /* Free previous situation */
    if (ReInfo) {
	ReInfo->_reTrackItf.trkShutdown();

	GfModUnloadList(&reEventModList);

	GfParmReleaseHandle(ReInfo->results);

	FREEZ(ReInfo->s);
	FREEZ(ReInfo);
    }
}


void
ReStartNewRace(void * /* dummy */)
{
    ReInitResults();
    ReStateManage();
}


/* Launch a race manager */
static void
reSelectRaceman(void *params)
{
    char	*p;
    
    ReInfo->params = params;
    FREEZ(ReInfo->_reFilename);
    ReInfo->_reFilename = strdup(GfParmGetFileName(params));
    while ((p = strstr(ReInfo->_reFilename, "/")) != 0) {
	ReInfo->_reFilename = p + 1;
    }
    p = ReInfo->_reFilename;
    p = strstr(p, PARAMEXT);
    if (p) {
	*p = '\0';
    }
    ReInfo->_reName = GfParmGetStr(params, RM_SECT_HEADER, RM_ATTR_NAME, "");
    ReStateApply(RE_STATE_CONFIG);
}

/* Register a race manager */
static void
reRegisterRaceman(tFList *racemanCur)
{
    sprintf(buf, "%sconfig/raceman/%s", LocalDir, racemanCur->name);
    racemanCur->userData = GfParmReadFile(buf, GFPARM_RMODE_STD);
    racemanCur->dispName = GfParmGetStr(racemanCur->userData, RM_SECT_HEADER, RM_ATTR_NAME, 0);
}

/* Sort race managers by priority */
static void
reSortRacemanList(tFList **racemanList)
{
    tFList *head;
    tFList *cur;
    tFList *tmp;

    head = *racemanList;
    cur = head;
    while (cur->next != head) {
	if (GfParmGetNum(cur->userData, RM_SECT_HEADER, RM_ATTR_PRIO, NULL, 10000) >
	    GfParmGetNum(cur->next->userData, RM_SECT_HEADER, RM_ATTR_PRIO, NULL, 10000)) {
	    /* swap cur and cur->next */
	    tmp = cur->next;
	    if (tmp->next != cur) {
		cur->next = tmp->next;
		tmp->next = cur;
		tmp->prev = cur->prev;
		cur->prev = tmp;
		cur->next->prev = cur;
		tmp->prev->next = tmp;
	    }
	    if (cur == head) {
		head = tmp;
	    } else {
		cur = tmp->prev;
	    }
	} else {
	    cur = cur->next;
	}
    }
    *racemanList = head;
}

/* Load race managers selection menu */
void
ReAddRacemanListButton(void *menuHandle)
{
    tFList	*racemanList;
    tFList	*racemanCur;
    
    racemanList = GfDirGetList("config/raceman");
    if (!racemanList) {
	GfOut("No race manager available\n");
	return;
    }
    racemanCur = racemanList;
    do {
	reRegisterRaceman(racemanCur);
	racemanCur = racemanCur->next;
    } while (racemanCur != racemanList);
    reSortRacemanList(&racemanList);
    
    racemanCur = racemanList;
    do {
	GfuiMenuButtonCreate(menuHandle,
			     racemanCur->dispName,
			     GfParmGetStr(racemanCur->userData, RM_SECT_HEADER, RM_ATTR_DESCR, ""),
			     racemanCur->userData,
			     reSelectRaceman);
	racemanCur = racemanCur->next;
    } while (racemanCur != racemanList);
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
initStartingGrid(void)
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
    char	*pole;
    void	*trHdle = ReInfo->track->params;
    void	*params = ReInfo->params;

    sprintf(path, "%s/%s", ReInfo->_reRaceName, RM_SECT_STARTINGGRID);
    
    /* Search for the first turn for find the pole side */
    curseg = ReInfo->track->seg->next;
    while (curseg->type == TR_STR) {
	/* skip the straight segments */
	curseg = curseg->next;
    }
    /* Set the pole for the inside of the first turn */
    if (curseg->type == TR_LFT) {
	pole = GfParmGetStr(params, path, RM_ATTR_POLE, "left");
    } else {
	pole = GfParmGetStr(params, path, RM_ATTR_POLE, "right");
    }
    /* Tracks definitions can force the pole side */
    pole = GfParmGetStr(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_POLE, pole);
    
    if (strcmp(pole, "left") == 0) {
	a = ReInfo->track->width;
	b = -a;
    } else {
	a = 0;
	b = ReInfo->track->width;
    }
    wi2 = ReInfo->track->width * 0.5;

    rows = (int)GfParmGetNum(params, path, RM_ATTR_ROWS, (char*)NULL, 2);
    rows = (int)GfParmGetNum(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_ROWS, (char*)NULL, rows);
    d1 = GfParmGetNum(params, path, RM_ATTR_TOSTART, (char*)NULL, 10);
    d1 = GfParmGetNum(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_TOSTART, (char*)NULL, d1);
    d2 = GfParmGetNum(params, path, RM_ATTR_COLDIST, (char*)NULL, 10);
    d2 = GfParmGetNum(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_COLDIST, (char*)NULL, d2);
    d3 = GfParmGetNum(params, path, RM_ATTR_COLOFFSET, (char*)NULL, 5);
    d3 = GfParmGetNum(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_COLOFFSET, (char*)NULL, d3);
    speedInit = GfParmGetNum(params, path, RM_ATTR_INITSPEED, (char*)NULL, 0.0);
    heightInit = GfParmGetNum(params, path, RM_ATTR_INITHEIGHT, (char*)NULL, 1.0);
    heightInit = GfParmGetNum(trHdle, RM_SECT_STARTINGGRID, RM_ATTR_INITHEIGHT, (char*)NULL, heightInit);

    if (rows < 1) {
	rows = 1;
    }
    for (i = 0; i < ReInfo->s->_ncars; i++) {
	car = &(ReInfo->carList[i]);
	car->_speed_x = speedInit;
	startpos = ReInfo->track->length - (d1 + (i / rows) * d2 + (i % rows) * d3);
	tr = a + b * ((i % rows) + 1) / (rows + 1);
	curseg = ReInfo->track->seg;  /* last segment */
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
	ReInfo->_reSimItf.config(car);
    }
}


static void
initPits(void)
{
    tTrackPitInfo	*pits;
    int			i;
    
    switch (ReInfo->track->pits.type) {
    case TR_PIT_ON_TRACK_SIDE:
	pits = &(ReInfo->track->pits);
	pits->driversPitsNb = ReInfo->s->_ncars;
	for (i =  0; i < pits->nMaxPits; i++) {
	    if (i < pits->driversPitsNb) {
		tCarElt *car = &(ReInfo->carList[i]);
		tTrackOwnPit *pit = &(pits->driversPits[i]);
		pits->driversPits[i].car = car;
		ReInfo->carList[i]._pit = pit;
		pit->lmin = pit->pos.seg->lgfromstart + pit->pos.toStart - pits->len / 2.0 + car->_dimension_x / 2.0;
		if (pit->lmin > ReInfo->track->length) {
		    pit->lmin -= ReInfo->track->length;
		}
		pit->lmax = pit->pos.seg->lgfromstart + pit->pos.toStart + pits->len / 2.0 - car->_dimension_x / 2.0;
		if (pit->lmax > ReInfo->track->length) {
		    pit->lmax -= ReInfo->track->length;
		}
	    } else {
		pits->driversPits[i].car = 0;
	    }
	}
	break;
    case TR_PIT_ON_SEPARATE_PATH:
	break;
    case TR_PIT_NONE:
	break;	
    }
    
}

/** Initialize the cars for a race.
    The car are positionned on the starting grid.
    @return	0 Ok
		-1 Error
 */
int
ReInitCars(void)
{
    int		nCars;
    int		index;
    int		i, j, k;
    char	*cardllname;
    int		robotIdx;
    tModInfo	*curModInfo;
    tRobotItf	*curRobot;
    void	*handle;
    char	*category;
    void	*cathdle;
    void	*carhdle;
    void	*robhdle;
    tCarElt	*elt;
    char	*focused;
    char	*str;
    int		focusedIdx;
    void	*params = ReInfo->params;
    
    /* Get the number of cars racing */
    nCars = GfParmGetEltNb(params, RM_SECT_DRIVERS_RACING);
    GfOut("loading %d cars\n", nCars);

    FREEZ(ReInfo->carList);
    ReInfo->carList = (tCarElt*)calloc(nCars, sizeof(tCarElt));
    ReInfo->s->current = -1;
    focused = GfParmGetStr(ReInfo->params, RM_SECT_DRIVERS, RM_ATTR_FOCUSED, "");
    focusedIdx = (int)GfParmGetNum(ReInfo->params, RM_SECT_DRIVERS, RM_ATTR_FOCUSEDIDX, NULL, 0);
    index = 0;
    for (i = 1; i < nCars + 1; i++) {
	/* Get Shared library name */
	sprintf(path, "%s/%d", RM_SECT_DRIVERS_RACING, i);
	cardllname = GfParmGetStr(ReInfo->params, path, RM_ATTR_MODULE, "");
	robotIdx = (int)GfParmGetNum(ReInfo->params, path, RM_ATTR_IDX, NULL, 0);
	if ((strcmp(focused, cardllname) == 0) && (focusedIdx == robotIdx)) {
	    ReInfo->s->current = i - 1;
	}
	sprintf(path, "drivers/%s/%s.%s", cardllname, cardllname, DLLEXT);
	/* load the robot shared library */
	if (GfModLoad(CAR_IDENT, path, ReInfo->modList)) {
	    GfTrace("Pb with loading %s driver\n", path);
	    break;
	}
	/* search for corresponding index */
	for (j = 0; j < MAX_MOD_ITF; j++) {
	    if ((*(ReInfo->modList))->modInfo[j].index == robotIdx) {
		/* good robot found */
		curModInfo = &((*(ReInfo->modList))->modInfo[j]);
		GfOut("Driver's name: %s\n", curModInfo->name);
		/* retrieve the robot interface (function pointers) */
		curRobot = (tRobotItf*)calloc(1, sizeof(tRobotItf));
		curModInfo->fctInit(robotIdx, (void*)(curRobot));
		sprintf(buf, "%sdrivers/%s/%s.xml", LocalDir, cardllname, cardllname);
		robhdle = GfParmReadFile(buf, GFPARM_RMODE_STD);
		if (!robhdle) {
		    sprintf(buf, "drivers/%s/%s.xml", cardllname, cardllname);
		    robhdle = GfParmReadFile(buf, GFPARM_RMODE_STD);
		}
		if (robhdle != NULL) {
		    elt = &(ReInfo->carList[index]);
		    
		    elt->index = index;
		    elt->robot = curRobot;
		    elt->_paramsHandle = robhdle;
		    elt->_driverIndex = robotIdx;
		    strncpy(elt->_modName, cardllname, MAX_NAME_LEN - 1);
		    elt->_modName[MAX_NAME_LEN - 1] = 0;

		    sprintf(path, "%s/%s/%d", ROB_SECT_ROBOTS, ROB_LIST_INDEX, robotIdx);
		    strncpy(elt->_name, GfParmGetStr(robhdle, path, ROB_ATTR_NAME, "<none>"), MAX_NAME_LEN - 1);
		    elt->_name[MAX_NAME_LEN - 1] = 0;
		    strncpy(elt->_carName, GfParmGetStr(robhdle, path, ROB_ATTR_CAR, ""), MAX_NAME_LEN - 1);
		    elt->_carName[MAX_NAME_LEN - 1] = 0;
		    elt->_raceNumber = (int)GfParmGetNum(robhdle, path, ROB_ATTR_RACENUM, (char*)NULL, 0);
		    if (strcmp(GfParmGetStr(robhdle, path, ROB_ATTR_TYPE, ROB_VAL_ROBOT), ROB_VAL_ROBOT)) {
			elt->_driverType = RM_DRV_HUMAN;
		    } else {
			elt->_driverType = RM_DRV_ROBOT;
		    }
		    elt->_skillLevel = 0;
		    str = GfParmGetStr(robhdle, path, ROB_ATTR_LEVEL, ROB_VAL_SEMI_PRO);
		    for(k = 0; k < (int)(sizeof(level_str)/sizeof(char*)); k++) {
			if (strcmp(level_str[k], str) == 0) {
			    elt->_skillLevel = k;
			    break;
			}
		    }
		    elt->_startRank  = index;
		    elt->_pos        = index+1;
		    elt->_remainingLaps = ReInfo->s->_totLaps;

		    /* handle contains the drivers modifications to the car */
		    /* Read Car model specifications */
		    sprintf(buf, "cars/%s/%s.xml", elt->_carName, elt->_carName);
		    GfOut("Car Specification: %s\n", buf);
		    carhdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
		    category = GfParmGetStr(carhdle, SECT_CAR, PRM_CATEGORY, NULL);
		    sprintf(buf, "Loading Driver %-20s... Car: %s", curModInfo->name, elt->_carName);
		    RmLoadingScreenSetText(buf);
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
			curRobot->rbNewTrack(robotIdx, ReInfo->track, carhdle, &handle, ReInfo->s);
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
    
    ReInfo->s->_ncars = nCars;
    if ((ReInfo->s->current > (nCars - 1)) || (ReInfo->s->current < 0)) {
	ReInfo->s->current = 0;
    }
    FREEZ(ReInfo->s->cars);
    ReInfo->s->cars = (tCarElt **)calloc(nCars, sizeof(tCarElt *));
    for (i = 0; i < nCars; i++) {
	ReInfo->s->cars[i] = &(ReInfo->carList[i]);
    }

    ReInfo->_reSimItf.init(nCars);

    initStartingGrid();

    initPits();
    
    return 0;
}

/** Dump the track segments on screen
    @param	track	track to dump
    @param	verbose	if set to 1 all the segments are described (long)
    @ingroup	racemantools
 */
static void
reDumpTrack(tTrack *track, int verbose)
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
    sprintf(buf, ">>> Track Author  %s", track->author);
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


/** Initialize the track for a race manager.
    @return	<tt>0 ... </tt>Ok<br>
		<tt>-1 .. </tt>Error
*/
int
ReInitTrack(void)
{
    char	*trackName;
    char	*catName;
    int		curTrkIdx;
    void	*params = ReInfo->params;
    void	*results = ReInfo->results;

    curTrkIdx = (int)GfParmGetNum(results, RE_SECT_CURRENT, RE_ATTR_CUR_TRACK, NULL, 1);
    sprintf(buf, "%s/%d", RM_SECT_TRACKS, curTrkIdx);
    trackName = GfParmGetStr(params, buf, RM_ATTR_NAME, 0);
    if (!trackName) return -1;
    catName = GfParmGetStr(params, buf, RM_ATTR_CATEGORY, 0);
    if (!catName) return -1;

    sprintf(buf, "Loading Track %s...", trackName);
    RmLoadingScreenSetText(buf);
    sprintf(buf, "tracks/%s/%s/%s.%s", catName, trackName, trackName, TRKEXT);
    ReInfo->track = ReInfo->_reTrackItf.trkBuild(buf);
    reDumpTrack(ReInfo->track, 0);

    return 0;
}

void
ReRaceCleanup(void)
{
    ReInfo->_reGameScreen = ReHookInit();
    ReInfo->_reSimItf.shutdown();
    if (ReInfo->_displayMode == RM_DISP_MODE_NORMAL) {
	ReInfo->_reGraphicItf.shutdowncars();
    }
    ReStoreRaceResults(ReInfo->_reRaceName);
    ReRaceCleanDrivers();
}


void
ReRaceCleanDrivers(void)
{
    int		i;
    tRobotItf	*robot;
    int		nCars;

    nCars = ReInfo->s->_ncars;
    for (i = 0; i < nCars; i++) {
	robot = ReInfo->s->cars[i]->robot;
	if (robot->rbShutdown) {
	    robot->rbShutdown(robot->index);
	}
	GfParmReleaseHandle(ReInfo->s->cars[i]->_paramsHandle);
    }
    free(ReInfo->s->cars);
    ReInfo->s->cars = 0;
    ReInfo->s->_ncars = 0;
    GfModUnloadList(&ReRaceModList);
}


char *
ReGetCurrentRaceName(void)
{
    int		curRaceIdx;
    void	*params = ReInfo->params;
    void	*results = ReInfo->results;

    curRaceIdx = (int)GfParmGetNum(results, RE_SECT_CURRENT, RE_ATTR_CUR_RACE, NULL, 1);
    sprintf(path, "%s/%d", RM_SECT_RACES, curRaceIdx);
    return GfParmGetStr(params, path, RM_ATTR_NAME, 0);
}

char *
ReGetPrevRaceName(void)
{
    int		curRaceIdx;
    void	*params = ReInfo->params;
    void	*results = ReInfo->results;

    curRaceIdx = (int)GfParmGetNum(results, RE_SECT_CURRENT, RE_ATTR_CUR_RACE, NULL, 1) - 1;
    sprintf(path, "%s/%d", RM_SECT_RACES, curRaceIdx);
    return GfParmGetStr(params, path, RM_ATTR_NAME, 0);
}
