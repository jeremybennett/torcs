/***************************************************************************

    file                 : lliaw.cpp
    created              : Sat Oct 30 19:49:42 CEST 1999
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

static void initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s);
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
 *	lliaw
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
lliaw(tModInfo *modInfo)
{
    modInfo->name    = "Lliaw";	/* name of the module (short) */
    modInfo->desc    = "For William";	/* description of the module (can be long) */
    modInfo->fctInit = InitFuncPt;	/* init function */
    modInfo->gfId    = ROB_IDENT;	/* supported framework version */
    modInfo->index   = 1;
    return 0;
}
static tdble	Tright[10];
static tdble	MaxSpeed[10];
static tdble	hold[10] = {0};
static tdble	shiftThld[10][MAX_GEARS+1];

const  tdble PGain[1]    = {0.016f};
const  tdble AGain[10]    = {0.004f};
const  tdble PnGain[10]   = {0.025f};
const  tdble Advance[10]  = {50.0};
const  tdble Advance2[10] = {30.0};
const  tdble Advance3[10] = {250.0};
const  tdble AdvStep[10]  = {25.0};
const  tdble VGain[10]    = {0.0005f};
static tdble preDy[10]    = {0};
static tdble spdtgt[10]   = {200.0};
static tdble spdtgt2[10]  = {0.1f};
static tdble Trightprev[10];

#include "common.cpp"

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
static void initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s)
{
    void	*hdle;
    char	*str;
    int		nbPts;
    int		idx;
    char	buf[256];
    tdble	spd = spdtgt2[0];
    tdble	tr = track->seg->next->width/2.0;
    tdble	dstfs = 0, fuel;
    
    DmTrack = track;
    str = strrchr(track->filename, '/') + 1;
    sprintf(buf, "drivers/lliaw/tracksdata/car_%s", str);
    *carParmHandle = GfParmReadFile(buf, GFPARM_RMODE_STD);
    if (*carParmHandle == NULL) {
	sprintf(buf, "drivers/lliaw/car.xml");
	*carParmHandle = GfParmReadFile(buf, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    } else {
	GfOut("%s Loaded\n", buf);
    }
    fuel = 0.0007 * DmTrack->length * (s->_totLaps + 1);
    GfParmSetNum(*carParmHandle, SECT_CAR, PRM_FUEL, (char*)NULL, fuel);

    sprintf(buf, "drivers/lliaw/tracksdata/%s", str);
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
    
    
    memset(&(car->ctrl), 0, sizeof(tCarCtrl));

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
    
    kk = 0.8f;
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

    car->_steerCmd = PGain[0] * Dy + VGain[0] * Vy + PnGain[0] * Dny + AGain[0] * Da * Da;

    if (car->_speed_x < 0) {
	car->_steerCmd *= 1.5;
    } else {
	car->_steerCmd *= 1.1f;
    }

    /*
     * speed control
     */
    CosA = cos(car->_yaw + car->_steerCmd*2.0);
    SinA = sin(car->_yaw + car->_steerCmd*2.0);
    curAdv = Advance2[0];
    AdvMax = car->_speed_x * 5.0;
    Amax = 0;
    while (curAdv < AdvMax) {
	x = X + CosA * curAdv;
	y = Y + SinA * curAdv;
	RtTrackGlobal2Local(seg, x, y, &trkPos, TR_LPOS_MAIN);
	Atmp = fabs(trkPos.toRight - seg->width / 2.0) / curAdv;
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
    SpeedStrategy(car, 0, tgtSpeed, s, Db);


#define AMARG 0.6
    if ((((Da > (PI/2.0-AMARG)) && (car->_trkPos.toRight < seg->width/3.0)) ||
	 ((Da < (AMARG-PI/2.0)) && (car->_trkPos.toRight > (seg->width - seg->width/3.0)))) && 
	(car->_gear < 2) && (car->_speed_x < 1.0)) {
	car->_steerCmd = -car->_steerCmd * 3.0;
	car->_gearCmd = -1;
    } else if ((fabs(Da) > (PI - (PI/4.0))) &&
	       ((car->_trkPos.toRight < 0) ||
		(car->_trkPos.toRight > seg->width))) {
	car->_steerCmd = -car->_steerCmd * 3.0;
    }
    if ((car->_speed_x < -0.5) && (car->_gear > 0)) {
	car->_brakeCmd = 1.0;
    }
    
}

