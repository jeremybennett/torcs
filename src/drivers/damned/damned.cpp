/***************************************************************************

    file                 : damned.cpp
    created              : Sat Mar 18 23:10:13 CET 2000
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

static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation *s);
static void drive(int index, tCarElt* car, tSituation *s);
static void newrace(int index, tCarElt* car, tSituation *s);

static tTrack    *DmTrack;

#ifdef _WIN32
/* should be present in mswindows */
BOOL WINAPI DllEntryPoint (HINSTANCE hDLL, DWORD dwReason, LPVOID Reserved)
{
    return TRUE;
}
#endif

/* #define RELAXATION(target, prev, rate) {(target) = (prev) + rate * ((target) - (prev)) * s->deltaTime; (prev) = (target);} */

int MinIndex = 100;

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

    if (index < MinIndex) {
	MinIndex = index;
    }
    
    itf->rbNewTrack = initTrack;			/* give the robot the track view called */
    /* for every track change or new race */
    itf->rbNewRace  = newrace;
    itf->rbDrive    = drive;			/* drive during race */
    itf->index      = index;
    return 0;
}

/*
 * Function
 *	damned
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
damned(tModInfo *modInfo)
{
    int		i;
    char	buf[256];
    
    for (i = 0; i < 10; i++) {
	sprintf(buf, "Damned %d", i+1);
	modInfo[i].name    = strdup(buf);	/* name of the module (short) */
	sprintf(buf, "EE robot #%d", i+1);
	modInfo[i].desc    = strdup(buf);	/* description of the module (can be long) */
	modInfo[i].fctInit = InitFuncPt;	/* init function */
	modInfo[i].gfId    = ROB_IDENT;	/* supported framework version */
	modInfo[i].index   = i+1;
    }
    return 0;
}


static tdble	shiftThld[10][MAX_GEARS+1];

