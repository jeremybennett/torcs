/***************************************************************************
                  trackselect.cpp -- interactive track selection                                      
                             -------------------                                         
    created              : Mon Aug 16 21:43:00 CEST 1999
    copyright            : (C) 1999 by Eric Espie                         
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
    @ingroup	racemantools
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <tgf.h>
#include <track.h>
#include <osspec.h>
#include <racemantools.h>


static tFList		*FileList;
static void		*scrHandle;
static int		TrackLabelId;
static tRmTrackSelect	*ts;

static void
rmtsActivate(void * /* dummy */)
{
    /* call display function of graphic */
}

static void
rmtsDeactivate(void * /* dummy */)
{
    
    GfuiScreenRelease(scrHandle);
    
    if (ts->prevScreen) {
	GfuiScreenActivate(ts->prevScreen);
    }
}

static void
rmtsPrevNext(void *vsel)
{
    if ((int)vsel == 0) {
	FileList = FileList->prev;
    } else {
	FileList = FileList->next;
    }
    GfuiLabelSetText(scrHandle, TrackLabelId, FileList->dispName);
    /* Change the track draw here */
}

static void
rmtsSelect(void *dummy)
{

    GfParmSetStr(ts->param, "Race", "track", FileList->name);

    rmtsDeactivate(NULL);
}

static void
rmtsAddKeys(void)
{
    GfuiAddKey(scrHandle, 13, "Select Track", NULL, rmtsSelect);
    GfuiAddKey(scrHandle, 27, "Cancel Selection", NULL, rmtsDeactivate);
    GfuiAddSKey(scrHandle, GLUT_KEY_LEFT, "Previous Track", (void*)0, rmtsPrevNext);
    GfuiAddSKey(scrHandle, GLUT_KEY_RIGHT, "Next Track", (void*)1, rmtsPrevNext);
    GfuiAddSKey(scrHandle, GLUT_KEY_F12, "Screen-Shot", NULL, GfuiScreenShot);
    
}

/** Get the track name
    @param	trackName	track name for file
    @return	Long track name
 */
char *
RmGetTrackName(char *trackName)
{
    char	buf[256];
    void	*trackHandle;
    char	*name;
    
    sprintf(buf, "tracks/%s/%s.%s", trackName, trackName, TRKEXT);
    trackHandle = GfParmReadFile(buf, GFPARM_RMODE_STD);
    if (trackHandle) {
	name = GfParmGetStr(trackHandle, TRK_SECT_HDR, TRK_ATT_NAME, trackName);
/* 	GfParmReleaseHandle(trackHandle); */
    } else {
	GfTrace1("File %s has pb\n", buf);
	return "";
    }
    return name;
}

/** Interactive track selection
    @param	vs	Pointer on a tRmTrackSelect structure (cast to void *)
    @warning	The race manager's parameters are updated but not saved.
 */
void
RmTrackSelect(void *vs)
{
    char		*defaultTrack;
    tFList		*FLCur;
    
    ts = (tRmTrackSelect*)vs;

    FileList = GfDirGetList("tracks");
    if (FileList == NULL) {
	return;
    }
    FLCur = FileList;
    do {
	FLCur->dispName = RmGetTrackName(FLCur->name);
	FLCur = FLCur->next;
    } while (FLCur != FileList);

    defaultTrack = GfParmGetStr(ts->param, "Race", "track", FileList->name);

    FLCur = FileList;
    do {
	if (strcmp(FLCur->name, defaultTrack) == 0) {
	    FileList = FLCur;
	    break;
	}
	FLCur = FLCur->next;
    } while (FLCur != FileList);
    
    scrHandle = GfuiScreenCreateEx((float*)NULL, NULL, rmtsActivate, NULL, (tfuiCallback)NULL, 1);
    GfuiScreenAddBgImg(scrHandle, "data/img/splash-qrtrk.png");

    rmtsAddKeys();

    GfuiTitleCreate(scrHandle, "Select Track", strlen("Select Track"));

    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-left.png",
		       "data/img/arrow-left.png",
		       "data/img/arrow-left.png",
		       "data/img/arrow-left-pushed.png",
		       80, 400, GFUI_ALIGN_HC_VB, 0,
		       (void*)0, rmtsPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);


    TrackLabelId = GfuiLabelCreate(scrHandle,
				   FileList->dispName,
				   GFUI_FONT_LARGE,
				   320, 400, GFUI_ALIGN_HC_VB,
				   30);

    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right-pushed.png",
		       540, 400, GFUI_ALIGN_HC_VB, 0,
		       (void*)1, rmtsPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiMenuBackQuitButtonCreate(scrHandle, "Select", "Select the track", NULL, rmtsSelect);
    
    GfuiScreenActivate(scrHandle);
}
