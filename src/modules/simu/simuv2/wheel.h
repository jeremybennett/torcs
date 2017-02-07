/***************************************************************************

    file                 : wheel.h
    created              : Sun Mar 19 00:09:18 CET 2000
    copyright            : (C) 2000-2017 by Eric Espie, Bernhard Wymann
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

#ifndef _WHEEL_H__
#define _WHEEL_H__

#include "differential.h"

typedef struct
{

    /* internal data */
    tSuspension  susp;		/* associated suspension */
    tBrake       brake;		/* associated brake disk */

    /* dynamic */
    t3Dd	forces;		/* forces acting on car */
    tdble	rollRes;	/* Rolling Resistance (summed over the car) */
    tdble	rideHeight;	/* height of the bottom of the car */
    tdble	zRoad;		/* z of the road */
    t3Dd   	pos;	   	/* world related */
    t3Dd	bodyVel;	/* world related */
    tdble  	driveTq;   	/* engine torque */
    tdble	vt;

    tdble  	spinTq;		/* spin torque feedback */
    tdble  	spinVel;   	/* spin velocity */
    tdble  	prespinVel;   	/* spin velocity */
    int     	state;     	/* wheel state */
    /* 1 and 2 are for suspension state */
#define SIM_WH_ONAIR 4	/* the wheel has no contact to the ground although the suspension is not fully extended */
    tdble	axleFz;		/* force from axle (anti-roll bar) */
    tTrkLocPos	trkPos;		/* current track position */
	t3Dd	surfaceNormal;	// Normal of the surface under this wheel
    tPosd	relPos;		/* relative pos / GC */
    tdble	sa;		/* slip angle */
    tdble	sx;		/* longitudinal slip value */
    tdble	steer;
    
    /* static */
    tPosd	staticPos;	/* pos relative to the GC (z is suspension travel at rest) */
				/* and angles are camber (ax), caster (ay) and toe (az) */
    tdble	rollCenter;

    tdble  	weight0;	/* initial weight on this wheel */
    tdble	tireSpringRate;
    tdble  	radius;
    tdble  	mu;
    tdble  	I;       	/* I = inertial moment of the wheel */
    tdble  	curI;       	/* Current inertia for the wheel (including transmission) */
    tdble	mfC;		/* Magic Formula C coeff */
    tdble	mfB;		/* Magic Formula B coeff */
    tdble	mfE;		/* Magic Formula E coeff */
    tdble	lfMax;		/* Load factor */
    tdble	lfMin;		/* Load factor */
    tdble	lfK;		/* Load factor */
    tdble	opLoad;		/* Operating load */
    tdble	mass;		/* total wheel mass (incl. brake) (unsprung mass) */
    tdble	camber;		/* camber, negative toward exterior on both sides */
    tdble	pressure;	/* initial tire pressure, environment temperature */
	tdble   rel_vel;    /* relative velocity - used for realstic suspension movement*/

    tDynAxis	in;
    tDynAxis	feedBack;

    tdble	preFn, preFt;
	
	// Additional parameters for the tire wear model
	tdble treadMass;				// Initial mass of the tread
	tdble baseMass;					// Mass of the tire minus the tread 
	tdble treadThinkness;			// Thinkness of the initial tread (brand new tire)
	tdble tireGasMass;				// Mass of the gas in the tire (constant)
	tdble tireConvectionSurface;	// Surface area regarding the convection model
	
	// Dynamic Tire properties (temp, wear, etc.)
	tdble	currentPressure;		// current tire pressure considering temperature
	tdble	currentTemperature;		// current temperature
	tdble	currentWear;			// [0..1], 1 means totally worn (tread thickness 0)
	tdble	currentGraining;		// [0..1], 1 means totally grained
	tdble	currentGripFactor;		// [0..1], 1 means best grip
    
	
} tWheel;

    

#endif /* _WHEEL_H__ */ 



