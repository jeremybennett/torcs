/***************************************************************************

    file        : raceinit.cpp
    created     : Sat Nov 16 10:34:35 CET 2002
    copyright   : (C) 2002 by Eric Espié                        
    email       : eric.espie@torcs.org   
    version     : $Id$                                  

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
    		
    @author	<a href=mailto:eric.espie@torcs.org>Eric Espie</a>
    @version	$Id$
*/


/* Race initialization routines */

#include <stdlib.h>
#include <stdio.h>
#include <tgf.h>
#include <raceman.h>
#include <robot.h>
#include <racemantools.h>

#include "racemain.h"
#include "racestate.h"
#include "racegl.h"

#include "raceinit.h"

static tModList *racemanModLoaded = 0;
static tModList *reEventModList = 0;
tModList *ReRaceModList = 0;

typedef struct 
{
    int		index;
    tModList	*curmod;
} tMainMod;

/* Race Engine Initialization */
void
ReInit(void)
{
    char	*dllname;
    char	key[256];

    //ReShutdown();

    ReInfo = (tRmInfo *)calloc(1, sizeof(tRmInfo));
    ReInfo->s = (tSituation *)calloc(1, sizeof(tSituation));
    ReInfo->modList = &ReRaceModList;
    ReInfo->_reParam = GfParmReadFile(RACE_ENG_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    GfOut("Loading Track Loader...\n");
    dllname = GfParmGetStr(ReInfo->_reParam, "Modules", "track", "");
    sprintf(key, "modules/track/%s.%s", dllname, DLLEXT);
    if (GfModLoad(0, key, &reEventModList)) return;
    reEventModList->modInfo->fctInit(reEventModList->modInfo->index, &ReInfo->_reTrackItf);

    GfOut("Loading Graphic Engine...\n");
    dllname = GfParmGetStr(ReInfo->_reParam, "Modules", "graphic", "");
    sprintf(key, "modules/graphic/%s.%s", dllname, DLLEXT);
    if (GfModLoad(0, key, &reEventModList)) return;
    reEventModList->modInfo->fctInit(reEventModList->modInfo->index, &ReInfo->_reGraphicItf);

    ReInfo->_reGameScreen = ReHookInit();
}

/* Race Engine Exit */
void
ReShutdown(int freeModules)
{
    /* Free previous situation */
    if (ReInfo) {
	ReInfo->_reTrackItf.trkShutdown();
	ReInfo->_reGraphicItf.shutdowntrack(); 

	GfModUnloadList(&reEventModList);

	free(ReInfo->s);
	free(ReInfo);
	ReInfo = 0;
    }

    /* Release the previously loaded modules */
    if (freeModules && (racemanModLoaded != NULL)) {
	GfModUnloadList(&racemanModLoaded);
    }
}

/* Launch a race manager */
static void
selectRaceman(void *vmod)
{
    tMainMod	*mod = (tMainMod*)vmod;
    tModList	*curmod = mod->curmod;

    GfModLoad(0, curmod->sopath, &racemanModLoaded);
    if (racemanModLoaded != NULL) {
	racemanModLoaded->modInfo[mod->index].fctInit(mod->index, &ReInfo->_reRacemanItf);
    } else {
	ReInfo->_reState = RE_STATE_ERROR;
    }
    ReStateManage();
}

/* Load race managers selection menu */
void
ReAddRacemanListButton(void *menuHandle)
{
    tModList	*list;
    tModList	*curmod;
    tMainMod	*mainMod;
    int		i;
    
    list = (tModList *)NULL;
    GfModInfoDir(0, "modules/raceman", 0, &list);
    
    curmod = list;
    if (curmod != NULL) {
	do {
	    curmod = curmod->next;
	    for (i = 0; i < MAX_MOD_ITF; i++) {
		if ((curmod->modInfo[i].name) && (curmod->modInfo[i].magic == RM_MAGIC)) {
		    mainMod = (tMainMod*)calloc(1, sizeof(tMainMod));
		    mainMod->index  = i;
		    mainMod->curmod = curmod;
		    
		    GfuiMenuButtonCreate(menuHandle,
					 curmod->modInfo[i].name,
					 curmod->modInfo[i].desc,
					 (void*)mainMod,
					 selectRaceman);
		}
	    }
	} while (curmod != list);
    }
}
