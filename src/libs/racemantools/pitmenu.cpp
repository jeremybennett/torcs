/***************************************************************************

    file                 : pitmenu.cpp
    created              : Mon Apr 24 18:16:37 CEST 2000
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

/** @file   
    		Pit menu command
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/
#include <stdlib.h>
#include <tgf.h>
#include <car.h>

static void		*menuHandle;
static int		fuelId;
static int		repairId;
static tCarElt		*rmCar;

static void
rmUpdtFuel(void * /* dummy */)
{
    char	*val;
    char	buf[32];
    
    val = GfuiEditboxGetString(menuHandle, fuelId);
    rmCar->pitcmd->fuel = (tdble)strtol(val, (char **)NULL, 0);
    sprintf(buf, "%f", rmCar->pitcmd->fuel);
    GfuiEditboxSetString(menuHandle, fuelId, buf);
    free(val);
}

static void
rmUpdtRepair(void * /* dummy */)
{
    char	*val;
    char	buf[32];
    
    val = GfuiEditboxGetString(menuHandle, repairId);
    rmCar->pitcmd->repair = strtol(val, (char **)NULL, 0);
    sprintf(buf, "%d", rmCar->pitcmd->repair);
    GfuiEditboxSetString(menuHandle, repairId, buf);
    free(val);
}

void
RmPitMenuStart(tCarElt *car, void *userdata, tfuiCallback callback)
{
    char	buf[256];
    int		y, x, dy;

    rmCar = car;
    menuHandle = GfuiMenuScreenCreate("Pit Stop Info");

    x = 80;
    y = 380;
    sprintf(buf, "Driver: %s", car->_name);
    GfuiLabelCreate(menuHandle, buf, GFUI_FONT_LARGE, x, y, GFUI_ALIGN_HL_VB, 0);
    dy = GfuiFontHeight(GFUI_FONT_LARGE) + 5;

    y -= dy;
    sprintf(buf, "Remaining Laps: %d", car->_remainingLaps);
    GfuiLabelCreate(menuHandle, buf, GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);

    y -= dy;
    sprintf(buf, "Remaining Fuel: %.1f l", car->_fuel);
    GfuiLabelCreate(menuHandle, buf, GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);

    y -= dy;
    GfuiLabelCreate(menuHandle, "Fuel amount (liters):", GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);

    sprintf(buf, "%d", (int)car->pitcmd->fuel);
    fuelId = GfuiEditboxCreate(menuHandle, buf, GFUI_FONT_MEDIUM_C,
			       x + GfuiFontWidth(GFUI_FONT_MEDIUM_C, "Fuel amount (liters):") + 20, y,
			       0, 10, NULL, (tfuiCallback)NULL, rmUpdtFuel);

    y -= dy;
    GfuiLabelCreate(menuHandle, "Repair amount:", GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);

    sprintf(buf, "%d", (int)car->pitcmd->repair);
    repairId = GfuiEditboxCreate(menuHandle, buf, GFUI_FONT_MEDIUM_C,
				 x + GfuiFontWidth(GFUI_FONT_MEDIUM_C, "Repair amount:") + 20, y,
				 0, 10, NULL, (tfuiCallback)NULL, rmUpdtRepair);
    
    GfuiMenuBackQuitButtonCreate(menuHandle, "Proceed", "Return to race", userdata, callback);

    GfuiScreenActivate(menuHandle);
}
