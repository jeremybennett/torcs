/***************************************************************************

    file                 : prmenu.cpp
    created              : Sun Jan 30 22:54:05 CET 2000
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <racemantools.h>
#include <osspec.h>
#include <track.h>
#include <practicectrl.h>

#include "practice.h"

void			*prMainMenuHandle = NULL;
static tRmTrackSelect	ts;
void 			*prPrevMenuHandle;
static int		prTitleId;
tModList		*prCtrlModLoaded = (tModList*)NULL;
tPractCtrlItf		*prCtrlItf;

typedef struct 
{
    int		index;
    tModList	*curmod;
} tMainMod;

static tPracticeFct practiceFct;


static void
prMenuOnDeactivate(void *dummy)
{
}

static void
prMenuOnActivate(void *dummy)
{
    char	*trackName;

    if (prCtrlModLoaded != NULL) {
	GfModUnloadList(&prCtrlModLoaded);
    }

    ts.param = GfParmReadFile(PRACTICE_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    trackName = GfParmGetStr(ts.param, "Race", "track", "");
    GfOut("track name = %s\n", trackName);
    trackName = RmGetTrackName(trackName);
    GfuiLabelSetText(prMainMenuHandle, prTitleId, trackName);
}

static void
prInitControl(void *vmod)
{
    tMainMod		*mod = (tMainMod*)vmod;
    tModList		*curmod = mod->curmod;

    GfModLoad(0, curmod->sopath, &prCtrlModLoaded);
    if (prCtrlModLoaded != NULL) {
	prCtrlItf = (tPractCtrlItf*)calloc(1, sizeof(tPractCtrlItf));
	prCtrlModLoaded->modInfo[mod->index].fctInit(mod->index, (void*)(prCtrlItf));
	GfuiScreenDeactivate();
	practiceFct.run = prRun;
	practiceFct.backMenu = prMainMenuHandle;
	prCtrlItf->startCtrl(&practiceFct);
    }
}

/*
 * Function
 *	prListControls
 *
 * Description
 *	list practice control modules
 *
 * Parameters
 *	none
 *
 * Return
 *	none
 *
 * Remarks
 *	
 */
static void
prListControls(void)
{
    tModList	*list;
    tModList	*curmod;
    tMainMod	*mainMod;
    int		i;
    
    list = (tModList *)NULL;
    GfModInfoDir(0, "modules/raceman/practice/control", 0, &list);
    
    curmod = list;
    if (curmod != NULL) {
	do {
	    curmod = curmod->next;
	    for (i = 0; i < MAX_MOD_ITF; i++) {
		if (curmod->modInfo[i].name) {
		    mainMod = (tMainMod*)calloc(1, sizeof(tMainMod));
		    mainMod->index  = i;
		    mainMod->curmod = curmod;
		    
		    GfuiMenuButtonCreate(prMainMenuHandle,
					 curmod->modInfo[i].name,
					 curmod->modInfo[i].desc,
					 (void*)mainMod,
					 prInitControl);
		}
	    }
	} while (curmod != list);
    }
}

void
prMenuRun(void *backmenu)
{
    char buf[256];
    
    prPrevMenuHandle = backmenu;
    
    if (prMainMenuHandle == NULL) {
	prMainMenuHandle = GfuiScreenCreateEx((float*)NULL, 
					      NULL, prMenuOnActivate, 
					      NULL, prMenuOnDeactivate, 
					      1);
	GfuiScreenAddBgImg(prMainMenuHandle, "data/img/splash-practice.png");

	GfuiMenuDefaultKeysAdd(prMainMenuHandle);
	sprintf(buf, "Torcs Practice Mode");
	GfuiTitleCreate(prMainMenuHandle, buf, strlen(buf));
	prTitleId = GfuiLabelCreate(prMainMenuHandle, buf, GFUI_FONT_LARGE,
				    320, 420, GFUI_ALIGN_HC_VB, 50);

	prListControls();
    
	ts.prevScreen = prMainMenuHandle;
	GfuiMenuButtonCreate(prMainMenuHandle, 
			     "Select Other Track", "Select a Track for Practice",
			     (void*)&ts, RmTrackSelect);

	GfuiMenuButtonCreate(prMainMenuHandle, 
			  "Select Driver", "Select the  Driver for Practice",
			  (void*)&ts, RmDriverSelect);
    
	GfuiMenuBackQuitButtonCreate(prMainMenuHandle,
				  "Back to Main", "Return to TORCS Main Menu",
				  prPrevMenuHandle, GfuiScreenActivate);
    }
    
    GfuiScreenActivate(prMainMenuHandle);
}

