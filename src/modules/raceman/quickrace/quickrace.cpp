/***************************************************************************

    file                 : quickrace.cpp
    created              : Sun Jan 30 22:42:04 CET 2000
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
#include <tgf.h>
#include <osspec.h>

#include "qracemain.h"

#ifdef _WIN32
BOOL WINAPI DllEntryPoint (HINSTANCE hDLL, DWORD dwReason, LPVOID Reserved)
{
    return TRUE;
}
#endif

static void
qrStart(void *backmenu)
{
    GfuiScreenDeactivate();
    qrMenuRun(backmenu);
}


/*
 * Function
 *	qraceInit
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
qraceInit(int index, void *p)
{
    tRacemanItf *itf = (tRacemanItf*)p;
    
    itf->start = qrStart;
    
    return 0;
}


/*
 * Function
 *	quickrace
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
quickrace(tModInfo *modInfo)
{
    modInfo->name = "Quick Race";	/* name of the module (short) */
    modInfo->desc = "Race Without practice nor qualification sessions";	/* description of the module (can be long) */
    modInfo->fctInit = qraceInit;	/* init function */
    modInfo->gfId = 0;			/* always loaded  */
    modInfo->index = 0;
    modInfo->prio = 10;			/* First */
    
    return 0;
}


