/***************************************************************************

    file        : mouseconfig.cpp
    created     : Thu Mar 13 21:27:03 CET 2003
    copyright   : (C) 2003 by Eric Espié                        
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
#include <stdlib.h>
#include <string.h>

#include <tgfclient.h>
#include <track.h>
#include <robot.h>
#include <playerpref.h>
#include <js.h>

#include "mouseconfig.h"

static void 	*scrHandle = NULL;
static void 	*scrHandle2 = NULL;
static void	*prevHandle = NULL;

static void	*PrefHdle = NULL;

static int	CalButton;

static tCtrlMouseInfo	mouseInfo;

typedef struct
{
    char	*name;
    tCtrlRef	ref;
    int		Id;
    char	*minName;
    float	min;
    char	*maxName;
    float	max;
    char	*powName;
    float	pow;
    int		keyboardPossible;
} tCmdInfo;

static tCmdInfo Cmd[] = {
    {HM_ATT_GEAR_R,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_GEAR_N,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_UP_SHFT,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_DN_SHFT,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_LEFTSTEER,  {1,  GFCTRL_TYPE_MOUSE_AXIS},   0, HM_ATT_LEFTSTEER_MIN, 0, HM_ATT_LEFTSTEER_MAX, 0, HM_ATT_LEFTSTEER_POW, 0, 1},
    {HM_ATT_RIGHTSTEER, {2,  GFCTRL_TYPE_MOUSE_AXIS},   0, HM_ATT_RIGHTSTEER_MIN, 0, HM_ATT_RIGHTSTEER_MAX, 0, HM_ATT_RIGHTSTEER_POW, 0, 1},
    {HM_ATT_THROTTLE,   {1,  GFCTRL_TYPE_MOUSE_BUT},    0, HM_ATT_THROTTLE_MIN, 0, HM_ATT_THROTTLE_MAX, 0, HM_ATT_THROTTLE_POW, 0, 1},
    {HM_ATT_BRAKE,      {2,  GFCTRL_TYPE_MOUSE_BUT},    0, HM_ATT_BRAKE_MIN, 0, HM_ATT_BRAKE_MAX, 0, HM_ATT_BRAKE_POW, 0, 1},
    {HM_ATT_ASR_CMD,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_ABS_CMD,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 1}
};

static int maxCmd = sizeof(Cmd) / sizeof(Cmd[0]);

static jsJoystick	*js[NUM_JOY] = {NULL};
static float		ax[MAX_AXES * NUM_JOY] = {0};
static int		rawb[NUM_JOY] = {0};

static float SteerSensVal;
static float DeadZoneVal;

static char buf[1024];

static int SteerSensEditId;
static int DeadZoneEditId;


static void mouseCalMenuInit(void);


static void
onSteerSensChange(void * /* dummy */)
{
    char	*val;
    float	fv;
    char	buf[32];

    val = GfuiEditboxGetString(scrHandle, SteerSensEditId);
    if (sscanf(val, "%f", &fv) == 1) {
	sprintf(buf, "%f", fv);
	SteerSensVal = fv;
	GfuiEditboxSetString(scrHandle, SteerSensEditId, buf);
    } else {
	GfuiEditboxSetString(scrHandle, SteerSensEditId, "");
    }
    
}

static void
onDeadZoneChange(void * /* dummy */)
{
    char	*val;
    float	fv;
    char	buf[32];

    val = GfuiEditboxGetString(scrHandle, DeadZoneEditId);
    if (sscanf(val, "%f", &fv) == 1) {
	sprintf(buf, "%f", fv);
	DeadZoneVal = fv;
	GfuiEditboxSetString(scrHandle, DeadZoneEditId, buf);
    } else {
	GfuiEditboxSetString(scrHandle, SteerSensEditId, "");
    }
    
}

