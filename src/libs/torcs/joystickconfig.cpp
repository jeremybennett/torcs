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

static char *Btn[] = {
"BTN1-0","BTN2-0","BTN3-0","BTN4-0","BTN5-0","BTN6-0","BTN7-0","BTN8-0","BTN9-0","BTN10-0","BTN11-0","BTN12-0","BTN13-0","BTN14-0","BTN15-0","BTN16-0",
"BTN17-0","BTN18-0","BTN19-0","BTN20-0","BTN21-0","BTN22-0","BTN23-0","BTN24-0","BTN25-0","BTN26-0","BTN27-0","BTN28-0","BTN29-0","BTN30-0","BTN31-0","BTN32-0",
"BTN1-1","BTN2-1","BTN3-1","BTN4-1","BTN5-1","BTN6-1","BTN7-1","BTN8-1","BTN9-1","BTN10-1","BTN11-1","BTN12-1","BTN13-1","BTN14-1","BTN15-1","BTN16-1",
"BTN17-1","BTN18-1","BTN19-1","BTN20-1","BTN21-1","BTN22-1","BTN23-1","BTN24-1","BTN25-1","BTN26-1","BTN27-1","BTN28-1","BTN29-1","BTN30-1","BTN31-1","BTN32-1",
"BTN1-2","BTN2-2","BTN3-2","BTN4-2","BTN5-2","BTN6-2","BTN7-2","BTN8-2","BTN9-2","BTN10-2","BTN11-2","BTN12-2","BTN13-2","BTN14-2","BTN15-2","BTN16-2",
"BTN17-2","BTN18-2","BTN19-2","BTN20-2","BTN21-2","BTN22-2","BTN23-2","BTN24-2","BTN25-2","BTN26-2","BTN27-2","BTN28-2","BTN29-2","BTN30-2","BTN31-2","BTN32-2",
"BTN1-3","BTN2-3","BTN3-3","BTN4-3","BTN5-3","BTN6-3","BTN7-3","BTN8-3","BTN9-3","BTN10-3","BTN11-3","BTN12-3","BTN13-3","BTN14-3","BTN15-3","BTN16-3",
"BTN17-3","BTN18-3","BTN19-3","BTN20-3","BTN21-3","BTN22-3","BTN23-3","BTN24-3","BTN25-3","BTN26-3","BTN27-3","BTN28-3","BTN29-3","BTN30-3","BTN31-3","BTN32-3",
"BTN1-4","BTN2-4","BTN3-4","BTN4-4","BTN5-4","BTN6-4","BTN7-4","BTN8-4","BTN9-4","BTN10-4","BTN11-4","BTN12-4","BTN13-4","BTN14-4","BTN15-4","BTN16-4",
"BTN17-4","BTN18-4","BTN19-4","BTN20-4","BTN21-4","BTN22-4","BTN23-4","BTN24-4","BTN25-4","BTN26-4","BTN27-4","BTN28-4","BTN29-4","BTN30-4","BTN31-4","BTN32-4",
"BTN1-5","BTN2-5","BTN3-5","BTN4-5","BTN5-5","BTN6-5","BTN7-5","BTN8-5","BTN9-5","BTN10-5","BTN11-5","BTN12-5","BTN13-5","BTN14-5","BTN15-5","BTN16-5",
"BTN17-5","BTN18-5","BTN19-5","BTN20-5","BTN21-5","BTN22-5","BTN23-5","BTN24-5","BTN25-5","BTN26-5","BTN27-5","BTN28-5","BTN29-5","BTN30-5","BTN31-5","BTN32-5",
"BTN1-6","BTN2-6","BTN3-6","BTN4-6","BTN5-6","BTN6-6","BTN7-6","BTN8-6","BTN9-6","BTN10-6","BTN11-6","BTN12-6","BTN13-6","BTN14-6","BTN15-6","BTN16-6",
"BTN17-6","BTN18-6","BTN19-6","BTN20-6","BTN21-6","BTN22-6","BTN23-6","BTN24-6","BTN25-6","BTN26-6","BTN27-6","BTN28-6","BTN29-6","BTN30-6","BTN31-6","BTN32-6",
"BTN1-7","BTN2-7","BTN3-7","BTN4-7","BTN5-7","BTN6-7","BTN7-7","BTN8-7","BTN9-7","BTN10-7","BTN11-7","BTN12-7","BTN13-7","BTN14-7","BTN15-7","BTN16-7",
};

