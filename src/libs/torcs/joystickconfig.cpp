/***************************************************************************

    file                 : joystickconfig.cpp
    created              : Wed Mar 21 21:46:11 CET 2001
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgf.h>
#include <track.h>
#include <robot.h>
#include "driverconfig.h"
#include <playerpref.h>
#include <js.h>

static void	*scrHandle1 = NULL;
static void	*scrHandle2 = NULL;
static void	*prevHandle = NULL;

static void	*PrefHdle = NULL;

static void joyCalMenuInit(void);

static char buf[1024];

typedef struct
{
    char	*name;
    tCtrlRef	ref;
    int		Id;
} tCmdInfo;

static tCmdInfo Cmd[] = {
    {HM_ATT_GEAR_R,   {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_GEAR_N,   {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_GEAR_1,   {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_GEAR_2,   {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_GEAR_3,   {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_GEAR_4,   {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_GEAR_5,   {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_GEAR_6,   {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_UP_SHFT,  {0,  GFCTRL_TYPE_JOY_BUT}, 0},
    {HM_ATT_DN_SHFT,  {1,  GFCTRL_TYPE_JOY_BUT}, 0},
    {HM_ATT_ASR_CMD,  {2,  GFCTRL_TYPE_JOY_BUT}, 0},
    {HM_ATT_ABS_CMD,  {3,  GFCTRL_TYPE_JOY_BUT}, 0},
    {HM_ATT_THROTTLE, {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_BRAKE,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0}
};
     
     
static int maxCmd = sizeof(Cmd) / sizeof(Cmd[0]);

static jsJoystick *js[NUM_JOY] = {NULL};

static int SteerSensEditId;

static void
updateButtonText(void)
{
    int		i;
    char	*str;
    float	fv;

    for (i = 0; i < maxCmd; i++) {
	str = GfctrlGetNameByRef(Cmd[i].ref.type, Cmd[i].ref.index);
	if (str) {
	    GfuiButtonSetText (scrHandle1, Cmd[i].Id, str);
	} else {
	    GfuiButtonSetText (scrHandle1, Cmd[i].Id, "---");
	}
    }

    fv = GfParmGetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_STEER_SENS, NULL, 0);
    sprintf(buf, "%f", fv);
    GfuiEditboxSetString(scrHandle1, SteerSensEditId, buf);

}

static float 	ax[MAX_AXES * NUM_JOY] = {0};
static int	rawb[NUM_JOY] = {0};

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
    glutPostRedisplay();
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
    glutPostRedisplay();
    return 1;
}


static void
Idle1(void)
{
    int		mask;
    int		b, i;
    int		index;
    char	*str;

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
		    GfuiButtonSetText (scrHandle1, Cmd[CurrentCmd].Id, str);
		    Cmd[CurrentCmd].ref.index = i + 32 * index;
		    Cmd[CurrentCmd].ref.type = GFCTRL_TYPE_JOY_BUT;
		    GfParmSetStr(PrefHdle, HM_SECT_JSPREF, Cmd[CurrentCmd].name, str);
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
onPush1(void *vi)
{
    int	index;    
    int i = (int)vi;
    
    CurrentCmd = i;
    GfuiButtonSetText (scrHandle1, Cmd[i].Id, "");
    Cmd[i].ref.index = -1;
    Cmd[i].ref.type = GFCTRL_TYPE_NOT_AFFECTED;
    GfParmSetStr(PrefHdle, HM_SECT_JSPREF, Cmd[i].name, "");
    glutIdleFunc(Idle1);
    InputWaited = 1;

    for (index = 0; index < NUM_JOY; index++) {
	if (js[index]) {
	    js[index]->read(&rawb[index], &ax[index * MAX_AXES]); /* initial value */
	}
    }
}

static void
onCancel1(void *param)
{
    GfuiScreenActivate(param);
}

static void
onSave(void * /* dummy */)
{
    GfParmWriteFile(NULL, PrefHdle, "preferences", GFPARM_PARAMETER, "../../config/params.dtd");
    GfuiScreenActivate(prevHandle);
}