static void
onSave(void * /* dummy */)
{
    int		i;
    char	*str;

    GfParmSetNum(PrefHdle, HM_SECT_MOUSEPREF, HM_ATT_STEER_SENS, NULL, SteerSensVal);
    GfParmSetNum(PrefHdle, HM_SECT_MOUSEPREF, HM_ATT_STEER_DEAD, NULL, DeadZoneVal);

    for (i = 0; i < maxCmd; i++) {
	str = GfctrlGetNameByRef(Cmd[i].ref.type, Cmd[i].ref.index);
	if (str) {
	    GfParmSetStr(PrefHdle, HM_SECT_MOUSEPREF, Cmd[i].name, str);
	} else {
	    GfParmSetStr(PrefHdle, HM_SECT_MOUSEPREF, Cmd[i].name, "");
	}
	if (Cmd[i].minName) {
	    GfParmSetNum(PrefHdle, HM_SECT_MOUSEPREF, Cmd[i].minName, NULL, Cmd[i].min);
	}
	if (Cmd[i].maxName) {
	    GfParmSetNum(PrefHdle, HM_SECT_MOUSEPREF, Cmd[i].maxName, NULL, Cmd[i].max);
	}
	if (Cmd[i].powName) {
	    GfParmSetNum(PrefHdle, HM_SECT_MOUSEPREF, Cmd[i].powName, NULL, Cmd[i].pow);
	}
    }

    GfParmWriteFile(NULL, PrefHdle, "preferences", GFPARM_PARAMETER, "../../config/params.dtd");
    GfuiScreenActivate(prevHandle);
}

static void
updateButtonText(void)
{
    int		i;
    char	*str;
    int		displayCal = GFUI_INVISIBLE;

    for (i = 0; i < maxCmd; i++) {
	str = GfctrlGetNameByRef(Cmd[i].ref.type, Cmd[i].ref.index);
	if (str) {
	    GfuiButtonSetText (scrHandle, Cmd[i].Id, str);
	} else {
	    GfuiButtonSetText (scrHandle, Cmd[i].Id, "---");
	}
	if (Cmd[i].ref.type == GFCTRL_TYPE_MOUSE_AXIS) {
	    displayCal = GFUI_VISIBLE;
	}
    }

    sprintf(buf, "%f", SteerSensVal);
    GfuiEditboxSetString(scrHandle, SteerSensEditId, buf);

    sprintf(buf, "%f", DeadZoneVal);
    GfuiEditboxSetString(scrHandle, DeadZoneEditId, buf);

    GfuiVisiblilitySet(scrHandle, CalButton, displayCal);
}

static void
onFocusLost(void *dummy)
{
    updateButtonText();
}

static int CurrentCmd;

static int InputWaited = 0;

static int
onKeyAction(unsigned char key, int modifier, int state)
{
    char *name;

    if (!InputWaited || (state == GFUI_KEY_UP)) {
	return 0;
    }
    if (key == 27) {
	/* escape */
	Cmd[CurrentCmd].ref.index = -1;
	Cmd[CurrentCmd].ref.type = GFCTRL_TYPE_NOT_AFFECTED;
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, Cmd[CurrentCmd].name, "");
    } else {
	name = GfctrlGetNameByRef(GFCTRL_TYPE_KEYBOARD, (int)key);
	Cmd[CurrentCmd].ref.index = (int)key;
	Cmd[CurrentCmd].ref.type = GFCTRL_TYPE_KEYBOARD;
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, Cmd[CurrentCmd].name, name);
    }

    glutIdleFunc(GfuiIdle);
    InputWaited = 0;
    updateButtonText();
    return 1;
}

static int
onSKeyAction(int key, int modifier, int state)
{
    char *name;

    if (!InputWaited || (state == GFUI_KEY_UP)) {
	return 0;
    }
    name = GfctrlGetNameByRef(GFCTRL_TYPE_SKEYBOARD, key);
    Cmd[CurrentCmd].ref.index = key;
    Cmd[CurrentCmd].ref.type = GFCTRL_TYPE_SKEYBOARD;
    GfParmSetStr(PrefHdle, HM_SECT_JSPREF, Cmd[CurrentCmd].name, name);

    glutIdleFunc(GfuiIdle);
    InputWaited = 0;
    updateButtonText();
    return 1;
}

