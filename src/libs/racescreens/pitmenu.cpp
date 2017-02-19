/***************************************************************************

    file                 : pitmenu.cpp
    created              : Mon Apr 24 18:16:37 CEST 2000
    copyright            : (C) 2013-2017 by Eric Espie, Bernhard Wymann
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
    Pit menu
    @author Bernhard Wymann, Eric Espie
    @version $Id$
*/

#include <stdlib.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tgfclient.h>
#include <car.h>
#include <portability.h>
#include <racescreens.h>

static void *menuHandle = NULL;
static int fuelId;
static int repairId;
static tCarElt *rmCar;
static tRmInfo *rmInfo;
static int tireChangeId;

static float LabelColor[] = {1.0, 0.0, 1.0, 1.0};

// list of tire change options.
static const char *tireChangeLabel[] = {
	"All",
	"None"
};
static const tCarPitCmd::TireChange tireChangeList[] = {
	tCarPitCmd::ALL,
	tCarPitCmd::NONE
};
static const int nbtireChangeOptions = sizeof(tireChangeLabel) / sizeof(tireChangeLabel[0]);
static int currentTireChangeOption = 0;

static void rmUpdtFuel(void * /* dummy */)
{
	char *val;
	const int BUFSIZE = 32;
	char buf[BUFSIZE];

	val = GfuiEditboxGetString(menuHandle, fuelId);
	rmCar->pitcmd.fuel = (tdble)strtol(val, (char **)NULL, 0);
	snprintf(buf, BUFSIZE, "%f", rmCar->pitcmd.fuel);
	GfuiEditboxSetString(menuHandle, fuelId, buf);
}


static void rmUpdtRepair(void * /* dummy */)
{
	char *val;
	const int BUFSIZE = 32;
	char buf[BUFSIZE];

	val = GfuiEditboxGetString(menuHandle, repairId);
	rmCar->pitcmd.repair = strtol(val, (char **)NULL, 0);
	snprintf(buf, BUFSIZE, "%d", rmCar->pitcmd.repair);
	GfuiEditboxSetString(menuHandle, repairId, buf);
}


static tfuiCallback rmCallback;
static void *rmUserData;


static void rmStopAndGo(void * /* dummy */)
{
	rmCar->_pitStopType = RM_PIT_STOPANDGO;
	rmCallback(rmUserData);
}


static void rmRepair(void* /* dummy */)
{
	rmCar->_pitStopType = RM_PIT_REPAIR;
	rmCallback(rmUserData);
}

// Manage tire change state.
static void changeTireState(void *vp)
{
	long i = (long) vp;

	if (i > 0) {
		currentTireChangeOption++;
		if (currentTireChangeOption >= nbtireChangeOptions) {
			currentTireChangeOption = 0;
		}
	} else {
		currentTireChangeOption--;
		if (currentTireChangeOption < 0) {
			currentTireChangeOption = nbtireChangeOptions - 1;
		}
	}

	rmCar->pitcmd.tireChange = tireChangeList[currentTireChangeOption];
	GfuiLabelSetText(menuHandle, tireChangeId, tireChangeLabel[currentTireChangeOption]);
}



/** @brief Pit menu
 *  @ingroup racemantools
 *  @param[in,out] car Car data is returned in tCarElt.pitcmd
 *  @param[in] reInfo Required for passing data to car setup screen, RmCarSetupScreenInit
 *  @param[in] userdata Userdata for callback
 *  @param[in] callback Callback to take action on the changes made
 */ 