static char *Axis[] = {
    "AXIS0-0", "AXIS1-0", "AXIS2-0", "AXIS3-0", "AXIS4-0", "AXIS5-0", "AXIS6-0", "AXIS7-0", "AXIS8-0", "AXIS9-0", "AXIS10-0", "AXIS11-0",
    "AXIS0-1", "AXIS1-1", "AXIS2-1", "AXIS3-1", "AXIS4-1", "AXIS5-1", "AXIS6-1", "AXIS7-1", "AXIS8-1", "AXIS9-1", "AXIS10-1", "AXIS11-1",
    "AXIS0-2", "AXIS1-2", "AXIS2-2", "AXIS3-2", "AXIS4-2", "AXIS5-2", "AXIS6-2", "AXIS7-2", "AXIS8-2", "AXIS9-2", "AXIS10-2", "AXIS11-2",
    "AXIS0-3", "AXIS1-3", "AXIS2-3", "AXIS3-3", "AXIS4-3", "AXIS5-3", "AXIS6-3", "AXIS7-3", "AXIS8-3", "AXIS9-3", "AXIS10-3", "AXIS11-3",
    "AXIS0-4", "AXIS1-4", "AXIS2-4", "AXIS3-4", "AXIS4-4", "AXIS5-4", "AXIS6-4", "AXIS7-4", "AXIS8-4", "AXIS9-4", "AXIS10-4", "AXIS11-4",
    "AXIS0-5", "AXIS1-5", "AXIS2-5", "AXIS3-5", "AXIS4-5", "AXIS5-5", "AXIS6-5", "AXIS7-5", "AXIS8-5", "AXIS9-5", "AXIS10-5", "AXIS11-5",
    "AXIS0-6", "AXIS1-6", "AXIS2-6", "AXIS3-6", "AXIS4-6", "AXIS5-6", "AXIS6-6", "AXIS7-6", "AXIS8-6", "AXIS9-6", "AXIS10-6", "AXIS11-6",
    "AXIS0-7", "AXIS1-7", "AXIS2-7", "AXIS3-7", "AXIS4-7", "AXIS5-7", "AXIS6-7", "AXIS7-7", "AXIS8-7", "AXIS9-7", "AXIS10-7", "AXIS11-7"
};

char *Yn[] = {HM_VAL_YES, HM_VAL_NO};

static jsJoystick *js[NUM_JOY] = {NULL};

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

static float 	ax[MAX_AXES * NUM_JOY] = {0};
static int	rawb[NUM_JOY] = {0};

static int CurrentCmd;

static void
Idle1(void)
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
		    /* Button i fired */
		    glutIdleFunc(GfuiIdle);
		    GfuiButtonSetText (scrHandle1, butId[CurrentCmd], Btn[i + 32 * index]);
		    CmdButton[CurrentCmd] = i + 32 * index;
		    GfParmSetStr(PrefHdle, HM_SECT_JSPREF, CmdAttrName[CurrentCmd], Btn[i + 32 * index]);
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
    GfuiButtonSetText (scrHandle1, butId[i], "");
    CmdButton[i] = -1;
    GfParmSetStr(PrefHdle, HM_SECT_JSPREF, CmdAttrName[i], "");
    glutIdleFunc(Idle1);
    
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
    int		index;
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
    
    switch (CalState) {
    case 0:
	memcpy(axCenter, ax, sizeof(axCenter));
	CalState = 1;
	break;
    case 1:
	axis = getMovedAxis();
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_LEFTSTEER, Axis[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_LEFTSTEER_MIN, NULL, ax[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_LEFTSTEER_MAX, NULL, axCenter[axis]);
	GfuiLabelSetText(scrHandle2, LabAxisId[0], Axis[axis]);
	sprintf(buf, "%.2f", ax[axis]);
	GfuiLabelSetText(scrHandle2, LabMinId[0], buf);
	CalState = 2;
	break;
    case 2:
	axis2 = getMovedAxis();
	GfParmSetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_RIGHTSTEER, Axis[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_RIGHTSTEER_MAX, NULL, ax[axis]);
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_RIGHTSTEER_MIN, NULL, axCenter[axis]);
	sprintf(buf, "%.2f", ax[axis]);
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
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE_MAX, NULL, ax[axis]*1.1);
	GfuiLabelSetText(scrHandle2, LabAxisId[1], Axis[axis]);
	sprintf(buf, "%.2f", axCenter[axis]);
	GfuiLabelSetText(scrHandle2, LabMinId[1], buf);
	sprintf(buf, "%.2f", ax[axis]*1.1);
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
	GfParmSetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE_MAX, NULL, ax[axis]*1.1);
	GfuiLabelSetText(scrHandle2, LabAxisId[2], Axis[axis]);
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





