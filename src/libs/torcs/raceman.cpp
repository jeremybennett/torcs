/***************************************************************************

    file                 : raceman.cpp
    created              : Sat Mar 18 23:43:05 CET 2000
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
#include <tgf.h>
#include <raceman.h>

#include "raceman.h"
#include "mainmenu.h"

typedef struct 
{
    int		index;
    tModList	*curmod;
} tMainMod;

static void
lauchRaceman(void *vmod)
{
    tMainMod	*mod = (tMainMod*)vmod;
    tModList	*curmod = mod->curmod;
    tRacemanItf	*racemanItf;

    GfModLoad(0, curmod->sopath, &RacemanModLoaded);
    if (RacemanModLoaded != NULL) {
	racemanItf = (tRacemanItf*)calloc(1, sizeof(tRacemanItf));
	RacemanModLoaded->modInfo[mod->index].fctInit(mod->index, (void*)(racemanItf));
	racemanItf->start(menuHandle);
    }
}

/*
 * Function
 *	TorcsLoadRaceMan
 *
 * Description
 *	load race manager modules
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
void
TorcsLoadRaceMan(void)
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
		if (curmod->modInfo[i].name) {
		    mainMod = (tMainMod*)calloc(1, sizeof(tMainMod));
		    mainMod->index  = i;
		    mainMod->curmod = curmod;
		    
		    GfuiMenuButtonCreate(menuHandle,
					 curmod->modInfo[i].name,
					 curmod->modInfo[i].desc,
					 (void*)mainMod,
					 lauchRaceman);
		}
	    }
	} while (curmod != list);
    }
}