static void
Idle(void)
{
    int		mask;
    int		b, i;
    int		index;
    char	*str;

    GfctrlMouseGetCurrent(&mouseInfo);

    /* Check for a mouse button pressed */
    for (i = 0; i < 3; i++) {
	if (mouseInfo.edgedn[i]) {
	    glutIdleFunc(GfuiIdle);
	    InputWaited = 0;
	    str = GfctrlGetNameByRef(GFCTRL_TYPE_MOUSE_BUT, i);
	    Cmd[CurrentCmd].ref.index = i;
	    Cmd[CurrentCmd].ref.type = GFCTRL_TYPE_MOUSE_BUT;
	    GfuiButtonSetText (scrHandle, Cmd[CurrentCmd].Id, str);
	    glutPostRedisplay();
	    return;
	}
    }

    /* Check for a mouse axis moved */
    for (i = 0; i < 4; i++) {
	if (mouseInfo.ax[i] > 20.0) {
	    glutIdleFunc(GfuiIdle);
	    InputWaited = 0;
	    str = GfctrlGetNameByRef(GFCTRL_TYPE_MOUSE_AXIS, i);
	    Cmd[CurrentCmd].ref.index = i;
	    Cmd[CurrentCmd].ref.type = GFCTRL_TYPE_MOUSE_AXIS;
	    GfuiButtonSetText (scrHandle, Cmd[CurrentCmd].Id, str);
	    glutPostRedisplay();
	    return;
	}
    }

    /* Check for a Joystick button pressed */
    for (index = 0; index < NUM_JOY; index++) {
	if (js[index]) {
	    js[index]->read(&b, &ax[index * MAX_AXES]);

	    /* Joystick buttons */
	    for (i = 0, mask = 1; i < 32; i++, mask *= 2) {
		if (((b & mask) != 0) && ((rawb[index] & mask) == 0)) {
		    /* Button i fired */
		    glutIdleFunc(GfuiIdle);
		    InputWaited = 0;
		    str = GfctrlGetNameByRef(GFCTRL_TYPE_JOY_BUT, i + 32 * index);
		    Cmd[CurrentCmd].ref.index = i + 32 * index;
		    Cmd[CurrentCmd].ref.type = GFCTRL_TYPE_JOY_BUT;
		    GfuiButtonSetText (scrHandle, Cmd[CurrentCmd].Id, str);
		    glutPostRedisplay();
		    rawb[index] = b;
		    return;
		}
	    }
	    rawb[index] = b;
	}
    }
}

static void
onPush(void *vi)
{
    int	index;    
    int	i = (int)vi;
    
    CurrentCmd = i;
    GfuiButtonSetText (scrHandle, Cmd[i].Id, "");
    Cmd[i].ref.index = -1;
    Cmd[i].ref.type = GFCTRL_TYPE_NOT_AFFECTED;
    GfParmSetStr(PrefHdle, HM_SECT_JSPREF, Cmd[i].name, "");
    if (Cmd[CurrentCmd].keyboardPossible) {
	InputWaited = 1;
    }
    glutIdleFunc(Idle);
    GfctrlMouseInitCenter();
    memset(&mouseInfo, 0, sizeof(mouseInfo));
    GfctrlMouseGetCurrent(&mouseInfo);

    for (index = 0; index < NUM_JOY; index++) {
	if (js[index]) {
	    js[index]->read(&rawb[index], &ax[index * MAX_AXES]); /* initial value */
	}
    }
}

static void
onActivate(void * /* dummy */)
{
    int		cmd;
    char	*prm;
    tCtrlRef	*ref;

    sprintf(buf, "%s%s", GetLocalDir(), HM_PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    /* Mouse Settings */
    for (cmd = 0; cmd < maxCmd; cmd++) {
	prm = GfctrlGetNameByRef(Cmd[cmd].ref.type, Cmd[cmd].ref.index);
	if (!prm) {
	    prm = "---";
	}
	prm = GfParmGetStr(PrefHdle, HM_SECT_MOUSEPREF, Cmd[cmd].name, prm);
	ref = GfctrlGetRefByName(prm);
	Cmd[cmd].ref.type = ref->type;
	Cmd[cmd].ref.index = ref->index;
	if (Cmd[cmd].minName) {
	    Cmd[cmd].min = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, Cmd[cmd].minName, NULL, Cmd[cmd].min);
	}
	if (Cmd[cmd].maxName) {
	    Cmd[cmd].max = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, Cmd[cmd].maxName, NULL, Cmd[cmd].max);
	}
	if (Cmd[cmd].powName) {
	    Cmd[cmd].pow = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, Cmd[cmd].powName, NULL, Cmd[cmd].pow);
	}
    }

    SteerSensVal = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, HM_ATT_STEER_SENS, NULL, 0);
    DeadZoneVal = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, HM_ATT_STEER_DEAD, NULL, 0);

    updateButtonText();
}


