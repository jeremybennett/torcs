/***************************************************************************

    file                 : raceman.h
    created              : Sun Jan 30 22:59:17 CET 2000
    copyright            : (C) 2000,2002 by Eric Espie
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
    		This is the race information structures.
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
    @ingroup	raceinfo
*/
 
#ifndef _RACEMANV1_H_
#define _RACEMANV1_H_

#include <ttypes.h>
#include <tgf.h>
#include <car.h>
#include <track.h>
#include <graphic.h>
#include <simu.h>

#define RCM_IDENT 0

#define RM_PRIO_QUICKRACE	10
#define RM_PRIO_SIMPLERACE	20
#define RM_PRIO_CHAMPIONSHIP	30
#define RM_PRIO_PRACTICE	90

#define RM_MAGIC	161102	/* Should be chaged every time the tRacemanItf structure is modified */
struct RmInfo;

typedef int (*tfRmRunState) (struct RmInfo *);
#define RM_SYNC		0x01
#define RM_ASYNC	0x02
#define RM_NEXT_STEP	0x04
#define RM_END_RACE	0x08
#define RM_NEXT_RACE	0x10
#define RM_NEXT_EVENT	0x20


/** Race manager module interface  */
typedef struct
{
    tfRmRunState	runState;
    tfuiCallback	start;
} tRacemanItf;



#define RCM_MAX_DT_SIMU		0.002
#define RCM_MAX_DT_ROBOTS	0.02

/** General info on current race */
typedef struct {
    int			ncars;		/**< number of cars */
    int			totLaps;	/**< total laps */
    int			state;
#define RM_RACE_FINISHING	1
#define RM_RACE_PAUSED		2
    int			type;		/**< Race type */
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

/** cars situation used to inform the GUI and the drivers */
typedef struct Situation {
    tRaceAdmInfo	raceInfo;
    double		deltaTime;
    double		currentTime;	/**< current time in sec since the beginning of the simulation */
    int			current;	/**< current car */
    tCarElt		**cars;		/**< list of cars */ 
} tSituation;

/* RACE ENGINE */

typedef struct 
{
    tTrackItf	trackItf;
    tGraphicItf	graphicItf;
    tSimItf	simItf;
    tRacemanItf	racemanItf;
} tRaceModIft;

#define RE_STATE_CONFIG			0
#define RE_STATE_RACE_EVENT_INIT	1
#define RE_STATE_RACE_TRACK_INIT	2
#define RE_STATE_PRE_RACE		3
#define RE_STATE_RACE_CARS_INIT		4
#define RE_STATE_RACE			5
#define RE_STATE_RACE_CARS_SHUTDOWN	6
#define RE_STATE_POST_RACE		7
#define RE_STATE_RACE_TRACK_SHUTDOWN	8
#define RE_STATE_RACE_EVENT_SHUTDOWN	9
#define RE_STATE_SHUTDOWN		10
#define RE_STATE_ERROR			11

/* Race Engine Car Information about the race */
typedef struct 
{
    tTrkLocPos	prevTrkPos;
    tdble	sTime;
    int		lapFlag;
    char	*raceMsg;
    double	totalPitTime;
    double	startPitTime;
} tReCarInfo;

/* Race Engine Information */
typedef struct
{
    int			state;
    tTrack		*track;
    void		*param;
    tRaceModIft		itf;
    void		*gameScreen;
    void		*menuScreen;
    char		*name;
    tReCarInfo		*carInfo;
    double		curTime;
    double		lastTime;
    double		timeMult;
    int			running;
} tRaceEngineInfo;

#define _reState	raceEngineInfo.state
#define _reTrack	raceEngineInfo.track
#define _reParam	raceEngineInfo.param
#define _reRacemanItf	raceEngineInfo.itf.racemanItf
#define _reTrackItf	raceEngineInfo.itf.trackItf
#define _reGraphicItf	raceEngineInfo.itf.graphicItf
#define _reSimItf	raceEngineInfo.itf.simItf
#define _reGameScreen	raceEngineInfo.gameScreen
#define _reMenuScreen	raceEngineInfo.menuScreen
#define _reName		raceEngineInfo.name
#define _reCarInfo	raceEngineInfo.carInfo
#define _reCurTime	raceEngineInfo.curTime
#define _reTimeMult	raceEngineInfo.timeMult
#define _reRunning	raceEngineInfo.running
#define _reLastTime	raceEngineInfo.lastTime

/* Lap based information */
typedef struct
{
    int		pos;		/* driver position */
    tdble	lapTime;	/* lap time */
    int		lapsBehind;	/* laps behind leader */
    int		event;		/* special event */
#define RM_EVENT_PIT_STOP	0x01
    void	*eventData;	/* event specific data */
} tDrvLapInfo;


/*
 * Race Manager General Info
 */
typedef struct RmInfo
{
    tCarElt		*carList;	/* List of all the cars racing */
    tSituation		*s;		/* Situation during race */
    tTrack		*track;		/* Current track */
    void		*params;	/* Raceman parameters */
    tModList		**modList;	/* drivers loaded */
    tDrvLapInfo 	*lapInfo;	/* per lap driver info using start index */
    tRaceEngineInfo	raceEngineInfo;
} tRmInfo;

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



