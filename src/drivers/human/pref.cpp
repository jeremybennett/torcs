/***************************************************************************

    file                 : pref.cpp
    created              : Sat Apr 29 16:51:03 CEST 2000
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
    		
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <tgf.h>

#include <track.h>
#include <car.h>
#include <raceman.h>
#include <robottools.h>
#include <robot.h>
#include <playerpref.h>
#include <js.h>
#include "pref.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

void	*PrefHdle;

int	Transmission;

int	NbPitStopProg		= 0;

int	ParamAsr		= 0;	/* anti-slip accel */
int	ParamAbs		= 1;	/* anti-lock brake */
int	RelButNeutral		= 0;
int	SeqShftAllowNeutral	= 0;

#define NB_CMD	16

tControlCmd	CmdControl[NB_CMD] = {
    {HM_ATT_UP_SHFT,    CMD_TYPE_JOY_BUT,       0, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_DN_SHFT,    CMD_TYPE_JOY_BUT,       1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_ASR_CMD,    CMD_TYPE_JOY_BUT,       2, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_ABS_CMD,    CMD_TYPE_JOY_BUT,       3, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_R,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_N,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_1,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_2,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_3,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_4,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_5,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_6,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_THROTTLE,   CMD_TYPE_ANALOG,        1, HM_ATT_THROTTLE_MIN,   0.0, 0.0, HM_ATT_THROTTLE_MAX,   1.0, HM_ATT_THROTTLE_SENS,   1.0, HM_ATT_THROTTLE_POW,   2.0},
    {HM_ATT_BRAKE,      CMD_TYPE_ANALOG,        1, HM_ATT_BRAKE_MIN,      0.0, 0.0, HM_ATT_BRAKE_MAX,      1.0, HM_ATT_BRAKE_SENS,      1.0, HM_ATT_BRAKE_POW,      2.0},
    {HM_ATT_LEFTSTEER,  CMD_TYPE_ANALOG,        0, HM_ATT_LEFTSTEER_MIN,  0.0, 0.0, HM_ATT_LEFTSTEER_MAX,  1.0, HM_ATT_LEFTSTEER_SENS,  2.0, HM_ATT_LEFTSTEER_POW,  1.0},
    {HM_ATT_RIGHTSTEER, CMD_TYPE_ANALOG,        0, HM_ATT_RIGHTSTEER_MIN, 0.0, 0.0, HM_ATT_RIGHTSTEER_MAX, 1.0, HM_ATT_RIGHTSTEER_SENS, 2.0, HM_ATT_RIGHTSTEER_POW, 1.0}
};


static char *Btn[] = {"BTN1", "BTN2", "BTN3", "BTN4", "BTN5", "BTN6", "BTN7", "BTN8", "BTN9", "BTN10", "BTN11", "BTN12", "BTN13", "BTN14", "BTN15", "BTN16",
		      "BTN17", "BTN18", "BTN19", "BTN20", "BTN21", "BTN22", "BTN23", "BTN24", "BTN25", "BTN26", "BTN27", "BTN28", "BTN29", "BTN30", "BTN31", "BTN32"};
static char *Axis[] = {"AXIS0", "AXIS1", "AXIS2", "AXIS3", "AXIS4", "AXIS5", "AXIS6", "AXIS7", "AXIS8", "AXIS9", "AXIS10", "AXIS11", "AXIS12"};

static char *MouseBtn[] = {"MOUSE_LEFT_BTN", "MOUSE_MIDDLE_BTN", "MOUSE_RIGHT_BTN"}; /* glut order */
static char *MouseAxis[] = {"MOUSE_LEFT", "MOUSE_RIGHT", "MOUSE_UP", "MOUSE_DOWN"};


char *Yn[] = {HM_VAL_YES, HM_VAL_NO};

extern jsJoystick js0;

