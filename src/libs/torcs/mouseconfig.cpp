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

#include <tgf.h>
#include <track.h>
#include <robot.h>
#include <playerpref.h>

#include "mouseconfig.h"

static void 	*scrHandle = NULL;
static void	*prevHandle = NULL;

static void	*PrefHdle = NULL;

typedef struct
{
    char	*name;
    tCtrlRef	ref;
    int		Id;
} tCmdInfo;

static tCmdInfo Cmd[] = {
    {HM_ATT_GEAR_R,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_GEAR_N,     {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_UP_SHFT,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_DN_SHFT,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_ASR_CMD,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_ABS_CMD,    {-1, GFCTRL_TYPE_NOT_AFFECTED}, 0},
    {HM_ATT_THROTTLE,   {1,  GFCTRL_TYPE_MOUSE_BUT}, 0},
    {HM_ATT_BRAKE,      {2,  GFCTRL_TYPE_MOUSE_BUT}, 0}
};

/* static int maxCmd = sizeof(Cmd) / sizeof(Cmd[0]); */
static int maxCmd = 0;

static char buf[1024];

static int SteerSensEditId;
static int DeadZoneEditId;


static void
onSteerSensChange(void * /* dummy */)
{
    char	*val;
    float	fv;
    char	buf[32];

    val = GfuiEditboxGetString(scrHandle, SteerSensEditId);
    if (sscanf(val, "%f", &fv) == 1) {
	sprintf(buf, "%f", fv);
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
	GfuiEditboxSetString(scrHandle, DeadZoneEditId, buf);
    } else {
	GfuiEditboxSetString(scrHandle, SteerSensEditId, "");
    }
    
}

static void
onSave(void * /* dummy */)
{
    char	*val;
    float	fv;
    int		i;
    char	*str;

    val = GfuiEditboxGetString(scrHandle, SteerSensEditId);
    if (sscanf(val, "%f", &fv) == 1) {
	GfParmSetNum(PrefHdle, HM_SECT_MOUSEPREF, HM_ATT_STEER_POW, NULL, fv);
    } 

    val = GfuiEditboxGetString(scrHandle, DeadZoneEditId);
    if (sscanf(val, "%f", &fv) == 1) {
	GfParmSetNum(PrefHdle, HM_SECT_MOUSEPREF, HM_ATT_STEER_DEAD, NULL, fv);
    }

    for (i = 0; i < maxCmd; i++) {
	str = GfctrlGetNameByRef(Cmd[i].ref.type, Cmd[i].ref.index);
	if (str) {
	    GfParmSetStr(PrefHdle, HM_SECT_MOUSEPREF, Cmd[i].name, str);
	} else {
	    GfParmSetStr(PrefHdle, HM_SECT_MOUSEPREF, Cmd[i].name, "");
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
    float	fv;

    for (i = 0; i < maxCmd; i++) {
	str = GfctrlGetNameByRef(Cmd[i].ref.type, Cmd[i].ref.index);
	if (str) {
	    GfuiButtonSetText (scrHandle, Cmd[i].Id, str);
	} else {
	    GfuiButtonSetText (scrHandle, Cmd[i].Id, "---");
	}
    }

    fv = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, HM_ATT_STEER_POW, NULL, 0);
    sprintf(buf, "%f", fv);
    GfuiEditboxSetString(scrHandle, SteerSensEditId, buf);

    fv = GfParmGetNum(PrefHdle, HM_SECT_MOUSEPREF, HM_ATT_STEER_DEAD, NULL, 0);
    sprintf(buf, "%f", fv);
    GfuiEditboxSetString(scrHandle, DeadZoneEditId, buf);
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

    InputWaited = 0;
    updateButtonText();
    return 1;
}

static void
onPush(void *vi)
{
    int i = (int)vi;
    
    CurrentCmd = i;
    GfuiButtonSetText (scrHandle, Cmd[i].Id, "");
    Cmd[i].ref.index = -1;
    Cmd[i].ref.type = GFCTRL_TYPE_NOT_AFFECTED;
    GfParmSetStr(PrefHdle, HM_SECT_JSPREF, Cmd[i].name, "");
    InputWaited = 1;
}

static void
onActivate(void * /* dummy */)
{
    int		cmd;
    char	*prm;
    tCtrlRef	*ref;

    sprintf(buf, "%s%s", LocalDir, HM_PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    /* JOYSTICK SETTINGS */
    for (cmd = 0; cmd < maxCmd; cmd++) {
	prm = GfctrlGetNameByRef(Cmd[cmd].ref.type, Cmd[cmd].ref.index);
	if (!prm) {
	    prm = "---";
	}
	prm = GfParmGetStr(PrefHdle, HM_SECT_MOUSEPREF, Cmd[cmd].name, prm);
	ref = GfctrlGetRefByName(prm);
	Cmd[cmd].ref.type = ref->type;
	Cmd[cmd].ref.index = ref->index;
    }
    updateButtonText();
}


void *
TorcsMouseMenuInit(void *prevMenu)
{
    int		x, y, x2, dy, i;
    int		cmd;
    char	*prm;
    tCtrlRef	*ref;

    prevHandle = prevMenu;
    sprintf(buf, "%s%s", LocalDir, HM_PREF_FILE);
    PrefHdle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);

    for (cmd = 0; cmd < maxCmd; cmd++) {
	prm = GfctrlGetNameByRef(Cmd[cmd].ref.type, Cmd[cmd].ref.index);
	if (!prm) {
	    prm = "---";
	}
	prm = GfParmGetStr(PrefHdle, HM_SECT_MOUSEPREF, Cmd[cmd].name, prm);
	ref = GfctrlGetRefByName(prm);
	Cmd[cmd].ref.type = ref->type;
	Cmd[cmd].ref.index = ref->index;
    }

    if (scrHandle) {
	return scrHandle;
    }

    scrHandle = GfuiScreenCreateEx((float*)NULL, NULL, onActivate, NULL, (tfuiCallback)NULL, 1);
    GfuiTitleCreate(scrHandle, "Mouse Configuration", 0);

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
    GfuiButtonCreate(scrHandle, "Save", GFUI_FONT_LARGE, 210, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     NULL, onSave, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);

    GfuiAddKey(scrHandle, 27, "Cancel", prevMenu, GfuiScreenActivate, NULL);
    GfuiButtonCreate(scrHandle, "Cancel", GFUI_FONT_LARGE, 430, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		     prevMenu, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);


    GfuiKeyEventRegister(scrHandle, onKeyAction);
    GfuiSKeyEventRegister(scrHandle, onSKeyAction);

    return scrHandle;
}
