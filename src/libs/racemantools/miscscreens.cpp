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

static void *confirmHdle = 0;

/** Confirmation (yes/no) screen.
    @param	question	Screen title.
    @param	yesLabel	Label string for the "yes" button.
    @param	yesTip		Tip string for the "yes" button.
    @param	yesScreen	Screen to activate if "yes" is choosen.
    @param	noLabel		Label string for the "no" button.
    @param	noTip		Tip string for the "no" button.	
    @param	noScreen	Screen to activate if "no" is choosen.
    @param	yesFirst	if set to "1" the order is yes/no else it is no/yes.
*/
void
RmConfirmScreen(char *question,
		char *yesLabel, char *yesTip, void *yesScreen,
		char *noLabel, char *noTip, void *noScreen,
		int yesFirst)
{
    if (confirmHdle) {
	GfuiScreenRelease(confirmHdle);
    }

    confirmHdle = GfuiMenuScreenCreate(question);
    GfuiScreenAddBgImg(confirmHdle, "data/img/splash-quit.png");

    if (yesFirst) {
	GfuiMenuButtonCreate(confirmHdle,
			     yesLabel,
			     yesTip,
			     yesScreen,
			     GfuiScreenActivate);
    
	GfuiMenuButtonCreate(confirmHdle,
			     noLabel,
			     noTip,
			     noScreen,
			     GfuiScreenActivate);
	GfuiAddKey(confirmHdle, 27, noTip, noScreen, GfuiScreenActivate);

    } else {

	GfuiMenuButtonCreate(confirmHdle,
			     noLabel,
			     noTip,
			     noScreen,
			     GfuiScreenActivate);

	GfuiMenuButtonCreate(confirmHdle,
			     yesLabel,
			     yesTip,
			     yesScreen,
			     GfuiScreenActivate);
	GfuiAddKey(confirmHdle, 27, yesTip, yesScreen, GfuiScreenActivate);
    }
    

    GfuiScreenActivate(confirmHdle);
}
