/***************************************************************************

    file                 : racemenu.cpp
    created              : Thu May  2 22:02:51 CEST 2002
    copyright            : (C) 2001 by Eric Espie
    email                : eric.espie@torcs.org
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

/** @file   
    		This is the race options menu.
    @ingroup	racemantools
    @author	<a href=mailto:eric.espie@torcs.org>Eric Espie</a>
    @version	$Id$
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>
#include <track.h>
#include <car.h>
#include <raceman.h>
#include <robot.h>
#include <racemantools.h>

static void		*scrHandle;
static tRmRaceParam	*rp;
static int		rmrpDistance;
static int		rmrpLaps;
static char		buf[256];
static int		rmrpDistId;
static int		rmrpLapsId;


static void
rmrpDeactivate(void *screen)
{
    GfuiScreenRelease(scrHandle);
    
    if (screen) {
	GfuiScreenActivate(screen);
    }
}

static void
rmrpUpdDist(void * /* dummy */)
{
    char	*val;

    val = GfuiEditboxGetString(scrHandle, rmrpDistId);
    rmrpDistance = strtol(val, (char **)NULL, 0);
    if (rmrpDistance == 0) {
	strcpy(buf, "---");
    } else {
	sprintf(buf, "%d", rmrpDistance);
	rmrpLaps = 0;
	GfuiEditboxSetString(scrHandle, rmrpLapsId, "---");
    }
    GfuiEditboxSetString(scrHandle, rmrpDistId, buf);
}

static void
rmrpUpdLaps(void * /* dummy */)
{
    char	*val;

    val = GfuiEditboxGetString(scrHandle, rmrpLapsId);
    rmrpLaps = strtol(val, (char **)NULL, 0);
    if (rmrpLaps == 0) {
	strcpy(buf, "---");
    } else {
	sprintf(buf, "%d", rmrpLaps);
	rmrpDistance = 0;
	GfuiEditboxSetString(scrHandle, rmrpDistId, "---");
    }
    GfuiEditboxSetString(scrHandle, rmrpLapsId, buf);
}


static void
rmrpValidate(void * /* dummy */)
{
    if (rp->confMask & RM_CONF_RACE_LEN) {
	rmrpUpdDist(0);
	rmrpUpdLaps(0);
	GfParmSetNum(rp->param, rp->title, RM_ATTR_DISTANCE, "km", rmrpDistance);
	GfParmSetNum(rp->param, rp->title, RM_ATTR_LAPS, (char*)NULL, rmrpLaps);
    }
    rmrpDeactivate(rp->nextScreen);
}

static void
rmrpAddKeys(void)
{
    GfuiAddKey(scrHandle, 27, "Cancel Modifications", rp->prevScreen, rmrpDeactivate);
    GfuiAddSKey(scrHandle, GLUT_KEY_F1, "Help", scrHandle, GfuiHelpScreen);
    GfuiAddSKey(scrHandle, GLUT_KEY_F12, "Screen-Shot", NULL, GfuiScreenShot);
    GfuiAddKey(scrHandle, 13, "Validate Modifications", NULL, rmrpValidate);
}

void
RmRaceParamMenu(void *vrp)
{
    int		y, x, dy, dx;

    rp = (tRmRaceParam*)vrp;

    sprintf(buf, "%s Options", rp->title);
    scrHandle = GfuiMenuScreenCreate(buf);
    GfuiScreenAddBgImg(scrHandle, "data/img/splash-raceopt.png");
    
    x = 80;
    y = 380;
    dx = 200;
    dy = GfuiFontHeight(GFUI_FONT_LARGE) + 5;

    if (rp->confMask & RM_CONF_RACE_LEN) {
	GfuiLabelCreate(scrHandle, "Race Distance (km):", GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);
	rmrpDistance = (int)GfParmGetNum(rp->param, rp->title, RM_ATTR_DISTANCE, "km", 0);
	if (rmrpDistance == 0) {
	    strcpy(buf, "---");
	    rmrpLaps = (int)GfParmGetNum(rp->param, rp->title, RM_ATTR_LAPS, NULL, 25);
	} else {
	    sprintf(buf, "%d", rmrpDistance);
	    rmrpLaps = 0;
	}
	rmrpDistId = GfuiEditboxCreate(scrHandle, buf, GFUI_FONT_MEDIUM_C,
				       x + dx, y,
				       0, 8, NULL, (tfuiCallback)NULL, rmrpUpdDist);

	y -= dy;
	GfuiLabelCreate(scrHandle, "Laps:", GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);
	if (rmrpLaps == 0) {
	    strcpy(buf, "---");
	} else {
	    sprintf(buf, "%d", rmrpLaps);
	}
	rmrpLapsId = GfuiEditboxCreate(scrHandle, buf, GFUI_FONT_MEDIUM_C,
				       x + dx, y,
				       0, 8, NULL, (tfuiCallback)NULL, rmrpUpdLaps);
    }
    
    GfuiButtonCreate(scrHandle, "Accept", GFUI_FONT_LARGE, 210, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, rmrpValidate, NULL, NULL, NULL);

    GfuiButtonCreate(scrHandle, "Cancel", GFUI_FONT_LARGE, 430, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     rp->prevScreen, rmrpDeactivate, NULL, NULL, NULL);

    rmrpAddKeys();
    
    GfuiScreenActivate(scrHandle);
}
