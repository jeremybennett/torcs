/***************************************************************************

    file                 : tutorial2.cpp
    created              : Sat Mar 18 23:29:35 CET 2000
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
#include <robot.h> 
#include <robottools.h>

static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation *s); 
static void drive(int index, tCarElt* car, tSituation *s); 
static void newrace(int index, tCarElt* car, tSituation *s); 
static int  InitFuncPt(int index, void *pt); 

/* 
 * Module entry point  
 */ 
extern "C" int 
tutorial2(tModInfo *modInfo) 
{ 
    modInfo->name    = "Tutorial2";         	/* name of the module (short) */ 
    modInfo->desc    = "Tutorial2 Robot"; 	/* description of the module */ 
    modInfo->fctInit = InitFuncPt;        	/* init function */ 
    modInfo->gfId    = ROB_IDENT;         	/* supported framework version */ 
    modInfo->index   = 1;                 	/* same as in XML file */ 

    return 0; 
} 

static int 
InitFuncPt(int index, void *pt) 
{ 
    tRobotItf *itf = (tRobotItf *)pt; 

    itf->rbNewTrack = initTrack;      /* give the robot the track view called */ 
    /* for every track change or new race */ 
    itf->rbNewRace  = newrace; 
    itf->rbDrive    = drive;          /* drive during race */ 
    itf->index      = index; 
    return 0; 
} 

static void  
initTrack(int index, tTrack* track, void **carParmHandle, tSituation *s) 
{ 
    *carParmHandle = NULL; 
} 

static void  
newrace(int index, tCarElt* car, tSituation *s) 
{ 
} 

static const tdble Kadvance = 30.0;

static void  
drive(int index, tCarElt* car, tSituation *s) 
{
    tdble	angle;
    tdble	centerControl;
    tdble	X, Y;
    tTrkLocPos	trkPos;

    memset(car->ctrl, 0, sizeof(tCarCtrl));
    /* steer control */
    /* get the difference between the tangent to the track and the car yaw */
    angle = RtTrackSideTgAngleL(&(car->_trkPos)) - car->_yaw;
    /* normalize to -PI +PI */
    NORM_PI_PI(angle);
    car->ctrl->steer = angle;
    /* get the normalized distance to the middle of the track */
    centerControl = car->_trkPos.toMiddle / car->_trkPos.seg->width;
    car->ctrl->steer -= centerControl;
    /* anticipate the car's position */
    X = car->_pos_X + cos(car->_yaw) * Kadvance;
    Y = car->_pos_Y + sin(car->_yaw) * Kadvance;
    /* convert global position into local position */
    RtTrackGlobal2Local(car->_trkPos.seg, X, Y, &trkPos, TR_LPOS_MAIN);
    centerControl = trkPos.toMiddle / trkPos.seg->width;
    car->ctrl->steer -= centerControl;
    

    /* throttle control */
    car->ctrl->gear = car->_gear;
    if (car->_gear == 0) {
	car->ctrl->gear++;
    }
    car->ctrl->accelCmd = 0.3; /* apply 30% of throttle */
} 
