/***************************************************************************

    file                 : racemantools.h
    created              : Sat Mar 18 23:33:01 CET 2000
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
 
/**
    @defgroup	racemantools	Tools for race managers.
    This is a collection of useful functions for programming a race manager.
*/

#ifndef __RACEMANTOOLS_H__
#define __RACEMANTOOLS_H__

#include <car.h>
#include <raceman.h>
#include <track.h>
#include <simu.h>
#include <practicectrl.h>

typedef struct
{
    void        *param;
    void        *prevScreen;
} tRmTrackSelect;

typedef struct
{
    void        *param;
    void        *prevScreen;
} tRmDrvSelect;


/* Lap based information */
typedef struct
{
    int		drv;		/* driver start index */
    tdble	lapTime;	/* lap time */
    int		event;		/* special event */
#define RM_EVENT_PIT_STOP	0x01
    void	*eventData;	/* event specific data */
} tDrvLapInfo;


/*
 * Race Manager General Info
 * can't be in interface/raceman.h because
 * of circular reference...
 */
typedef struct
{
    tCarElt	*carList;	/* List of all the cars racing */
    tSituation	*s;		/* Situation during race */
    tTrack	*track;		/* Current track */
    tSimItf	*simItf;	/* Simulation interface */
    void	*params;	/* Raceman parameters */
    tModList	**modList;	/* drivers loaded */
    tDrvLapInfo *lapInfo;	/* per lap driver info using start index */
} tRmInfo;


extern void RmTrackSelect(void * /* vs */);
extern char *RmGetTrackName(char * /* trackName */);

extern void RmDumpTrack(tTrack * /* track */, int /* verbose */);
extern int RmInitCars(tRmInfo * /* raceInfo */);

extern void RmDriversSelect(void * /* vs */);
extern void RmDriverSelect(void * /* vs */);

extern void RmPracticeResults(void * /* prevHdle */, char * /* trackname */, tRingListHead * /* res */);

extern void RmPitMenuStart(tCarElt * /* car */, void * /* userdata */, tfuiCallback /* callback */);

extern void RmLoadingScreenStart(char * /* text */, char * /* bgimg */);
extern void RmLoadingScreenSetText(char * /* text */);

extern int RmInitResults(tRmInfo * /* rmInfo */);
extern void RmShutdownResults(tRmInfo * /* rmInfo */);


#endif /* __RACEMANTOOLS_H__ */

