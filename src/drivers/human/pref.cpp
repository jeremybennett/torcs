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

#define NB_CMD	16

tControlCmd	CmdControl[NB_CMD] = {
    {HM_ATT_UP_SHFT,    CMD_TYPE_JOY_BUT,       0, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_DN_SHFT,    CMD_TYPE_JOY_BUT,       1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_ASR_CMD,    CMD_TYPE_JOY_BUT,       2, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_ABS_CMD,    CMD_TYPE_JOY_BUT,       3, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_R,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_N,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_1,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_2,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_3,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_4,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_5,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_GEAR_6,     CMD_TYPE_NOT_AFFECTED, -1, NULL, 0.0, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0, NULL, 0.0},

    {HM_ATT_THROTTLE,   CMD_TYPE_ANALOG, 1, HM_ATT_THROTTLE_MIN,   0.0, 0.0, HM_ATT_THROTTLE_MAX,   1.0, HM_ATT_THROTTLE_SENS, 1.0, HM_ATT_THROTTLE_POW, 2.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_BRAKE,      CMD_TYPE_ANALOG, 1, HM_ATT_BRAKE_MIN,      0.0, 0.0, HM_ATT_BRAKE_MAX,      1.0, HM_ATT_BRAKE_SENS,    1.0, HM_ATT_BRAKE_POW,    2.0, NULL, 0.0, NULL, 0.0},
    {HM_ATT_LEFTSTEER,  CMD_TYPE_ANALOG, 0, HM_ATT_LEFTSTEER_MIN,  0.0, 0.0, HM_ATT_LEFTSTEER_MAX,  1.0, HM_ATT_STEER_SENS,    2.0, HM_ATT_STEER_POW,    1.0, HM_ATT_STEER_SPD, 0.0, HM_ATT_STEER_DEAD, 0.0},
    {HM_ATT_RIGHTSTEER, CMD_TYPE_ANALOG, 0, HM_ATT_RIGHTSTEER_MIN, 0.0, 0.0, HM_ATT_RIGHTSTEER_MAX, 1.0, HM_ATT_STEER_SENS,    2.0, HM_ATT_STEER_POW,    1.0, HM_ATT_STEER_SPD, 0.0, HM_ATT_STEER_DEAD, 0.0}
};


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
"BTN17-7","BTN18-7","BTN19-7","BTN20-7","BTN21-7","BTN22-7","BTN23-7","BTN24-7","BTN25-7","BTN26-7","BTN27-7","BTN28-7","BTN29-7","BTN30-7","BTN31-7","BTN32-7"
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

static char *MouseBtn[] = {"MOUSE_LEFT_BTN", "MOUSE_MIDDLE_BTN", "MOUSE_RIGHT_BTN"}; /* glut order */
static char *MouseAxis[] = {"MOUSE_LEFT", "MOUSE_RIGHT", "MOUSE_UP", "MOUSE_DOWN"};


char *Yn[] = {HM_VAL_YES, HM_VAL_NO};

extern int joyPresent;


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

    if (joyPresent) {
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
	CmdControl[cmd].deadZone = (CmdControl[cmd].max - CmdControl[cmd].min) * CmdControl[cmd].deadZone / 100.0;
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