void
HmReadPrefs(int index)
{
    char	*prm;
    char	*defaultSettings;
    char	sstring[256];
    uint	i, cmd;
    float	tmp;
    uint	maxButton;
    uint	maxAxis;
    uint	maxMouseButton;
    uint	maxMouseAxis;
    
    
    sprintf(sstring, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, index);

    PrefHdle = GfParmReadFile(HM_PREF_FILE, GFPARM_RMODE_REREAD | GFPARM_RMODE_CREAT);

    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_TRANS, HM_VAL_AUTO);
    if (strcmp(prm, HM_VAL_AUTO) == 0) {
	Transmission = 0;
    } else {
	Transmission = 1;
    }

    /* Parameters Settings */
    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_ABS, Yn[ParamAbs]);
    if (strcmp(prm, Yn[0]) == 0) {
	ParamAbs = 1;
    } else {
	ParamAbs = 0;
    }
    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_ASR, Yn[ParamAsr]);
    if (strcmp(prm, Yn[0]) == 0) {
	ParamAsr = 1;
    } else {
	ParamAsr = 0;
    }

    maxButton      = sizeof(Btn)       / sizeof(char*);
    maxAxis        = sizeof(Axis)      / sizeof(char*);
    maxMouseButton = sizeof(MouseBtn)  / sizeof(char*);
    maxMouseAxis   = sizeof(MouseAxis) / sizeof(char*);

    if (!js0.notWorking()) {
	defaultSettings = HM_SECT_JSPREF;
    } else {
	defaultSettings = HM_SECT_MOUSEPREF;
    }

    /* Command Settings */
    for (cmd = 0; cmd < NB_CMD; cmd++) {
	switch (CmdControl[cmd].type) {
	case CMD_TYPE_ANALOG:
	    prm = Axis[CmdControl[cmd].val];
	    break;
	case CMD_TYPE_JOY_BUT:
	    prm = Btn[CmdControl[cmd].val];
	    break;
	case CMD_TYPE_MOUSE_BUT:
	    prm = MouseBtn[CmdControl[cmd].val];
	    break;
	case CMD_TYPE_MOUSE_MOVE:
	    prm = MouseAxis[CmdControl[cmd].val];
	    break;
	default:
	    prm = NULL;
	    break;
	}
	prm = GfParmGetStr(PrefHdle, defaultSettings, CmdControl[cmd].name, prm);
	prm = GfParmGetStr(PrefHdle, sstring, CmdControl[cmd].name, prm);
	if (!prm || (strlen(prm) == 0)) {
	    CmdControl[cmd].type = CMD_TYPE_NOT_AFFECTED;
	    GfOut("%s -> NONE (-1)\n", CmdControl[cmd].name);
	    continue;
	}
	if (CmdControl[cmd].minName) {
	    CmdControl[cmd].min = (float)GfParmGetNum(PrefHdle, defaultSettings, CmdControl[cmd].minName, (char*)NULL, (tdble)CmdControl[cmd].min);
	    CmdControl[cmd].min = CmdControl[cmd].minVal = (float)GfParmGetNum(PrefHdle, sstring, CmdControl[cmd].minName, (char*)NULL, (tdble)CmdControl[cmd].min);
	}
	if (CmdControl[cmd].maxName) {
	    CmdControl[cmd].max = (float)GfParmGetNum(PrefHdle, defaultSettings, CmdControl[cmd].maxName, (char*)NULL, (tdble)CmdControl[cmd].max);
	    CmdControl[cmd].max = (float)GfParmGetNum(PrefHdle, sstring, CmdControl[cmd].maxName, (char*)NULL, (tdble)CmdControl[cmd].max);
	}	
	if (CmdControl[cmd].sensName) {
	    CmdControl[cmd].sens = 1.0f / (float)GfParmGetNum(PrefHdle, defaultSettings, CmdControl[cmd].sensName, (char*)NULL, 1.0 / (tdble)CmdControl[cmd].sens);
	    CmdControl[cmd].sens = 1.0f / (float)GfParmGetNum(PrefHdle, sstring, CmdControl[cmd].sensName, (char*)NULL, 1.0 / (tdble)CmdControl[cmd].sens);
	}	
	if (CmdControl[cmd].powName) {
	    CmdControl[cmd].pow = (float)GfParmGetNum(PrefHdle, defaultSettings, CmdControl[cmd].powName, (char*)NULL, (tdble)CmdControl[cmd].pow);
	    CmdControl[cmd].pow = (float)GfParmGetNum(PrefHdle, sstring, CmdControl[cmd].powName, (char*)NULL, (tdble)CmdControl[cmd].pow);
	}
	if (CmdControl[cmd].min > CmdControl[cmd].max) {
	    tmp = CmdControl[cmd].min;
	    CmdControl[cmd].min = CmdControl[cmd].max;
	    CmdControl[cmd].max = tmp;
	}
	for (i = 0; i < maxButton; i++) {
	    if (strcmp(prm, Btn[i]) == 0) {
		CmdControl[cmd].val = i;
		CmdControl[cmd].type = CMD_TYPE_JOY_BUT;
		GfOut("%s -> %s (%d)\n", CmdControl[cmd].name, Btn[i], i);
		break;
	    }
	}
	if (i != maxButton) {
	    continue;
	}
	for (i = 0; i < maxAxis; i++) {
	    if (strcmp(prm, Axis[i]) == 0) {
		CmdControl[cmd].val = i;
		CmdControl[cmd].type = CMD_TYPE_ANALOG;
		GfOut("%s -> %s (%d)\n", CmdControl[cmd].name, Axis[i], i);
		break;
	    }
	}
	if (i != maxAxis) {
	    continue;
	}
	for (i = 0; i < maxMouseButton; i++) {
	    if (strcmp(prm, MouseBtn[i]) == 0) {
		CmdControl[cmd].val = i;
		CmdControl[cmd].type = CMD_TYPE_MOUSE_BUT;
		GfOut("%s -> %s (%d)\n", CmdControl[cmd].name, MouseBtn[i], i);
		break;
	    }
	}
	if (i != maxMouseButton) {
	    continue;
	}
	for (i = 0; i < maxMouseAxis; i++) {
	    if (strcmp(prm, MouseAxis[i]) == 0) {
		CmdControl[cmd].val = i;
		CmdControl[cmd].type = CMD_TYPE_MOUSE_MOVE;
		GfOut("%s -> %s (%d)\n", CmdControl[cmd].name, MouseAxis[i], i);
		break;
	    }
	}
	if (i != maxMouseAxis) {
	    continue;
	}
	
	CmdControl[cmd].type = CMD_TYPE_NOT_AFFECTED;
	GfOut("%s -> NONE (-1)\n", CmdControl[cmd].name);
    }

    prm = GfParmGetStr(PrefHdle, defaultSettings, HM_ATT_REL_BUT_NEUTRAL, Yn[RelButNeutral]);
    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_REL_BUT_NEUTRAL, prm);
    if (strcmp(prm, Yn[0]) == 0) {
	RelButNeutral = 1;
    } else {
	RelButNeutral = 0;
    }

    prm = GfParmGetStr(PrefHdle, defaultSettings, HM_ATT_SEQSHFT_ALLOW_NEUTRAL, Yn[SeqShftAllowNeutral]);
    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_SEQSHFT_ALLOW_NEUTRAL, prm);
    if (strcmp(prm, Yn[0]) == 0) {
	SeqShftAllowNeutral = 1;
    } else {
	SeqShftAllowNeutral = 0;
    }

