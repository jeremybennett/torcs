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

#define TRACKFILENAME		"/home/berni/track.dat"
#define TRACKDESCFILENAME   "/home/berni/track.txt"
#define RMAX				10000.0
#define BOTS 10
#define BUFSIZE 256


static const tdble g = 9.81;

/*
	compute the angle between the track and the car
*/
inline tdble queryAngleToTrack(tCarElt * car)
{
	tdble angle = RtTrackSideTgAngleL(&(car->_trkPos)) - car->_yaw;
	NORM_PI_PI(angle);
	return angle;
}

/* compute the radius given three points */
inline tdble radius(tdble x1, tdble y1, tdble x2, tdble y2, tdble x3, tdble y3)
{
	tdble dx1 = x2 - x1;
	tdble dy1 = y2 - y1;
	tdble dx2 = x3 - x2;
	tdble dy2 = y3 - y2;

	tdble z = (dy1*dx2 - dx1*dy2);

	if (z != 0.0) {
		tdble k = (dx2*(x3-x1) - dy2*(y1-y3))/z;
		return sqrt((1.0+k*k)*(dx1*dx1+dy1*dy1))/2.0;
	} else {
		return FLT_MAX;
	}
}

inline tdble sign(tdble number)
{
	return (number >= 0.0) ? 1.0 : -1.0;
}

#endif // _BERNIW_H_

