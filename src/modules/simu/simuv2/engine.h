/***************************************************************************

    file                 : engine.h
    created              : Sun Mar 19 00:07:07 CET 2000
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

#ifndef _ENGINE_H_
#define _ENGINE_H_

#define MAXPTS	40

typedef struct {
    tdble rads;
    tdble a;
    tdble b;
} tEngineCurveElem;

typedef struct {
    tdble		maxTq;
    tEngineCurveElem	data[MAXPTS];
} tEngineCurve;

typedef struct
{
    tEngineCurve	curve;
    tdble		revsLimiter;
    tdble		revsMax;
    tdble		tickover;
    tdble		I;
    tdble		rads;   /* revs in rad/s ... */
    tdble		Tq;	/* output torque */
    tdble		fuelcons;
    tdble		brakeCoeff;
} tEngine;

#endif /* _ENGINE_H_ */ 



