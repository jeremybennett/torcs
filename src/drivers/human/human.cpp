/***************************************************************************

    file                 : human.cpp
    created              : Sat Mar 18 23:16:38 CET 2000
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


#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <js.h>

#include <tgf.h>

#include <track.h>
#include <car.h>
#include <raceman.h>
#include <robottools.h>
#include <robot.h>

#include <playerpref.h>
#include "pref.h"


static void initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s);
static void drive_mt(int index, tCarElt* car, tSituation *s);
static void drive_at(int index, tCarElt* car, tSituation *s);
static void newrace(int index, tCarElt* car, tSituation *s);
static int  pitcmd(int index, tCarElt* car, tSituation *s);

int joyPresent = 0;

static char	sstring[1024];
static char	buf[1024];

static tTrack	*curTrack;

static int	NbPitStops = 0;
static int	LastPitStopLap = 0;

static void	*DrvInfo;

static float color[] = {1.0, 1.0, 1.0, 1.0};

static tCtrlJoyInfo	*joyInfo = NULL;
static tCtrlMouseInfo	*mouseInfo = NULL;

static int AutoReverseEngaged = 0;

typedef struct 
{
    int		state;
    int		edgeDn;
    int		edgeUp;
} tKeyInfo;

static tKeyInfo keyInfo[256];
static tKeyInfo skeyInfo[256];

static int currentKey[256];
static int currentSKey[256];


#ifdef _WIN32
/* should be present in mswindows */
BOOL WINAPI DllEntryPoint (HINSTANCE hDLL, DWORD dwReason, LPVOID Reserved)
{
    return TRUE;
}
#endif

static void
shutdown(int index)
{
    static int firstTime = 1;
    
    if (firstTime) {
	GfParmReleaseHandle(DrvInfo);
	GfParmReleaseHandle(PrefHdle);
	GfctrlJoyRelease(joyInfo);
	GfctrlMouseRelease(mouseInfo);
	GfuiKeyEventRegisterCurrent(NULL);
	GfuiSKeyEventRegisterCurrent(NULL);
	firstTime = 0;
    }
}



/*
 * Function
 *	InitFuncPt
 *
 * Description
 *	Robot functions initialisation
 *
 * Parameters
 *	pt	pointer on functions structure
 *
 * Return
 *	0
 *
 * Remarks
 *	
 */
static int
InitFuncPt(int index, void *pt)
{
    tRobotItf	*itf = (tRobotItf *)pt;

    itf->rbNewTrack = initTrack;	/* give the robot the track view called */
					/* for every track change or new race */
    itf->rbNewRace  = newrace;

    HmReadPrefs(index);

    if (Transmission == 0) {
	itf->rbDrive    = drive_at;
    } else {
	itf->rbDrive    = drive_mt;		/* drive during race */
    }
    itf->rbShutdown = shutdown;
    itf->rbPitCmd   = pitcmd;
    itf->index      = index;

    return 0;
}

/*
 * Function
 *	human
 *
 * Description
 *	DLL entry point (general to all types of modules)
 *
 * Parameters
 *	modInfo	administrative info on module
 *
 * Return
 *	0
 *
 * Remarks
 *	
 */
extern "C" int
human(tModInfo *modInfo)
{
    int		i;
    char	*driver;

    memset(modInfo, 0, 10*sizeof(tModInfo));

    sprintf(buf, "%sdrivers/human/human.xml", GetLocalDir());
    DrvInfo = GfParmReadFile(buf, GFPARM_RMODE_REREAD | GFPARM_RMODE_CREAT);
    
    if (DrvInfo != NULL) {
	for (i = 0; i < 10; i++) {
	    sprintf(sstring, "Robots/index/%d", i+1);
	    driver = GfParmGetStr(DrvInfo, sstring, "name", "");
	    if (strlen(driver) == 0) {
		break;
	    }
	    modInfo->name    = driver;	/* name of the module (short) */
	    modInfo->desc    = "Joystick controlable driver";	/* description of the module (can be long) */
	    modInfo->fctInit = InitFuncPt;	/* init function */
	    modInfo->gfId    = ROB_IDENT;	/* supported framework version */
	    modInfo->index   = i+1;
	    modInfo++;
	}
    }
    
    joyInfo = GfctrlJoyInit();
    if (joyInfo) {
	joyPresent = 1;
    }

    mouseInfo = GfctrlMouseInit();

    return 0;
}


