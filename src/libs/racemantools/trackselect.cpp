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
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <track.h>
#include <osspec.h>
#include <racemantools.h>

#ifdef DMALLOC
#include "dmalloc.h"
#endif

/* Tracks Categories */
static tFList		*CategoryList;
static void		*scrHandle;
static int		TrackLabelId;
static int		CatLabelId;
static tRmTrackSelect	*ts;
static char		buf[256];

static void
rmtsActivate(void * /* dummy */)
{
    /* call display function of graphic */
}

static void
rmtsFreeLists(void *vl)
{
    GfDirFreeList((tFList*)(((tFList*)vl)->userData), NULL);
}


static void
rmtsDeactivate(void * /* dummy */)
{
    
    GfuiScreenRelease(scrHandle);

    GfDirFreeList(CategoryList, rmtsFreeLists);
    if (ts->prevScreen) {
	GfuiScreenActivate(ts->prevScreen);
    }
}

static void
rmtsPrevNext(void *vsel)
{
    if ((int)vsel == 0) {
	CategoryList->userData = (void*)(((tFList*)CategoryList->userData)->prev);
    } else {
	CategoryList->userData = (void*)(((tFList*)CategoryList->userData)->next);
    }
    GfuiLabelSetText(scrHandle, TrackLabelId, ((tFList*)CategoryList->userData)->dispName);
    /* Change the track draw here */
}

static void
rmCatPrevNext(void *vsel)
{
    if ((int)vsel == 0) {
	CategoryList = CategoryList->prev;
    } else {
	CategoryList = CategoryList->next;
    }
    GfuiLabelSetText(scrHandle, CatLabelId, CategoryList->dispName);
    GfuiLabelSetText(scrHandle, TrackLabelId, ((tFList*)CategoryList->userData)->dispName);
    /* Change the track draw here */
}

 void
rmtsSelect(void *dummy)
{

    GfParmSetStr(ts->param, "Race/Track", "category", CategoryList->name);
    GfParmSetStr(ts->param, "Race/Track", "name", ((tFList*)CategoryList->userData)->name);

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
    @param	category	track category directory
    @param	trackName	track name for file
    @return	Long track name
 */
char *
RmGetTrackName(char *category, char *trackName)
{
    void	*trackHandle;
    char	*name;
    
    sprintf(buf, "tracks/%s/%s/%s.%s", category, trackName, trackName, TRKEXT);
    trackHandle = GfParmReadFile(buf, GFPARM_RMODE_STD); /* don't release, the name is used later */
    if (trackHandle) {
	name = GfParmGetStr(trackHandle, TRK_SECT_HDR, TRK_ATT_NAME, trackName);
    } else {
	GfTrace1("File %s has pb\n", buf);
	return "";
    }
    return name;
}
/** Get the track category name from the directory name
    @param	category	track category directory
    @return	category display name
*/
char *
RmGetCategoryName(char *category)
{
    void	*categoryHandle;
    char	*name;
    
    sprintf(buf, "data/tracks/%s.%s", category, TRKEXT);
    categoryHandle = GfParmReadFile(buf, GFPARM_RMODE_STD); /* don't release, the name is used later */
    if (categoryHandle) {
	name = GfParmGetStr(categoryHandle, TRK_SECT_HDR, TRK_ATT_NAME, category);
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
    char	*defaultTrack;
    char	*defaultCategory;
    tFList	*CatCur;
    tFList	*TrList, *TrCur;
    
    ts = (tRmTrackSelect*)vs;
    
    /* Get the list of categories directories */
    CategoryList = GfDirGetList("tracks");
    if (CategoryList == NULL) {
	GfTrace("RmTrackSelect: No track category available\n");
	return;
    }
    CatCur = CategoryList;
    do {
	CatCur->dispName = RmGetCategoryName(CatCur->name);
	if (strlen(CatCur->dispName) == 0) {
	    GfTrace1("RmTrackSelect: No definition for track category %s\n", CatCur->name);
	    return;
	}
	/* get the tracks in the category directory */
	sprintf(buf, "tracks/%s", CatCur->name);
	TrList = GfDirGetList(buf);
	if (TrList == NULL) {
	    GfTrace1("RmTrackSelect: No track for category %s available\n", CatCur->name);
	    return;
	}
	CatCur->userData = (void*)TrList;
	TrCur = TrList;
	do {
	    TrCur->dispName = RmGetTrackName(CatCur->name, TrCur->name);
	    if (strlen(TrCur->dispName) == 0) {
		GfTrace1("RmTrackSelect: No definition for track %s\n", TrCur->name);
		return;
	    }
	    TrCur = TrCur->next;
	} while (TrCur != TrList);
	
	CatCur = CatCur->next;
    } while (CatCur != CategoryList);

    defaultCategory = GfParmGetStr(ts->param, "Race/Track", "category", CategoryList->name);
    /* XXX coherency check */
    defaultTrack = GfParmGetStr(ts->param, "Race/Track", "name", ((tFList*)CategoryList->userData)->name);

    CatCur = CategoryList;
    do {
	if (strcmp(CatCur->name, defaultCategory) == 0) {
	    CategoryList = CatCur;
	    TrCur = (tFList*)(CatCur->userData);
	    do {
		if (strcmp(TrCur->name, defaultTrack) == 0) {
		    CatCur->userData = (void*)TrCur;
		    break;
		}
		TrCur = TrCur->next;
	    } while (TrCur != TrList);
	    break;
	}
	CatCur = CatCur->next;
    } while (CatCur != CategoryList);
    
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
		       (void*)0, rmCatPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);


    CatLabelId = GfuiLabelCreate(scrHandle,
				 CategoryList->dispName,
				 GFUI_FONT_LARGE,
				 320, 400, GFUI_ALIGN_HC_VB,
				 30);

    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right-pushed.png",
		       540, 400, GFUI_ALIGN_HC_VB, 0,
		       (void*)1, rmCatPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-left.png",
		       "data/img/arrow-left.png",
		       "data/img/arrow-left.png",
		       "data/img/arrow-left-pushed.png",
		       80, 370, GFUI_ALIGN_HC_VB, 0,
		       (void*)0, rmtsPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);


    TrackLabelId = GfuiLabelCreate(scrHandle,
				   ((tFList*)CategoryList->userData)->dispName,
				   GFUI_FONT_LARGE,
				   320, 370, GFUI_ALIGN_HC_VB,
				   30);

    GfuiGrButtonCreate(scrHandle,
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right.png",
		       "data/img/arrow-right-pushed.png",
		       540, 370, GFUI_ALIGN_HC_VB, 0,
		       (void*)1, rmtsPrevNext,
		       NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiMenuBackQuitButtonCreate(scrHandle, "Select", "Select the track", NULL, rmtsSelect);
    
    GfuiScreenActivate(scrHandle);
}
