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


static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation *s);
static void drive_mt(int index, tCarElt* car, tSituation *s);
static void drive_at(int index, tCarElt* car, tSituation *s);
static void newrace(int index, tCarElt* car, tSituation *s);
static int  pitcmd(int index, tCarElt* car, tSituation *s);

static jsJoystick js0(0);

static char	sstring[256];

static tTrack	*curTrack;

static int	NbPitStops = 0;
static int	LastPitStopLap = 0;

static void	*DrvInfo;

static float color[] = {1.0, 1.0, 1.0, 1.0};


#ifdef _WIN32
/* should be present in mswindows */
BOOL WINAPI DllEntryPoint (HINSTANCE hDLL, DWORD dwReason, LPVOID Reserved)
{
    return TRUE;
}
#endif

static void
shutdown(void)
{
    GfParmReleaseHandle(DrvInfo);
    GfParmReleaseHandle(PrefHdle);
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
    itf->rbPitCmd = pitcmd;
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

    DrvInfo = GfParmReadFile("drivers/human/human.xml", GFPARM_RMODE_REREAD | GFPARM_RMODE_CREAT);
    
    if ((!js0.notWorking()) && (DrvInfo != NULL)) {
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
	/* GfOut("Joystick: %s\n", js0.getName()); */
    } else {
	GfTrace("JOYSTICK NOT WORKING ! Player not available\n");
    }
    
    

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
static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation *s)
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
    sprintf(sstring, "drivers/human/tracks/%s/car-%s-%d.xml", trackname, carname, index);
    *carParmHandle = GfParmReadFile(sstring, GFPARM_RMODE_REREAD);
    if (*carParmHandle != NULL) {
	GfOut("Player: %s Loaded\n", sstring);
    } else {
	sprintf(sstring, "drivers/human/car-%s-%d.xml", carname, index);
	*carParmHandle = GfParmReadFile(sstring, GFPARM_RMODE_REREAD);
	if (*carParmHandle != NULL) {
	    GfOut("Player: %s Loaded\n", sstring);
	} else {
	    sprintf(sstring, "drivers/human/tracks/%s/car-%s.xml", trackname, carname);
	    *carParmHandle = GfParmReadFile(sstring, GFPARM_RMODE_REREAD);
	    if (*carParmHandle != NULL) {
		GfOut("Player: %s Loaded\n", sstring);
	    } else {
		sprintf(sstring, "drivers/human/car-%s.xml", carname);
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
static tdble	Gear;

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

    if (s->_raceType == RM_TYPE_PRACTICE) {
	RtTelemInit(-10, 10);
	RtTelemNewChannel("Ax", &car->_accel_x, -30, 30);
	RtTelemNewChannel("Ay", &car->_accel_y, -30, 30);
	RtTelemNewChannel("Steer", &car->ctrl->steer, -1, 1);
	RtTelemNewChannel("Throttle", &car->ctrl->accelCmd, -1, 1);
	RtTelemNewChannel("Brake", &car->ctrl->brakeCmd, -1, 1);
	RtTelemNewChannel("Gear", &Gear, -10, 10);
	RtTelemNewChannel("Speed", &car->_speed_x, -100, 100);
    }


}

static int	 edgeup[32] = {0};
static int	 edgedn[32] = {0};


static void common_drive(int index, tCarElt* car, tSituation *s)
{
    int		 b;
    int		 i;
    tdble	 slip;
    static float ABS = 1.0;
    static float AntiSlip = 1.0;
    static int	 lap = 0;
    static float ax0[_JS_MAX_AXES];
    static int	 rawb = 0;
    int		 mask;
    float	 brake;
    
    Gear = (tdble)car->_gear;	/* telemetry */

    memset(car->ctrl, 0, sizeof(tCarCtrl));

    if (car->_laps != LastPitStopLap) {
	car->ctrl->raceCmd = RM_CMD_PIT_ASKED;
    }

    js0.read(&b, ax0);

    /* Joystick buttons */
    for (i = 0, mask = 1; i < 32; i++, mask *= 2) {
	if (((b & mask) != 0) && ((rawb & mask) == 0)) {
	    edgeup[i] = 1;
	} else {
	    edgeup[i] = 0;
	}
	if (((b & mask) == 0) && ((rawb & mask) != 0)) {
	    edgedn[i] = 1;
	} else {
	    edgedn[i] = 0;
	}
    }
    rawb = b;
    

    if ((CmdButton[CMD_BUT_ABS] != -1) && edgeup[CmdButton[CMD_BUT_ABS]]) {
	ParamAbs = 1 - ParamAbs;
	sprintf(sstring, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, index);
	GfParmSetStr(PrefHdle, sstring, HM_ATT_ABS, Yn[1 - ParamAbs]);
	GfParmWriteFile(HM_PREF_FILE, PrefHdle, "Human", GFPARM_PARAMETER, "../../libs/tgf/params.dtd");
    }
    if ((CmdButton[CMD_BUT_ASR] != -1) && edgeup[CmdButton[CMD_BUT_ASR]]) {
	ParamAsr = 1 - ParamAsr;
	sprintf(sstring, "%s/%s/%d", HM_SECT_PREF, HM_LIST_DRV, index);
	GfParmSetStr(PrefHdle, sstring, HM_ATT_ASR, Yn[1 - ParamAsr]);
	GfParmWriteFile(HM_PREF_FILE, PrefHdle, "Human", GFPARM_PARAMETER, "../../libs/tgf/params.dtd");
    }

    if (ParamAbs) {
	car->ctrl->msg[0] = "ABS";
    }
    if (ParamAsr) {
	car->ctrl->msg[1] = "ASR";
    }
    memcpy(car->ctrl->msgColor, color, sizeof(car->ctrl->msgColor));

    if (CmdSteer != -1) {
	car->ctrl->steer = -SIGN(ax0[CmdSteer]) * SteerPow * pow(fabs(ax0[CmdSteer]), SteerSens);
    } else {
	car->ctrl->steer = 0;
    }
    
    if (CmdBrake != -1) {
	brake = ax0[CmdBrake];
    } else {
	brake = 0;
    }
    
    if (brake < BrkMin) {
	brake = BrkMin;
    } else if (brake > BrkMax) {
	brake = BrkMax;
    }

    car->ctrl->brakeCmd = fabs(BrkPow * pow(fabs((brake - BrkMinVal)/(BrkMax-BrkMin)), BrkSens));
    if ((ParamAbs) /* && (car->ctrl->brakeCmd < (0.9 * BrkPow)) */ ) {
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
	car->ctrl->brakeCmd = MIN(car->ctrl->brakeCmd, ABS);
    }
    
    if (CmdThrottle != -1) {
	if ((ax0[CmdThrottle] > ThrMin) && (ax0[CmdThrottle] < ThrMax)) {
	    car->ctrl->accelCmd = fabs(ThrPow * pow(fabs((ax0[CmdThrottle] - ThrMinVal)/(ThrMax-ThrMin)), ThrSens));
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
		car->ctrl->accelCmd = MIN(car->ctrl->accelCmd, AntiSlip);
	    }
	}
    } else {
	car->ctrl->accelCmd = 0;
    }
    
    if (car->_laps == 1) {
	if (s->_raceType == RM_TYPE_PRACTICE) {
	    if (lap == 0) {
		RtTelemStartMonitoring("Player");
	    }
	    RtTelemUpdate(car->_curLapTime);
	}
    }
    if (car->_laps == 2) {
	if (s->_raceType == RM_TYPE_PRACTICE) {
	    if (lap == 1) {
		RtTelemShutdown();
	    }
	}
    }
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
    car->ctrl->gear = car->_gear;
    /* manual shift sequential */
    if ((CmdButton[CMD_BUT_UP_SHFT] != -1) && edgeup[CmdButton[CMD_BUT_UP_SHFT]]) {
	car->ctrl->gear++;
    }
    if ((CmdButton[CMD_BUT_DN_SHFT] != -1) && edgeup[CmdButton[CMD_BUT_DN_SHFT]]) {
	car->ctrl->gear--;
    }
    /* manual shift direct */
    if (RelButNeutral) {
	for (i = CMD_BUT_GEAR_R; i <= CMD_BUT_GEAR_6; i++) {
	    if ((CmdButton[i] != -1) && edgedn[CmdButton[i]]) {
		car->ctrl->gear = 0;
	    }
	}
    }
    for (i = CMD_BUT_GEAR_R; i <= CMD_BUT_GEAR_6; i++) {
	if ((CmdButton[i] != -1) && edgeup[CmdButton[i]]) {
	    car->ctrl->gear = i - CMD_BUT_GEAR_N;
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
    
    /* manual shift */
    car->ctrl->gear = car->_gear;
    if (edgeup[CmdButton[CMD_BUT_UP_SHFT]]) {
	car->ctrl->gear++;
	manual = 1;
    }
    if (edgeup[CmdButton[CMD_BUT_DN_SHFT]]) {
	car->ctrl->gear--;
	manual = 1;
    }

    /* manual shift direct */
    if (RelButNeutral) {
	for (i = CMD_BUT_GEAR_R; i < CMD_BUT_GEAR_2; i++) {
	    if ((CmdButton[i] != -1) && edgedn[CmdButton[i]]) {
		car->ctrl->gear = 0;
		manual = 1;
	    }
	}
    }
    for (i = CMD_BUT_GEAR_R; i < CMD_BUT_GEAR_2; i++) {
	if ((CmdButton[i] != -1) && edgeup[CmdButton[i]]) {
	    car->ctrl->gear = i - CMD_BUT_GEAR_N;
	    manual = 1;
	}
    }
    
    /* auto shift */
    if (!manual) {
	if (car->_speed_x > shiftThld[gear]) {
	    car->ctrl->gear++;
	} else if ((car->_gear > 1) && (car->_speed_x < (shiftThld[gear-1] - 4.0))) {
	    car->ctrl->gear--;
	}
	if (car->_gear <= 0) {
	    car->ctrl->gear++;
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

    car->pitcmd->fuel = MAX(MIN(f1, f2), 0);

    LastPitStopLap = car->_laps;

    car->pitcmd->repair = (int)car->_dammage;

    return ROB_PIT_MENU; /* The player is able to modify the value by menu */
}