/*
 * Function
 *	
 *
 * Description
 *	search under drivers/human/tracks/<trackname>/car-<model>-<index>.xml
 *		     drivers/human/car-<model>-<index>.xml
 *		     drivers/human/tracks/<trackname>/car-<model>.xml
 *		     drivers/human/car-<model>.xml
 *
 * Parameters
 *	
 *
 * Return
 *	
 *
 * Remarks
 *	
 */
static void initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s)
{
    char	*carname;
    char	*s1, *s2;
    char	trackname[256];
    tdble	fuel;

    curTrack = track;
    s1 = strrchr(track->filename, '/') + 1;
    s2 = strchr(s1, '.');
    strncpy(trackname, s1, s2-s1);
    trackname[s2-s1] = 0;
    sprintf(sstring, "Robots/index/%d", index);
    carname = GfParmGetStr(DrvInfo, sstring, "car name", "");
    sprintf(sstring, "%sdrivers/human/tracks/%s/car-%s-%d.xml", GetLocalDir(), trackname, carname, index);
    *carParmHandle = GfParmReadFile(sstring, GFPARM_RMODE_REREAD);
    if (*carParmHandle != NULL) {
	GfOut("Player: %s Loaded\n", sstring);
    } else {
	sprintf(sstring, "%sdrivers/human/car-%s-%d.xml", GetLocalDir(), carname, index);
	*carParmHandle = GfParmReadFile(sstring, GFPARM_RMODE_REREAD);
	if (*carParmHandle != NULL) {
	    GfOut("Player: %s Loaded\n", sstring);
	} else {
	    sprintf(sstring, "%sdrivers/human/tracks/%s/car-%s.xml", GetLocalDir(), trackname, carname);
	    *carParmHandle = GfParmReadFile(sstring, GFPARM_RMODE_REREAD);
	    if (*carParmHandle != NULL) {
		GfOut("Player: %s Loaded\n", sstring);
	    } else {
		sprintf(sstring, "%sdrivers/human/car-%s.xml", GetLocalDir(), carname);
		*carParmHandle = GfParmReadFile(sstring, GFPARM_RMODE_REREAD);
		if (*carParmHandle != NULL) {
		    GfOut("Player: %s Loaded\n", sstring);
		}
	    }
	}
    }
    if (curTrack->pits.type != TR_PIT_NONE) {
	sprintf(sstring, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, index);
	NbPitStopProg = (int)GfParmGetNum(PrefHdle, sstring, HM_ATT_NBPITS, (char*)NULL, 0);
	GfOut("Player: index %d , Pits stops %d\n", index, NbPitStopProg);
    } else {
	NbPitStopProg = 0;
    }
    fuel = 0.0008 * curTrack->length * (s->_totLaps + 1) / (1.0 + ((tdble)NbPitStopProg)) + 20.0;
    GfParmSetNum(*carParmHandle, SECT_CAR, PRM_FUEL, (char*)NULL, fuel);    
}


/*
 * Function
 *	
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	
 */
static tdble shiftThld[MAX_GEARS+1];
static tdble Gear;
static tdble distToStart;

void newrace(int index, tCarElt* car, tSituation *s)
{
    int		i;

    for (i = 0; i < MAX_GEARS; i++) {
	if (car->_gearRatio[i] != 0) {
	    shiftThld[i] = car->_enginerpmRedLine * car->_wheelRadius(2) * 0.85 / car->_gearRatio[i];
	    GfOut("Gear %d: Spd %f\n", i, shiftThld[i] * 3.6);
	} else {
	    shiftThld[i] = 10000.0;
	}
    }

    if (MouseControlUsed) {
	GfctrlMouseCenter();
    }

    memset(keyInfo, 0, sizeof(keyInfo));
    memset(skeyInfo, 0, sizeof(skeyInfo));

    memset(currentKey, 0, sizeof(currentKey));
    memset(currentSKey, 0, sizeof(currentSKey));
    

#ifndef WIN32
#ifdef TELEMETRY
    //if (s->_raceType == RM_TYPE_PRACTICE) {
	RtTelemInit(-10, 10);
	RtTelemNewChannel("Dist", &distToStart, 0, 0);
	RtTelemNewChannel("Ax", &car->_accel_x, 0, 0);
	RtTelemNewChannel("Ay", &car->_accel_y, 0, 0);
	RtTelemNewChannel("Steer", &car->ctrl->steer, 0, 0);
	RtTelemNewChannel("Throttle", &car->ctrl->accelCmd, 0, 0);
	RtTelemNewChannel("Brake", &car->ctrl->brakeCmd, 0, 0);
	RtTelemNewChannel("Gear", &Gear, 0, 0);
	RtTelemNewChannel("Speed", &car->_speed_x, 0, 0);
	//}
#endif
#endif

}

