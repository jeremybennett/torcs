/***************************************************************************

    file                 : raceman.h
    created              : Sun Jan 30 22:59:17 CET 2000
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
 
 
#ifndef _RACEMANV1_H_
#define _RACEMANV1_H_

#include <ttypes.h>
#include <tgf.h>
#include <car.h>

#define RCM_IDENT	((0x01)<<RCM_IDENT_SHIFT)	/* allowed from 0x01 to 0xFF */

#define RCM_MAX_DT_SIMU		0.002
#define RCM_MAX_DT_ROBOTS	0.02

/* General info on current race */
typedef struct {
    int			ncars;		/* number of cars */
    int			totLaps;	/* total laps */
    int			state;
#define RM_RACE_FINISHING	1
#define RM_RACE_PAUSED		2
    int			type;		/* Race type */
#define RM_TYPE_PRACTICE	1
#define RM_TYPE_QUALIF		2
#define RM_TYPE_RACE		3
    int                 maxDammage;
    unsigned long	fps;
} tRaceAdmInfo;
#define _ncars		raceInfo.ncars
#define _totLaps	raceInfo.totLaps
#define _raceState	raceInfo.state
#define _raceType	raceInfo.type
#define _maxDammage	raceInfo.maxDammage

/* cars situation used to inform the GUI and the drivers */
typedef struct {
    tRaceAdmInfo	raceInfo;
    double		deltaTime;
    double		currentTime;	/* current time in sec since the beginning of the simulation */
    int			current;	/* current car */
    tCarElt		**cars;		/* list of cars */ 
} tSituation;

    

typedef struct 
{
    tfuiCallback	start;
} tRacemanItf;

/*
 * Parameters name definitions for Race Managers
 */
#define RM_SECT_DRIVERS		"Drivers"
#define RM_SECT_STARTINGGRID	"Starting Grid"
#define RM_SECT_RACE		"Race"
#define RM_SECT_SIMUL		"Simulation"

#define RM_LIST_DRIVERS		"drivers"

#define RM_ATTR_NDRIVERS	"ndrivers"
#define RM_ATTR_MODULE		"module"
#define RM_ATTR_IDX		"idx"
#define RM_ATTR_FOCUSED		"focused module"
#define RM_ATTR_FOCUSEDIDX	"focused idx"

#define RM_ATTR_TIMESTEP	"time step"

#define RM_ATTR_TYPE		"type"
#define RM_ATTR_ROWS		"rows"
#define RM_ATTR_TOSTART		"distance to start"
#define RM_ATTR_COLDIST		"distance between columns"
#define RM_ATTR_COLOFFSET	"offset within a column"
#define RM_ATTR_INITSPEED	"initial speed"
#define RM_ATTR_INITHEIGHT	"initial height"
#define RM_ATTR_SHOW_RACE	"show race"
#define RM_ATTR_MAX_DMG		"maximum dammage"
#define RM_ATTR_DISTANCE	"distance"
#define RM_ATTR_LAPS		"laps"
#define RM_ATTR_POLE		"pole position side"
#endif /* _RACEMANV1_H_ */ 



