/***************************************************************************

    file                 : ttypes.h
    created              : Sun Jan 30 23:00:20 CET 2000
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
 
#ifndef _TTYPES_H_
#define _TTYPES_H_

#include <tgf.h>

const tdble PI = 3.14159265358979323846;  /* PI */
const tdble G = 9.80665; /* m/s/s */

/* conversion */
#define RADS2RPM(x) ((x)*9.549296585)
#define RPM2RADS(x) ((x)*.104719755)
#define RAD2DEG(x)  ((x)*(180.0/PI))
#define DEG2RAD(x)  ((x)*(PI/180.0))
#define FEET2M(x)   ((x)*0.304801)
#define SIGN(x)     ((x) < 0 ? -1.0 : 1.0)

/* normalization */
#define NORM0_2PI(x) {\
	while ((x) > 2*PI) { (x) -= 2*PI; } \
	while ((x) < 0) { (x) += 2*PI; } }

#define NORM_PI_PI(x) {\
	while ((x) > PI) { (x) -= 2*PI; } \
	while ((x) < -PI) { (x) += 2*PI; } }


#ifndef DIST
#define DIST(x1, y1, x2, y2) sqrt(((x1) - (x2)) * ((x1) - (x2)) + ((y1) - (y2)) * ((y1) - (y2)))
#endif

#ifndef MIN
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#endif

typedef struct {
    float	x;
    float	y;
    float	z;
} t3Df;

typedef struct {
    tdble	x;
    tdble	y;
    tdble	z;
} t3Dd;

typedef struct {
    int		x;
    int		y;
    int		z;
} t3Di;


typedef struct {
    tdble	x;
    tdble	y;
    tdble	z;
    tdble	ax;
    tdble	ay;
    tdble	az;
} tPosd;

/* Dynamic point structure */
typedef struct 
{
    tPosd pos; /* pos */
    tPosd vel; /* velocity */
    tPosd acc; /* acceleration */
} tDynPt;

/* Forces and moments */
typedef struct
{
    t3Dd F;
    t3Dd M;
} tForces;


/* Idents shift */
#define CAR_IDENT_SHIFT		0
#define TRK_IDENT_SHIFT		8
#define RCM_IDENT_SHIFT		16
#define RPL_IDENT_SHIFT		24

/* car state */
#define CAR_RACING	1
#define CAR_PITTING	2
#define CAR_WRECKED	3

/* designation */
#define FRNT_RGT	0	/* front right */
#define FRNT_LFT	1	/* front left */
#define REAR_RGT	2	/* rear right */
#define REAR_LFT	3	/* rear left */
#define FRNT		0	/* front */
#define REAR		1	/* rear */
#define RIGHT		0
#define LEFT		1

#endif /* _TTYPES_H_ */ 



