/***************************************************************************

    file                 : tita.cpp
    created              : Tue Mar  7 22:09:50 CET 2000
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



#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <tgf.h>

#include <track.h>
#include <car.h>
#include <raceman.h>
#include <robot.h>
#include <robottools.h>


#include "common.h"

static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation *s);
static void drive(int index, tCarElt* car, tSituation *s);
static void newrace(int index, tCarElt* car, tSituation *s);

tTrack		*DmTrack;
static char	ParamNames[256];

#ifdef _WIN32
/* should be present in mswindows */
BOOL WINAPI DllEntryPoint (HINSTANCE hDLL, DWORD dwReason, LPVOID Reserved)
{
    return TRUE;
}
#endif

/* #define RELAXATION(target, prev, gain) {(target) = (prev) + gain * ((target) - (prev)) * s->deltaTime; (prev) = (target);} */

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
    tRobotItf *itf = (tRobotItf *)pt;
    
    itf->rbNewTrack = initTrack;			/* give the robot the track view called */
    /* for every track change or new race */
    itf->rbNewRace  = newrace;
    itf->rbDrive    = drive;			/* drive during race */
    itf->index      = index;
    return 0;
}

/*
 * Function
 *	tita
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
tita(tModInfo *modInfo)
{
    modInfo->name    = "Tita";	/* name of the module (short) */
    modInfo->desc    = "For Jonathan";	/* description of the module (can be long) */
    modInfo->fctInit = InitFuncPt;	/* init function */
    modInfo->gfId    = ROB_IDENT;	/* supported framework version */
    modInfo->index   = 1;
    return 0;
}
tdble	Tright[10];
tdble	MaxSpeed[10];
tdble	hold[10] = {0};
tdble	shiftThld[10][MAX_GEARS+1];

static tdble PGain[10]    = {0.02};
static tdble AGain[10]    = {0.008};
static tdble PnGain[10]   = {0.02};
static tdble Advance[10]  = {35.0};
static tdble Advance2[10] = {20.0};
static tdble AdvStep[10]  = {20.0};
static tdble VGain[10]    = {0.0005};
static tdble preDy[10]    = {0};
static tdble spdtgt[10]   = {115.0};
static tdble spdtgt2[10]  = {1.0};
static tdble steerMult[10]  = {2.0};
static tdble Trightprev[10];

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

#define SIMU_PRMS	"Simulation Parameters"
#define PGAIN		"PGain"
#define AGAIN		"AGain"
#define PNGAIN		"PnGain"
#define ADVANCE		"Advance"
#define ADVANCE2	"Advance2"
#define ADVSTEP		"AdvStep"
#define VGAIN		"VGain"
#define PREDY		"preDy"
#define SPDTGT		"spdtgt"
#define SPDTGT2		"spdtgt2"
#define STEERMULT	"steerMult"

tdble Gmax;

