/***************************************************************************

    file                 : tanhoj.cpp
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
static int pitcmd(int index, tCarElt* car, tSituation *s);

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
    itf->rbPitCmd   = pitcmd;
    return 0;
}

/*
 * Function
 *	tanhoj
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
tanhoj(tModInfo *modInfo)
{
    modInfo->name    = "Tanhoj";	/* name of the module (short) */
    modInfo->desc    = "For Jonathan";	/* description of the module (can be long) */
    modInfo->fctInit = InitFuncPt;	/* init function */
    modInfo->gfId    = ROB_IDENT;	/* supported framework version */
    modInfo->index   = 1;
    return 0;
}
tdble	Tright[1];
tdble	TRightMin[1];
tdble	TRightMax[1];
tdble	MaxSpeed[1];
tdble	hold[1] = {0};
tdble	shiftThld[1][MAX_GEARS+1];
int     LookForward = 0;

static tdble PGain[1]		= {0.02};
static tdble AGain[1]		= {0.008};
static tdble Advance[1]		= {35.0};
static tdble Advance2[1]	= {20.0};
static tdble AdvStep[1]		= {20.0};
static tdble VGain[1]		= {0.0005};
static tdble preDy[1]		= {0};
static tdble spdtgt[1]		= {115.0};
static tdble spdtgt2[1]		= {1.0};
static tdble steerMult[1]	= {2.0};
static tdble Trightprev[1];

static tdble PitPGain[1]	= {0.05};
static tdble PitAGain[1]	= {0.008};
static tdble PitVGain[1]	= {0.01};

static tdble PitEntry = -1;
static tdble PitStart;
static tdble DistEntry = 50.0;
static tdble DistFullStop = 2.5;
static tdble FrontMu = 1.0;
static tdble MaxDammage = 1000;
static tdble PitOffset = 0.5;
static tdble D1 = 15.0;
static tdble O1 = 0.5;
static tdble D2 = 10.0;
static tdble O2 = 0.0;
static tdble D3 = 60.0;
static tdble KSteer = 1.0;




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
#define ADVANCE		"Advance"
#define ADVANCE2	"Advance2"
#define ADVSTEP		"AdvStep"
#define VGAIN		"VGain"
#define SPDTGT		"spdtgt"
#define SPDTGT2		"spdtgt2"
#define STEERMULT	"steerMult"
#define FUEL		"fuel"
#define DISTENTRY	"dist to prepare pit entry"
#define DISTFSTOP	"dist to full stop"
#define PITPGAIN	"PitPGain"
#define PITAGAIN	"PitAGain"
#define PITVGAIN	"PitVGain"
#define MAXDAMMAGE	"Max Dammage"
#define PITOFFSET	"Pit Offset"
#define DIST1		"dist1"
#define DIST2		"dist2"
#define DIST3		"dist3"
#define OFF1		"off1"
#define OFF2		"off2"
#define KSTEER		"KSteer"

