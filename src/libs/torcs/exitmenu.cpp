/***************************************************************************

    file                 : exitmenu.cpp
    created              : Sat Mar 18 23:42:12 CET 2000
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


#include <profiler.h>

#include <stdio.h>
#include <tgf.h>
#include "exitmenu.h"
#include "mainmenu.h"

static void 
endofprog(void *dummy)
{
    STOP_ACTIVE_PROFILES();
    PRINT_PROFILE();
/*     glutSetKeyRepeat(GLUT_KEY_REPEAT_ON); */
    exit(0);
}

static void *exitmenuHandle = NULL;

/*
 * Function
 *	TorcsExitMenuInit
 *
 * Description
 *	init the exit menus
 *
 * Parameters
 *	none
 *
 * Return
 *	0 ok -1 nok
 *
 * Remarks
 *	
 */
void *
TorcsExitMenuInit(void *mainMenu)
{
    if (exitmenuHandle) return exitmenuHandle;

    exitmenuHandle = GfuiMenuScreenCreate("Quit ?");
    GfuiScreenAddBgImg(exitmenuHandle, "data/img/splash-quit.png");

    GfuiMenuButtonCreate(exitmenuHandle,
		      "No, Back to Game",
		      "Return to TORCS",
		      mainMenu,
		      GfuiScreenActivate);
    
    GfuiMenuButtonCreate(exitmenuHandle,
		      "Yes, Let's Quit",
		      "Exit of TORCS",
		      NULL,
		      endofprog);
    return exitmenuHandle;
}

