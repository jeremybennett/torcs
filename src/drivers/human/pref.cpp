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
#include "pref.h"

void	*PrefHdle;

int	Transmission;

int	NbPitStopProg = 0;

int	ParamAsr	 = 0;	/* anti-slip accel */
int	ParamAbs	 = 1;	/* anti-lock brake */

#define NB_CMD	12

int	CmdButton[NB_CMD] = {0, 1, 2, 3, -1, -1, -1, -1, -1, -1, -1, -1};


static char	*CmdAttrName[NB_CMD] = {
    HM_ATT_UP_SHFT,
    HM_ATT_DN_SHFT,
    HM_ATT_ASR_CMD,
    HM_ATT_ABS_CMD,
    HM_ATT_GEAR_R,
    HM_ATT_GEAR_N,
    HM_ATT_GEAR_1,
    HM_ATT_GEAR_2,
    HM_ATT_GEAR_3,
    HM_ATT_GEAR_4,
    HM_ATT_GEAR_5,
    HM_ATT_GEAR_6
};


int	RelButNeutral	= 0;

int	CmdSteer	= 0;
float	SteerSens	= 2.0;
float	SteerPow	= 1.0;
int	CmdThrottle	= 1;
float	ThrMin		= 0.0;
float	ThrMinVal	= 0;
float	ThrMax		= 0;
float	ThrSens		= 1.0;
float	ThrPow		= 2.0;
int	CmdBrake	= 1;
float	BrkMin		= 0;
float	BrkMinVal	= 0;
float	BrkMax		= 1.0;
float	BrkSens		= 1.0;
float	BrkPow		= 2.0;

static char *Btn[] = {"BTN1", "BTN2", "BTN3", "BTN4", "BTN5", "BTN6", "BTN7", "BTN8", "BTN9", "BTN10", "BTN11", "BTN12", "BTN13", "BTN14", "BTN15", "BTN16",
		      "BTN17", "BTN18", "BTN19", "BTN20", "BTN21", "BTN22", "BTN23", "BTN24", "BTN25", "BTN26", "BTN27", "BTN28", "BTN29", "BTN30", "BTN31", "BTN32"};
static char *Axis[] = {"AXIS0", "AXIS1", "AXIS2", "AXIS3", "AXIS4", "AXIS5", "AXIS6", "AXIS7", "AXIS8", "AXIS9", "AXIS10", "AXIS11", "AXIS12"};

char *Yn[] = {HM_VAL_YES, HM_VAL_NO};