static void
updateKeys(void)
{
    int	i;
    int	key;

    for (i = 0; i < nbCmdControl; i++) {
	if (CmdControl[i].type == GFCTRL_TYPE_KEYBOARD) {
	    key = CmdControl[i].val;
	    if (currentKey[key] == GFUI_KEY_DOWN) {
		if (keyInfo[key].state == GFUI_KEY_UP) {
		    keyInfo[key].edgeDn = 1;
		} else {
		    keyInfo[key].edgeDn = 0;
		}
	    } else {
		if (keyInfo[key].state == GFUI_KEY_DOWN) {
		    keyInfo[key].edgeUp = 1;
		} else {
		    keyInfo[key].edgeUp = 0;
		}
	    }
	    keyInfo[key].state = currentKey[key];
	}

	if (CmdControl[i].type == GFCTRL_TYPE_SKEYBOARD) {
	    key = CmdControl[i].val;
	    if (currentSKey[key] == GFUI_KEY_DOWN) {
		if (skeyInfo[key].state == GFUI_KEY_UP) {
		    skeyInfo[key].edgeDn = 1;
		} else {
		    skeyInfo[key].edgeDn = 0;
		}
	    } else {
		if (skeyInfo[key].state == GFUI_KEY_DOWN) {
		    skeyInfo[key].edgeUp = 1;
		} else {
		    skeyInfo[key].edgeUp = 0;
		}
	    }
	    skeyInfo[key].state = currentSKey[key];
	}
    }
}


static int
onKeyAction(unsigned char key, int modifier, int state)
{
    currentKey[key] = state;
    
    return 0;
}

static int
onSKeyAction(int key, int modifier, int state)
{
    currentSKey[key] = state;
    
    return 0;
}

