/***************************************************************************

    file        : controlconfig.cpp
    created     : Wed Mar 12 21:20:34 CET 2003
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

#include "controlconfig.h"
#include "mouseconfig.h"
#include "joystickconfig.h"

static void 	*scrHandle = NULL;
static void	*prevHandle = NULL;
static void	*PrefHdle = NULL;

static int	MouseCalButton;
static int	JoyCalButton;

static tCtrlMouseInfo	mouseInfo;
static char	CurrentSection[256];

/* Selected gear change mode for the current player */
typedef enum { GEAR_MODE_AUTO = 1, GEAR_MODE_SEQ = 2, GEAR_MODE_GRID = 4 } tGearChangeMode;
static tGearChangeMode GearChangeMode;

/* Control command information */
static tCmdInfo Cmd[] = {
    {HM_ATT_LEFTSTEER,  {1,  GFCTRL_TYPE_MOUSE_AXIS},   0, 0, HM_ATT_LEFTSTEER_MIN,  0, HM_ATT_LEFTSTEER_MAX,  0, HM_ATT_LEFTSTEER_POW,  1.0, 1},
    {HM_ATT_RIGHTSTEER, {2,  GFCTRL_TYPE_MOUSE_AXIS},   0, 0, HM_ATT_RIGHTSTEER_MIN, 0, HM_ATT_RIGHTSTEER_MAX, 0, HM_ATT_RIGHTSTEER_POW, 1.0, 1},
    {HM_ATT_THROTTLE,   {1,  GFCTRL_TYPE_MOUSE_BUT},    0, 0, HM_ATT_THROTTLE_MIN,   0, HM_ATT_THROTTLE_MAX,   0, HM_ATT_THROTTLE_POW,   1.0, 1},
    {HM_ATT_BRAKE,      {2,  GFCTRL_TYPE_MOUSE_BUT},    0, 0, HM_ATT_BRAKE_MIN,      0, HM_ATT_BRAKE_MAX,      0, HM_ATT_BRAKE_POW,      1.0, 1},
    {HM_ATT_CLUTCH,     {3,  GFCTRL_TYPE_MOUSE_BUT},    0, 0, HM_ATT_CLUTCH_MIN,     0, HM_ATT_CLUTCH_MAX,     0, HM_ATT_CLUTCH_POW,     1.0, 1},
    {HM_ATT_ABS_CMD,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_ASR_CMD,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_SPDLIM_CMD, {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_LIGHT1_CMD, {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_GEAR_R,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_GEAR_N,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_DN_SHFT,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_UP_SHFT,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_GEAR_1,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_GEAR_2,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_GEAR_3,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_GEAR_4,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_GEAR_5,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {HM_ATT_GEAR_6,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0, 0, 0, 0, 0, 0, 0, 0, 1}
};

static const int maxCmd = sizeof(Cmd) / sizeof(Cmd[0]);
static const int iCmdReverseGear = 9;
static const int iCmdNeutralGear = 10;

/* Command editbox visibility according to the selected gear changing mode */
typedef struct tCmdDispInfo
{
    unsigned visible;
    int      y;
} tCmdDispInfo;

static tCmdDispInfo CmdDispInfo[] = {
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ | GEAR_MODE_GRID, 400 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ | GEAR_MODE_GRID, 370 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ | GEAR_MODE_GRID, 340 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ | GEAR_MODE_GRID, 310 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ | GEAR_MODE_GRID, 280 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ | GEAR_MODE_GRID, 250 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ | GEAR_MODE_GRID, 220 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ | GEAR_MODE_GRID, 190 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ | GEAR_MODE_GRID, 160 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ | GEAR_MODE_GRID, 400 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ | GEAR_MODE_GRID, 370 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ,                  340 },
    { GEAR_MODE_AUTO | GEAR_MODE_SEQ,                  310 },
    {                                  GEAR_MODE_GRID, 340 },
    {                                  GEAR_MODE_GRID, 310 },
    {                                  GEAR_MODE_GRID, 280 },
    {                                  GEAR_MODE_GRID, 250 },
    {                                  GEAR_MODE_GRID, 220 },
    {                                  GEAR_MODE_GRID, 190 }
};

static jsJoystick	*js[NUM_JOY] = {NULL};
static float		ax[MAX_AXES * NUM_JOY] = {0};
static float 		axCenter[MAX_AXES * NUM_JOY];
static int		rawb[NUM_JOY] = {0};

static float SteerSensVal;
static float DeadZoneVal;

static char buf[1024];

static int SteerSensEditId;
static int DeadZoneEditId;

static int ReloadValues = 1;


static void
onSteerSensChange(void * /* dummy */)
{
    char	*val;
    float	fv;

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

    val = GfuiEditboxGetString(scrHandle, DeadZoneEditId);
    if (sscanf(val, "%f", &fv) == 1) {
	sprintf(buf, "%f", fv);
	DeadZoneVal = fv;
	GfuiEditboxSetString(scrHandle, DeadZoneEditId, buf);
    } else {
	GfuiEditboxSetString(scrHandle, SteerSensEditId, "");
    }
    
}

/* Save settings in the players preferences XML file */
static void
onSave(void * /* dummy */)
{
    int		i;
    char	*str;

    /* Allow neutral gear in sequential mode if no reverse gear command defined */
    if (GearChangeMode == GEAR_MODE_SEQ
	&& !GfctrlGetNameByRef(Cmd[iCmdReverseGear].ref.type, Cmd[iCmdReverseGear].ref.index))
	GfParmSetStr(PrefHdle, CurrentSection, HM_ATT_SEQSHFT_ALLOW_NEUTRAL, HM_VAL_YES);
    else
	GfParmSetStr(PrefHdle, CurrentSection, HM_ATT_SEQSHFT_ALLOW_NEUTRAL, HM_VAL_NO);

    /* Release gear lever goes neutral in grid mode if no neutral gear command defined */
    if (GearChangeMode == GEAR_MODE_GRID
	&& !GfctrlGetNameByRef(Cmd[iCmdNeutralGear].ref.type, Cmd[iCmdNeutralGear].ref.index))
	GfParmSetStr(PrefHdle, CurrentSection, HM_ATT_REL_BUT_NEUTRAL, HM_VAL_YES);
    else
	GfParmSetStr(PrefHdle, CurrentSection, HM_ATT_REL_BUT_NEUTRAL, HM_VAL_NO);

    GfParmSetNum(PrefHdle, CurrentSection, HM_ATT_STEER_SENS, NULL, SteerSensVal);
    GfParmSetNum(PrefHdle, CurrentSection, HM_ATT_STEER_DEAD, NULL, DeadZoneVal);

    for (i = 0; i < maxCmd; i++) {
	str = GfctrlGetNameByRef(Cmd[i].ref.type, Cmd[i].ref.index);
	if (str) {
	    GfParmSetStr(PrefHdle, CurrentSection, Cmd[i].name, str);
	} else {
	    GfParmSetStr(PrefHdle, CurrentSection, Cmd[i].name, "");
	}
	if (Cmd[i].minName) {
	    GfParmSetNum(PrefHdle, CurrentSection, Cmd[i].minName, NULL, Cmd[i].min);
	}
	if (Cmd[i].maxName) {
	    GfParmSetNum(PrefHdle, CurrentSection, Cmd[i].maxName, NULL, Cmd[i].max);
	}
	if (Cmd[i].powName) {
	    GfParmSetNum(PrefHdle, CurrentSection, Cmd[i].powName, NULL, Cmd[i].pow);
	}
    }

    GfParmWriteFile(NULL, PrefHdle, "preferences");
    GfuiScreenActivate(prevHandle);
}

static void
updateButtonText(void)
{
    int		i;
    char	*str;
    int		displayMouseCal = GFUI_INVISIBLE;
    int		displayJoyCal = GFUI_INVISIBLE;

    /* For each control: */
    for (i = 0; i < maxCmd; i++) {

	/* Update associated editbox according to detected input device action */
	str = GfctrlGetNameByRef(Cmd[i].ref.type, Cmd[i].ref.index);
	if (str) {
	    GfuiButtonSetText (scrHandle, Cmd[i].Id, str);
	} else {
	    GfuiButtonSetText (scrHandle, Cmd[i].Id, "---");
	}

	/* According to detected action, set the visibility of the mouse or joystick
	   calibration button */
	if (Cmd[i].ref.type == GFCTRL_TYPE_MOUSE_AXIS) {
	    displayMouseCal = GFUI_VISIBLE;
	} else if (Cmd[i].ref.type == GFCTRL_TYPE_JOY_AXIS) {
	    displayJoyCal = GFUI_VISIBLE;
	}
    }

    /* Update Steer Sensibility editbox */
    sprintf(buf, "%f", SteerSensVal);
    GfuiEditboxSetString(scrHandle, SteerSensEditId, buf);

    /* Update Steer Dead Zone editbox */
    sprintf(buf, "%f", DeadZoneVal);
    GfuiEditboxSetString(scrHandle, DeadZoneEditId, buf);

    /* Show / hide mouse / joystick calibration button(s),
       according to the detected input device actions */
    GfuiVisibilitySet(scrHandle, MouseCalButton, displayMouseCal);
    GfuiVisibilitySet(scrHandle, JoyCalButton, displayJoyCal);
}

static void
onFocusLost(void * /* dummy */)
{
    updateButtonText();
}

static int CurrentCmd;

static int InputWaited = 0;

static int
onKeyAction(unsigned char key, int /* modifier */, int state)
{
    char *name;

    if (!InputWaited || (state == GFUI_KEY_UP)) {
	return 0;
    }
    if (key == 27) {
	/* escape */
	Cmd[CurrentCmd].ref.index = -1;
	Cmd[CurrentCmd].ref.type = GFCTRL_TYPE_NOT_AFFECTED;
	GfParmSetStr(PrefHdle, CurrentSection, Cmd[CurrentCmd].name, "");
    } else {
	name = GfctrlGetNameByRef(GFCTRL_TYPE_KEYBOARD, (int)key);
	Cmd[CurrentCmd].ref.index = (int)key;
	Cmd[CurrentCmd].ref.type = GFCTRL_TYPE_KEYBOARD;
	GfParmSetStr(PrefHdle, CurrentSection, Cmd[CurrentCmd].name, name);
    }

    glutIdleFunc(GfuiIdle);
    InputWaited = 0;
    updateButtonText();
    return 1;
}

static int
onSKeyAction(int key, int /* modifier */, int state)
{
    char *name;

    if (!InputWaited || (state == GFUI_KEY_UP)) {
	return 0;
    }
    name = GfctrlGetNameByRef(GFCTRL_TYPE_SKEYBOARD, key);
    Cmd[CurrentCmd].ref.index = key;
    Cmd[CurrentCmd].ref.type = GFCTRL_TYPE_SKEYBOARD;
    GfParmSetStr(PrefHdle, CurrentSection, Cmd[CurrentCmd].name, name);

    glutIdleFunc(GfuiIdle);
    InputWaited = 0;
    updateButtonText();
    return 1;
}

static int
getMovedAxis(void)
{
    int		i;
    int		Index = -1;
    float	maxDiff = 0.3;

    for (i = 0; i < MAX_AXES * NUM_JOY; i++) {
	if (maxDiff < fabs(ax[i] - axCenter[i])) {
	    maxDiff = fabs(ax[i] - axCenter[i]);
	    Index = i;
	}
    }
    return Index;
}

static void
Idle(void)
{
    int		mask;
    int		b, i;
    int		index;
    char	*str;
    int		axis;

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

    /* detect joystick movement */
    axis = getMovedAxis();
    if (axis != -1) {
	glutIdleFunc(GfuiIdle);
	InputWaited = 0;
	Cmd[CurrentCmd].ref.type = GFCTRL_TYPE_JOY_AXIS;
	Cmd[CurrentCmd].ref.index = axis;
	str = GfctrlGetNameByRef(GFCTRL_TYPE_JOY_AXIS, axis);
	GfuiButtonSetText (scrHandle, Cmd[CurrentCmd].Id, str);
	glutPostRedisplay();
	return;
    }
}

static void
onPush(void *vi)
{
    int		index;    
    long	i = (long)vi;
    
    CurrentCmd = i;
    GfuiButtonSetText (scrHandle, Cmd[i].Id, "");
    Cmd[i].ref.index = -1;
    Cmd[i].ref.type = GFCTRL_TYPE_NOT_AFFECTED;
    GfParmSetStr(PrefHdle, CurrentSection, Cmd[i].name, "");
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
    memcpy(axCenter, ax, sizeof(axCenter));
}

static void
onActivate(void * /* dummy */)
{
    int		cmd;
    char	*prm;
    tCtrlRef	*ref;

    if (ReloadValues) {
	sprintf(buf, "%s%s", GetLocalDir(), HM_PREF_FILE);
	PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

	/* For each control  */
	for (cmd = 0; cmd < maxCmd; cmd++) {
	    prm = GfctrlGetNameByRef(Cmd[cmd].ref.type, Cmd[cmd].ref.index);
	    if (!prm) {
		prm = "---";
	    }
	    /* Load associated command value from preferences XML file for the current player,
	       by default from the default "mouse" settings */
	    prm = GfParmGetStr(PrefHdle, HM_SECT_MOUSEPREF, Cmd[cmd].name, prm);
	    prm = GfParmGetStr(PrefHdle, CurrentSection, Cmd[cmd].name, prm);
	    ref = GfctrlGetRefByName(prm);
	    Cmd[cmd].ref.type = ref->type;
	    Cmd[cmd].ref.index = ref->index;

	    if (Cmd[cmd].minName) {
		Cmd[cmd].min = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, Cmd[cmd].minName, NULL, Cmd[cmd].min);
		Cmd[cmd].min = GfParmGetNum(PrefHdle, CurrentSection, Cmd[cmd].minName, NULL, Cmd[cmd].min);
	    }
	    if (Cmd[cmd].maxName) {
		Cmd[cmd].max = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, Cmd[cmd].maxName, NULL, Cmd[cmd].max);
		Cmd[cmd].max = GfParmGetNum(PrefHdle, CurrentSection, Cmd[cmd].maxName, NULL, Cmd[cmd].max);
	    }
	    if (Cmd[cmd].powName) {
		Cmd[cmd].pow = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, Cmd[cmd].powName, NULL, Cmd[cmd].pow);
		Cmd[cmd].pow = GfParmGetNum(PrefHdle, CurrentSection, Cmd[cmd].powName, NULL, Cmd[cmd].pow);
	    }

	    /* Show / hide control editbox according to selected gear changing mode */
	    if (GearChangeMode & CmdDispInfo[cmd].visible)
	    {
	      GfuiVisibilitySet(scrHandle, Cmd[cmd].labelId, GFUI_VISIBLE);
	      GfuiVisibilitySet(scrHandle, Cmd[cmd].Id, GFUI_VISIBLE);
	    }
	    else
	    {
	      GfuiVisibilitySet(scrHandle, Cmd[cmd].labelId, GFUI_INVISIBLE);
	      GfuiVisibilitySet(scrHandle, Cmd[cmd].Id, GFUI_INVISIBLE);
	    }
	}

	SteerSensVal = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, HM_ATT_STEER_SENS, NULL, 0);
	SteerSensVal = GfParmGetNum(PrefHdle, CurrentSection, HM_ATT_STEER_SENS, NULL, SteerSensVal);
	DeadZoneVal = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, HM_ATT_STEER_DEAD, NULL, 0);
	DeadZoneVal = GfParmGetNum(PrefHdle, CurrentSection, HM_ATT_STEER_DEAD, NULL, DeadZoneVal);
    }
    
    updateButtonText();
}

