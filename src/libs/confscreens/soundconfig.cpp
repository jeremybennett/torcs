/***************************************************************************

    file        : soundconfig.cpp
    created     : Thu Dec 12 15:12:07 CET 2004
    copyright   : (C) 2004 Eric Espié, Bernhard Wymann, baseed on simuconfig.cpp
    email       : berniw@bluewin.ch
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
    		
    @version	$Id$
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgfclient.h>
#include <raceinit.h>
#include <graphic.h>

#include "soundconfig.h"

static float LabelColor[] = {1.0, 0.0, 1.0, 1.0};

// list of options.
static char *soundOptionList[] = {GR_ATT_SOUND_STATE_ENABLED, GR_ATT_SOUND_STATE_DISABLED};
static const int nbOptions = sizeof(soundOptionList) / sizeof(soundOptionList[0]);
static int curOption = 0;

// gui label id.
static int SoundOptionId;

// gui screen handles.
static void	*scrHandle = NULL;
static void	*prevHandle = NULL;

// parameters to configure.
static void	*paramHandle = NULL;


// Read sound configuration.
static void readSoundCfg(void)
{
	char *optionName;
	int	i;
	char buf[1024];

	sprintf(buf, "%s%s", GetLocalDir(), GR_SOUND_PARM_CFG);
	paramHandle = GfParmReadFile(buf, GFPARM_RMODE_REREAD | GFPARM_RMODE_CREAT);
	optionName = GfParmGetStr(paramHandle, GR_SCT_SOUND, GR_ATT_SOUND_STATE, soundOptionList[0]);

	for (i = 0; i < nbOptions; i++) {
		if (strcmp(optionName, soundOptionList[i]) == 0) {
			curOption = i;
			break;
		}
	}

	GfParmReleaseHandle(paramHandle);
	paramHandle = NULL;

	GfuiLabelSetText(scrHandle, SoundOptionId, soundOptionList[curOption]);
}


// Save the choosen values in the corresponding parameter file.
static void saveSoundOption(void *)
{
	char buf[1024];
	sprintf(buf, "%s%s", GetLocalDir(), GR_SOUND_PARM_CFG);
	paramHandle = GfParmReadFile(buf, GFPARM_RMODE_REREAD | GFPARM_RMODE_CREAT);
	GfParmSetStr(paramHandle, GR_SCT_SOUND, GR_ATT_SOUND_STATE, soundOptionList[curOption]);
	GfParmWriteFile(NULL, paramHandle, "sound");
	GfParmReleaseHandle(paramHandle);
	paramHandle = NULL;

	// Return to previous screen.
	GfuiScreenActivate(prevHandle);
	return;
}


// Toggle sound state enabled/disabled.
static void changeSoundState(void *vp)
{
	if (vp == 0) {
		curOption--;
		if (curOption < 0) {
	    	curOption = nbOptions - 1;
		}
	} else {
		curOption++;
		if (curOption == nbOptions) {
	    curOption = 0;
	}
    }
    GfuiLabelSetText(scrHandle, SoundOptionId, soundOptionList[curOption]);
}

// Sound menu
void * SoundMenuInit(void *prevMenu)
{
	int x, y, x2, x3, x4, dy;

	// Has screen already been created?
	if (scrHandle) {
		return scrHandle;
	}

	prevHandle = prevMenu;

	scrHandle = GfuiScreenCreate();
	GfuiTitleCreate(scrHandle, "Sound Configuration", 0);
	GfuiScreenAddBgImg(scrHandle, "data/img/splash-simucfg.png");

	x = 20;
	x2 = 200;
	x3 = 440;
	x4 = (x2+x3)/2;
	y = 370;
	dy = 30;

	y -= dy;
	GfuiLabelCreate(scrHandle, "Sound System State", GFUI_FONT_LARGE, 320, 400, GFUI_ALIGN_HC_VB, 0);
	GfuiGrButtonCreate(scrHandle, "data/img/arrow-left.png", "data/img/arrow-left.png",
			"data/img/arrow-left.png", "data/img/arrow-left-pushed.png",
			x2, y, GFUI_ALIGN_HC_VB, 1,
			(void*)-1, changeSoundState,
			NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

	GfuiGrButtonCreate(scrHandle, "data/img/arrow-right.png", "data/img/arrow-right.png",
			"data/img/arrow-right.png", "data/img/arrow-right-pushed.png",
			x3, y, GFUI_ALIGN_HC_VB, 1,
			(void*)1, changeSoundState,
			NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

	SoundOptionId = GfuiLabelCreate(scrHandle, "", GFUI_FONT_LARGE_C, x4, y, GFUI_ALIGN_HC_VB, 32);
	GfuiLabelSetColor(scrHandle, SoundOptionId, LabelColor);

	GfuiButtonCreate(scrHandle, "Accept", GFUI_FONT_LARGE, 210, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
	NULL, saveSoundOption, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

	GfuiButtonCreate(scrHandle, "Cancel", GFUI_FONT_LARGE, 430, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
	prevMenu, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

	GfuiAddKey(scrHandle, 13, "Save", NULL, saveSoundOption, NULL);
	GfuiAddKey(scrHandle, 27, "Cancel Selection", prevMenu, GfuiScreenActivate, NULL);
	GfuiAddSKey(scrHandle, GLUT_KEY_F12, "Screen-Shot", NULL, GfuiScreenShot, NULL);
	GfuiAddSKey(scrHandle, GLUT_KEY_LEFT, "Previous Option in list", (void*)0, changeSoundState, NULL);
	GfuiAddSKey(scrHandle, GLUT_KEY_RIGHT, "Next Option in list", (void*)1, changeSoundState, NULL);

	readSoundCfg();

	return scrHandle;
}
