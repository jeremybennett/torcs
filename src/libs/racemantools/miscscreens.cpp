/***************************************************************************

    file        : miscscreens.cpp
    created     : Sun Dec  8 13:01:47 CET 2002
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

#include <stdio.h>
#include <tgf.h>

#include <racemantools.h>

static void *twoStateHdle = 0;
static void *triStateHdle = 0;


void
RmTwoStateScreen(char *title,
		 char *label1, char *tip1, void *screen1,
		 char *label2, char *tip2, void *screen2)
{
    if (twoStateHdle) {
	GfuiScreenRelease(twoStateHdle);
    }
    twoStateHdle = GfuiMenuScreenCreate(title);
    GfuiScreenAddBgImg(twoStateHdle, "data/img/splash-quit.png");

    GfuiMenuButtonCreate(twoStateHdle,
			 label1, tip1, screen1,
			 GfuiScreenActivate);

    GfuiMenuButtonCreate(twoStateHdle,
			 label2, tip2, screen2,
			 GfuiScreenActivate);

    GfuiAddKey(twoStateHdle, 27, tip2, screen2, GfuiScreenActivate);

    GfuiScreenActivate(twoStateHdle);
}


void
RmTriStateScreen(char *title,
		 char *label1, char *tip1, void *screen1,
		 char *label2, char *tip2, void *screen2,
		 char *label3, char *tip3, void *screen3)
{
    if (triStateHdle) {
	GfuiScreenRelease(triStateHdle);
    }
    triStateHdle = GfuiMenuScreenCreate(title);
    GfuiScreenAddBgImg(triStateHdle, "data/img/splash-quit.png");

    GfuiMenuButtonCreate(triStateHdle,
			 label1, tip1, screen1,
			 GfuiScreenActivate);

    GfuiMenuButtonCreate(triStateHdle,
			 label2, tip2, screen2,
			 GfuiScreenActivate);

    GfuiMenuButtonCreate(triStateHdle,
			 label3, tip3, screen3,
			 GfuiScreenActivate);
    


    GfuiAddKey(triStateHdle, 27, tip3, screen3, GfuiScreenActivate);

    GfuiScreenActivate(triStateHdle);
}
