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
#include <raceman.h>
#include <robot.h>
#include "driverconfig.h"
#include <playerpref.h>
#include <js.h>

#ifdef DMALLOC
#include "dmalloc.h"
#endif

static void	*scrHandle1 = NULL;
static void	*scrHandle2 = NULL;
static void	*prevHandle = NULL;

static void	*PrefHdle = NULL;

static void joyCalMenuInit(void);


#define NB_CMD	14

int	CmdButton[NB_CMD] = {-1, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, -1, -1};

static char	*CmdAttrName[NB_CMD] = {
    HM_ATT_GEAR_R,
    HM_ATT_GEAR_N,
    HM_ATT_GEAR_1,
    HM_ATT_GEAR_2,
    HM_ATT_GEAR_3,
    HM_ATT_GEAR_4,
    HM_ATT_GEAR_5,
    HM_ATT_GEAR_6,
    HM_ATT_UP_SHFT,
    HM_ATT_DN_SHFT,
    HM_ATT_ASR_CMD,
    HM_ATT_ABS_CMD,
    HM_ATT_THROTTLE,
    HM_ATT_BRAKE
};

int butId[NB_CMD];

static char *Btn[] = {"BTN1", "BTN2", "BTN3", "BTN4", "BTN5", "BTN6", "BTN7", "BTN8", "BTN9", "BTN10", "BTN11", "BTN12", "BTN13", "BTN14", "BTN15", "BTN16",
		      "BTN17", "BTN18", "BTN19", "BTN20", "BTN21", "BTN22", "BTN23", "BTN24", "BTN25", "BTN26", "BTN27", "BTN28", "BTN29", "BTN30", "BTN31", "BTN32"};
static char *Axis[] = {"AXIS0", "AXIS1", "AXIS2", "AXIS3", "AXIS4", "AXIS5", "AXIS6", "AXIS7", "AXIS8", "AXIS9", "AXIS10", "AXIS11", "AXIS12"};

char *Yn[] = {HM_VAL_YES, HM_VAL_NO};

static jsJoystick *js0 = NULL;

static void
updateButtonText(void)
{
    int i;
    
    for (i = 0; i < NB_CMD; i++) {
	if (CmdButton[i] != -1) {
	    GfuiButtonSetText (scrHandle1, butId[i], Btn[CmdButton[i]]);
	} else {
	    GfuiButtonSetText (scrHandle1, butId[i], "---");
	}
    }
    
}

static float 	ax0[_JS_MAX_AXES];
static int	rawb = 0;

static int CurrentCmd;

static void
Idle1(void)
{
    int		mask;
    int		b, i;
    
    js0->read(&b, ax0);

    /* Joystick buttons */
    for (i = 0, mask = 1; i < 32; i++, mask *= 2) {
	if (((b & mask) != 0) && ((rawb & mask) == 0)) {
	    /* Button i fired */
	    glutIdleFunc(GfuiIdle);
	    GfuiButtonSetText (scrHandle1, butId[CurrentCmd], Btn[i]);
	    CmdButton[CurrentCmd] = i;
	    GfParmSetStr(PrefHdle, HM_SECT_JSPREF, CmdAttrName[CurrentCmd], Btn[i]);
	    glutPostRedisplay();
	    rawb = b;
	    return;
	}
    }
    rawb = b;
}


static void
onPush1(void *vi)
{
    int i = (int)vi;
    
    CurrentCmd = i;
    GfuiButtonSetText (scrHandle1, butId[i], "");
    CmdButton[i] = -1;
    GfParmSetStr(PrefHdle, HM_SECT_JSPREF, CmdAttrName[i], "");
    glutIdleFunc(Idle1);
    js0->read(&rawb, ax0); /* initial value */

}

static void
onCancel1(void *param)
{
    GfuiScreenActivate(param);
}

static void
onSave(void * /* dummy */)
{
    GfParmWriteFile(HM_PREF_FILE, PrefHdle, "preferences", GFPARM_PARAMETER, "../../config/params.dtd");
    GfuiScreenActivate(prevHandle);
}