void RmPitMenuStart(tCarElt *car, tRmInfo *reInfo, void *userdata, tfuiCallback callback)
{
	const int BUFSIZE = 256;
	char buf[BUFSIZE];
	int	y, x, dy;

	rmCar = car;
	rmInfo = reInfo;

	if (menuHandle) {
		GfuiScreenRelease(menuHandle);
	}
	menuHandle = GfuiMenuScreenCreate("Pit Stop Info");

	x = 80;
	y = 380;
	snprintf(buf, BUFSIZE, "Driver: %s", car->_name);
	GfuiLabelCreate(menuHandle, buf, GFUI_FONT_LARGE_C, x, y, GFUI_ALIGN_HL_VB, 0);
	dy = GfuiFontHeight(GFUI_FONT_LARGE_C) + 5;

	y -= dy;
	snprintf(buf, BUFSIZE, "Remaining Laps: %d", car->_remainingLaps);
	GfuiLabelCreate(menuHandle, buf, GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);

	y -= dy;
	snprintf(buf, BUFSIZE, "Remaining Fuel: %.1f l", car->_fuel);
	GfuiLabelCreate(menuHandle, buf, GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);

	y -= dy;
	GfuiLabelCreate(menuHandle, "Fuel amount (liters):", GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);

	int dx = GfuiFontWidth(GFUI_FONT_MEDIUM_C, "Fuel amount (liters)") + 20;
	snprintf(buf, BUFSIZE, "%d", (int)car->pitcmd.fuel);
	fuelId = GfuiEditboxCreate(menuHandle, buf, GFUI_FONT_MEDIUM_C,
					x + dx, y,
					100, 10, NULL, (tfuiCallback)NULL, rmUpdtFuel);

	y -= dy;
	GfuiLabelCreate(menuHandle, "Repair amount:", GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);

	snprintf(buf, BUFSIZE, "%d", (int)car->pitcmd.repair);
	repairId = GfuiEditboxCreate(menuHandle, buf, GFUI_FONT_MEDIUM_C,
					x + dx, y,
					100, 10, NULL, (tfuiCallback)NULL, rmUpdtRepair);

	y -= dy;

	int x2 = x + dx - 15;
	int x3 = x + dx + 100 + 14;
	int x4 = (x2+x3)/2;

	GfuiLabelCreate(menuHandle, "Tire change:", GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);

	if (!(reInfo->raceRules.tireFactor > 0.0f) || car->info.skillLevel != 3) {
		currentTireChangeOption = tCarPitCmd::NONE;
		rmCar->pitcmd.tireChange = tCarPitCmd::NONE;
		tireChangeId = GfuiLabelCreate(menuHandle, "Tire wear is off", GFUI_FONT_MEDIUM_C, x + dx, y, GFUI_ALIGN_HL_VB, 32);
	} else {
		tireChangeId = GfuiLabelCreate(menuHandle, tireChangeLabel[currentTireChangeOption], GFUI_FONT_MEDIUM_C, x4, y, GFUI_ALIGN_HC_VB, 32);

		GfuiGrButtonCreate(menuHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
			"data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
			x2, y-5, GFUI_ALIGN_HL_VB, 1,
			(void*)-1, changeTireState,
			NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
		GfuiGrButtonCreate(menuHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
			"data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
			x3, y-5, GFUI_ALIGN_HR_VB, 1,
			(void*)1, changeTireState,
			NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

		rmCar->pitcmd.tireChange = tireChangeList[currentTireChangeOption];
		GfuiLabelSetColor(menuHandle, tireChangeId, LabelColor);
	}

	GfuiButtonCreate(menuHandle, "Repair", GFUI_FONT_LARGE, 160, 40, 130, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
				NULL, rmRepair, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
	rmCallback = callback;
	rmUserData = userdata;

	int buttonid;
	// Just enable stop and go if penalty is pending
	buttonid = GfuiButtonCreate(menuHandle, "Stop & Go", GFUI_FONT_LARGE, 320, 40, 130, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
				NULL, rmStopAndGo, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
	tCarPenalty *penalty = GF_TAILQ_FIRST(&(car->_penaltyList));
	if (!penalty || (penalty && penalty->penalty != RM_PENALTY_STOPANDGO)) {
		GfuiEnable(menuHandle, buttonid, GFUI_DISABLE);
	}

	// Just enable car setup button in practice and qualifying sessions
	buttonid = GfuiButtonCreate(menuHandle, "Setup", GFUI_FONT_LARGE, 480, 40, 130, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		RmCarSetupScreenInit(menuHandle, rmCar, rmInfo), GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
	if (reInfo->s->raceInfo.type != RM_TYPE_PRACTICE && reInfo->s->raceInfo.type != RM_TYPE_QUALIF) {
		GfuiEnable(menuHandle, buttonid, GFUI_DISABLE);
	}
	
	GfuiScreenActivate(menuHandle);
}
