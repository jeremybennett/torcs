/***************************************************************************

    file                 : practice.h
    created              : Sun Jan 30 22:53:28 CET 2000
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
 
 
#ifndef _PRACTICE_H__
#define _PRACTICE_H__

#include <ttypes.h>
#include <track.h>
#include <car.h>
#include <simu.h>
#include <graphic.h>
#include <telemetry.h>
#include <robot.h>
#include <racemantools.h>
#include <practicectrl.h>




typedef struct 
{
    tTrkLocPos	prevTrkPos;
    tdble	sTime;
    int		lapFlag;
    tdble	topSpd;
    tdble	botSpd;
    tdble	fuel;
} tprCarInfo;

extern void		*prMainMenuHandle;
extern void 		*prPrevMenuHandle;
extern tPractCtrlItf	*prCtrlItf;
extern tGraphicItf	prGraphicItf;
extern tSituation 	prTheSituation;
extern tTrack		*prTheTrack;
extern tModList		*prCtrlModLoaded;
extern int prShowRace;


extern void prMenuRun(void *backmenu);

extern void prRun(void);
extern void prEndSession(void);

extern void prLoadTrackModule(void);
extern void prStart(void);
extern void prStop(void);
extern void prUpdate(void);
extern void prUpdateBlind(void);
extern void prShutdown(void);


extern void praceglRun(void);
extern void praceglShutdown(void);

#endif /* _PRACTICE_H__ */ 