static void common_drive(int index, tCarElt* car, tSituation *s)
{
    tdble	 slip;
    static float ABS = 1.0;
    static float AntiSlip = 1.0;
    static int	 lap = 0;
    float	 ax0;
    float	 brake;
    float	 throttle;
    float	 leftSteer;
    float	 rightSteer;
    int		 scrw, scrh, dummy;
    static int	 firstTime = 1;

    if (firstTime) {
	if (MouseControlUsed) {
	    GfuiMouseShow();
	    GfctrlMouseInitCenter();
	}
	GfuiKeyEventRegisterCurrent(onKeyAction);
	GfuiSKeyEventRegisterCurrent(onSKeyAction);
	firstTime = 0;
    }

    updateKeys();

    distToStart = RtGetDistFromStart(car);
    
    Gear = (tdble)car->_gear;	/* telemetry */

    GfScrGetSize(&scrw, &scrh, &dummy, &dummy);

    memset(&(car->ctrl), 0, sizeof(tCarCtrl));

    if (car->_laps != LastPitStopLap) {
	car->_raceCmd = RM_CMD_PIT_ASKED;
    }

    if (joyPresent) {
	GfctrlJoyGetCurrent(joyInfo);
    }

    GfctrlMouseGetCurrent(mouseInfo);

    if (((CmdControl[CMD_ABS].type == GFCTRL_TYPE_JOY_BUT) && joyInfo->edgeup[CmdControl[CMD_ABS].val]) ||
	((CmdControl[CMD_ABS].type == GFCTRL_TYPE_KEYBOARD) && keyInfo[CmdControl[CMD_ABS].val].edgeUp) ||
	((CmdControl[CMD_ABS].type == GFCTRL_TYPE_SKEYBOARD) && skeyInfo[CmdControl[CMD_ABS].val].edgeUp)) {
	ParamAbs = 1 - ParamAbs;
	sprintf(sstring, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, index);
	GfParmSetStr(PrefHdle, sstring, HM_ATT_ABS, Yn[1 - ParamAbs]);
	GfParmWriteFile(HM_PREF_FILE, PrefHdle, "Human", GFPARM_PARAMETER, "../../libs/tgf/params.dtd");
    }
    if (((CmdControl[CMD_ASR].type == GFCTRL_TYPE_JOY_BUT) && joyInfo->edgeup[CmdControl[CMD_ASR].val]) ||
	((CmdControl[CMD_ASR].type == GFCTRL_TYPE_KEYBOARD) && keyInfo[CmdControl[CMD_ASR].val].edgeUp) ||
	((CmdControl[CMD_ASR].type == GFCTRL_TYPE_SKEYBOARD) && skeyInfo[CmdControl[CMD_ASR].val].edgeUp)) {
	ParamAsr = 1 - ParamAsr;
	sprintf(sstring, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, index);
	GfParmSetStr(PrefHdle, sstring, HM_ATT_ASR, Yn[1 - ParamAsr]);
	GfParmWriteFile(HM_PREF_FILE, PrefHdle, "Human", GFPARM_PARAMETER, "../../libs/tgf/params.dtd");
    }

    if (ParamAbs) {
	car->_msgCmd[0] = "ABS";
    }
    if (ParamAsr) {
	car->_msgCmd[1] = "ASR";
    }
    memcpy(car->_msgColorCmd, color, sizeof(car->_msgColorCmd));

    switch (CmdControl[CMD_LEFTSTEER].type) {
    case GFCTRL_TYPE_JOY_AXIS:
	ax0 = joyInfo->ax[CmdControl[CMD_LEFTSTEER].val] - CmdControl[CMD_LEFTSTEER].deadZone;
	if (ax0 > CmdControl[CMD_LEFTSTEER].max) {
	    ax0 = CmdControl[CMD_LEFTSTEER].max;
	} else if (ax0 < CmdControl[CMD_LEFTSTEER].min) {
	    ax0 = CmdControl[CMD_LEFTSTEER].min;
	}
	leftSteer = -SIGN(ax0) * CmdControl[CMD_LEFTSTEER].pow * pow(fabs(ax0), CmdControl[CMD_LEFTSTEER].sens) / (1.0 + CmdControl[CMD_LEFTSTEER].spdSens * car->_speed_x);
	break;
    case GFCTRL_TYPE_MOUSE_AXIS:
	ax0 = mouseInfo->ax[CmdControl[CMD_LEFTSTEER].val] - CmdControl[CMD_LEFTSTEER].deadZone;
	if (ax0 > CmdControl[CMD_LEFTSTEER].max) {
	    ax0 = CmdControl[CMD_LEFTSTEER].max;
	} else if (ax0 < CmdControl[CMD_LEFTSTEER].min) {
	    ax0 = CmdControl[CMD_LEFTSTEER].min;
	}
	ax0 = ax0 * CmdControl[CMD_LEFTSTEER].pow;
	leftSteer = pow(fabs(ax0), CmdControl[CMD_LEFTSTEER].sens) / (1.0 + CmdControl[CMD_LEFTSTEER].spdSens * car->_speed_x / 10.0);
	break;
    default:
	leftSteer = 0;
	break;
    }

    switch (CmdControl[CMD_RIGHTSTEER].type) {
    case GFCTRL_TYPE_JOY_AXIS:
	ax0 = joyInfo->ax[CmdControl[CMD_RIGHTSTEER].val] - CmdControl[CMD_RIGHTSTEER].deadZone;
	if (ax0 > CmdControl[CMD_RIGHTSTEER].max) {
	    ax0 = CmdControl[CMD_RIGHTSTEER].max;
	} else if (ax0 < CmdControl[CMD_RIGHTSTEER].min) {
	    ax0 = CmdControl[CMD_RIGHTSTEER].min;
	}
	rightSteer = -SIGN(ax0) * CmdControl[CMD_RIGHTSTEER].pow * pow(fabs(ax0), CmdControl[CMD_RIGHTSTEER].sens) / (1.0 + CmdControl[CMD_RIGHTSTEER].spdSens * car->_speed_x);
	break;
    case GFCTRL_TYPE_MOUSE_AXIS:
	ax0 = mouseInfo->ax[CmdControl[CMD_RIGHTSTEER].val] - CmdControl[CMD_RIGHTSTEER].deadZone;
	if (ax0 > CmdControl[CMD_RIGHTSTEER].max) {
	    ax0 = CmdControl[CMD_RIGHTSTEER].max;
	} else if (ax0 < CmdControl[CMD_RIGHTSTEER].min) {
	    ax0 = CmdControl[CMD_RIGHTSTEER].min;
	}
	ax0 = ax0 * CmdControl[CMD_RIGHTSTEER].pow;
	rightSteer = - pow(fabs(ax0), CmdControl[CMD_RIGHTSTEER].sens) / (1.0 + CmdControl[CMD_RIGHTSTEER].spdSens * car->_speed_x / 10.0);
	break;
    default:
	rightSteer = 0;
	break;
    }

    car->_steerCmd = leftSteer + rightSteer;
    

    switch (CmdControl[CMD_BRAKE].type) {
    case GFCTRL_TYPE_JOY_AXIS:
	brake = joyInfo->ax[CmdControl[CMD_BRAKE].val] - CmdControl[CMD_BRAKE].deadZone;
	if (brake > CmdControl[CMD_BRAKE].max) {
	    brake = CmdControl[CMD_BRAKE].max;
	} else if (brake < CmdControl[CMD_BRAKE].min) {
	    brake = CmdControl[CMD_BRAKE].min;
	}
	car->_brakeCmd = fabs(CmdControl[CMD_BRAKE].pow *
			      pow(fabs((brake - CmdControl[CMD_BRAKE].minVal) /
				       (CmdControl[CMD_BRAKE].max - CmdControl[CMD_BRAKE].min)),
				  CmdControl[CMD_BRAKE].sens));
	break;
    case GFCTRL_TYPE_MOUSE_AXIS:
	ax0 = mouseInfo->ax[CmdControl[CMD_BRAKE].val] - CmdControl[CMD_BRAKE].deadZone;
	if (ax0 > CmdControl[CMD_BRAKE].max) {
	    ax0 = CmdControl[CMD_BRAKE].max;
	} else if (ax0 < CmdControl[CMD_BRAKE].min) {
	    ax0 = CmdControl[CMD_BRAKE].min;
	}
	ax0 = ax0 * CmdControl[CMD_BRAKE].pow;
	car->_brakeCmd =  pow(fabs(ax0), CmdControl[CMD_BRAKE].sens) / (1.0 + CmdControl[CMD_BRAKE].spdSens * car->_speed_x / 10.0);
	break;
    case GFCTRL_TYPE_JOY_BUT:
	car->_brakeCmd = joyInfo->levelup[CmdControl[CMD_BRAKE].val];
	break;
    case GFCTRL_TYPE_MOUSE_BUT:
	car->_brakeCmd = mouseInfo->button[CmdControl[CMD_BRAKE].val];
	break;
    case GFCTRL_TYPE_KEYBOARD:
	car->_brakeCmd = keyInfo[CmdControl[CMD_BRAKE].val].state;
	break;
    case GFCTRL_TYPE_SKEYBOARD:
	car->_brakeCmd = skeyInfo[CmdControl[CMD_BRAKE].val].state;
	break;
    default:
	car->_brakeCmd = 0;
	break;
    }

    switch (CmdControl[CMD_THROTTLE].type) {
    case GFCTRL_TYPE_JOY_AXIS:
	throttle = joyInfo->ax[CmdControl[CMD_THROTTLE].val] - CmdControl[CMD_THROTTLE].deadZone;
	if (throttle > CmdControl[CMD_THROTTLE].max) {
	    throttle = CmdControl[CMD_THROTTLE].max;
	} else if (throttle < CmdControl[CMD_THROTTLE].min) {
	    throttle = CmdControl[CMD_THROTTLE].min;
	}
	car->_accelCmd = fabs(CmdControl[CMD_THROTTLE].pow *
				   pow(fabs((throttle - CmdControl[CMD_THROTTLE].minVal) /
					    (CmdControl[CMD_THROTTLE].max - CmdControl[CMD_THROTTLE].min)),
				       CmdControl[CMD_THROTTLE].sens));
	break;
    case GFCTRL_TYPE_MOUSE_AXIS:
	ax0 = mouseInfo->ax[CmdControl[CMD_THROTTLE].val] - CmdControl[CMD_THROTTLE].deadZone;
	if (ax0 > CmdControl[CMD_THROTTLE].max) {
	    ax0 = CmdControl[CMD_THROTTLE].max;
	} else if (ax0 < CmdControl[CMD_THROTTLE].min) {
	    ax0 = CmdControl[CMD_THROTTLE].min;
	}
	printf("axO:%f", ax0);
	ax0 = ax0 * CmdControl[CMD_THROTTLE].pow;
	car->_accelCmd =  pow(fabs(ax0), CmdControl[CMD_THROTTLE].sens) / (1.0 + CmdControl[CMD_THROTTLE].spdSens * car->_speed_x / 10.0);
	printf("  axO:%f  accelCmd:%f\n", ax0, car->_accelCmd);
	break;
    case GFCTRL_TYPE_JOY_BUT:
	car->_accelCmd = joyInfo->levelup[CmdControl[CMD_THROTTLE].val];
	break;
    case GFCTRL_TYPE_MOUSE_BUT:
	car->_accelCmd = mouseInfo->button[CmdControl[CMD_THROTTLE].val];
	break;
    case GFCTRL_TYPE_KEYBOARD:
	car->_accelCmd = keyInfo[CmdControl[CMD_THROTTLE].val].state;
	break;
    case GFCTRL_TYPE_SKEYBOARD:
	car->_accelCmd = skeyInfo[CmdControl[CMD_THROTTLE].val].state;
	break;
    default:
	car->_accelCmd = 0;
	break;
    }

    if (AutoReverseEngaged) {
	/* swap brake and throttle */
	brake = car->_brakeCmd;
	car->_brakeCmd = car->_accelCmd;
	car->_accelCmd = brake;
    }
    
    if (ParamAbs) {
	tdble meanSpd = 0;
	int i;

	slip = 0;
	for (i = 0; i < 4; i++) {
	    meanSpd += car->_wheelSpinVel(i);
	}
	meanSpd /= 4.0;

	if (meanSpd > 1.0) {
	    for (i = 0; i < 4; i++) {
		if (((meanSpd - car->_wheelSpinVel(i)) / meanSpd) < -0.1) {
		    slip = 1.0;
		}
	    }
	}
	if (slip != 0) {
	    ABS *= 0.9;
	    if (ABS < 0.1)
		ABS = 0.1;
	} else {
	    if (ABS < 0.1)
		ABS = 0.1;
	    ABS *= 1.1;
	    if (ABS > 1.0)
		ABS = 1.0;
	}
	car->_brakeCmd = MIN(car->_brakeCmd, ABS);
    }


    if (ParamAsr) {
	slip = 0;
	if (car->_speed_x > 0.1)
	    slip = (car->_wheelRadius(3) * car->_wheelSpinVel(3) - car->_speed_x);

	if (slip > 1.0) {
	    AntiSlip *= 0.9;
	    if (AntiSlip < 0.1)
		AntiSlip = 0.1;
	} else {
	    if (AntiSlip < 0.1)
		AntiSlip = 0.1;
	    AntiSlip *= 1.1;
	    if (AntiSlip > 1.0)
		AntiSlip = 1.0;
	}
	car->_accelCmd = MIN(car->_accelCmd, AntiSlip);
    }

#ifndef WIN32
#ifdef TELEMETRY
    if ((car->_laps > 1) && (car->_laps < 5)) {
	    if (lap == 1) {
		RtTelemStartMonitoring("Player");
	    }
	    RtTelemUpdate(car->_curLapTime);
    }
    if (car->_laps == 5) {
	    if (lap == 4) {
		RtTelemShutdown();
	    }
    }
#endif
#endif

    lap = car->_laps;
}


