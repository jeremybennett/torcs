/***************************************************************************

    file                 : berniw.h
    created              : Mon Mai 15 16:52:00 CET 2000
    copyright            : (C) 2000 by Bernhard Wymann
    email                : berniw@bluewin.ch
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

#ifndef _BERNIW_H_
#define _BERNIW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tgf.h>
#include <track.h>
#include <car.h>
#include <raceman.h>
#include <robot.h>
#include <robottools.h>
#include <math.h>
#include <ttypes.h>
#include "spline.h"
#include "trackdesc.h"
#include "mycar.h"
#include "pathfinder.h"

#define RES					1
#define TRACKFILENAME		"/home/berni/track.dat"
#define TRACKDESCFILENAME   "/home/berni/track.txt"
#define RMAX				10000.0


/*
	compute the slip on the rear wheels
*/
inline tdble queryRearSlip(tCarElt * car, tdble speed)
{
	tdble rear_speed = (car->_wheelSpinVel(REAR_RGT) + car->_wheelSpinVel(REAR_LFT)) * car->_wheelRadius(REAR_LFT) / 2.0;
	if (fabs(speed) < 1.0) return 1.0; else return fabs(rear_speed / speed);
}


/*
	compute the inverse of the rear slip => speed == 0 is allowed
*/
inline tdble queryInverseRearSlip(tCarElt * car, tdble speed)
{
	tdble rear_speed = (car->_wheelSpinVel(REAR_RGT) + car->_wheelSpinVel(REAR_LFT)) * car->_wheelRadius(REAR_LFT) / 2.0;
	if (fabs(rear_speed) < 3.0) return 1.0; return fabs(speed / rear_speed);
}


/*
	compute the acceleration value for a given speed
*/
inline tdble queryAcceleration(tCarElt * car, tdble speed)
{
	tdble accel = speed / car->_wheelRadius(REAR_RGT) * car->_gearRatio[car->_gear + car->_gearOffset] / car->_enginerpmMax;
	if (accel > 1.0) return 1.0; else return accel;
}


/*
	compute the angle between the track and the car
*/
inline tdble queryAngleToTrack(tCarElt * car)
{
	tdble angle = RtTrackSideTgAngleL(&(car->_trkPos)) - car->_yaw;
	NORM_PI_PI(angle);
	return angle;
}

#endif // _BERNIW_H_
