/***************************************************************************

    file                 : practice.cpp
    created              : Sun Jan 30 22:53:18 CET 2000
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
#include <osspec.h>

#include <raceman.h>

#include "practice.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

#ifdef _WIN32
BOOL WINAPI DllEntryPoint (HINSTANCE hDLL, DWORD dwReason, LPVOID Reserved)
{
    return TRUE;
}
#endif

/*
 * Function
 *	prStart
 *
 * Description
 *	Called when the practice mode is selected by user
 *
 * Parameters
 *	menu to go back at the end
 *
 * Return
 *	none
 */
static void
prStart(void *backmenu)
{
    GfuiScreenDeactivate();	/* deactivate previous menu screen */
    prMenuRun(backmenu);	/* call the practice menu */
}


/*
 * Function
 *	prInit
 *
 * Description
 *	init the menus
 *
 * Parameters
 *	
 *
 * Return
 *	
 *
 * Remarks
 *	
 */
static int
prInit(int index, void *p)
{
    tRacemanItf *itf = (tRacemanItf*)p;
    
    itf->start = prStart;
    
    return 0;
}


/*
 * Function
 *	practice
 *
 * Description
 *	Entry point of the module
 *
 * Parameters
 *	pointer on info structure
 *
 * Return
 *	0 if ok
 *     -1 if error
 */
extern "C" int
practice(tModInfo *modInfo)
{
    modInfo->name = "Practice";	/* name of the module (short) */
    modInfo->desc = "Practice Sessions";	/* description of the module (can be long) */
    modInfo->fctInit = prInit;	/* init function */
    modInfo->gfId = 0;		/* always loaded  */
    modInfo->index = 0;
    modInfo->prio = 1000;	/* in order to be listed at the end */
    
    return 0;
}


