/***************************************************************************

    file                 : tita.cpp
    created              : Mon Nov  1 21:09:12 CET 1999
    copyright            : (C) 1999 by Eric Espie & Christophe Guionneau
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

tTrack    *DmTrack;

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
    modInfo->desc    = "For Tristan";	/* description of the module (can be long) */
    modInfo->fctInit = InitFuncPt;	/* init function */
    modInfo->gfId    = ROB_IDENT;	/* supported framework version */
    modInfo->index   = 1;
    return 0;
}
static tdble	Tright[10];
static tdble	MaxSpeed[10];
static tdble	hold[10] = {0};
static tdble	shiftThld[10][MAX_GEARS+1];

const  tdble PGain[1]    = {0.02};
const  tdble AGain[10]    = {0.008};
const  tdble PnGain[10]   = {0.02};
const  tdble Advance[10]  = {35.0};
const  tdble Advance2[10] = {20.0};
const  tdble Advance3[10] = {200.0};
const  tdble AdvStep[10]  = {20.0};
const  tdble VGain[10]    = {0.0005};
static tdble preDy[10]    = {0};
static tdble spdtgt[10]   = {115.0};
static tdble spdtgt2[10]  = {1.5};
static tdble Trightprev[10];


void
InitGears(tCarElt* car, int idx)
{
    int i;

    for (i = 0; i < MAX_GEARS; i++) {
	if (car->_gearRatio[i] != 0) {
	    shiftThld[idx][i] = car->_enginerpmRedLine * car->_wheelRadius(2) * 0.9 / car->_gearRatio[i];
	} else {
	    shiftThld[idx][i] = 10000.0;
	}
    }
}

static tdble lastAccel[10] = {0};
static tdble lastBrkCmd[10] = {0};