static void
DevCalibrate(void *menu)
{
    ReloadValues = 0;
    GfuiScreenActivate(menu);
}


/* */
void *
TorcsControlMenuInit(void *prevMenu, int idx, char *gearChangeMode)
{
    int		x, x2, i;
    int		index;

    ReloadValues = 1;

    /* Select current player section in the players preferences */
    sprintf(CurrentSection, "%s/%d", HM_SECT_DRVPREF, idx);

    prevHandle = prevMenu;

    /* Determine selected gear changing mode for current player */
    GearChangeMode = GEAR_MODE_AUTO;
    if (strcmp(gearChangeMode, HM_VAL_SEQ) == 0) {
      GearChangeMode = GEAR_MODE_SEQ;
    } else if (strcmp(gearChangeMode, HM_VAL_GRID) == 0) {
      GearChangeMode = GEAR_MODE_GRID;
    }

    /* Load players preferences XML file */
    sprintf(buf, "%s%s", GetLocalDir(), HM_PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    /* Don't recreate screen if already done */
    if (scrHandle) {
	return scrHandle;
    }

    /* Initialize joysticks layer */
    for (index = 0; index < NUM_JOY; index++) {
	if (js[index] == NULL) {
	    js[index] = new jsJoystick(index);
	}
    
	if (js[index]->notWorking()) {
	    /* don't configure the joystick */
	    js[index] = NULL;
	}
	else {
	  GfOut("Detected joystick #%d type '%s' %d axes %d buttons\n", 
		index, js[index]->getName(), js[index]->getNumAxes()
/* Stangely, plibjs/jsJoystick has no getNumButtons() member */
#ifdef JPM
		, js[index]->getNumButtons()
#endif
		);
	}
    }
    
    scrHandle = GfuiScreenCreateEx((float*)NULL, NULL, onActivate, NULL, (tfuiCallback)NULL, 1);

    /* Screen title */
    GfuiTitleCreate(scrHandle, "Control Configuration", 0);

    /* Background image */
    GfuiScreenAddBgImg(scrHandle, "data/img/splash-mouseconf.png");

    /* Default keyboard shortcuts */
    GfuiMenuDefaultKeysAdd(scrHandle);

    /* Screen coordinates for labels, buttons, ... */
    x = 10;
    x2 = 210;

    /* For each control (in Cmd array), create the associated label and editbox */
    for (i = 0; i < maxCmd; i++) {
	Cmd[i].labelId = GfuiLabelCreate(scrHandle, Cmd[i].name, GFUI_FONT_MEDIUM, x, CmdDispInfo[i].y, GFUI_ALIGN_HL_VB, 0);
	Cmd[i].Id = GfuiButtonStateCreate (scrHandle, "MOUSE_MIDDLE_BUTTON", GFUI_FONT_MEDIUM_C, x+x2, CmdDispInfo[i].y, 0, GFUI_ALIGN_HC_VB, GFUI_MOUSE_DOWN, 
					   (void*)i, onPush, NULL, (tfuiCallback)NULL, onFocusLost);
	/* If first column done, change to the second */
	if (i == maxCmd / 2 - 1) {
	    x = 320;
	    x2 = 220;
	}
    }

    /* Steer Sensibility label and associated editbox */
    GfuiLabelCreate(scrHandle, "Steer Sensibility", GFUI_FONT_MEDIUM, 30, 90, GFUI_ALIGN_HL_VB, 0);
    SteerSensEditId = GfuiEditboxCreate(scrHandle, "", GFUI_FONT_MEDIUM_C,
					200, 90, 80, 8, NULL, (tfuiCallback)NULL, onSteerSensChange);

    /* Steer Dead Zone label and associated editbox */
    GfuiLabelCreate(scrHandle, "Steer Dead Zone", GFUI_FONT_MEDIUM, 340, 90, GFUI_ALIGN_HL_VB, 0);
    DeadZoneEditId = GfuiEditboxCreate(scrHandle, "", GFUI_FONT_MEDIUM_C,
					510, 90, 80, 8, NULL, (tfuiCallback)NULL, onDeadZoneChange);


    /* Save button and associated keyboard shortcut */
    GfuiAddKey(scrHandle, 13 /* Return */, "Save", NULL, onSave, NULL);
    GfuiButtonCreate(scrHandle, "Save", GFUI_FONT_LARGE, 160, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, onSave, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    /* Mouse calibration screen access button */
    MouseCalButton = GfuiButtonCreate(scrHandle, "Calibrate", GFUI_FONT_LARGE, 320, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
				      MouseCalMenuInit(scrHandle, Cmd, maxCmd), DevCalibrate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    /* Joystick/joypad/wheel calibration screen access button */
    JoyCalButton = GfuiButtonCreate(scrHandle, "Calibrate", GFUI_FONT_LARGE, 320, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
				    JoyCalMenuInit(scrHandle, Cmd, maxCmd), DevCalibrate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    /* Cancel button and associated keyboard shortcut */
    GfuiAddKey(scrHandle, 27 /* Escape */, "Cancel", prevMenu, GfuiScreenActivate, NULL);
    GfuiButtonCreate(scrHandle, "Cancel", GFUI_FONT_LARGE, 480, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     prevMenu, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);


    /* General callbacks for keyboard keys and special keys */
    GfuiKeyEventRegister(scrHandle, onKeyAction);
    GfuiSKeyEventRegister(scrHandle, onSKeyAction);

    return scrHandle;
}
