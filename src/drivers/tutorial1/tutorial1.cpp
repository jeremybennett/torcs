/***************************************************************************

    file                 : tutorial1.cpp
    created              : Sat Mar 18 23:28:44 CET 2000
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
#include <math.h>

#include <tgf.h> 
#include <track.h> 
#include <car.h> 
#include <raceman.h> 
#include <robottools.h>
#include <robot.h>

static void	*DrvInfo;
static char	sstring[256];
static tTrack	*curTrack;

static void initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s); 
static void newrace(int index, tCarElt* car, tSituation *s); 
static int  InitFuncPt(int index, void *pt); 
static void drive1(int index, tCarElt* car, tSituation *s); 
static void drive2(int index, tCarElt* car, tSituation *s); 
static void drive3(int index, tCarElt* car, tSituation *s); 

static tfRbDrive DriveFct[10] = {
    drive1, drive2, drive3, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};


/* 
 * Module entry point  
 */ 
extern "C" int 
tutorial1(tModInfo *modInfo) 
{
    int		i;
    char	*driver;
    
    memset(modInfo, 0, 10*sizeof(tModInfo));

    DrvInfo = GfParmReadFile("drivers/tutorial1/tutorial1.xml", GFPARM_RMODE_REREAD);
    if (DrvInfo == NULL) {
	return 0;
    }
    
    for (i = 0; i < 10; i++) {
	sprintf(sstring, "Robots/index/%d", i+1);
	driver = GfParmGetStr(DrvInfo, sstring, "name", "");
	if (strlen(driver) == 0) {
	    break;
	}
	modInfo->name    = driver;	/* name of the module (short) */
	modInfo->desc    = "Tutorial Robot";	/* description of the module (can be long) */
	modInfo->fctInit = InitFuncPt;	/* init function */
	modInfo->gfId    = ROB_IDENT;	/* supported framework version */
	modInfo->index   = i+1;
	modInfo++;
    }

    return 0; 
} 

static int 
InitFuncPt(int index, void *pt) 
{ 
    tRobotItf *itf  = (tRobotItf *)pt; 

    itf->rbNewTrack = initTrack;      	/* give the robot the track view called */ 
    					/* for every track change or new race */ 
    itf->rbNewRace  = newrace; 
    itf->rbDrive    = DriveFct[index-1];          /* drive during race */ 
    itf->index      = index; 
    return 0; 
} 

static void  
initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s) 
{ 
    curTrack = track;
    *carParmHandle = NULL; 
} 

static void  
newrace(int index, tCarElt* car, tSituation *s) 
{ 
} 


/*
 * TUTORIAL 1
 */
static void  
drive1(int index, tCarElt* car, tSituation *s) 
{ 
    memset(&car->ctrl, 0, sizeof(tCarCtrl)); 
    car->_brakeCmd = 1.0; /* all brakes on ... */ 
    /*  
     * add the driving code here to modify the 
     * car->_steerCmd 
     * car->_accelCmd 
     * car->_brakeCmd 
     */ 
} 

/*
 * TUTORIAL 2
 */
static void  
drive2(int index, tCarElt* car, tSituation *s) 
{
    static tdble	lastDeltaLane = 0;
    static tdble	lane = 0;
    tdble		deltaLane;

#define STEER_GAIN	0.1
#define DAMP_GAIN	0.1
    
    memset(&car->ctrl, 0, sizeof(tCarCtrl));
    
    /* throttle control */
    car->_gearCmd = car->_gear;
    if (car->_gearCmd == 0) {
	car->_gearCmd++;
    }
    car->_accelCmd = 0.3; /* apply 30% of throttle */

    /* steer control */
    deltaLane = lane - car->_trkPos.toMiddle;
    car->_steerCmd = STEER_GAIN * deltaLane + DAMP_GAIN * (deltaLane - lastDeltaLane) / s->deltaTime;
    lastDeltaLane = deltaLane;
    
} 

/*
 * TUTORIAL 3
 */


static tdble
critDist(tdble v0, tdble v1, tdble a_max)
{
    tdble dv = v1 - v0;
    
    if (dv > 0.0) {
	return 0.0;
    }
    return fabs((v0 + 0.5 * dv) * dv / (9.81 * a_max));
}

#define SPEED_MAX	120.0
#define CORN_MYU	1.4
#define A_MAX		1.5

static tdble
cornSpd(tdble radius)
{
    return (tdble)sqrt(radius * 9.81 * CORN_MYU);
}