static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation *s)
{
    void	*hdle;
    char	*str;
    char	buf[256];
    tdble	fuel;
    
    DmTrack = track;
    if (DmTrack->pits.type == TR_PIT_ON_TRACK_SIDE) {
	PitEntry = DmTrack->pits.pitEntry->lgfromstart;
	PitStart = DmTrack->pits.pitStart->lgfromstart;
    }
    
    str = strrchr(track->filename, '/') + 1;
    sprintf(ParamNames, "drivers/tanhoj/tracksdata/car_%s", str);
    *carParmHandle = GfParmReadFile(ParamNames, GFPARM_RMODE_STD);
    if (*carParmHandle == NULL) {
	sprintf(ParamNames, "drivers/tanhoj/car1.xml");
	*carParmHandle = GfParmReadFile(ParamNames, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
	GfOut("drivers/tanhoj/car1.xml Loaded\n");
    } else {
	GfOut("%s Loaded\n", ParamNames);
    }
    fuel = 0.0007 * DmTrack->length * (s->_totLaps + 1);
    
    sprintf(buf, "drivers/tanhoj/tracksdata/%s", str);
    hdle = GfParmReadFile(buf, GFPARM_RMODE_STD);
    if (hdle) {
	PGain[0]     = GfParmGetNum(hdle, SIMU_PRMS, PGAIN,     NULL, PGain[0]);
	AGain[0]     = GfParmGetNum(hdle, SIMU_PRMS, AGAIN,     NULL, AGain[0]);
	Advance[0]   = GfParmGetNum(hdle, SIMU_PRMS, ADVANCE,   NULL, Advance[0]);
	Advance2[0]  = GfParmGetNum(hdle, SIMU_PRMS, ADVANCE2,  NULL, Advance2[0]);
	AdvStep[0]   = GfParmGetNum(hdle, SIMU_PRMS, ADVSTEP,   NULL, AdvStep[0]);
	VGain[0]     = GfParmGetNum(hdle, SIMU_PRMS, VGAIN,     NULL, VGain[0]);
	spdtgt[0]    = GfParmGetNum(hdle, SIMU_PRMS, SPDTGT,    NULL, spdtgt[0]);
	spdtgt2[0]   = GfParmGetNum(hdle, SIMU_PRMS, SPDTGT2,   NULL, spdtgt2[0]);
	steerMult[0] = GfParmGetNum(hdle, SIMU_PRMS, STEERMULT, NULL, steerMult[0]);
	fuel         = GfParmGetNum(hdle, SIMU_PRMS, FUEL,	NULL, fuel);
	DistEntry    = GfParmGetNum(hdle, SIMU_PRMS, DISTENTRY,	NULL, DistEntry);
	DistFullStop = GfParmGetNum(hdle, SIMU_PRMS, DISTFSTOP,	NULL, DistEntry);
	PitPGain[0]  = GfParmGetNum(hdle, SIMU_PRMS, PITPGAIN,  NULL, PGain[0]);
	PitAGain[0]  = GfParmGetNum(hdle, SIMU_PRMS, PITAGAIN,  NULL, AGain[0]);
	PitVGain[0]  = GfParmGetNum(hdle, SIMU_PRMS, PITVGAIN,  NULL, VGain[0]);
	MaxDammage   = GfParmGetNum(hdle, SIMU_PRMS, MAXDAMMAGE,NULL, MaxDammage);
	PitOffset    = GfParmGetNum(hdle, SIMU_PRMS, PITOFFSET, NULL, PitOffset);
	D1           = GfParmGetNum(hdle, SIMU_PRMS, DIST1,     NULL, D1);
	D2           = GfParmGetNum(hdle, SIMU_PRMS, DIST2,     NULL, D2);
	D3           = GfParmGetNum(hdle, SIMU_PRMS, DIST3,     NULL, D3);
	O1           = GfParmGetNum(hdle, SIMU_PRMS, OFF1,      NULL, O1);
	O2           = GfParmGetNum(hdle, SIMU_PRMS, OFF2,      NULL, O2);
	KSteer       = GfParmGetNum(hdle, SIMU_PRMS, KSTEER,    NULL, KSteer);
	GfParmReleaseHandle(hdle);
    }
    GfParmSetNum(*carParmHandle, SECT_CAR, PRM_FUEL, (char*)NULL, fuel);
    FrontMu = (GfParmGetNum(*carParmHandle, SECT_FRNTRGTWHEEL, PRM_MU, NULL, FrontMu) +
	       GfParmGetNum(*carParmHandle, SECT_FRNTLFTWHEEL, PRM_MU, NULL, FrontMu)) / 2.0;
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
static tdble	Gear;
static tdble	TargetSpeed;
static tdble	InvBrkCmd;

void newrace(int index, tCarElt* car, tSituation *s)
{
    
    Tright[0] = Trightprev[0] = car->_trkPos.toRight;
    hold[0] = 8.0;

    car->_vect(0).type = CAR_VECT_INVALID;
    car->_vect(0).color[0] = .5;
    car->_vect(0).color[1] = .5;
    car->_vect(0).color[2] = .5;

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


static int lastpit = 0;
static int PitState = 0;
#define NONE			0
#define BEFORE_PIT_ENTRY	1
#define PIT_ENTRY_PASSED	2
#define NEAR_PIT		3
#define OUT_OF_PITS		4
#define EXITING_PITS		5

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
    tdble 	Dy, Dny;
    tdble 	Vy;
    tTrkLocPos	trkPos;
    tdble 	X, Y, x, y, CosA, SinA;
    tTrackSeg	*seg;
    tTrackSeg	*curSeg = 0;
    tdble	Da, Db;
    tdble	tgtSpeed = -1.0;
    tdble	lgfs;
    tdble	vtgt1, vtgt2;
    tdble	curAdv, curAdvMax, Amax, Atmp, AdvMax;
    tdble	aGain = AGain[0];
    tdble	vGain = VGain[0];
    tdble	pGain = PGain[0];
    tdble	KK = 2.0;
    tdble	dL, dW;
    tdble	dst;
    int		lastState;

    static tdble	Curtime = 0;
    static tdble	adv;
    static int		lap = 0;
    
    Gear = (tdble)car->_gear;
    LookForward = 1;

    memset(car->ctrl, 0, sizeof(tCarCtrl));

    Curtime += s->deltaTime;
    trkPos = car->_trkPos;
    X = car->_pos_X;
    Y = car->_pos_Y;
    seg = trkPos.seg;
    lgfs = GetDistToStart(car);
    MaxSpeed[0] = 10000.0;

    TRightMin[0] = 0.0;
    TRightMax[0] = DmTrack->width;

    /*
     * Pit-stop management
     */
    if (PitEntry != -1) {
	RtDistToPit(car, DmTrack, &dL, &dW);
	do {
	    lastState = PitState;

	    switch (PitState) {
	
	    case BEFORE_PIT_ENTRY:

		dst = PitEntry - lgfs;
		if (dst < 0) {
		    dst += DmTrack->length;
		}
		if (dst < DistEntry) {
		    /* Before Pit Entry */
		    hold[0] = Curtime;
		    LookForward = 1;
		    MaxSpeed[0] = sqrt(2.0 * G * dst * FrontMu + 1100.0) * .78;
		    if (dW > 0) {
			Tright[0] = DmTrack->width - 2.0;
		    } else {
			Tright[0] = 2.0;
		    }
		    TRightMin[0] = TRightMax[0] = Tright[0];
		    KK = 0.05;
		} else if (trkPos.seg->raceInfo & TR_PITENTRY) {
		    PitState = PIT_ENTRY_PASSED;
		}
		break;
	
	    case PIT_ENTRY_PASSED:

		switch(DmTrack->pits.side) {
		case TR_RGT:
		    curSeg = trkPos.seg->rside;
		    Tright[0] = -2.0;
		    break;
		case TR_LFT:
		    curSeg = trkPos.seg->lside;
		    Tright[0] = DmTrack->width + 2.0;
		    break;
		}

		/* Pit Entry */
		if ((curSeg->raceInfo & TR_PIT) || (dL < D3)) {
		    PitState = NEAR_PIT;
		} else {
		    hold[0] = Curtime;
		    LookForward = 0;
		    MaxSpeed[0] = sqrt(2.0 * G * dL * FrontMu) * .78;
		    if (dW > 0) {
			Tright[0] = DmTrack->width + 2.0;
		    } else {
			Tright[0] = -2.0;
		    }
		    TRightMin[0] = TRightMax[0] = Tright[0];
		    KK = 10.0;
		}
		
		break;

	    case NEAR_PIT:

		aGain = PitAGain[0];
		vGain = PitVGain[0];
		pGain = PitPGain[0];
		/* on the pit lane */
		hold[0] = Curtime;
		LookForward = 0;
		car->ctrl->raceCmd = RM_CMD_PIT_ASKED;
		MaxSpeed[0] = sqrt(2.0 * G * dL * FrontMu) * .75;

		if (dL > D2) {
		    Tright[0] = trkPos.toRight + (fabs(dW) - O2) * SIGN(dW);
		    KK = 50.0;
		} else if (dL > D1) {
		    Tright[0] = trkPos.toRight + (fabs(dW) - O1) * SIGN(dW);
		    KK = 100.0;
		} else {
		    Tright[0] = trkPos.toRight + (fabs(dW) - PitOffset) * SIGN(dW);
		    if (dL < DistFullStop) {
			MaxSpeed[0] = 0.0;
		    } else {
			MaxSpeed[0] = 5.0;
		    }
		    KK = 100.0;
		}
		TRightMin[0] = TRightMax[0] = Tright[0];
		break;

	    case OUT_OF_PITS:
		hold[0] = Curtime + 3.0;
		PitState = EXITING_PITS;
		break;

	    case EXITING_PITS:
		if (hold[0] > Curtime) {
		    aGain = PitAGain[0];
		    vGain = PitVGain[0];
		    pGain = PitPGain[0];
		    Tright[0] = trkPos.toRight + (fabs(dW) - 5.0) * SIGN(dW);
		    LookForward = 0;
		    if (trkPos.toRight < Tright[0]) {
			TRightMin[0] = trkPos.toRight;
			TRightMax[0] = Tright[0];
		    } else {
			TRightMax[0] = trkPos.toRight;
			TRightMin[0] = Tright[0];
		    }
		    KK = 0.5;
		} else {
		    switch(DmTrack->pits.side) {
		    case TR_RGT:
			curSeg = trkPos.seg->rside;
			Tright[0] = -2.0;
			break;
		    case TR_LFT:
			curSeg = trkPos.seg->lside;
			Tright[0] = DmTrack->width + 2.0;
			break;
		    }
		
		    if (curSeg->raceInfo & TR_PIT) {
			/* on the pit lane */
			hold[0] = Curtime;
			LookForward = 0;
			if (trkPos.toRight < Tright[0]) {
			    TRightMin[0] = trkPos.toRight;
			    TRightMax[0] = Tright[0];
			} else {
			    TRightMax[0] = trkPos.toRight;
			    TRightMin[0] = Tright[0];
			}
			KK = 0.5;
		    } else if (trkPos.seg->raceInfo & TR_PITEXIT) {
			PitState = NONE;
		    } else {
			switch(DmTrack->pits.side) {
			case TR_RGT:
			    curSeg = trkPos.seg->rside;
			    Tright[0] = 2.0;
			    break;
			case TR_LFT:
			    curSeg = trkPos.seg->lside;
			    Tright[0] = DmTrack->width - 2.0;
			    break;
			}
			hold[0] = Curtime;
			LookForward = 0;
			KK = 0.1;
		    }
		}
		break;

	    default:
		if (car->_dammage > MaxDammage) {
		    PitState = BEFORE_PIT_ENTRY;
		}
		if ((car->_fuel <  0.0007 * DmTrack->length * 2) && (s->_totLaps - s->cars[0]->_laps > 2)) {
		    PitState = BEFORE_PIT_ENTRY;
		}
		break;
	    }
	} while (lastState != PitState);
    }

    CosA = cos(car->_yaw);
    SinA = sin(car->_yaw);

    adv = Advance[0];
    
    vtgt1 = spdtgt[0];
    vtgt2 = spdtgt2[0];

    CollDet(car, 0, s, Curtime);
    

    /* proportionnal */
    Dy = trkPos.toRight;

    Da = RtTrackSideTgAngleL(&trkPos) - car->_yaw;
    NORM_PI_PI(Da);
    
    
    if (Curtime > hold[0]) {
	//Tright[0] = seg->width / 2.0;
	Tright[0] = Dy;
    }
    
    if (LookForward) {
	x = X + (CosA) * adv;
	y = Y + (SinA) * adv;
	RtTrackGlobal2Local(trkPos.seg, x, y, &trkPos, TR_LPOS_MAIN);
	Dny = seg->width / 2.0 - trkPos.toRight;

	Tright[0] += Dny;
    }
    
    RELAXATION(Tright[0], Trightprev[0], KK);

    if (Tright[0] < TRightMin[0]) {
	Tright[0] = TRightMin[0];
    } else if (Tright[0] > TRightMax[0]) {
	Tright[0] = TRightMax[0];
    }

/*     printf("TRt=%f  TR=%f", Tright[0], Dy); */

    Dy = Tright[0] - Dy;

    /* derivation */
    Vy = (Dy - preDy[0]) / s->deltaTime;
    preDy[0] = Dy;


    car->ctrl->steer = pGain * Dy + vGain * Vy - aGain * Da * Da * SIGN(Da);
    car->ctrl->steer *= steerMult[0] * (1 - exp(-fabs(car->_speed_x) * KSteer));
    
/*     printf("  Dy=%f  Vy=%f  Da=%f  Steer=%f\n", Dy, Vy, Da, car->ctrl->steer); */
    
    if (car->_speed_x < 0) {
	car->ctrl->steer *= 1.5;
    }

    /*
     * speed control
     */
    CosA = cos(car->_yaw + car->ctrl->steer*2.0);
    SinA = sin(car->_yaw + car->ctrl->steer*2.0);
    curAdv = Advance2[0];
    AdvMax = car->_speed_x * 5.0;
    Amax = 0;
    while (curAdv < AdvMax) {
	x = X + CosA * curAdv;
	y = Y + SinA * curAdv;
	RtTrackGlobal2Local(seg, x, y, &trkPos, TR_LPOS_MAIN);
	Atmp = fabs(trkPos.toRight - Tright[0]) / curAdv;
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
    TargetSpeed = tgtSpeed * 1.15;
    SpeedStrategy(car, 0, TargetSpeed, s, Db);


#define AMARG 0.9
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
		RtTelemStartMonitoring("Tanhoj");
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

static int pitcmd(int index, tCarElt* car, tSituation *s)
{
    tdble	f1, f2;

    f1 = car->_tank - car->_fuel;
    
    f2 = 0.0007 * (DmTrack->length * s->cars[0]->_remainingLaps + car->_trkPos.seg->lgfromstart) - car->_fuel;

    car->pitcmd->fuel = MAX(MIN(f1, f2), 0);

    car->pitcmd->repair = (int)car->_dammage;
    
    lastpit = car->_laps;
    PitState = OUT_OF_PITS; /* next state */

    printf("PIT STOP: fuel %f / repair %d\n", car->pitcmd->fuel, car->pitcmd->repair);
    
    return ROB_PIT_IM; /* The player is able to modify the value by menu */
}
