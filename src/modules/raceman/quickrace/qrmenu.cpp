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
#include "qracemain.h"
#include <osspec.h>

void			*qrMainMenuHandle = NULL;
static tRmTrackSelect	ts;
static void 		*qrPrevMenuHandle;
static int		qrTitleId;

static void
qrSelectTrack(void *dummy)
{
    RmTrackSelect((void*)&ts);
}

static void
qrMenuOnActivate(void *dummy)
{
    char	buf[256];
    char	*trackName;
    
    qrLoadTrackModule();
    ts.param = GfParmReadFile(QRACE_CFG, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    GfParmWriteFile(QRACE_CFG, ts.param, "quick race", GFPARM_PARAMETER, "../../dtd/params.dtd");

    trackName = GfParmGetStr(ts.param, "Race", "track", "");

    GfOut("track name = %s\n", trackName);
    sprintf(buf, "tracks/%s/%s.%s", trackName, trackName, TRKEXT);
    /* TODO free the previous track */
    qrTheTrack = qrTrackItf.trkBuild(buf);

    sprintf(buf, "%s", qrTheTrack->name);
    GfuiLabelSetText(qrMainMenuHandle, qrTitleId, buf);
}


void
qrMenuRun(void *backmenu)
{
    char buf[256];
    
    qrPrevMenuHandle = backmenu;
    
    if (qrMainMenuHandle == NULL) {
	qrMainMenuHandle = GfuiScreenCreateEx((float*)NULL, 
					      NULL, qrMenuOnActivate, 
					      NULL, (tfuiCallback)NULL, 
					      1);
	GfuiScreenAddBgImg(qrMainMenuHandle, "data/img/splash-qr.png");

	GfuiMenuDefaultKeysAdd(qrMainMenuHandle);
	sprintf(buf, "Torcs Quick Race");
	GfuiTitleCreate(qrMainMenuHandle, buf, strlen(buf));
	qrTitleId = GfuiLabelCreate(qrMainMenuHandle, buf, GFUI_FONT_LARGE,
				 320, 420, GFUI_ALIGN_HC_VB, 50);

	GfuiMenuButtonCreate(qrMainMenuHandle,
			  "Race", "Launch a Quick Race",
			  NULL, qraceRun);
    
	ts.prevScreen = qrMainMenuHandle;
	GfuiMenuButtonCreate(qrMainMenuHandle, 
			  "Select Track", "Select a Track for Quick Race",
			  NULL, qrSelectTrack);

	GfuiMenuButtonCreate(qrMainMenuHandle, 
			  "Select Drivers", "Select the List of Drivers for Quick Race",
			  (void*)(&ts), RmDriversSelect);
    
	GfuiMenuBackQuitButtonCreate(qrMainMenuHandle,
				  "Back to Main", "Return to TORCS Main Menu",
				  qrPrevMenuHandle, GfuiScreenActivate);
    }
    
    GfuiScreenActivate(qrMainMenuHandle);
}

