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

void	*PrefHdle;

int	Transmission;

int	NbPitStopProg		= 0;

int	ParamAsr		= 0;	/* anti-slip accel */
int	ParamAbs		= 1;	/* anti-lock brake */
int	RelButNeutral		= 0;
int	SeqShftAllowNeutral	= 0;
int	AutoReverse		= 0;

tControlCmd	CmdControl[] = {
    {HM_ATT_UP_SHFT,    GFCTRL_TYPE_JOY_BUT,       0, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_DN_SHFT,    GFCTRL_TYPE_JOY_BUT,       1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_ASR_CMD,    GFCTRL_TYPE_JOY_BUT,       2, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_ABS_CMD,    GFCTRL_TYPE_JOY_BUT,       3, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_R,     GFCTRL_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_N,     GFCTRL_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_1,     GFCTRL_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_2,     GFCTRL_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_3,     GFCTRL_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_4,     GFCTRL_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_5,     GFCTRL_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_6,     GFCTRL_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},

    {HM_ATT_THROTTLE,   GFCTRL_TYPE_JOY_AXIS, 1, HM_ATT_THROTTLE_MIN,   0.0, 0.0, HM_ATT_THROTTLE_MAX,   1.0, HM_ATT_THROTTLE_SENS, 1.0, HM_ATT_THROTTLE_POW, 2.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_BRAKE,      GFCTRL_TYPE_JOY_AXIS, 1, HM_ATT_BRAKE_MIN,      0.0, 0.0, HM_ATT_BRAKE_MAX,      1.0, HM_ATT_BRAKE_SENS,    1.0, HM_ATT_BRAKE_POW,    2.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_LEFTSTEER,  GFCTRL_TYPE_JOY_AXIS, 0, HM_ATT_LEFTSTEER_MIN,  0.0, 0.0, HM_ATT_LEFTSTEER_MAX,  1.0, HM_ATT_STEER_SENS,    2.0, HM_ATT_LEFTSTEER_POW,    1.0, HM_ATT_STEER_SPD, 0.0, HM_ATT_STEER_DEAD, 0.0},
    {HM_ATT_RIGHTSTEER, GFCTRL_TYPE_JOY_AXIS, 0, HM_ATT_RIGHTSTEER_MIN, 0.0, 0.0, HM_ATT_RIGHTSTEER_MAX, 1.0, HM_ATT_STEER_SENS,    2.0, HM_ATT_RIGHTSTEER_POW,    1.0, HM_ATT_STEER_SPD, 0.0, HM_ATT_STEER_DEAD, 0.0}
};

const int nbCmdControl = sizeof(CmdControl) / sizeof(CmdControl[0]);

typedef struct
{
    char	*settings;
    char	*parmName;
} tCtrl;


static tCtrl	controlList[] = {
    {HM_SECT_JSPREF,    HM_VAL_JOYSTICK},
    {HM_SECT_KEYBPREF,  HM_VAL_KEYBOARD},
    {HM_SECT_MOUSEPREF, HM_VAL_MOUSE}
};
static const int nbControl = sizeof(controlList) / sizeof(controlList[0]);


char *Yn[] = {HM_VAL_YES, HM_VAL_NO};

extern int joyPresent;
int MouseControlUsed;