void
HmReadPrefs(int index)
{
    char	*prm;
    char	sstring[256];
    uint	i, cmd;
    uint	maxButton;
    float	tmp;
    
    sprintf(sstring, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, index);

    PrefHdle = GfParmReadFile(HM_PREF_FILE, GFPARM_RMODE_REREAD | GFPARM_RMODE_CREAT);

    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_TRANS, HM_VAL_AUTO);
    if (strcmp(prm, HM_VAL_AUTO) == 0) {
	Transmission = 0;
    } else {
	Transmission = 1;
    }
    free(prm);
    NbPitStopProg = (int)GfParmGetNum(PrefHdle, sstring, HM_ATT_NBPITS, (char*)NULL, 0);
    /* Parameters Settings */
    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_ABS, Yn[ParamAbs]);
    if (strcmp(prm, Yn[0]) == 0) {
	ParamAbs = 1;
    } else {
	ParamAbs = 0;
    }
    free(prm);
    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_ASR, Yn[ParamAsr]);
    if (strcmp(prm, Yn[0]) == 0) {
	ParamAsr = 1;
    } else {
	ParamAsr = 0;
    }
    free(prm);

    maxButton = sizeof(Btn)/sizeof(char*);

    /* JOYSTICK SETTINGS */
    for (cmd = 0; cmd < NB_CMD; cmd++) {
	prm = GfParmGetStr(PrefHdle, HM_SECT_JSPREF, CmdAttrName[cmd], Btn[CmdButton[cmd]]);
	prm = GfParmGetStr(PrefHdle, sstring, CmdAttrName[cmd], prm);
	for (i = 0; i < maxButton; i++) {
	    if (strcmp(prm, Btn[i]) == 0) {
		CmdButton[cmd] = i;
		GfOut("%s -> %s (%d)\n", CmdAttrName[cmd], Btn[i], i);
		break;
	    }
	}
	free(prm);
	if (i == maxButton) {
	    CmdButton[cmd] = -1;
	    GfOut("%s -> NONE (-1)\n", CmdAttrName[cmd]);
	}
    }

    prm = GfParmGetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_REL_BUT_NEUTRAL, Yn[RelButNeutral]);
    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_REL_BUT_NEUTRAL, prm);
    if (strcmp(prm, Yn[0]) == 0) {
	RelButNeutral = 1;
    } else {
	RelButNeutral = 0;
    }
    free(prm);

    prm = GfParmGetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_STEER, Axis[CmdSteer]);
    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_STEER, prm);
    for (i = 0; i < sizeof(Axis)/sizeof(char*); i++) {
	if (strcmp(prm, Axis[i]) == 0) {
	   CmdSteer  = i;
	}
    }
    free(prm);
    SteerSens = 1.0/(float)GfParmGetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_STEER_SENS,
				      (char*)NULL, (tdble)(1.0/SteerSens));
    SteerSens = 1.0/(float)GfParmGetNum(PrefHdle, sstring, HM_ATT_STEER_SENS,
				      (char*)NULL, (tdble)(1.0/SteerSens));
    SteerPow = (float)GfParmGetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_STEER_POW, (char*)NULL, (tdble)SteerPow);
    SteerPow = (float)GfParmGetNum(PrefHdle, sstring, HM_ATT_STEER_POW, (char*)NULL, (tdble)SteerPow);

    prm = GfParmGetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE, Axis[CmdThrottle]);
    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_THROTTLE, prm);
    for (i = 0; i < sizeof(Axis)/sizeof(char*); i++) {
	if (strcmp(prm, Axis[i]) == 0) {
	   CmdThrottle  = i;
	}
    }
    free(prm);
    ThrMin = (float)GfParmGetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE_MIN, (char*)NULL, (tdble)ThrMin);
    ThrMinVal = ThrMin = (float)GfParmGetNum(PrefHdle, sstring, HM_ATT_THROTTLE_MIN, (char*)NULL, (tdble)ThrMin);
    ThrMax = (float)GfParmGetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE_MAX, (char*)NULL, (tdble)ThrMax);
    ThrMax = (float)GfParmGetNum(PrefHdle, sstring, HM_ATT_THROTTLE_MAX, (char*)NULL, (tdble)ThrMax);
    ThrSens = 1.0/(float)GfParmGetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE_SENS,
				      (char*)NULL, (tdble)(1.0/ThrSens));
    ThrSens = 1.0/(float)GfParmGetNum(PrefHdle, sstring, HM_ATT_THROTTLE_SENS,
				      (char*)NULL, (tdble)(1.0/ThrSens));
    ThrPow = (float)GfParmGetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_THROTTLE_POW, (char*)NULL, (tdble)ThrPow);
    ThrPow = (float)GfParmGetNum(PrefHdle, sstring, HM_ATT_THROTTLE_POW, (char*)NULL, (tdble)ThrPow);
    if (ThrMin > ThrMax) {
	tmp = ThrMin;
	ThrMin = ThrMax;
	ThrMax = tmp;
    }
    
    prm = GfParmGetStr(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE, Axis[CmdBrake]);
    prm = GfParmGetStr(PrefHdle, sstring, HM_ATT_BRAKE, prm);
    for (i = 0; i < sizeof(Axis)/sizeof(char*); i++) {
	if (strcmp(prm, Axis[i]) == 0) {
	   CmdBrake  = i;
	}
    }
    free(prm);
    BrkMin = (float)GfParmGetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE_MIN, (char*)NULL, (tdble)BrkMin);
    BrkMinVal = BrkMin = (float)GfParmGetNum(PrefHdle, sstring, HM_ATT_BRAKE_MIN, (char*)NULL, (tdble)BrkMin);
    BrkMax = (float)GfParmGetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE_MAX, (char*)NULL, (tdble)BrkMax);
    BrkMax = (float)GfParmGetNum(PrefHdle, sstring, HM_ATT_BRAKE_MAX, (char*)NULL, (tdble)BrkMax);
    BrkSens = 1.0/(float)GfParmGetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE_SENS, (char*)NULL, (tdble)(1.0/BrkSens));
    BrkSens = 1.0/(float)GfParmGetNum(PrefHdle, sstring, HM_ATT_BRAKE_SENS, (char*)NULL, (tdble)(1.0/BrkSens));
    BrkPow = (float)GfParmGetNum(PrefHdle, HM_SECT_JSPREF, HM_ATT_BRAKE_POW, (char*)NULL, (tdble)BrkPow);
    BrkPow = (float)GfParmGetNum(PrefHdle, sstring, HM_ATT_BRAKE_POW, (char*)NULL, (tdble)BrkPow);
    if (BrkMin > BrkMax) {
	tmp = BrkMin;
	BrkMin = BrkMax;
	BrkMax = tmp;
    }

#if 0
    GfOut("Transmission  = %d\n", Transmission);
    GfOut("NbPitStopProg = %d\n", NbPitStopProg);
    GfOut("ParamAsr      = %d\n", ParamAsr);
    GfOut("ParamAbs      = %d\n", ParamAbs);
    GfOut("CmdSteer      = %d\n", CmdSteer);
    GfOut("SteerSens     = %f\n", SteerSens);
    GfOut("SteerPow      = %f\n", SteerPow);
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