/*
 * Function
 *	
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	
 *
 * Remarks
 *	
 */
static void drive_mt(int index, tCarElt* car, tSituation *s)
{
    int		i;
    
    common_drive(index, car, s);
    car->_gearCmd = car->_gear;
    /* manual shift sequential */
    if (((CmdControl[CMD_UP_SHFT].type == GFCTRL_TYPE_JOY_BUT) && joyInfo->edgeup[CmdControl[CMD_UP_SHFT].val]) ||
	((CmdControl[CMD_UP_SHFT].type == GFCTRL_TYPE_MOUSE_BUT) && mouseInfo->edgeup[CmdControl[CMD_UP_SHFT].val]) ||
	((CmdControl[CMD_UP_SHFT].type == GFCTRL_TYPE_KEYBOARD) && keyInfo[CmdControl[CMD_UP_SHFT].val].edgeUp) ||
	((CmdControl[CMD_UP_SHFT].type == GFCTRL_TYPE_SKEYBOARD) && skeyInfo[CmdControl[CMD_UP_SHFT].val].edgeUp)) {
	car->_gearCmd++;
    }
    if (((CmdControl[CMD_DN_SHFT].type == GFCTRL_TYPE_JOY_BUT) && joyInfo->edgeup[CmdControl[CMD_DN_SHFT].val]) ||
	((CmdControl[CMD_DN_SHFT].type == GFCTRL_TYPE_MOUSE_BUT) && mouseInfo->edgeup[CmdControl[CMD_DN_SHFT].val]) ||
	((CmdControl[CMD_DN_SHFT].type == GFCTRL_TYPE_KEYBOARD) && keyInfo[CmdControl[CMD_DN_SHFT].val].edgeUp) ||
	((CmdControl[CMD_DN_SHFT].type == GFCTRL_TYPE_SKEYBOARD) && skeyInfo[CmdControl[CMD_DN_SHFT].val].edgeUp)) {
	if (SeqShftAllowNeutral || (car->_gearCmd > 1)) {
	    car->_gearCmd--;
	}
    }
    /* manual shift direct */
    if (RelButNeutral) {
	for (i = CMD_GEAR_R; i <= CMD_GEAR_6; i++) {
	    if (((CmdControl[i].type == GFCTRL_TYPE_JOY_BUT) && joyInfo->edgedn[CmdControl[i].val]) ||
		((CmdControl[i].type == GFCTRL_TYPE_MOUSE_BUT) && mouseInfo->edgedn[CmdControl[i].val]) ||
		((CmdControl[i].type == GFCTRL_TYPE_KEYBOARD) && keyInfo[CmdControl[i].val].edgeDn) ||
		((CmdControl[i].type == GFCTRL_TYPE_SKEYBOARD) && skeyInfo[CmdControl[i].val].edgeDn)) {
		car->_gearCmd = 0;
	    }
	}
    }
    for (i = CMD_GEAR_R; i <= CMD_GEAR_6; i++) {
	if (((CmdControl[i].type == GFCTRL_TYPE_JOY_BUT) && joyInfo->edgeup[CmdControl[i].val]) ||
	    ((CmdControl[i].type == GFCTRL_TYPE_MOUSE_BUT) && mouseInfo->edgeup[CmdControl[i].val]) ||
	    ((CmdControl[i].type == GFCTRL_TYPE_KEYBOARD) && keyInfo[CmdControl[i].val].edgeUp) ||
	    ((CmdControl[i].type == GFCTRL_TYPE_SKEYBOARD) && skeyInfo[CmdControl[i].val].edgeUp)) {
	    car->_gearCmd = i - CMD_GEAR_N;
	}
    }
    
}
/*
 * Function
 *	
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	
 *
 * Remarks
 *	
 */
