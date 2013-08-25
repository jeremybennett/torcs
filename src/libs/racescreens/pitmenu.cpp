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
    @ingroup	racemantools
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/
#include <stdlib.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tgfclient.h>
#include <car.h>
#include <portability.h>
#include <racescreens.h>

static void		*menuHandle = NULL;
static int		fuelId;
static int		repairId;
static tCarElt	*rmCar;
static tRmInfo  *rmInfo;

static int steerLockId;



static void
rmUpdtFuel(void * /* dummy */)
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


/*static void CarSetupScreen(void *  )
{
	GfuiScreenActivate(RmCarSetupScreenInit(menuHandle, rmCar));
}*/


static tdble steerincs = 0.0f;
static tdble steerdecs = 0.0f;
static tdble steerincb = 0.0f;
static tdble steerdecb = 0.0f;

static void rmSetSteerLock(tdble value)
{
	if (value > rmCar->pitcmd.setup.steerLock.max) {
		value = rmCar->pitcmd.setup.steerLock.max;
	} else if (value < rmCar->pitcmd.setup.steerLock.min) {
		value = rmCar->pitcmd.setup.steerLock.min;
	}
	rmCar->pitcmd.setup.steerLock.value = value;
	value = GfParmSI2Unit("deg", value);
	const int BUFSIZE = 32;
	char buf[BUFSIZE];

	snprintf(buf, BUFSIZE, "%4.2f", value);
	GfuiEditboxSetString(menuHandle, steerLockId, buf);
}


static void rmEnterSteerLock(void *vp)
{
	const char *val = GfuiEditboxGetString(menuHandle, steerLockId);
	tdble value = (tdble) atof(val);
	value = GfParmUnit2SI("deg", value);
	rmSetSteerLock(value);
}


static void rmUpdtSteerLock(void *vp)
{
	tdble delta = *((tdble*)vp);
	tdble value = rmCar->pitcmd.setup.steerLock.value;
	value += delta;
	rmSetSteerLock(value);
}


static tfuiCallback rmCallback;
static void *rmUserData;


static void
rmStopAndGo(void * /* dummy */)
{
	rmCar->_pitStopType = RM_PIT_STOPANDGO;
	rmCallback(rmUserData);
}


static void
rmRepair(void* /* dummy */)
{
	rmCar->_pitStopType = RM_PIT_REPAIR;
	rmCallback(rmUserData);
}


void
RmPitMenuStart(tCarElt *car, tRmInfo *reInfo, void *userdata, tfuiCallback callback)
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
					0, 10, NULL, (tfuiCallback)NULL, rmUpdtFuel);

	y -= dy;
	GfuiLabelCreate(menuHandle, "Repair amount:", GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);

	snprintf(buf, BUFSIZE, "%d", (int)car->pitcmd.repair);
	repairId = GfuiEditboxCreate(menuHandle, buf, GFUI_FONT_MEDIUM_C,
					x + dx, y,
					0, 10, NULL, (tfuiCallback)NULL, rmUpdtRepair);


	y -= dy;
	GfuiLabelCreate(menuHandle, "Steer Lock:", GFUI_FONT_MEDIUM_C, x, y, GFUI_ALIGN_HL_VB, 0);

//GfParmSI2Unit("deg", car->pitcmd.setup.steerLock.value);

	/*static const char* tip = "This is a tip";
	tMnuCallbackInfo *cbinfo = (tMnuCallbackInfo*)calloc(1, sizeof(tMnuCallbackInfo));
	cbinfo->screen = menuHandle;
	cbinfo->labelId = GfuiTipCreate(menuHandle, tip, strlen(tip));
	GfuiVisibilitySet(menuHandle, cbinfo->labelId, 0);*/

	static const int w = 40;

	steerincb = (rmCar->pitcmd.setup.steerLock.max - rmCar->pitcmd.setup.steerLock.min)/20.0f;
	steerdecb = -steerincb;
	steerincs = steerincb/10.0f;
	steerdecs = -steerincs;

	snprintf(buf, BUFSIZE, "%4.2f", GfParmSI2Unit("deg", car->pitcmd.setup.steerLock.value));
	steerLockId = GfuiEditboxCreate(menuHandle, buf, GFUI_FONT_MEDIUM_C,
		x + dx, y,
		w, 5, NULL, (tfuiCallback)NULL, rmEnterSteerLock);

	GfuiGrButtonCreate(menuHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
		"data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
		x + dx - 12 - 24, y-5, GFUI_ALIGN_HR_VB, 1,
		(void*)&steerdecb, rmUpdtSteerLock,
		NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

	GfuiGrButtonCreate(menuHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
		"data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
		x + dx - 12, y-5, GFUI_ALIGN_HR_VB, 1,
		(void*)&steerdecs, rmUpdtSteerLock,
		NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

	/*GfuiGrButtonCreate(menuHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
		"data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
		x + dx + w + 12, y-5, GFUI_ALIGN_HL_VB, 1,
		(void*)&steerincs, rmUpdtSteerLock,
		NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
*/
	GfuiGrButtonCreate(menuHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
		"data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
		x + dx + w + 12 + 24, y-5, GFUI_ALIGN_HL_VB, 1,
		(void*)&steerincb, rmUpdtSteerLock,
		NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

	int id = GfuiLeanButtonCreate(menuHandle, "+", GFUI_FONT_MEDIUM_C,
		x + dx + w + 12 + 6, y, 12, GFUI_ALIGN_HC_VB, 1,
		(void*)NULL, NULL,
		NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
	//GfuiEnable(menuHandle, steerLockId, GFUI_DISABLE);

/*
#define	GFUI_DISABLE	1
#define	GFUI_ENABLE	0
	extern int GfuiEnable(void *scr, int id, int flag);
*/

/*
	cbinfo = (tMnuCallbackInfo*)calloc(1, sizeof(tMnuCallbackInfo));
	cbinfo->screen = scr;
	cbinfo->labelId = GfuiTipCreate(scr, tip, strlen(tip));

	GfuiVisibilitySet(scr, cbinfo->labelId, 0);

	bId = GfuiButtonCreate(scr,
		text,
		GFUI_FONT_LARGE,
		xpos, ypos, GFUI_BTNSZ, GFUI_ALIGN_HC_VB, 0,
		userdata, onpush,
		(void*)cbinfo, dispInfo,
		remInfo);
*/





	//GfuiMenuBackQuitButtonCreate(menuHandle, "Repair", "Return to race", userdata, callback);
	// TODO: Only show in practise/qualifying
	GfuiButtonCreate(menuHandle, "Setup", GFUI_FONT_LARGE, 160, 80, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		RmCarSetupScreenInit(menuHandle, rmCar, rmInfo), GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

	GfuiButtonCreate(menuHandle, "Repair", GFUI_FONT_LARGE, 160, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
				NULL, rmRepair, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
	rmCallback = callback;
	rmUserData = userdata;

	// TODO: Just show stop and go if penalty is pending
	GfuiButtonCreate(menuHandle, "Stop & Go", GFUI_FONT_LARGE, 480, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
				NULL, rmStopAndGo, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

	GfuiScreenActivate(menuHandle);
}