static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation *s)
{
    void	*hdle;
    char	*str;
    char	buf[256];
    tdble	fuel;
    tdble	tmpMu;
    
    
    DmTrack = track;
    str = strrchr(track->filename, '/') + 1;
    sprintf(ParamNames, "drivers/tita/tracksdata/car_%s", str);
    *carParmHandle = GfParmReadFile(ParamNames, GFPARM_RMODE_STD);
    if (*carParmHandle == NULL) {
	sprintf(ParamNames, "drivers/tita/car.xml");
	*carParmHandle = GfParmReadFile(ParamNames, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
	GfOut("drivers/tita/car.xml Loaded\n");
    } else {
	GfOut("%s Loaded\n", ParamNames);
    }
    fuel = 0.0007 * DmTrack->length * (s->_totLaps + 1);
    GfParmSetNum(*carParmHandle, SECT_CAR, PRM_FUEL, (char*)NULL, fuel);

    Gmax = GfParmGetNum(*carParmHandle, SECT_FRNTRGTWHEEL, PRM_MU, (char*)NULL, 1.0);
    tmpMu = GfParmGetNum(*carParmHandle, SECT_FRNTLFTWHEEL, PRM_MU, (char*)NULL, 1.0);
    Gmax = MIN(Gmax, tmpMu);
    tmpMu = GfParmGetNum(*carParmHandle, SECT_REARRGTWHEEL, PRM_MU, (char*)NULL, 1.0);
    Gmax = MIN(Gmax, tmpMu);
    tmpMu = GfParmGetNum(*carParmHandle, SECT_REARLFTWHEEL, PRM_MU, (char*)NULL, 1.0);
    Gmax = MIN(Gmax, tmpMu);
/*     Gmax = Gmax * GfParmGetNum(*carParmHandle, SECT_CAR, PRM_MASS, (char*)NULL, 1000.0); */

    sprintf(buf, "drivers/tita/tracksdata/%s", str);
    hdle = GfParmReadFile(buf, GFPARM_RMODE_STD);
    if (hdle) {
	PGain[0]     = GfParmGetNum(hdle, SIMU_PRMS, PGAIN,     NULL, PGain[0]);
	AGain[0]     = GfParmGetNum(hdle, SIMU_PRMS, AGAIN,     NULL, AGain[0]);
	PnGain[0]    = GfParmGetNum(hdle, SIMU_PRMS, PNGAIN,    NULL, PnGain[0]);
	Advance[0]   = GfParmGetNum(hdle, SIMU_PRMS, ADVANCE,   NULL, Advance[0]);
	Advance2[0]  = GfParmGetNum(hdle, SIMU_PRMS, ADVANCE2,  NULL, Advance2[0]);
	AdvStep[0]   = GfParmGetNum(hdle, SIMU_PRMS, ADVSTEP,   NULL, AdvStep[0]);
	VGain[0]     = GfParmGetNum(hdle, SIMU_PRMS, VGAIN,     NULL, VGain[0]);
	preDy[0]     = GfParmGetNum(hdle, SIMU_PRMS, PREDY,     NULL, preDy[0]);
	spdtgt[0]    = GfParmGetNum(hdle, SIMU_PRMS, SPDTGT,    NULL, spdtgt[0]);
	spdtgt2[0]   = GfParmGetNum(hdle, SIMU_PRMS, SPDTGT2,   NULL, spdtgt2[0]);
	steerMult[0] = GfParmGetNum(hdle, SIMU_PRMS, STEERMULT, NULL, steerMult[0]);

	GfParmReleaseHandle(hdle);
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
 */
static int	curidx;
static tdble	Gear;
static tdble	TargetSpeed;
static tdble	InvBrkCmd;

void newrace(int index, tCarElt* car, tSituation *s)
{
    
    Tright[0] = Trightprev[0] = car->_trkPos.toRight;
    hold[0] = 8.0;
    curidx = 0;

    InitGears(car, 0);

    if (s->_raceType == RM_TYPE_PRACTICE) {
	RtTelemInit(-10, 10);
	RtTelemNewChannel("Ax", &car->_accel_x, -30, 30);
	RtTelemNewChannel("Ay", &car->_accel_y, -30, 30);
	RtTelemNewChannel("Vaz", &car->_yaw_rate, -10, 10);
	RtTelemNewChannel("Steer", &car->ctrl->steer, -1, 1);
	RtTelemNewChannel("Throttle", &car->ctrl->accelCmd, -1, 1);
	RtTelemNewChannel("Brake", &InvBrkCmd, -1, 1);
	RtTelemNewChannel("Gear", &Gear, -10, 10);
	RtTelemNewChannel("Speed", &car->_speed_x, -100, 100);
	RtTelemNewChannel("Target Speed", &TargetSpeed, -100, 100);
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
static void drive(int index, tCarElt* car, tSituation *s)
{
    static tdble Curtime = 0;
    tdble 		Dy, Dny;
    tdble 		Vy;
    tTrkLocPos		trkPos, trkPos2;
    tdble 		X, Y, x, y, CosA, SinA;
    tTrackSeg		*seg;
    tdble		Da, Db;
    tdble		tgtSpeed = -1.0;
    tdble		lgfs;
    tdble		vtgt1, vtgt2;
    static tdble	lgfsprev = 0.0;
    tdble		adv;
    tdble		curAdv, curAdvMax, Amax, Atmp, AdvMax;

    static int		lap = 0;
    
    
    Gear = (tdble)car->_gear;
    
    memset(car->ctrl, 0, sizeof(tCarCtrl));

    Curtime += s->deltaTime;

    MaxSpeed[0] = 10000.0;
    trkPos = car->_trkPos;
    X = car->_pos_X;
    Y = car->_pos_Y;
    seg = trkPos.seg;
    CosA = cos(car->_yaw);
    SinA = sin(car->_yaw);
    lgfs = GetDistToStart(car) + fabs(preDy[0]);
    if (lgfs < DmTrack->seg->next->length) {
	curidx = 0;
	if (lgfsprev > lgfs) {
	    lgfsprev = 0;
	}
    }

    adv = Advance[0] + 5.0 * sqrt(fabs(car->_speed_x));
    
    if (Curtime > hold[0]) {
	    Tright[0] = seg->width / 2.0;
    }

    
    vtgt1 = spdtgt[0];
    vtgt2 = spdtgt2[0];

    x = X + (CosA) * adv;
    y = Y + (SinA) * adv;
    RtTrackGlobal2Local(trkPos.seg, x, y, &trkPos2, TR_LPOS_MAIN);
    Dny = seg->width / 2.0 - trkPos2.toRight;

    CollDet(car, 0, s, Curtime, Dny);
    
    RELAXATION(Tright[0], Trightprev[0], 2.0);

    /* proportionnal */
    Dy = Tright[0] - trkPos.toRight;

    /* derivation */
    Vy = (Dy - preDy[0]) / s->deltaTime;
    preDy[0] = Dy;

    Da = RtTrackSideTgAngleL(&trkPos) - car->_yaw;
    NORM_PI_PI(Da);
    

    car->ctrl->steer = PGain[0] * Dy + VGain[0] * Vy + PnGain[0] * Dny + AGain[0] * Da * Da;

    if (car->_speed_x < 0) {
	car->ctrl->steer *= 1.5;
    } else {
	car->ctrl->steer *= 1.1;
    }

    /*
     * speed control
     */
    CosA = cos(car->_yaw + car->ctrl->steer*2.0);
    SinA = sin(car->_yaw + car->ctrl->steer*2.0);
    curAdv = Advance2[0];
    AdvMax = fabs(car->_speed_x) * 5.0 + 1.0;
    Amax = 0;
    while (curAdv < AdvMax) {
	x = X + CosA * curAdv;
	y = Y + SinA * curAdv;
	RtTrackGlobal2Local(seg, x, y, &trkPos, TR_LPOS_MAIN);
	Atmp = fabs(trkPos.toRight - car->_trkPos.toRight) / AdvMax;
	if (Amax < Atmp) {
	    Amax = Atmp;
	    curAdvMax = curAdv;
	}
	curAdv += AdvStep[0];
    }

    Db = car->_yaw_rate;
    Amax = 1.0 - Amax;
    Amax = Amax * Amax;
    if (tgtSpeed < 0) {
	tgtSpeed = (vtgt1 * Amax  + vtgt2) *
	    (1.0 + tan(fabs(car->_trkPos.seg->angle[TR_XE] + car->_trkPos.seg->angle[TR_XS])));
	tgtSpeed = MIN(tgtSpeed, MaxSpeed[0] / 1.15);
    }
    if (tgtSpeed < 41.0) {
	TargetSpeed = tgtSpeed * 1.15;
    } else {
	TargetSpeed = tgtSpeed * 1.15;
    }
    SpeedStrategy(car, 0, TargetSpeed, s, Db);


#define AMARG 0.6
    if ((((Da > (PI/2.0-AMARG)) && (car->_trkPos.toRight < seg->width/3.0)) ||
	 ((Da < (AMARG-PI/2.0)) && (car->_trkPos.toRight > (seg->width - seg->width/3.0)))) && 
	(car->_gear < 2) && (car->_speed_x < 1.0)) {
	car->ctrl->steer = -car->ctrl->steer * 3.0;
	car->ctrl->gear = -1;
    } else if ((fabs(Da) > (PI - (PI/4.0))) &&
	       ((car->_trkPos.toRight < 0) ||
		(car->_trkPos.toRight > seg->width))) {
	car->ctrl->steer = -car->ctrl->steer * 3.0;
    }
    if ((car->_speed_x < -0.5) && (car->_gear > 0)) {
	car->ctrl->brakeCmd = 1.0;
    }

    if (car->_laps == 2) {
	if (s->_raceType == RM_TYPE_PRACTICE) {
	    if (lap == 1) {
		RtTelemStartMonitoring("Tita");
	    }
	    RtTelemUpdate(car->_curLapTime);
	}
    }
    if (car->_laps == 3) {
	if (s->_raceType == RM_TYPE_PRACTICE) {
	    if (lap == 2) {
		RtTelemShutdown();
	    }
	}
    }
    lap = car->_laps;

    InvBrkCmd = - car->ctrl->brakeCmd;
}

