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

/** @file   
    		Global types used in TORCS.
    @author	<a href=mailto:eric.espie@torcs.org>Eric Espie</a>
    @version	$Id$
    @ingroup	definitions
*/

#ifndef _TTYPES_H_
#define _TTYPES_H_

#include <tgf.h>

const tdble PI = 3.14159265358979323846;  /**< PI */
const tdble G = 9.80665; /**< m/s/s */

/* conversion */
#define RADS2RPM(x) ((x)*9.549296585)		/**< Radian/s to RPM conversion */
#define RPM2RADS(x) ((x)*.104719755)		/**< RPM to Radian/s conversion */
#define RAD2DEG(x)  ((x)*(180.0/PI))		/**< Radian to degree conversion */
#define DEG2RAD(x)  ((x)*(PI/180.0))		/**< Degree to radian conversion */
#define FEET2M(x)   ((x)*0.304801)		/**< Feet to meter conversion */
#define SIGN(x)     ((x) < 0 ? -1.0 : 1.0)	/**< Sign of the expression */

/** Angle normalization between 0 and 2 * PI */
#define NORM0_2PI(x) 				\
do {						\
	while ((x) > 2*PI) { (x) -= 2*PI; }	\
	while ((x) < 0) { (x) += 2*PI; } 	\
} while (0)

/** Angle normalization between -PI and PI */
#define NORM_PI_PI(x) 				\
do {						\
	while ((x) > PI) { (x) -= 2*PI; }	\
	while ((x) < -PI) { (x) += 2*PI; } 	\
} while (0)


#ifndef DIST
/** Distance between two points */
#define DIST(x1, y1, x2, y2) sqrt(((x1) - (x2)) * ((x1) - (x2)) + ((y1) - (y2)) * ((y1) - (y2)))
#endif

#ifndef MIN
/** Minimum between two values */
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#endif


typedef struct {
    float	x;
    float	y;
    float	z;
} t3Df;

/** 3D point.
    @ingroup definitions
*/
typedef struct {
    tdble	x;		/**< x coordinate */
    tdble	y;		/**< y coordinate */
    tdble	z;		/**< z coordinate */
} t3Dd;

typedef struct {
    int		x;
    int		y;
    int		z;
} t3Di;

/** 6 DOF position.
    @ingroup definitions
*/
typedef struct {
    tdble	x;		/**< x coordinate */
    tdble	y;		/**< y coordinate */
    tdble	z;		/**< z coordinate */
    tdble	ax;		/**< angle along x axis */
    tdble	ay;		/**< angle along y axis */
    tdble	az;		/**< angle along z axis */
} tPosd;

/** Dynamic point structure.
    @ingroup definitions
*/
typedef struct 
{
    tPosd pos; /**< position */
    tPosd vel; /**< velocity */
    tPosd acc; /**< acceleration */
} tDynPt;

/** Forces and moments */
typedef struct
{
    t3Dd F; /**< Forces */
    t3Dd M; /**< Moments */
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
#define FRNT_RGT	0	/**< front right */
#define FRNT_LFT	1	/**< front left */
#define REAR_RGT	2	/**< rear right */
#define REAR_LFT	3	/**< rear left */
#define FRNT		0	/**< front */
#define REAR		1	/**< rear */
#define RIGHT		0	/**< right */
#define LEFT		1	/**< left */

#endif /* _TTYPES_H_ */ 



