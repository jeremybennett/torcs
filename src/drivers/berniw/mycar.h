/***************************************************************************

    file                 : mycar.h
    created              : Mon Oct 10 13:51:00 CET 2001
    copyright            : (C) 2001-2002 by Bernhard Wymann
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

/*
	this class holds some properties of the car
*/

#ifndef _MYCAR_H_
#define _MYCAR_H_

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
#include "trackdesc.h"
#include "pathfinder.h"

class Pathfinder;
class PathSeg;

class MyCar
{
	public:
		/* possible behaviours */
		static const int INSANE = 0;
		static const int PUSH = 1;
		static const int NORMAL = 2;
		static const int CAREFUL = 3;
		static const int SLOW = 4;
		static const int START = 5;

		static const int DRWD = 0;
		static const int DFWD = 1;
		static const int D4WD = 2;

		static const tdble PATHERR = 0.5;			/* if derror > PATHERR we take actions to come back to the path [m] */
		static const tdble CORRLEN = 30.0;			/* CORRLEN * derror is the length of the correction [m] */
		static const tdble CARWIDTH = 2.2;			/* width of the car [m] */
		static const tdble CARLEN = 6.0;			/* length of the car [m] */
		static const tdble TURNTOL = 1.0;			/* tolerance for end backing up [m] */
		static const tdble TURNSPEED = 3.0;			/* if speed lower than this you can back up [m/s] */
		static const tdble MARGIN = 0.3;			/* security margin from track border [m] */
		static const tdble AEROMAGIC = 9.7;			/* aerodynamic lift factor [-] */
		static const tdble STABLESPEED = 80.0;		/* we brake currentspeed/stablespeed if car seems unstable [m/s] */
		static const tdble TIMETOCATCH = 5.0;		/* when do we start thinking about overtaking [s]*/
		static const tdble MINOVERTAKERANGE = 250.0;/* minimum length for overtaking [m] */
		static const tdble OVERTAKERADIUS = 100.0;	/* min allowed radius to start overtaking [m] */
		static const tdble OVERTAKEDIST = 3.0;		/* minimal distance of CG's while overtaking [m] */

		MyCar(TrackDesc* track, tCarElt* car, tSituation *situation);
		~MyCar();

		void info(void);
		void update(TrackDesc* track, tCarElt* car, tSituation *situation);
		void loadBehaviour(int id);
		tdble queryInverseSlip(tCarElt * car, tdble speed);
		tdble queryAcceleration(tCarElt * car, tdble speed);
		inline tCarElt* getCarPtr() { return mycar; }

		Pathfinder* pf;

		/* data for behavior */
		int bmode;
		tdble behaviour[6][12];
		int MAXDAMMAGE;								/* if dammage > MAXDAMMAGE then we plan a pit stop [-] */
		tdble DIST;									/* minimal distance to other cars [m] */
		tdble MAXRELAX;								/* to avoid skidding (0..0.99) [-] */
		tdble MAXANGLE;								/* biggest allowed angle to the path [deg] */
		tdble ACCELINC;								/* increment/decrement for acceleration [-] */
		tdble MININVSLIP;							/* 1/slip ==> defines maximum allowed slip [-] */
		tdble SFTUPRATIO;							/* rpm/rpmmax ratio for shift up (0.3..0.85) [-] */
		tdble SFTDOWNRATIO;							/* hmmm, more complicated [-] */
		tdble SFTDOWNSTEER;							/* max steer value for shift down [-] */
		tdble SPEEDSQRFACTOR;						/* multiplier for speedsqr */
		tdble GCTIME;								/* minimal time between gear changes */
		tdble ACCELLIMIT;							/* maximal allowed acceleration */
		tdble PATHERRFACTOR;						/* if derror > PATHERR*PATHERRFACTOR we compute a corrected path [-] */

		/* static data (car geometry) */
		tdble wheelbase;
		tdble wheeltrack;
		tdble cgcorr_b;
		tdble cgh;
		tdble carmass;
		tdble ca;
		tdble cw;
		int drivetrain;

		/* dynamic data */
		tdble mass;
		int currentsegid;
		int destsegid;
		double trtime;

		TrackSegment* currentseg;
		TrackSegment* destseg;
		PathSeg* currentpathseg;
		PathSeg* destpathseg;

		int undamaged;
		tdble lastfuel;
		tdble fuelperlap;
		tdble lastpitfuel;

		int count;
		tdble turnaround;
		int tr_mode;
		tdble accel;
		bool fuelchecked;
		bool startmode;

		t3Dd currentpos;
		t3Dd dir;
		tdble speed;
		tdble speedsqr;
		tdble derror;			/* distance to desired trajectory */

	private:
		tCarElt* mycar;
};


class OtherCar
{
	public:
		TrackDesc* track;
		tCarElt* me;
		tdble dt;
		int id;
		int currentsegid;
		t3Dd currentpos;
		t3Dd dir;
		tdble speedsqr;
		tdble speed;

		void init(TrackDesc* itrack, tCarElt* car, tSituation *situation);
		void update(void);

};

#endif // _MYCAR_H_