static void
InitGears(tCarElt* car, int idx)
{
    int i;
    int index = idx - 1;

    for (i = 0; i < MAX_GEARS; i++) {
	if (car->_gearRatio[i] != 0) {
	    shiftThld[index][i] = car->_enginerpmRedLine * car->_wheelRadius(2) * 0.9 / car->_gearRatio[i];
	} else {
	    shiftThld[index][i] = 10000.0;
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
static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation *s)
{
    char	buf[256];
    
    DmTrack = track;
    sprintf(buf, "drivers/damned/%d/car.xml", index);
    *carParmHandle = GfParmReadFile(buf, GFPARM_RMODE_STD);
    if (*carParmHandle == NULL) {
	*carParmHandle = GfParmReadFile("drivers/damned/car1.xml", GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    } else {
	GfOut("%s loaded\n", buf);
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
static tdble      Tright[10];
static tdble      Trightprev[10];
static tdble lastBrkCmd[10] = {0};
static tdble lastAccel[10];

static tdble AccSteer[10] = { 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
static tdble AccAngle[10] = { 3.0, 3.0, 3.0, 0.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0 };



static void
SpeedStrategy(tCarElt* car, int idx, tdble Vtarget, tdble steer, tdble maxBrk, tSituation *s, tdble aspect)
{
    const tdble Dx = 6.0;
    static tdble slip;
    tdble accelTgt;
    int gear;

    gear = car->_gear;

    if (Vtarget > car->_speed_x) {
	/* speed management */
	accelTgt = car->ctrl->accelCmd = MIN((Vtarget+1.0 - car->_speed_x) / Dx, 1.0);
    
	/* anti-slip */
	/* assume SPOOL differential and rwd */
	if (car->_speed_x > 0) {
	    slip = (car->_wheelRadius(3) * car->_wheelSpinVel(3) - car->_speed_x) / car->_speed_x;
	} else {
	    slip = 0;
	}
	if ((car->_gear == 1) && (idx != 2) && (idx != 3)) {
	    car->ctrl->accelCmd = car->ctrl->accelCmd * exp(-fabs(steer) * AccSteer[idx]) * exp(-fabs(aspect) * AccAngle[idx]) + 0.1;
	} else if (car->_gear > 1) {
	    car->ctrl->accelCmd = car->ctrl->accelCmd * exp(-fabs(aspect) * 0.5) ; //+ 0.15;
	}
	
	
	if ((slip > 0.2) && (car->_gear > 1)) {
	    car->ctrl->accelCmd = 0;
	    //lastAccel = 0.0;
	} else {
	    RELAXATION(car->ctrl->accelCmd, lastAccel[idx], 3.0);
	}
	
    } else {
	if (car->_speed_x > 0) {
	    slip = (car->_speed_x - car->_wheelRadius(0) * MIN(car->_wheelSpinVel(0), car->_wheelSpinVel(1))) / car->_speed_x;
	} else {
	    slip = 0;
	}
	car->ctrl->brakeCmd = MIN(-MIN((Vtarget+1.0 - car->_speed_x) / 20.0, 1.0)  * maxBrk, maxBrk);
	if (slip > 0.2) {
	    car->ctrl->brakeCmd = 0.0;
	} else {
	    RELAXATION(car->ctrl->brakeCmd, lastBrkCmd[idx], 3.0);
	}
	
	lastAccel[idx] = 0;
    }


    /* shift */
    gear += car->_gearOffset;
    car->ctrl->gear = car->_gear;
    
    if (car->_speed_x > shiftThld[idx][gear]) {
	car->ctrl->gear++;
    } else if ((car->_gear > 1) && (car->_speed_x < (shiftThld[idx][gear-1] - 4.0))) {
	car->ctrl->gear--;
    }
    if (car->_gear <= 0) {
	car->ctrl->gear++;
    }

}


static tdble
dmGetDistToStart(tCarElt *car)
{
    tTrackSeg	*seg;
    tdble	lg;
    
    seg = car->_trkPos.seg;
    lg = seg->lgfromstart;
    
    switch (seg->type) {
    case TR_STR:
	lg += car->_trkPos.toStart;
	break;
    default:
	lg += car->_trkPos.toStart * seg->radius;
	break;
    }
    return lg;
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
const  tdble PGain[10]   = {	0.08,	0.10,   0.2,	0.25,	0.2,	0.2,	0.2,	0.02,	0.01,	0.02	};
const  tdble AGain[10]   = {	0.30,	0.10,   0.15,	0.1,	0.15,	0.05,	0.08,	0.08,	0.008,	0.08	};
static tdble PnGain[10]  = {	0.10,	0.15,   0.08,	0.1,	0.08,	0.01,	0.05,	0.015,	0.01,	0.015	};
const  tdble PnnGain[10] = {	0.0,	0.00,   0.00,	0.00,	0.00,	0.015,	0.02,	0.00,	0.00,	0.00	};
static tdble Advance[10] = {	18.0,	15.0,   0.0,	0.0,	0,	40,	40.8,	0.0,	40.8,	0	};
static tdble Advance2[10]= {	15.0,	15.0,   0.0,	0.0,	0,	15,	40,	0.0,	40.8,	0	};
const  tdble Advance3[10]= {	-15.0,	-17.0,  -16.0,	-5.0,	-26.0,	-30.0,	-35.0,	0.0,	-30.0,	-30.0	};
const  tdble Advance4[10]= {	4.00,	4.0,    4.0,	4.0,	4.0,	4.0,	4.0,	4.0,	4.0,	4.0	};
const  tdble VGain[10]   = {	0.010,	0.02,   0.01,	0.02,	0.01,	0.005,	0.02,	0.0005,	0.0005,	0.0005	};
static tdble preDy[10]   = {	0.0,	0,      0,	0,	0,	0,	0,	0,	0,	0	};
static tdble spdtgt[10]  = {	5000,	5000,  	10000,	20000,	10000,	10000,	10000,	10000,	920,	10000	};
static tdble spdtgt2[10] = {	10,	0,	0,	0,	0,	0,	13,	0,	12,	0	};
static tdble maxBrk[10]  = {	1.0,	1.0,	1.0,	1.0,	1.0,	1.0,	1.0,	1.0,	1.0,	1.0	};
static tdble hold[10] = {0};
static tdble steerk[10] = {	1.0,	1.0,	1.0,	1.1,	1.0,	1.0, 	1.0, 	1.0, 	1.0, 	1.0	};
static tdble MaxSpeed[10];

void newrace(int index, tCarElt* car, tSituation *s)
{
    Tright[index-1] = Trightprev[index-1] = car->_trkPos.toRight;
    hold[index-1] = 5.0;
    InitGears(car, index);
    spdtgt2[2] = DmTrack->width - 4.0;
    Advance[2] = Advance2[2] = DmTrack->width * 2.0;
    spdtgt2[3] = DmTrack->width - 4.0;
    Advance[3] = Advance2[3] = DmTrack->width * 2.5;
    spdtgt2[4] = DmTrack->width - 3.0;
    Advance[4] = Advance2[4] = DmTrack->width * 2.0;
    spdtgt2[5] = DmTrack->width - 5.0;
    spdtgt2[7] = DmTrack->width;
    Advance[7] = Advance2[7] = DmTrack->width * 2.0 + 8.0;
    spdtgt2[9] = DmTrack->width + 2.5;
    Advance[9] = Advance2[9] = DmTrack->width * 2.0 + 3.0;
}

static void drive(int index, tCarElt* car, tSituation *s)
{
    static tdble Curtime = 0;
    tdble 	Dy, Dny /* , Dnny */;
    tdble 	Vy;
    tTrkLocPos	trkPos;
    tdble 	X, Y, x, y, CosA, SinA;
    int 	idx = index - 1;
    tTrackSeg	*seg;
    tdble	Da, Db;
    tCarElt	*otherCar;
    int		i;
    tdble	lgfs, lgfs2, dlg;
    tdble	vtgt1, vtgt2;
    tdble	dspd = 0;
    tdble	maxdlg;
    tdble	vang;
    
    memset(car->ctrl, 0, sizeof(tCarCtrl));

    if (index == MinIndex) {
	Curtime += s->deltaTime;
    }
    
    trkPos = car->_trkPos;
    X = car->_pos_X;
    Y = car->_pos_Y;
    seg = trkPos.seg;
    CosA = cos(car->_yaw);
    SinA = sin(car->_yaw);
    lgfs = dmGetDistToStart(car);
    if (Curtime > hold[idx]) {
	Tright[idx] = seg->width / 2.0;
    }


    if (idx == 1) {
	Advance[1] = (0.3 * car->_speed_x + 10.0) * seg->kFriction;
	spdtgt2[1]  = 20.0 * seg->kFriction - 12.0;
    }

    vtgt1 = spdtgt[idx];
    vtgt2 = spdtgt2[idx];
    maxdlg = 200.0;
    MaxSpeed[idx] = 10000;
    /*
     * Collision detection
     */
    for (i = 0; i < s->_ncars; i++) {
	otherCar = s->cars[i];
	if ((otherCar == car) || (otherCar->_state & RM_CAR_STATE_NO_SIMU)) {
	    continue;
	}
	lgfs2 = dmGetDistToStart(otherCar);
	dlg = lgfs2 - lgfs;
	if (dlg > (DmTrack->length / 2.0)) dlg -= DmTrack->length;
	if (dlg < -(DmTrack->length / 2.0)) dlg += DmTrack->length;

	dspd = car->_speed_x - otherCar->_speed_x;
	if ((dlg > -(car->_dimension_x + 1.0)) &&
	    ((dlg < (dspd*6.0 + 10.0)) ||
	    (dlg < (car->_dimension_x * 4.0)))) {
	    /* risk of collision */
	    tdble MARGIN = 6.0;
	    if (fabs(car->_trkPos.toRight - otherCar->_trkPos.toRight) < MARGIN) {
		if (car->_trkPos.toRight < otherCar->_trkPos.toRight) {
		    if (otherCar->_trkPos.toRight > MARGIN) {
			Tright[idx] = otherCar->_trkPos.toRight - (MARGIN + 2.0);
		    } else {
			//Tright[idx] = otherCar->_trkPos.toRight + MARGIN;
			if (dlg > (car->_dimension_x * 2.0)) {
			    /* MaxSpeed[idx] = otherCar->_speed_x * .9; */
			    /* Tright[idx] = otherCar->_trkPos.toRight + (MARGIN * 2.0); */
			}
		    }
		} else {
		    if (otherCar->_trkPos.toRight < (seg->width - MARGIN)) {
			Tright[idx] = otherCar->_trkPos.toRight + (MARGIN + 2.0);
		    } else {
			//Tright[idx] = otherCar->_trkPos.toRight - MARGIN;
			if (dlg > (car->_dimension_x * 2.0)) {
			    /* MaxSpeed[idx] = otherCar->_speed_x * .9; */
			   /*  Tright[idx] = otherCar->_trkPos.toRight - (MARGIN * 2.0); */
			}
		    }
		}
		hold[idx] = Curtime + 2.0;
		if ((dlg > (car->_dimension_x /2.0)) && (dlg < (car->_dimension_x * 3.0)) && (fabs(car->_trkPos.toRight - otherCar->_trkPos.toRight) < 2.0)) {
		    MaxSpeed[idx] = otherCar->_speed_x * .9;
		}
	    }
	}
    }
    RELAXATION(Tright[idx], Trightprev[idx], 0.5);

    /* proportionnal */
    Dy = Tright[idx] - trkPos.toRight;

    /* derivation */
    Vy = (Dy - preDy[idx]) / s->deltaTime;
    preDy[idx] = Dy;

    /* angular target */
    Da = RtTrackSideTgAngleL(&trkPos) - car->_yaw;
    NORM_PI_PI(Da);
    
    x = X + (CosA) * Advance[idx];
    y = Y + (SinA) * Advance[idx];
    RtTrackGlobal2Local(trkPos.seg, x, y, &trkPos, TR_LPOS_MAIN);
    Dny = seg->width / 2.0 - trkPos.toRight;

/*     x = X + (CosA) * Advance2[idx]; */
/*     y = Y + (SinA) * Advance2[idx]; */
/*     RtTrackGlobal2Local(trkPos.seg, x, y, &trkPos, TR_LPOS_MAIN); */
/*     Dnny = Tright[idx] - trkPos.toRight; */

    Dy = 2.0 * Dy / DmTrack->width;
    if (Dy > 0) {
	Dy = Dy * Dy;
    } else {
	Dy = -Dy * Dy;
    }
    
    car->ctrl->steer = PGain[idx] * Dy + VGain[idx] * Vy + PnGain[idx] * Dny + AGain[idx] * Da * Da;

    if (car->_speed_x < 0) {
	car->ctrl->steer *= 1.5;
    } else {
	car->ctrl->steer *= steerk[idx];
    }
	


    /*
     * speed control
     */
    vang = atan2(car->_speed_Y, car->_speed_X);
    CosA = cos(vang);
    SinA = sin(vang);
    x = X + (CosA) * (0.04 * car->_speed_x * car->_speed_x - Advance3[idx]);
    y = Y + (SinA) * (0.04 * car->_speed_x * car->_speed_x - Advance3[idx]);
    RtTrackGlobal2Local(trkPos.seg, x, y, &trkPos, TR_LPOS_MAIN);

    Dny = Advance4[idx] * fabs(trkPos.toRight - seg->width /2.0) / (seg->width * 2.0);
    Dny = exp(-Dny * Dny * Dny * Dny);

    Db = car->_yaw_rate;
    SpeedStrategy(car, idx, MIN((vtgt1 * Dny  + vtgt2) * 1.8, MaxSpeed[idx]), car->ctrl->steer, maxBrk[idx], s, Db);

#define AMARG 0.6
    if ((((Da > (PI/2.0-AMARG)) && (car->_trkPos.toRight < seg->width/3.0)) ||
	 ((Da < (AMARG-PI/2.0)) && (car->_trkPos.toRight > seg->width-seg->width/3.0))) && 
	(car->_gear < 2) && (car->_speed_x < 3.5)) {
	car->ctrl->steer = -car->ctrl->steer * 2.0;
	car->ctrl->gear = -1;
    } else if ((fabs(Da) > (PI - (PI/4.0))) &&
	       ((car->_trkPos.toRight < 0) ||
		(car->_trkPos.toRight > seg->width))) {
	car->ctrl->steer = car->ctrl->steer * 6.0;
    }
    if ((car->_speed_x < -0.5) && (car->_gear > 0)) {
	car->ctrl->brakeCmd = 1.0;
    }
}

