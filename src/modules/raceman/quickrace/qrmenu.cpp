/***************************************************************************

    file                 : qrmenu.cpp
    created              : Sun Jan 30 22:41:52 CET 2000
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
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <racemantools.h>
#include <osspec.h>

#include "qracemain.h"

void			*qrMainMenuHandle = NULL;
static char		buf[256];

void
qrMenuRun(void)
{
    if (qrMainMenuHandle == NULL) {
	qrMainMenuHandle = GfuiScreenCreateEx((float*)NULL, 
					      NULL, (tfuiCallback)NULL, 
					      NULL, (tfuiCallback)NULL, 
					      1);
	GfuiScreenAddBgImg(qrMainMenuHandle, "data/img/splash-qr.png");

	GfuiMenuDefaultKeysAdd(qrMainMenuHandle);

	sprintf(buf, "Torcs Quick Race");
	GfuiTitleCreate(qrMainMenuHandle, buf, strlen(buf));

	GfuiMenuButtonCreate(qrMainMenuHandle,
			  "Race", "Launch a Quick Race",
			  RmInfo->_reGameScreen, GfuiScreenActivate);
    
	GfuiMenuButtonCreate(qrMainMenuHandle, 
			  "Configure", "Configure Quick Race",
			  NULL, qrConfigRunState);

	GfuiMenuBackQuitButtonCreate(qrMainMenuHandle,
				  "Back to Main", "Return to previous Menu",
				  RmInfo->_reMenuScreen, GfuiScreenActivate);
    }
    
    GfuiScreenActivate(qrMainMenuHandle);
}
