/***************************************************************************

    file                 : optionmenu.cpp
    created              : Mon Apr 24 14:22:53 CEST 2000
    copyright            : (C) 2000, 2001 by Eric Espie
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

#include <stdio.h>
#include <tgf.h>
#include "optionmenu.h"
#include "driverconfig.h"
#include "joystickconfig.h"

void *
TorcsOptionOptionInit(void *precMenu)
{
    void *optionHandle;
    void *playerHandle;
    void *JoystickHandle;

    optionHandle = GfuiMenuScreenCreate("OPTIONS");

    GfuiScreenAddBgImg(optionHandle, "data/img/splash-options.png");

    GfuiMenuButtonCreate(optionHandle,
			 "Graphic", "Configure graphic parameters",
			 GfScrMenuInit(optionHandle), GfuiScreenActivate);
    
    JoystickHandle = TorcsJoystick1MenuInit(optionHandle);
    playerHandle = TorcsDriverMenuInit(optionHandle);

    if (JoystickHandle) {
	GfuiMenuButtonCreate(optionHandle,
			     "Player", "Configure player parameters",
			     playerHandle, GfuiScreenActivate);
	GfuiMenuButtonCreate(optionHandle,
			     "Joystick", "Configure joystick parameters",
			     JoystickHandle, GfuiScreenActivate);
	
    }
    
    GfuiMenuBackQuitButtonCreate(optionHandle,
				 "Back",
				 "Back to Main",
				 precMenu,
				 GfuiScreenActivate);

    return optionHandle;
}