void
HmReadPrefs(int index)
{
    char	*prm;
    char	*defaultSettings;
    char	sstring[1024];
    int		cmd;
    float	tmp;
    tCtrlRef	*ref;
    int		i;

    sprintf(sstring, "%s%s", GetLocalDir(), HM_PREF_FILE);
    PrefHdle = GfParmReadFile(sstring, GFPARM_RMODE_REREAD | GFPARM_RMODE_CREAT);

    sprintf(sstring, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, index);
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

    prm = GfParmGetStr(PrefHdle, HM_SECT_PREF, HM_ATT_CONTROL, controlList[2].parmName);
    for (i = 0; i < nbControl; i++) {
	if (!strcmp(prm, controlList[i].parmName)) {
	    break;
	}
    }
    if (i == nbControl) {
	i = 2;
    }
    if ((i == 0) && !joyPresent) {
	i = 2;
    }
    MouseControlUsed = 0;

    defaultSettings = controlList[i].settings;

    /* Command Settings */
    for (cmd = 0; cmd < nbCmdControl; cmd++) {
	prm = GfctrlGetNameByRef(CmdControl[cmd].type, CmdControl[cmd].val);
	prm = GfParmGetStr(PrefHdle, defaultSettings, CmdControl[cmd].name, prm);
	prm = GfParmGetStr(PrefHdle, sstring, CmdControl[cmd].name, prm);
	if (!prm || (strlen(prm) == 0)) {
	    CmdControl[cmd].type = GFCTRL_TYPE_NOT_AFFECTED;
	    GfOut("%s -> NONE (-1)\n", CmdControl[cmd].name);
	    continue;
	}
	ref = GfctrlGetRefByName(prm);
	CmdControl[cmd].type = ref->type;
	CmdControl[cmd].val = ref->index;
	GfOut("%s -> %s\n", CmdControl[cmd].name, prm);

	if (CmdControl[cmd].minName) {
	    CmdControl[cmd].min = (float)GfParmGetNum(PrefHdle, defaultSettings, CmdControl[cmd].minName, (char*)NULL, (tdble)CmdControl[cmd].min);
	    CmdControl[cmd].min = CmdControl[cmd].minVal = (float)GfParmGetNum(PrefHdle, sstring, CmdControl[cmd].minName, (char*)NULL, (tdble)CmdControl[cmd].min);
	}
	if (CmdControl[cmd].maxName) {
	    CmdControl[cmd].max = (float)GfParmGetNum(PrefHdle, defaultSettings, CmdControl[cmd].maxName, (char*)NULL, (tdble)CmdControl[cmd].max);
	    CmdControl[cmd].max = (float)GfParmGetNum(PrefHdle, sstring,         CmdControl[cmd].maxName, (char*)NULL, (tdble)CmdControl[cmd].max);
	}	
	if (CmdControl[cmd].sensName) {
	    CmdControl[cmd].sens = 1.0f / (float)GfParmGetNum(PrefHdle, defaultSettings, CmdControl[cmd].sensName, (char*)NULL, 1.0 / (tdble)CmdControl[cmd].sens);
	    CmdControl[cmd].sens = 1.0f / (float)GfParmGetNum(PrefHdle, sstring,         CmdControl[cmd].sensName, (char*)NULL, 1.0 / (tdble)CmdControl[cmd].sens);
	}	
	if (CmdControl[cmd].powName) {
	    CmdControl[cmd].pow = (float)GfParmGetNum(PrefHdle, defaultSettings, CmdControl[cmd].powName, (char*)NULL, (tdble)CmdControl[cmd].pow);
	    CmdControl[cmd].pow = (float)GfParmGetNum(PrefHdle, sstring,         CmdControl[cmd].powName, (char*)NULL, (tdble)CmdControl[cmd].pow);
	}
	if (CmdControl[cmd].spdSensName) {
	    CmdControl[cmd].spdSens = (float)GfParmGetNum(PrefHdle, defaultSettings, CmdControl[cmd].spdSensName, (char*)NULL, (tdble)CmdControl[cmd].spdSens);
	    CmdControl[cmd].spdSens = (float)GfParmGetNum(PrefHdle, sstring,         CmdControl[cmd].spdSensName, (char*)NULL, (tdble)CmdControl[cmd].spdSens);
	    CmdControl[cmd].spdSens = CmdControl[cmd].spdSens / 100.0;
	}
	if (CmdControl[cmd].deadZoneName) {
	    CmdControl[cmd].deadZone = (float)GfParmGetNum(PrefHdle, defaultSettings, CmdControl[cmd].deadZoneName, (char*)NULL, (tdble)CmdControl[cmd].deadZone);
	    CmdControl[cmd].deadZone = (float)GfParmGetNum(PrefHdle, sstring,         CmdControl[cmd].deadZoneName, (char*)NULL, (tdble)CmdControl[cmd].deadZone);
	}
	if (CmdControl[cmd].min > CmdControl[cmd].max) {
	    tmp = CmdControl[cmd].min;
	    CmdControl[cmd].min = CmdControl[cmd].max;
	    CmdControl[cmd].max = tmp;
	}
	CmdControl[cmd].deadZone = (CmdControl[cmd].max - CmdControl[cmd].min) * CmdControl[cmd].deadZone;
	if (CmdControl[cmd].type == GFCTRL_TYPE_MOUSE_AXIS) {
	    MouseControlUsed = 1;
	}
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

    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_AUTOREVERSE, Yn[AutoReverse]);
    if (strcmp(prm, Yn[0]) == 0) {
	AutoReverse = 1;
    } else {
	AutoReverse = 0;
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