static void
onActivate1(void * /* dummy */)
{
    int		cmd;
    char	*prm;
    tCtrlRef	*ref;

    sprintf(buf, "%s%s", GetLocalDir(), HM_PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    /* JOYSTICK SETTINGS */
    for (cmd = 0; cmd < maxCmd; cmd++) {
	prm = GfctrlGetNameByRef(Cmd[cmd].ref.type, Cmd[cmd].ref.index);
	if (!prm) {
	    prm = "---";
	}
	prm = GfParmGetStr(PrefHdle, HM_SECT_JSPREF, Cmd[cmd].name, prm);
	ref = GfctrlGetRefByName(prm);
	Cmd[cmd].ref.type = ref->type;
	Cmd[cmd].ref.index = ref->index;
    }
    updateButtonText();
}

static void
onFocusLost1(void * /* dummy */)
{
    updateButtonText();
}

static void
onSteerSensChange(void * /* dummy */)
{
    char	*val;
    float	fv;
    char	buf[32];

    val = GfuiEditboxGetString(scrHandle1, SteerSensEditId);
    if (sscanf(val, "%f", &fv) == 1) {
	sprintf(buf, "%f", fv);
	GfuiEditboxSetString(scrHandle1, SteerSensEditId, buf);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_STEER_SENS, NULL, fv);
    } else {
	GfuiEditboxSetString(scrHandle1, SteerSensEditId, "");
    }
    
}