void
SpeedStrategy(tCarElt* car, int idx, tdble Vtarget, tSituation *s, tdble aspect)
{
    const tdble Dx = 2.0;
    tdble slip;
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
	if (gear == 1) {
	    car->ctrl->accelCmd = car->ctrl->accelCmd * exp(-fabs(car->ctrl->steer) * 4.0) * exp(-fabs(aspect) * 4.0) + 0.2;
	} else if (gear > 1) {
	    if (car->_speed_x < 40.0) {
		car->ctrl->accelCmd = car->ctrl->accelCmd * exp(-fabs(aspect) * 4.0) + 0.15;
	    }
	}
	
	
	if ((slip > 0.2) && (gear > 1)) {
	    car->ctrl->accelCmd = 0;
	} else {
	    RELAXATION(car->ctrl->accelCmd, lastAccel[idx], 3.0);
	}
	lastBrkCmd[idx] = 0;
    } else {
	if (car->_speed_x > 0) {
	    slip = (car->_speed_x - car->_wheelRadius(0) * MIN(car->_wheelSpinVel(0), car->_wheelSpinVel(1))) / car->_speed_x;
	} else {
	    slip = 0;
	}
	car->ctrl->brakeCmd = MIN(-MIN((Vtarget+1.0 - car->_speed_x) / 10.0, 1.0), 1.0);
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

tdble
GetDistToStart(tCarElt *car)
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


void
CollDet(tCarElt* car, int idx, tSituation *s, tdble Curtime)
{
    int		i;
    tCarElt	*otherCar;
    tdble	lgfs, lgfs2, dlg;
    tdble	dspd;
    tdble	maxdlg;
    tTrackSeg	*seg;

    maxdlg = 200.0;
    seg = car->_trkPos.seg;
    lgfs = GetDistToStart(car);
    car->_vect(0).type = CAR_VECT_INVALID;
    for (i = 0; i < s->_ncars; i++) {
	otherCar = s->cars[i];
	if (otherCar == car) {
	    continue;
	}
	lgfs2 = GetDistToStart(otherCar);
	dlg = lgfs2 - lgfs;
	if (dlg > (DmTrack->length / 2.0)) dlg -= DmTrack->length;
	if (dlg < -(DmTrack->length / 2.0)) dlg += DmTrack->length;

	dspd = car->_speed_x - otherCar->_speed_x;
	if (((dlg < maxdlg) && (dlg > -(car->_dimension_x + 1.0))) &&
	    ((dlg < (dspd*4.0)) ||
	    (dlg < (car->_dimension_x * 2.0)))) {
	    car->_vect(0).type = CAR_VECT_ABSOLUTE;
	    car->_vect(0).start.x = car->_pos_X;
	    car->_vect(0).start.y = car->_pos_Y;
	    car->_vect(0).start.z = car->_vect(0).end.z = car->_pos_Z+ 2.0;
	    car->_vect(0).end.x = otherCar->_pos_X;
	    car->_vect(0).end.y = otherCar->_pos_Y;
	    maxdlg = dlg;
	    /* risk of collision */
#define MARGIN 5.0
	    if (fabs(car->_trkPos.toRight - otherCar->_trkPos.toRight) < MARGIN) {
		if (car->_trkPos.toRight < otherCar->_trkPos.toRight) {
		    if (otherCar->_trkPos.toRight > MARGIN) {
			Tright[idx] = otherCar->_trkPos.toRight - MARGIN;
		    } else {
			//Tright[idx] = otherCar->_trkPos.toRight + MARGIN;
			if (dlg > (car->_dimension_x * 2.0)) {
			    MaxSpeed[idx] = otherCar->_speed_x - 3.0;
			}
		    }
		} else {
		    if (otherCar->_trkPos.toRight < seg->width - MARGIN) {
			Tright[idx] = otherCar->_trkPos.toRight + MARGIN;
		    } else {
			//Tright[idx] = otherCar->_trkPos.toRight - MARGIN;
			if (dlg > (car->_dimension_x * 2.0)) {
			    MaxSpeed[idx] = otherCar->_speed_x - 3.0;
			}
		    }
		}
		hold[idx] = Curtime + 1.0;
	    }
	}
    }

    if (Tright[idx] < 0.0) {
	Tright[idx] = 0.0;
    } else if (Tright[idx] > seg->width) {
	Tright[idx] = seg->width;
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
typedef struct 
{
    tdble	tr;
    tdble	dstfs;
    tdble	spd;
} tTgtPt;

tTgtPt *TgtPts;

#define SCT "Trajectory"
#define LST "Trajectory/Points"
#define TR  "to right"
#define TL  "to left"
#define TSL "to start line"
#define SPD "speed"
static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation *s)
{
    void	*hdle;
    char	*str;
    int		nbPts;
    int		idx;
    char	buf[256];
    tdble	spd = spdtgt2[0];
    tdble	tr = track->seg->next->width/2.0;
    tdble	dstfs = 0;
    
    DmTrack = track;
    str = strrchr(track->filename, '/') + 1;
    sprintf(buf, "drivers/tita/tracksdata/car_%s", str);
    *carParmHandle = GfParmReadFile(buf, GFPARM_RMODE_STD);
    if (*carParmHandle == NULL) {
	*carParmHandle = GfParmReadFile("drivers/tita/car1.xml", GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    }
    sprintf(buf, "drivers/tita/tracksdata/%s", str);
    hdle = GfParmReadFile(buf, GFPARM_RMODE_STD);
    if (hdle) {
	nbPts = GfParmGetEltNb(hdle, LST);
	TgtPts = (tTgtPt*)NULL;
	if (nbPts) {
	    TgtPts = (tTgtPt*)calloc(nbPts+1, sizeof(tTgtPt));
	    GfParmListSeekFirst(hdle, LST);
	    idx = 0;
	    do {
		tr = track->width - GfParmGetCurNum(hdle, LST, TL, (char*)NULL, (track->width - tr));
		TgtPts[idx].tr = tr = GfParmGetCurNum(hdle, LST, TR, (char*)NULL, tr);
		TgtPts[idx].dstfs = dstfs = GfParmGetCurNum(hdle, LST, TSL, (char*)NULL, dstfs);
		TgtPts[idx].spd = spd = GfParmGetCurNum(hdle, LST, SPD, (char*)NULL, spd);
		idx++;
	    } while (GfParmListSeekNext(hdle, LST) == 0);
	    TgtPts[idx].dstfs = track->length + 1.0;
	    TgtPts[idx].tr = TgtPts[idx-1].tr;
	    TgtPts[idx].spd = spd;
	}
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

void newrace(int index, tCarElt* car, tSituation *s)
{
    Tright[0] = Trightprev[0] = car->_trkPos.toRight;
    hold[0] = 8.0;
    curidx = 0;

    car->_vect(0).type = CAR_VECT_INVALID;
    car->_vect(0).color[0] = .5;
    car->_vect(0).color[1] = .5;
    car->_vect(0).color[2] = .5;

    InitGears(car, 0);
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
    tdble 	Dy, Dny;
    tdble 	Vy;
    tTrkLocPos	trkPos;
    tdble 	X, Y, x, y, CosA, SinA, kk;
    tTrackSeg	*seg;
    tdble	Da, Db;
    tdble tgtSpeed = -1.0;
    tdble	lgfs;
    tdble	vtgt1, vtgt2;
    static tdble lgfsprev = 0.0;
    tdble adv;
    tdble	curAdv, curAdvMax, Amax, Atmp, AdvMax;

    static int   disp = 0;
    
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
    if (TgtPts) {
	while (lgfs > TgtPts[curidx+1].dstfs) {
	    curidx++;
	}
	tgtSpeed = TgtPts[curidx].spd;
    }

    adv = Advance[0];
    
    if (Curtime > hold[0]) {
	if (TgtPts) {
	    Tright[0] = TgtPts[curidx].tr;
	} else {
	    Tright[0] = seg->width / 2.0;
	}
	
    }

    
    vtgt1 = spdtgt[0];
    vtgt2 = spdtgt2[0];

    CollDet(car, 0, s, Curtime);
    
    kk = 0.8;
    RELAXATION(Tright[0], Trightprev[0], kk);

    adv = 4 * MIN(Tright[0], seg->width - Tright[0]);
    //adv = 4.0 * MIN(trkPos.toRight, trkPos.toLeft);

    /* proportionnal */
    Dy = Tright[0] - trkPos.toRight;
    if (TgtPts) {
	if (Curtime > hold[0]) {
	    tgtSpeed -= fabs(Dy)/2.0;
	}
	if ((lgfs - lgfsprev) > 10.0) {
	    if (disp) printf("%f --> %f (%f) --> %f (%f)\n", lgfs, Tright[0], trkPos.toRight, tgtSpeed*3.6, car->_speed_x*3.6);
	    lgfsprev = lgfs;
	}
    }

    /* derivation */
    Vy = (Dy - preDy[0]) / s->deltaTime;
    preDy[0] = Dy;

    Da = RtTrackSideTgAngleL(&trkPos) - car->_yaw;
    NORM_PI_PI(Da);
    
    x = X + (CosA) * adv;
    y = Y + (SinA) * adv;
    RtTrackGlobal2Local(trkPos.seg, x, y, &trkPos, TR_LPOS_MAIN);
    Dny = Tright[0] - trkPos.toRight;

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
	tgtSpeed = (vtgt1 * Amax  + vtgt2) * (1.0 + tan(fabs(car->_trkPos.seg->angle[TR_XE]+car->_trkPos.seg->angle[TR_XS])));
	tgtSpeed = MIN(tgtSpeed, MaxSpeed[0]);
    }
    SpeedStrategy(car, 0, tgtSpeed * 1.6, s, Db);


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
    
}