#if 0
    GfOut("jsType 	 = %d\n", jsType);
    GfOut("Transmission  = %d\n", Transmission);
    GfOut("NbPitStopProg = %d\n", NbPitStopProg);
    GfOut("ParamAsr      = %d\n", ParamAsr);
    GfOut("ParamAbs      = %d\n", ParamAbs);
    GfOut("CmdLeftSteer  = %d\n", CmdLeftSteer);
    GfOut("LeftSteerSens = %f\n", LeftSteerSens);
    GfOut("LeftSteerPow  = %f\n", LeftSteerPow);
    GfOut("CmdThrottle   = %d\n", CmdThrottle);
    GfOut("ThrMin        = %f\n", ThrMin);
    GfOut("ThrMinVal     = %f\n", ThrMinVal);
    GfOut("ThrMax        = %f\n", ThrMax);
    GfOut("ThrSens       = %f\n", ThrSens);
    GfOut("ThrPow        = %f\n", ThrPow);
    GfOut("CmdBrake      = %d\n", CmdBrake);
    GfOut("BrkMin        = %f\n", BrkMin);
    GfOut("BrkMinVal     = %f\n", BrkMinVal);
    GfOut("BrkMax        = %f\n", BrkMax);
    GfOut("BrkSens       = %f\n", BrkSens);
    GfOut("BrkPow        = %f\n", BrkPow);
#endif
}