void *
TorcsJoystick1MenuInit(void *prevMenu)
{
    int		x, y, x2, dy, i;
    int		cmd;
    char	*prm;
    int		index;
    tCtrlRef	*ref;
    int		joyPresent = 0;

    for (index = 0; index < NUM_JOY; index++) {
	if (js[index] == NULL) {
	    js[index] = new jsJoystick(index);
	}
    
	if (js[index]->notWorking()) {
	    /* don't configure the joystick */
	    js[index] = NULL;
	} else {
	    joyPresent = 1;
	}
    }
    if (!joyPresent) {
	return NULL;
    }

    prevHandle = prevMenu;
    sprintf(buf, "%s%s", GetLocalDir(), HM_PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    /* JOYSTICK SETTINGS */
    for (cmd = 0; cmd < maxCmd; cmd++) {
	prm = GfctrlGetNameByRef(Cmd[cmd].ref.type, Cmd[cmd].ref.index);
	if (!prm) {
	    prm = "---";
	}
	prm = GfParmGetStr(PrefHdle, HM_SECT_JSPREF, Cmd[cmd].name, prm);
	ref = GfctrlGetRefByName(prm);
	Cmd[cmd].ref.type = ref->type;
	Cmd[cmd].ref.index = ref->index;
    }

    /* screen already created */
    if (scrHandle1) {
	updateButtonText();
	return scrHandle1;
    }
    
    joyCalMenuInit();
    
    scrHandle1 = GfuiScreenCreateEx(NULL, NULL, onActivate1, NULL, NULL, 1);
    GfuiTitleCreate(scrHandle1, "Joystick Configuration", 0);
    GfuiMenuDefaultKeysAdd(scrHandle1);

    GfuiScreenAddBgImg(scrHandle1, "data/img/splash-joyconf.png");

    GfuiLabelCreate(scrHandle1, "Manual", GFUI_FONT_MEDIUM, 160, 380, GFUI_ALIGN_HC_VB, 0);
    GfuiLabelCreate(scrHandle1, "Sequential", GFUI_FONT_MEDIUM, 480, 380, GFUI_ALIGN_HC_VB, 0);

    x = 40;
    x2 = 180;
    y = 340;
    dy = 30;

    for (i = 0; i < maxCmd; i++) {
	GfuiLabelCreate(scrHandle1, Cmd[i].name, GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
	Cmd[i].Id = GfuiButtonStateCreate (scrHandle1, "                ", GFUI_FONT_MEDIUM, x+x2, y, 0, GFUI_ALIGN_HC_VB, GFUI_MOUSE_DOWN, 
					   (void*)i, onPush1, NULL, (tfuiCallback)NULL, onFocusLost1);
	y -= dy;
	if (i == 7) {
	    x = 360;
	    y = 340;
	} else if ((i == 9) || (i == 11)) {
	    y -= dy;
	}
    }

    GfuiLabelCreate(scrHandle1, "Steer Sensibility", GFUI_FONT_MEDIUM, 40, 90, GFUI_ALIGN_HL_VB, 0);
    SteerSensEditId = GfuiEditboxCreate(scrHandle1, "", GFUI_FONT_MEDIUM_C,
					210, 90, 80, 8, NULL, (tfuiCallback)NULL, onSteerSensChange);

    updateButtonText();

    GfuiButtonCreate(scrHandle1, "Save", GFUI_FONT_LARGE, 160, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, onSave, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiButtonCreate(scrHandle1, "Calibrate", GFUI_FONT_LARGE, 320, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     scrHandle2, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiButtonCreate(scrHandle1, "Cancel", GFUI_FONT_LARGE, 480, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     prevMenu, onCancel1, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiAddKey(scrHandle1, 27, "Cancel Selection", prevMenu, onCancel1, NULL);

    GfuiKeyEventRegister(scrHandle1, onKeyAction);
    GfuiSKeyEventRegister(scrHandle1, onSKeyAction);
    
    return scrHandle1;
}

#define NB_STEPS	5

static char *Instructions[] = {
    "Center the joystick then press a button",
    "Steer left then press a button",
    "Steer right then press a button",
    "Apply full throttle then press a button",
    "Apply full brake then press a button",
    "Calibration terminated",
    "Calibration failed"
};

static int CalState;
static int InstId;

static char *LabName[] = { "Steer", "Throttle", "Brake" };
static int  LabAxisId[3];
static int  LabMinId[3];
static int  LabMaxId[3];



static void
onCancel2(void * /* dummy */)
{
    GfuiScreenActivate(prevHandle);
}

static float 	axCenter[MAX_AXES * NUM_JOY];

static int
getMovedAxis(void)
{
    int		i;
    int		Index = 0;
    float	maxDiff = -1;

    for (i = 0; i < MAX_AXES * NUM_JOY; i++) {
	if (maxDiff < fabs(ax[i] - axCenter[i])) {
	    maxDiff = fabs(ax[i] - axCenter[i]);
	    Index = i;
	}
    }
    return Index;
}


static void
JoyCalAutomaton(void)
{
    static int axis, axis2;
    char buf[128];
    char *str;

    switch (CalState) {
    case 0:
	memcpy(axCenter, ax, sizeof(axCenter));
	CalState = 1;
	break;
    case 1:
	axis = getMovedAxis();
	str = GfctrlGetNameByRef(GFCTRL_TYPE_JOY_AXIS, axis);
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_LEFTSTEER, str);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_LEFTSTEER_MIN, NULL, ax[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_LEFTSTEER_MAX, NULL, axCenter[axis]);
	GfuiLabelSetText(scrHandle2, LabAxisId[0], str);
	sprintf(buf, "%.2f", ax[axis]);
	GfuiLabelSetText(scrHandle2, LabMinId[0], buf);
	CalState = 2;
	break;
    case 2:
	axis2 = getMovedAxis();
	str = GfctrlGetNameByRef(GFCTRL_TYPE_JOY_AXIS, axis);
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_RIGHTSTEER, str);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_RIGHTSTEER_MAX, NULL, ax[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_RIGHTSTEER_MIN, NULL, axCenter[axis]);
	sprintf(buf, "%.2f", ax[axis]);
	GfuiLabelSetText(scrHandle2, LabMaxId[0], buf);
	if ((Cmd[12].ref.type == GFCTRL_TYPE_NOT_AFFECTED) ||
	    (Cmd[12].ref.type == GFCTRL_TYPE_JOY_AXIS)) {
	    CalState = 3;
	} else {
	    if ((Cmd[13].ref.type == GFCTRL_TYPE_NOT_AFFECTED) ||
		(Cmd[13].ref.type == GFCTRL_TYPE_JOY_AXIS)) {
		CalState = 4;
	    } else {
		CalState = 5;
	    }
	}
	break;
    case 3:
	axis = getMovedAxis();
	str = GfctrlGetNameByRef(GFCTRL_TYPE_JOY_AXIS, axis);
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE, str);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE_MIN, NULL, axCenter[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE_MAX, NULL, ax[axis]*1.1);
	GfuiLabelSetText(scrHandle2, LabAxisId[1], str);
	sprintf(buf, "%.2f", axCenter[axis]);
	GfuiLabelSetText(scrHandle2, LabMinId[1], buf);
	sprintf(buf, "%.2f", ax[axis]*1.1);
	GfuiLabelSetText(scrHandle2, LabMaxId[1], buf);
	if ((Cmd[13].ref.type == GFCTRL_TYPE_NOT_AFFECTED) ||
	    (Cmd[13].ref.type == GFCTRL_TYPE_JOY_AXIS)) {
	    CalState = 4;
	} else {
	    CalState = 5;
	}
	break;
    case 4:
	axis = getMovedAxis();
	str = GfctrlGetNameByRef(GFCTRL_TYPE_JOY_AXIS, axis);
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE, str);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE_MIN, NULL, axCenter[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE_MAX, NULL, ax[axis]*1.1);
	GfuiLabelSetText(scrHandle2, LabAxisId[2], str);
	sprintf(buf, "%.2f", axCenter[axis]);
	GfuiLabelSetText(scrHandle2, LabMinId[2], buf);
	sprintf(buf, "%.2f", ax[axis]*1.1);
	GfuiLabelSetText(scrHandle2, LabMaxId[2], buf);
	CalState = 5;
	break;
    }
    GfuiLabelSetText(scrHandle2, InstId, Instructions[CalState]);
}


static void
Idle2(void)
{
    int		mask;
    int		b, i;
    int		index;

    for (index = 0; index < NUM_JOY; index++) {
	if (js[index]) {
	    js[index]->read(&b, &ax[index * MAX_AXES]);

	    /* Joystick buttons */
	    for (i = 0, mask = 1; i < 32; i++, mask *= 2) {
		if (((b & mask) != 0) && ((rawb[index] & mask) == 0)) {
		    /* Button fired */
		    JoyCalAutomaton();
		    glutPostRedisplay();
		    if (CalState > 4) {
			glutIdleFunc(GfuiIdle);
		    }
		    rawb[index] = b;
		    return;
		}
	    }
	    rawb[index] = b;
	}
    }
}


static void
onActivate2(void * /* dummy */)
{
    int i;
    int index;
    
    CalState = 0;
    GfuiLabelSetText(scrHandle2, InstId, Instructions[CalState]);
    glutIdleFunc(Idle2);
    for (index = 0; index < NUM_JOY; index++) {
	if (js[index]) {
	    js[index]->read(&rawb[index], &ax[index * MAX_AXES]); /* initial value */
	}
    }
    for (i = 0; i < 3; i++) {
	GfuiLabelSetText(scrHandle2, LabAxisId[i], "");
	GfuiLabelSetText(scrHandle2, LabMinId[i], "");
 	GfuiLabelSetText(scrHandle2, LabMaxId[i], "");
    }
}


static void
joyCalMenuInit(void)
{
    int x, y, dy, i;
    
    scrHandle2 = GfuiScreenCreateEx(NULL, NULL, onActivate2, NULL, NULL, 1);
    #define TITLE2 "Joystick Calibration"
    GfuiTitleCreate(scrHandle2, TITLE2, 0);
    GfuiMenuDefaultKeysAdd(scrHandle2);

    GfuiScreenAddBgImg(scrHandle2, "data/img/splash-joycal.png");

    x = 128;
    y = 300;
    dy = 50;
    
    for (i = 0; i < 3; i++) {
	GfuiLabelCreate(scrHandle2, LabName[i], GFUI_FONT_LARGE, x, y, GFUI_ALIGN_HC_VC, 0);
	LabAxisId[i] = GfuiLabelCreate(scrHandle2, "                ", GFUI_FONT_MEDIUM, 2 * x, y, GFUI_ALIGN_HC_VC, 0);
	LabMinId[i] = GfuiLabelCreate(scrHandle2,  "                ", GFUI_FONT_MEDIUM, 3 * x, y, GFUI_ALIGN_HC_VC, 0);
	LabMaxId[i] = GfuiLabelCreate(scrHandle2,  "                ", GFUI_FONT_MEDIUM, 4 * x, y, GFUI_ALIGN_HC_VC, 0);
	y -= dy;
    }

    InstId = GfuiLabelCreate(scrHandle2, Instructions[CalState], GFUI_FONT_MEDIUM, 320, 80, GFUI_ALIGN_HC_VB, 0);

    GfuiButtonCreate(scrHandle2, "Save", GFUI_FONT_LARGE, 160, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
     NULL, onSave, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    
    GfuiButtonCreate(scrHandle2, "Reset", GFUI_FONT_LARGE, 320, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
     NULL, onActivate2, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
    
    GfuiButtonCreate(scrHandle2, "Cancel", GFUI_FONT_LARGE, 480, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
     NULL, onCancel2, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiAddKey(scrHandle2, 27, "Cancel Selection", NULL, onCancel2, NULL);
    
}