void *
TorcsMouseMenuInit(void *prevMenu)
{
    int		x, y, x2, dy, i;
    int		index;

    prevHandle = prevMenu;
    sprintf(buf, "%s%s", GetLocalDir(), HM_PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    if (scrHandle) {
	return scrHandle;
    }
    mouseCalMenuInit();

    for (index = 0; index < NUM_JOY; index++) {
	if (js[index] == NULL) {
	    js[index] = new jsJoystick(index);
	}
    
	if (js[index]->notWorking()) {
	    /* don't configure the joystick */
	    js[index] = NULL;
	}
    }
    
    scrHandle = GfuiScreenCreateEx((float*)NULL, NULL, onActivate, NULL, (tfuiCallback)NULL, 1);
    GfuiTitleCreate(scrHandle, "Mouse/Keyboard/Pad Configuration", 0);

    GfuiScreenAddBgImg(scrHandle, "data/img/splash-mouseconf.png");

    GfuiMenuDefaultKeysAdd(scrHandle);

    x = 30;
    x2 = 210;
    y = 340;
    dy = 30;

    for (i = 0; i < maxCmd; i++) {
	GfuiLabelCreate(scrHandle, Cmd[i].name, GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
	Cmd[i].Id = GfuiButtonStateCreate (scrHandle, "MOUSE_MIDDLE_BUTTON", GFUI_FONT_MEDIUM_C, x+x2, y, 0, GFUI_ALIGN_HC_VB, GFUI_MOUSE_DOWN, 
					   (void*)i, onPush, NULL, (tfuiCallback)NULL, onFocusLost);
	y -= dy;
	if (i == 3) {
	    x = 340;
	    y = 340;
	    x2 = 200;
	}
    }

    GfuiLabelCreate(scrHandle, "Steer Sensibility", GFUI_FONT_MEDIUM, 30, 90, GFUI_ALIGN_HL_VB, 0);
    SteerSensEditId = GfuiEditboxCreate(scrHandle, "", GFUI_FONT_MEDIUM_C,
					200, 90, 80, 8, NULL, (tfuiCallback)NULL, onSteerSensChange);

    GfuiLabelCreate(scrHandle, "Steer Dead Zone", GFUI_FONT_MEDIUM, 340, 90, GFUI_ALIGN_HL_VB, 0);
    DeadZoneEditId = GfuiEditboxCreate(scrHandle, "", GFUI_FONT_MEDIUM_C,
					510, 90, 80, 8, NULL, (tfuiCallback)NULL, onDeadZoneChange);


    GfuiAddKey(scrHandle, 13, "Save", NULL, onSave, NULL);
    GfuiButtonCreate(scrHandle, "Save", GFUI_FONT_LARGE, 160, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, onSave, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    CalButton = GfuiButtonCreate(scrHandle, "Calibrate", GFUI_FONT_LARGE, 320, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
				 scrHandle2, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiAddKey(scrHandle, 27, "Cancel", prevMenu, GfuiScreenActivate, NULL);
    GfuiButtonCreate(scrHandle, "Cancel", GFUI_FONT_LARGE, 480, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     prevMenu, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);


    GfuiKeyEventRegister(scrHandle, onKeyAction);
    GfuiSKeyEventRegister(scrHandle, onSKeyAction);

    return scrHandle;
}

/*
 * Mouse calibration
 */
static int	InstId;
static int	CalState;
static int	scrw, scrh;


static char *Instructions[] = {
    "Move Mouse for maximum left steer then press a button",
    "Move Mouse for maximum right steer then press a button",
    "Move Mouse for full throttle then press a button",
    "Move Mouse for full brake then press a button",
    "Calibration terminated",
    "Calibration failed"
};

static void Idle2(void);

static int
GetNextAxis(void)
{
    int i;

    for (i = CalState; i < 4; i++) {
	if (Cmd[4 + i].ref.type == GFCTRL_TYPE_MOUSE_AXIS) {
	    return i;
	}
    }
    return i;
}


static void
MouseCalAutomaton(void)
{
    float	ax;

    switch (CalState) {
    case 0:
    case 1:
	GfctrlMouseGetCurrent(&mouseInfo);
	ax = mouseInfo.ax[Cmd[4 + CalState].ref.index];
	if (ax == 0.0) {
	    return;		/* ignore no move input */
	}
	Cmd[4 + CalState].max = ax;
	Cmd[4 + CalState].pow = 1.0 / ax;
	break;

    case 2:
    case 3:
	GfctrlMouseGetCurrent(&mouseInfo);
	ax = mouseInfo.ax[Cmd[4 + CalState].ref.index];
	if (ax == 0.0) {
	    return;		/* ignore no move input */
	}
	Cmd[4 + CalState].max = ax;
	Cmd[4 + CalState].pow = 1.0 / ax;
	break;
	
    }

    CalState++;
    CalState = GetNextAxis();
    GfuiLabelSetText(scrHandle2, InstId, Instructions[CalState]);
    if (CalState < 4) {
	glutIdleFunc(Idle2);
    } else {
	glutIdleFunc(GfuiIdle);
    }
}

static void
Idle2(void)
{
    int	i;

    GfctrlMouseGetCurrent(&mouseInfo);

    /* Check for a mouse button pressed */
    for (i = 0; i < 3; i++) {
	if (mouseInfo.edgedn[i]) {
	    MouseCalAutomaton();
	    return;
	}
    }
}

static void
IdleMouseInit(void)
{
    /* Get the center mouse position  */
    memset(&mouseInfo, 0, sizeof(mouseInfo));
    GfctrlMouseGetCurrent(&mouseInfo);
    GfctrlMouseInitCenter();
    glutIdleFunc(Idle2);
}

static void
onActivate2(void * /* dummy */)
{
    int dummy;

    GfScrGetSize(&scrw, &scrh, &dummy, &dummy);
    CalState = 0;
    GetNextAxis();
    GfuiLabelSetText(scrHandle2, InstId, Instructions[CalState]);
    if (CalState < 4) {
	glutIdleFunc(IdleMouseInit);
	GfctrlMouseCenter();
    }
}

static void
onCancel2(void * /* dummy */) 
{
    GfuiScreenActivate(prevHandle);
}

static void
mouseCalMenuInit(void)
{
    int x, y, dy;
    
    if (scrHandle2) {
	return;
    }

    scrHandle2 = GfuiScreenCreateEx(NULL, NULL, onActivate2, NULL, NULL, 1);
    GfuiTitleCreate(scrHandle2, "Mouse Calibration", 0);
    GfuiMenuDefaultKeysAdd(scrHandle2);

    GfuiScreenAddBgImg(scrHandle2, "data/img/splash-mousecal.png");

    x = 128;
    y = 300;
    dy = 50;

    InstId = GfuiLabelCreate(scrHandle2, "", GFUI_FONT_MEDIUM, 320, 80, GFUI_ALIGN_HC_VB, 60);

    GfuiButtonCreate(scrHandle2, "Save", GFUI_FONT_LARGE, 160, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
     NULL, onSave, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    
    GfuiButtonCreate(scrHandle2, "Reset", GFUI_FONT_LARGE, 320, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
     NULL, onActivate2, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    
    GfuiButtonCreate(scrHandle2, "Cancel", GFUI_FONT_LARGE, 480, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
     NULL, onCancel2, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiAddKey(scrHandle2, 27, "Cancel Selection", NULL, onCancel2, NULL);
    
}