static void  
drive3(int index, tCarElt* car, tSituation *s) 
{
    static tdble	lastDeltaLane = 0;
    static tdble	lane = 0;
    static tdble	lastAccel = 0;
    static tdble	lastBrake = 0;
    tdble		deltaLane;
    tdble		dfs;
    tdble		securDist;
    tdble		curLg;
    tdble		tgtSpd;
    tdble		cornspd;
    tTrackSeg		*curSeg;
    tdble		slip;

#define STEER_GAIN	0.1
#define DAMP_GAIN	0.1
#define DIST_FROM_INSIDE 2.0
    
    memset(&car->ctrl, 0, sizeof(tCarCtrl));
    
    /* steer control */
    
    /* lane update */
    curSeg = car->_trkPos.seg;
    switch (curSeg->type) {
    case TR_STR:
	lane /= 2.0;
	break;
    case TR_RGT:
	lane = - (RtTrackGetWidth(curSeg, car->_trkPos.toStart)/2.0 - DIST_FROM_INSIDE);
	break;
    case TR_LFT:
	lane = RtTrackGetWidth(curSeg, car->_trkPos.toStart)/2.0 - DIST_FROM_INSIDE;
	break;
    }

    deltaLane = lane - car->_trkPos.toMiddle;
    car->_steerCmd = STEER_GAIN * deltaLane + DAMP_GAIN * (deltaLane - lastDeltaLane) / s->deltaTime;
    lastDeltaLane = deltaLane;
    
    /* throttle control */

    /* Compute the target speed */
    dfs = RtGetDistFromStart(car);
    securDist = dfs + critDist(car->_speed_x, 0.0, A_MAX); 	/* distance needed to stop */
    tgtSpd = SPEED_MAX;
    curSeg = car->_trkPos.seg;
    do {
	curLg = curSeg->lgfromstart;
	if (curSeg == car->_trkPos.seg) {
	    curLg += curSeg->length;
	}
	if (curLg < dfs) {
	    /* start line crossed */
	    curLg += curTrack->length;
	}
	if (curLg > securDist) {
	    /* don't care yet, it is too far */
	    break;
	}
	if (curSeg->type != TR_STR) {
	    cornspd = cornSpd(curSeg->radius);
	    if ((cornspd < car->_speed_x) &&
		(critDist(car->_speed_x, cornspd, A_MAX) < curLg) &&
		(cornspd < tgtSpd)) {
		tgtSpd = cornspd;
	    } else if ((cornspd > car->_speed_x) &&
		       (cornspd < tgtSpd)) {
		tgtSpd = cornspd;
	    }
	}
	curSeg = curSeg->next;
    } while (curSeg != car->_trkPos.seg);

    /* Accelerator/Brake command */
#define CMD_STEP 0.05

    if (car->_speed_x < tgtSpd) {
	/* accelerate */
	lastBrake = 0;
	if (car->_speed_x < tgtSpd * 0.8) {
	    lastAccel += CMD_STEP;
	} else {
	    lastAccel += CMD_STEP / 10.0;
	}
	
	if (lastAccel > 1.0) lastAccel = 1.0;

	slip = 0;
	if (car->_speed_x > 0.1) {
	    slip = (car->_wheelRadius(3) * car->_wheelSpinVel(3) - car->_speed_x);
	}
	
	if (slip > 1.0) {
	    lastAccel *= 0.8;
	}
    } else {
	/* brake */
	if (car->_speed_x > tgtSpd * 1.2) {
	    lastAccel = 0;
	    lastBrake += CMD_STEP;
	    if (lastBrake > 1.0) lastBrake = 1.0;
	} else {
	    lastAccel -= CMD_STEP / 10.0;
	}
    }
    car->_accelCmd = lastAccel;
    car->_brakeCmd = lastBrake;

    /* Gear Selection */
    car->_gearCmd = car->_gear;
    if (car->_gearCmd == 0) {
	car->_gearCmd++;
    } else {
	if (car->_enginerpm > car->_enginerpmRedLine * 0.95)
	    car->_gearCmd++;
	if (car->_gear > 1 &&
	    car->_enginerpm /
	    car->_gearRatio[car->_gear + car->_gearOffset] *
	    car->_gearRatio[car->_gear - 1 + car->_gearOffset] <
	    car->_enginerpmRedLine * 0.80)
	    car->_gearCmd++;
    }
    
} 