static void
onActivate1(void * /* dummy */)
{
    int		maxButton, cmd;
    char	*prm;
    int		i;

    PrefHdle = GfParmReadFile(HM_PREF_FILE, GFPARM_RMODE_REREAD | GFPARM_RMODE_CREAT);
    
    maxButton = sizeof(Btn)/sizeof(char*);

    /* JOYSTICK SETTINGS */
    for (cmd = 0; cmd < NB_CMD; cmd++) {
	if (CmdButton[cmd] != -1) {
	    prm = GfParmGetStr(PrefHdle, HM_SECT_JSPREF, CmdAttrName[cmd], Btn[CmdButton[cmd]]);
	} else {
	    prm = GfParmGetStr(PrefHdle, HM_SECT_JSPREF, CmdAttrName[cmd], "---");
	}
	for (i = 0; i < maxButton; i++) {
	    if (strcmp(prm, Btn[i]) == 0) {
		CmdButton[cmd] = i;
		break;
	    }
	}
	if (i == maxButton) {
	    CmdButton[cmd] = -1;
	}
    }
    updateButtonText();
}

static void
onFocusLost1(void * /* dummy */)
{
    updateButtonText();
}


void *
TorcsJoystick1MenuInit(void *prevMenu)
{
    int		x, y, x2, dy, i;
    int		maxButton, cmd;
    char	*prm;
    
    if (js0 == NULL) {
	js0 = new jsJoystick(0);
    }
    
    if (js0->notWorking()) {
	/* don't configure the joystick */
	return NULL;
    }

    prevHandle = prevMenu;
    PrefHdle = GfParmReadFile(HM_PREF_FILE, GFPARM_RMODE_REREAD | GFPARM_RMODE_CREAT);

    maxButton = sizeof(Btn)/sizeof(char*);

    /* JOYSTICK SETTINGS */
    for (cmd = 0; cmd < NB_CMD; cmd++) {
	if (CmdButton[cmd] != -1) {
	    prm = GfParmGetStr(PrefHdle, HM_SECT_JSPREF, CmdAttrName[cmd], Btn[CmdButton[cmd]]);
	} else {
	    prm = GfParmGetStr(PrefHdle, HM_SECT_JSPREF, CmdAttrName[cmd], "---");
	}
	for (i = 0; i < maxButton; i++) {
	    if (strcmp(prm, Btn[i]) == 0) {
		CmdButton[cmd] = i;
		break;
	    }
	}
	if (i == maxButton) {
	    CmdButton[cmd] = -1;
	}
    }

    /* screen already created */
    if (scrHandle1) {
	updateButtonText();
	return scrHandle1;
    }
    
    joyCalMenuInit();
    
    scrHandle1 = GfuiScreenCreateEx(NULL, NULL, onActivate1, NULL, NULL, 1);
    #define TITLE1 "Controls"
    GfuiTitleCreate(scrHandle1, TITLE1, strlen(TITLE1));
    GfuiMenuDefaultKeysAdd(scrHandle1);

    GfuiScreenAddBgImg(scrHandle1, "data/img/splash-joyconf.png");

    GfuiLabelCreate(scrHandle1, "Manual", GFUI_FONT_MEDIUM, 160, 380, GFUI_ALIGN_HC_VB, 0);
    GfuiLabelCreate(scrHandle1, "Sequential", GFUI_FONT_MEDIUM, 480, 380, GFUI_ALIGN_HC_VB, 0);

    x = 40;
    x2 = 180;
    y = 340;
    dy = 30;

    for (i = 0; i < NB_CMD; i++) {
	GfuiLabelCreate(scrHandle1, CmdAttrName[i], GFUI_FONT_MEDIUM, x, y, GFUI_ALIGN_HL_VB, 0);
	butId[i] = GfuiButtonStateCreate (scrHandle1, " BTN32 ", GFUI_FONT_MEDIUM, x+x2, y, 0, GFUI_ALIGN_HC_VB, GFUI_MOUSE_DOWN, 
					  (void*)i, onPush1, NULL, (tfuiCallback)NULL, onFocusLost1);
	y -= dy;
	if (i == 7) {
	    x = 360;
	    y = 340;
	} else if ((i == 9) || (i == 11)) {
	    y -= dy;
	}
    }


    updateButtonText();

    GfuiButtonCreate(scrHandle1, "Save", GFUI_FONT_LARGE, 160, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, onSave, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiButtonCreate(scrHandle1, "Calibrate", GFUI_FONT_LARGE, 320, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     scrHandle2, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiButtonCreate(scrHandle1, "Cancel", GFUI_FONT_LARGE, 480, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     prevMenu, onCancel1, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiAddKey(scrHandle1, 27, "Cancel Selection", prevMenu, onCancel1);

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

static float 	axCenter[_JS_MAX_AXES];

static int
getMovedAxis(void)
{
    int		i;
    int		Index = 0;
    float	maxDiff = -1;

    for (i = 0; i < _JS_MAX_AXES; i++) {
	if (maxDiff < fabs(ax0[i] - axCenter[i])) {
	    maxDiff = fabs(ax0[i] - axCenter[i]);
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
    
    switch (CalState) {
    case 0:
	memcpy(axCenter, ax0, sizeof(axCenter));
	CalState = 1;
	break;
    case 1:
	axis = getMovedAxis();
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_LEFTSTEER, Axis[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_LEFTSTEER_MIN, NULL, ax0[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_LEFTSTEER_MAX, NULL, axCenter[axis]);
	GfuiLabelSetText(scrHandle2, LabAxisId[0], Axis[axis]);
	sprintf(buf, "%.2f", ax0[axis]);
	GfuiLabelSetText(scrHandle2, LabMinId[0], buf);
	CalState = 2;
	break;
    case 2:
	axis2 = getMovedAxis();
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_RIGHTSTEER, Axis[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_RIGHTSTEER_MAX, NULL, ax0[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_RIGHTSTEER_MIN, NULL, axCenter[axis]);
	sprintf(buf, "%.2f", ax0[axis]);
	GfuiLabelSetText(scrHandle2, LabMaxId[0], buf);
	if (CmdButton[12] == -1) {
	    CalState = 3;
	} else if (CmdButton[13] == -1) {
	    CalState = 4;
	} else {
	    CalState = 5;
	}
	break;
    case 3:
	axis = getMovedAxis();
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE, Axis[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE_MIN, NULL, axCenter[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE_MAX, NULL, ax0[axis]*1.1);
	GfuiLabelSetText(scrHandle2, LabAxisId[1], Axis[axis]);
	sprintf(buf, "%.2f", axCenter[axis]);
	GfuiLabelSetText(scrHandle2, LabMinId[1], buf);
	sprintf(buf, "%.2f", ax0[axis]*1.1);
	GfuiLabelSetText(scrHandle2, LabMaxId[1], buf);
	if (CmdButton[13] == -1) {
	    CalState = 4;
	} else {
	    CalState = 5;
	}
	break;
    case 4:
	axis = getMovedAxis();
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE, Axis[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE_MIN, NULL, axCenter[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE_MAX, NULL, ax0[axis]*1.1);
	GfuiLabelSetText(scrHandle2, LabAxisId[2], Axis[axis]);
	sprintf(buf, "%.2f", axCenter[axis]);
	GfuiLabelSetText(scrHandle2, LabMinId[2], buf);
	sprintf(buf, "%.2f", ax0[axis]*1.1);
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
    
    js0->read(&b, ax0);

    /* Joystick buttons */
    for (i = 0, mask = 1; i < 32; i++, mask *= 2) {
	if (((b & mask) != 0) && ((rawb & mask) == 0)) {
	    /* Button fired */
	    JoyCalAutomaton();
	    glutPostRedisplay();
	    if (CalState > 4) {
		glutIdleFunc(GfuiIdle);
	    }
	    rawb = b;
	    return;
	}
    }
    rawb = b;
    
}


static void
onActivate2(void * /* dummy */)
{
    int i;
    
    CalState = 0;
    GfuiLabelSetText(scrHandle2, InstId, Instructions[CalState]);
    glutIdleFunc(Idle2);
    js0->read(&rawb, ax0); /* initial value */
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
    GfuiTitleCreate(scrHandle2, TITLE2, strlen(TITLE2));
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

    GfuiAddKey(scrHandle2, 27, "Cancel Selection", NULL, onCancel2);
    
}





