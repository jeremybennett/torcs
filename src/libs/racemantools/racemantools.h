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
    void        *param;		/* Race manager parameters where to set the selected track */
    void        *prevScreen;	/* Race manager screen to go back */
    void        *nextScreen;	/* Race manager screen to go after select */
    tTrackItf	trackItf;	/* Track module interface */
} tRmTrackSelect;

typedef struct
{
    void        *param;
    void        *prevScreen;	/* Race manager screen to go back */
    void        *nextScreen;	/* Race manager screen to go after select */
} tRmDrvSelect;

typedef struct
{
    void        *param;
    void        *prevScreen;
    void        *nextScreen;	/* Race manager screen to go after select */
    char	*title;
} tRmRaceParam;




extern void RmTrackSelect(void * /* vs */);
extern char *RmGetTrackName(char * /* category */, char * /* trackName */);

extern void RmDumpTrack(tTrack * /* track */, int /* verbose */);
extern int RmInitCars(tRmInfo * /* raceInfo */);
extern int RmInitTrack(tRmInfo * /* raceInfo */);

extern void RmDriversSelect(void * /* vs */);
extern void RmDriverSelect(void * /* vs */);

extern void RmPracticeResults(void * /* prevHdle */, char * /* trackname */, tRingListHead * /* res */);

extern void RmPitMenuStart(tCarElt * /* car */, void * /* userdata */, tfuiCallback /* callback */);

extern void RmLoadingScreenStart(char * /* text */, char * /* bgimg */);
extern void RmLoadingScreenSetText(char * /* text */);

extern int RmInitResults(tRmInfo * /* rmInfo */);
extern void RmShutdownResults(tRmInfo * /* rmInfo */);
extern void RmSaveResults(tRmInfo *rmInfo);
extern void RmShowResults(void */* prevHdle */, tRmInfo */* info */);

extern void RmConfirmScreen(char *question,
			    char *yesLabel, char *yesTip, void *yesScreen,
			    char *noLabel, char *noTip, void *noScreen,
			    int yesFirst);

extern void RmRaceParamMenu(void *vrp);


#endif /* __RACEMANTOOLS_H__ */