static void drive_at(int index, tCarElt* car, tSituation *s)
{
    int	gear, i;
    static int	manual = 0;

    common_drive(index, car, s);

    /* shift */
    gear = car->_gear;

    if (gear > 0) {
	/* return to auto-shift */
	manual = 0;
    }
    gear += car->_gearOffset;
    car->_gearCmd = car->_gear;
    
    if (!AutoReverse) {
	/* manual shift */
	if (((CmdControl[CMD_UP_SHFT].type == GFCTRL_TYPE_JOY_BUT) && joyInfo->edgeup[CmdControl[CMD_UP_SHFT].val]) ||
	    ((CmdControl[CMD_UP_SHFT].type == GFCTRL_TYPE_KEYBOARD) && keyInfo[CmdControl[CMD_UP_SHFT].val].edgeUp) ||
	    ((CmdControl[CMD_UP_SHFT].type == GFCTRL_TYPE_SKEYBOARD) && skeyInfo[CmdControl[CMD_UP_SHFT].val].edgeUp)) {
	    car->_gearCmd++;
	    manual = 1;
	}
	if (((CmdControl[CMD_DN_SHFT].type == GFCTRL_TYPE_JOY_BUT) && joyInfo->edgeup[CmdControl[CMD_DN_SHFT].val]) ||
	    ((CmdControl[CMD_DN_SHFT].type == GFCTRL_TYPE_KEYBOARD) && keyInfo[CmdControl[CMD_DN_SHFT].val].edgeUp) ||
	    ((CmdControl[CMD_DN_SHFT].type == GFCTRL_TYPE_SKEYBOARD) && skeyInfo[CmdControl[CMD_DN_SHFT].val].edgeUp)) {
	    car->_gearCmd--;
	    manual = 1;
	}

	/* manual shift direct */
	if (RelButNeutral) {
	    for (i = CMD_GEAR_R; i < CMD_GEAR_2; i++) {
		if (((CmdControl[i].type == GFCTRL_TYPE_JOY_BUT) && joyInfo->edgedn[CmdControl[i].val]) ||
		    ((CmdControl[i].type == GFCTRL_TYPE_MOUSE_BUT) && mouseInfo->edgedn[CmdControl[i].val]) ||
		    ((CmdControl[i].type == GFCTRL_TYPE_KEYBOARD) && keyInfo[CmdControl[i].val].edgeDn) ||
		    ((CmdControl[i].type == GFCTRL_TYPE_SKEYBOARD) && skeyInfo[CmdControl[i].val].edgeDn)) {
		    car->_gearCmd = 0;
		    /* return to auto-shift */
		    manual = 0;
		}
	    }
	}
	for (i = CMD_GEAR_R; i < CMD_GEAR_2; i++) {
	    if (((CmdControl[i].type == GFCTRL_TYPE_JOY_BUT) && joyInfo->edgeup[CmdControl[i].val]) ||
		((CmdControl[i].type == GFCTRL_TYPE_MOUSE_BUT) && mouseInfo->edgeup[CmdControl[i].val]) ||
		((CmdControl[i].type == GFCTRL_TYPE_KEYBOARD) && keyInfo[CmdControl[i].val].edgeUp) ||
		((CmdControl[i].type == GFCTRL_TYPE_SKEYBOARD) && skeyInfo[CmdControl[i].val].edgeUp)) {
		car->_gearCmd = i - CMD_GEAR_N;
		manual = 1;
	    }
	}
    }

    /* auto shift */
    if (!manual && !AutoReverseEngaged) {
	if (car->_speed_x > shiftThld[gear]) {
	    car->_gearCmd++;
	} else if ((car->_gearCmd > 1) && (car->_speed_x < (shiftThld[gear-1] - 4.0))) {
	    car->_gearCmd--;
	}
	if (car->_gearCmd <= 0) {
	    car->_gearCmd++;
	}
    }

    if (AutoReverse) {
	/* Automatic Reverse Gear Mode */
	if (!AutoReverseEngaged) {
	    if ((car->_brakeCmd > car->_accelCmd) && (car->_speed_x < 1.0)) {
		AutoReverseEngaged = 1;
		car->_gearCmd = CMD_GEAR_R - CMD_GEAR_N;
	    }
	} else {
	    /* currently in autoreverse mode */
	    if ((car->_brakeCmd > car->_accelCmd) && (car->_speed_x > -1.0) && (car->_speed_x < 1.0)) {
		AutoReverseEngaged = 0;
		car->_gearCmd = CMD_GEAR_1 - CMD_GEAR_N;
	    }
	}
    }
}

static int pitcmd(int index, tCarElt* car, tSituation *s)
{
    tdble	f1, f2;
    tdble	ns;
    

    NbPitStops++;
    f1 = car->_tank - car->_fuel;
    if (NbPitStopProg < NbPitStops) {
	ns = 1.0;
    } else {
	ns = 1.0 + (NbPitStopProg - NbPitStops);
    }
    
    f2 = 0.00065 * (curTrack->length * car->_remainingLaps + car->_trkPos.seg->lgfromstart) / ns - car->_fuel;

    car->_pitFuel = MAX(MIN(f1, f2), 0);

    LastPitStopLap = car->_laps;

    car->_pitRepair = (int)car->_dammage;

    return ROB_PIT_MENU; /* The player is able to modify the value by menu */
}

