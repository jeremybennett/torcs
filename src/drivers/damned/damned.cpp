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

static void initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s);
static void drive(int index, tCarElt* car, tSituation *s);
static void newrace(int index, tCarElt* car, tSituation *s);
static int  pitCmd(int index, tCarElt *car, tSituation *s);

static tTrack    *DmTrack;


static tdble      Tright[10];
static tdble      Trightprev[10];
static tdble lastBrkCmd[10] = {0};
static tdble lastAccel[10];

static tdble AccSteer[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static tdble AccAngle[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const  tdble PGain[10]   = {	0.08,	0.1,   0.2,	0.05,	0.05,	0.08,	0.2,	0.02,	0.02,	0.1	};
static tdble AGain[10]   = {	0.30,	0.0,   0.25,	0.01,	0.01,	0.05,	0.08,	0.08,	0.08,	0.4	};
static tdble PnGain[10]  = {	0.10,	0.1,   0.08,	0.05,	0.05,	0.08,	0.015,	0.02,	0.015,	0.15	};
const  tdble PnnGain[10] = {	0.0,	0.00,   0.00,	0.00,	0.00,	0.005,	0.0,	0.00,	0.00,	0.00	};
static tdble Advance[10] = {	18.0,	18.0,   0.0,	0.0,	0,	0,	0.0,	0.0,	0.0,	0	};
static tdble Advance2[10]= {	15.0,	15.0,   0.0,	0.0,	0,	15,	0.0,	0.0,	0.0,	0	};
static tdble Advance3[10]= {	-5.0,	-5.0,  -16.0,	0.0,	0.0,	-10.0,	0.0,	0.0,	0.0,	5.0	};
const  tdble Advance4[10]= {	4.00,	4.0,    4.0,	4.0,	4.0,	4.0,	4.0,	4.0,	4.0,	4.0	};
//static tdble Advance5[10] = {	18.0,	15.0,   0.0,	0.0,	0,	0,	0.0,	0.0,	0.0,	0	};
static tdble VGain[10]   = {	0.010,	0.01,   0.01,	0.02,	0.02,	0.005,	0.0002,	0.0005,	0.0005,	0.01	};
static tdble preDy[10]   = {	0.0,	0,      0,	0,	0,	0,	0,	0,	0,	0	};
static tdble spdtgt[10]  = {	5000,	5000,  	10000,	5000,	5000,	10000,	10000,	10000,	10000,	10000	};
static tdble spdtgt2[10] = {	10,	10,	0,	0,	0,	0,	0,	0,	0,	0	};
static tdble spdtgt2ref[10] = {	10,	10,	0,	0,	0,	0,	0,	0,	0,	0	};
static tdble maxBrk[10]  = {	1.0,	1.0,	1.0,	1.0,	1.0,	1.0,	1.0,	1.0,	1.0,	1.0	};
static double hold[10] =    {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	};
static tdble steerk[10] = {	1.0,	1.0,	0.7,	1.00,	1.0,	0.7, 	1.0, 	1.0, 	1.0, 	0.9	};
static tdble MaxFuel[10] = {	30.0,	50.0,	100.0,	70.0,	80.0,	100.0, 	100.0, 	100.0, 	100.0, 	100.0	};
static tdble MaxSpeed[10];

#define PIT_STATE_NO            -1
#define PIT_STATE_NONE           0
#define PIT_STATE_ASKED          1
#define PIT_STATE_ENTERED        2
#define PIT_STATE_PITLANE_BEFORE 3
#define PIT_STATE_PIT_ENTRY      4
#define PIT_STATE_PIT_EXIT       5
#define PIT_STATE_PITLANE_AFTER  6
#define PIT_STATE_EXIT           7

static int PitState[10] = {PIT_STATE_NONE, PIT_STATE_NONE, PIT_STATE_NONE, PIT_STATE_NONE, PIT_STATE_NONE, PIT_STATE_NONE, PIT_STATE_NONE, PIT_STATE_NONE, PIT_STATE_NONE, PIT_STATE_NONE};
static tdble O1[10] = {-35.0, -15.0, -15.0, -15.0, -15.0, -15.0, -15.0, -15.0, -15.0, -15.0};
static tdble O2[10] = {-60.0, -60.0, -60.0, -60.0, -60.0, -60.0, -60.0, -60.0, -60.0, -60.0};
static tdble O3[10] = {15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0};
static tdble O4[10] = {15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0};
static tdble OP[10] = {12.0, 12.0, 12.0, 15.0, 12.0, 12.0, 12.0, 18.0, 18.0, 12.0};
static tdble OW[10] = {2.0, 3.0, 3.0, 2.0, 2.0, 2.0, 0.0, 4.0, 4.0, 2.0};
static tdble VM;
static tdble VM1[10] = {7.0, 8.0, 8.0, 10.0, 8.0, 8.0, 8.0, 20.0, 20.0, 8.0};
static tdble VM2[10] = {2.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 7.0, 7.0, 3.0};
static tdble VM3[10] = {25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 10.0, 25.0, 25.0, 25.0};
static tdble VI[10];

static tdble OffsetApproach;
static tdble OffsetFinal;
static tdble OffsetExit;
static tdble LgfsFinal[10];
static tdble ConsFactor;


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
    itf->rbPitCmd   = pitCmd;
    itf->rbShutdown = NULL;
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

static tdble
dmGetDistToStart(tTrkLocPos *trkPos)
{
    tTrackSeg	*seg;
    tdble	lg;
    
    seg = trkPos->seg;
    lg = seg->lgfromstart;
    
    switch (seg->type) {
    case TR_STR:
	lg += trkPos->toStart;
	break;
    default:
	lg += trkPos->toStart * seg->radius;
	break;
    }
    return lg;
}

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



static void initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s)
{
    char	buf[256];
    tdble	fuel;
    tTrackSeg * seg;

    DmTrack = track;

    sprintf(buf, "drivers/damned/%d/car-%s.xml", index, track->category);

    *carParmHandle = GfParmReadFile(buf, GFPARM_RMODE_STD);
    if (*carParmHandle == NULL) {
	sprintf(buf, "drivers/damned/%d/car.xml", index);
	*carParmHandle = GfParmReadFile(buf, GFPARM_RMODE_STD);
    }
    if (*carParmHandle == NULL) {
	*carParmHandle = GfParmReadFile("drivers/damned/car1.xml", GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    } else {
	GfOut("%s loaded\n", buf);
    }
    ConsFactor = 0.00064 * DmTrack->length * GfParmGetNum(carHandle, SECT_ENGINE, PRM_FUELCONS, (char*)NULL, 0.0622);
    fuel = (s->_totLaps + 1) * ConsFactor + 6.0;
    fuel = MIN(fuel, MaxFuel[index-1]);
    GfParmSetNum(*carParmHandle, SECT_CAR, PRM_FUEL, (char*)NULL, fuel);

    if ((track->pits.type != TR_PIT_ON_TRACK_SIDE) || (s->_raceType != RM_TYPE_RACE)) {
	PitState[index - 1] = PIT_STATE_NO;
    } else {
	if (track->pits.side == TR_LFT) {
	    OffsetApproach = track->width / 2.0;
	    OffsetExit = OffsetApproach + 3.0;
	    seg = track->pits.pitStart->lside;
 	    OffsetApproach += RtTrackGetWidth(seg, 0);
	    if (seg->lside) {
		OffsetExit += RtTrackGetWidth(seg, 0);
		seg = seg->lside;
		OffsetApproach += RtTrackGetWidth(seg, 0);
	    }
	    OffsetFinal = OffsetApproach + track->pits.width * 0.5;
	    OffsetApproach -= track->pits.width * 1.5;
	} else {
	    OffsetApproach = -track->width / 2.0;
	    OffsetExit = OffsetApproach - 3.0;
	    seg = track->pits.pitStart->rside;
 	    OffsetApproach -= RtTrackGetWidth(seg, 0);
	    if (seg->rside) {
		OffsetExit -= RtTrackGetWidth(seg, 0);
		seg = seg->rside;
		OffsetApproach -= RtTrackGetWidth(seg, 0);
	    }
	    OffsetFinal = OffsetApproach - track->pits.width * 0.5;
	    OffsetApproach += track->pits.width * 1.5;
	}
	VM = track->pits.speedLimit;
    }
}

void newrace(int index, tCarElt* car, tSituation *s)
{
    tdble width = DmTrack->width;
    
    if (strcmp(DmTrack->category, "dirt") == 0) {
	width *= 0.8;
    }
    
    Tright[index-1] = Trightprev[index-1] = car->_trkPos.toRight;
    hold[index-1] = 10.0;
    InitGears(car, index);

    spdtgt2[0] = width - 4.0;
    Advance[0] = Advance2[0] = width * 2.0;

    spdtgt2[1] = width - 4.0;
    Advance[1] = Advance2[1] = width * 2.0;

/*     spdtgt2ref[1] = spdtgt2[1] = width / 2.0 - 1.0; */
/*     Advance[1] = width * 1.88 + 5.0; */
/*     Advance2[1] = width * 2.8 + 5.0; */

    spdtgt2ref[2] = spdtgt2[2] = width * .8 + 7.5;
    Advance[2] = Advance2[2] = width * 2.0 + 3.0;

    spdtgt2ref[3] = spdtgt2[3] = width / 2.0 - 1.0;
    Advance[3] = Advance2[3] = width * 2.0 + 6.0;

    spdtgt2ref[4] = spdtgt2[4] = width + 3.0;
    Advance[4] = Advance2[4] = width * 2.0 + 6.0;

    spdtgt2ref[5] = spdtgt2[5] = width + 3.0;
    Advance[5] = Advance2[5] = width * 2.0 + 6.0;

    spdtgt2[6] = width + 3.0;
    Advance[6] = Advance2[6] = width * 2.0 + 15.0;

    spdtgt2[7] = width + 3.0;
    Advance[7] = Advance2[7] = width * 2.0 + 8.0;

    spdtgt2[8] = width + 3.0;
    Advance[8] = Advance2[8] = width * 2.0 + 8.0;

    spdtgt2[9] = (width + 2.5) * 1.1;
    Advance[9] = Advance2[9] = width * 2.0 - 1.0;

    if (car->_pit) {
	LgfsFinal[index - 1] = dmGetDistToStart(&car->_pit->pos);
    } else {
	PitState[index - 1] = PIT_STATE_NO;
    }
}

static tdble
Spline(tdble p0, tdble p1, tdble pos, tdble start, tdble end)
{
    tdble t2, t3;
    tdble h0, h1;
    tdble t;

    if (start < 0) {
	start += DmTrack->length;
    }
    if (start > DmTrack->length) {
	start -= DmTrack->length;
    }
    if (end < 0) {
	end += DmTrack->length;
    }
    if (end > DmTrack->length) {
	end -= DmTrack->length;
    }
    if (start > end) {
	end += DmTrack->length;
	if (pos < start) {
	    pos += DmTrack->length;
	}
    }
    t = (pos - start) / (end - start);
    
    t2 = t * t;
    t3 = t * t2;
    h1 = 3 * t2 - 2 * t3;
    h0 = 1 - h1;
    
    return h0 * p0 + h1 * p1;
}

static int
isBetween(tdble lgfs, tdble start, tdble end)
{
    if (start < 0) {
	start += DmTrack->length;
    }
    if (start > DmTrack->length) {
	start -= DmTrack->length;
    }
    if (end < 0) {
	end += DmTrack->length;
    }
    if (end > DmTrack->length) {
	end -= DmTrack->length;
    }
    if (((lgfs > start) && (lgfs < end)) ||
	((start > end) &&
	 ((lgfs > start) || (lgfs < end)))) {
	return 1;
    }
    return 0;
}


static tdble
getOffset(int index, tCarElt* car, tTrkLocPos *trkPos, tdble *maxSpeed)
{
    int 	idx = index - 1;
    tdble	offset = 0;
    tdble	lgfs;
    static tTrackPitInfo *pits = &DmTrack->pits;;
    static tdble	 Entry = pits->pitEntry->lgfromstart;
    static tdble	 Start = pits->pitStart->lgfromstart;
    static tdble	 End   = pits->pitEnd->lgfromstart;
    static tdble	 Exit  = pits->pitExit->lgfromstart;
    

    switch (PitState[idx]) {
    case PIT_STATE_NONE:
	break;
	
    case PIT_STATE_ASKED:
    case PIT_STATE_ENTERED:
	lgfs = dmGetDistToStart(&car->_trkPos);

	if (isBetween(lgfs, Entry + O1[idx], Start + O2[idx])) {
	    offset = Spline(0, OffsetApproach, lgfs, Entry + O1[idx], Start + O2[idx]);
	    if (PitState[idx] == PIT_STATE_ASKED) {
		VI[idx] = car->_speed_x;
	    }
	    *maxSpeed = Spline(VI[idx], VM, lgfs, Entry + O1[idx], Start + O2[idx]);
	    hold[idx] = 0;
	    PitState[idx] = PIT_STATE_ENTERED;
	    break;
	}
	if (PitState[idx] == PIT_STATE_ASKED) {
	    break;
	}
	
	/* FALL THROUGH */
    case PIT_STATE_PITLANE_BEFORE:
	lgfs = dmGetDistToStart(&car->_trkPos);

	if (isBetween(lgfs, Start + O2[idx], LgfsFinal[idx] - OP[idx])) {
	    PitState[idx] = PIT_STATE_PITLANE_BEFORE;
	    offset = OffsetApproach;
	    *maxSpeed = Spline(VM, VM1[idx], lgfs, Start + O2[idx], LgfsFinal[idx] - OP[idx]);
	    hold[idx] = 0;
	    break;
	}

	/* FALL THROUGH */
    case PIT_STATE_PIT_ENTRY:
	lgfs = dmGetDistToStart(&car->_trkPos);

	
	if (isBetween(lgfs, LgfsFinal[idx] - OP[idx], LgfsFinal[idx])) {
	    PitState[idx] = PIT_STATE_PIT_ENTRY;
	    //offset = Spline(OffsetApproach, OffsetFinal, lgfs, LgfsFinal[idx] - OP[idx], LgfsFinal[idx]);
	    offset = OffsetFinal + SIGN(OffsetFinal) * OW[idx];
	    *maxSpeed = Spline(VM2[idx], 0, lgfs, LgfsFinal[idx] - OP[idx], LgfsFinal[idx]);
	    hold[idx] = 0;
	    car->ctrl->raceCmd = RM_CMD_PIT_ASKED;
	    break;
	}

	/* FALL THROUGH */
    case PIT_STATE_PIT_EXIT:
	lgfs = dmGetDistToStart(&car->_trkPos);

	if (isBetween(lgfs, LgfsFinal[idx] - OP[idx], LgfsFinal[idx] + OP[idx])) {
	    PitState[idx] = PIT_STATE_PIT_EXIT;
	    //offset = Spline(OffsetFinal, OffsetApproach, lgfs, LgfsFinal[idx], LgfsFinal[idx] + OP[idx]);
	    offset = OffsetExit;
	    *maxSpeed = Spline(VM3[idx], VM, lgfs, LgfsFinal[idx], LgfsFinal[idx] + OP[idx]);
	    hold[idx] = 0;
	    break;
	}

	/* FALL THROUGH */
    case PIT_STATE_PITLANE_AFTER:
	lgfs = dmGetDistToStart(&car->_trkPos);

	if (isBetween(lgfs, LgfsFinal[idx] + OP[idx], End + O3[idx])) {
	    PitState[idx] = PIT_STATE_PITLANE_BEFORE;
	    offset = OffsetExit;
	    *maxSpeed = VM;
	    hold[idx] = 0;
	    break;
	}

	/* FALL THROUGH */
    case PIT_STATE_EXIT:
	lgfs = dmGetDistToStart(&car->_trkPos);

	if (isBetween(lgfs, End + O3[idx], Exit - O4[idx])) {
	    PitState[idx] = PIT_STATE_EXIT;
	    offset = Spline(OffsetExit, 0, lgfs, End + O3[idx], Exit - O4[idx]);
	    hold[idx] = 0;
	    break;
	}
	PitState[idx] = PIT_STATE_NONE;
	break;
    }

    return offset;
}

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
	    car->ctrl->accelCmd = car->ctrl->accelCmd * exp(-fabs(aspect) * 0.3) ; //+ 0.15;
	}
	
	
	if ((slip > 1.0) && (car->_gear > 1)) {
	    car->ctrl->accelCmd /= 2.0;
	    //lastAccel = 0.0;
	} else {
	    //RELAXATION(car->ctrl->accelCmd, lastAccel[idx], 30.0);
	}
	
    } else {
	if (car->_speed_x > 0) {
	    slip = (car->_speed_x - car->_wheelRadius(0) * MIN(car->_wheelSpinVel(0), car->_wheelSpinVel(1))) / car->_speed_x;
	} else {
	    slip = 0;
	}
	car->ctrl->brakeCmd = MIN(MIN((car->_speed_x - Vtarget) / 20.0, 1.0)  * maxBrk, maxBrk);
	if (slip > 0.3) {
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


static void drive(int index, tCarElt* car, tSituation *s)
{
    static double Curtime = 0;
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
    tdble	offset = 0;
    tdble	dist;

    memset(car->ctrl, 0, sizeof(tCarCtrl));
    
    MaxSpeed[idx] = 10000;
    trkPos = car->_trkPos;
    seg = trkPos.seg;
    lgfs = dmGetDistToStart(&car->_trkPos);
    X = car->_pos_X;
    Y = car->_pos_Y;
    CosA = cos(car->_yaw);
    SinA = sin(car->_yaw);

    Curtime = s->currentTime;
    
    //Tright[idx] = trkPos.toRight;
    if (Curtime > hold[idx]) {
	Tright[idx] = DmTrack->width / 2.0;
/*     } else { */
/* 	if (index == 2) printf ("time=%f hold=%f TR=%f\n", Curtime, hold[idx], Tright[idx]); */
    }
    
    if ((PitState[idx] == PIT_STATE_NONE) && 
	((car->_dammage > 5000) || 
	 ((car->_fuel < (ConsFactor + 5.0)) && ((s->_totLaps - car->_laps) > 1)))) {
	PitState[idx] = PIT_STATE_ASKED;
    }
    if (PitState[idx] != PIT_STATE_NO) {
	offset = getOffset(index, car, &trkPos, &MaxSpeed[idx]);
    }
    
	Advance[0] = (0.3 * car->_speed_x + 10.0) * seg->surface->kFriction;
	spdtgt2[0]  = 20.0 * seg->surface->kFriction - 12.0;
    
	Advance[1] = (0.3 * car->_speed_x + 10.0) * seg->surface->kFriction;
	spdtgt2[1]  = 20.0 * seg->surface->kFriction - 12.0;

	//Advance[1] = Advance5[1] / seg->surface->kFriction;
/* 	spdtgt2[1] = spdtgt2ref[1] * seg->surface->kFriction; */
/* 	Advance3[1] = (seg->surface->kFriction - 1.5) * 25.0; */
	//steerk[1] = 1.0 - (seg->surface->kFriction - 1.4);

	spdtgt2[3] = spdtgt2ref[3] * (seg->surface->kFriction - .3);
	spdtgt2[4] = spdtgt2ref[4] * (seg->surface->kFriction - .3);
	spdtgt2[5] = spdtgt2ref[5] * (seg->surface->kFriction - .3);

    vtgt1 = spdtgt[idx];
    vtgt2 = spdtgt2[idx];
    maxdlg = 200.0;
    /*
     * Collision detection
     */
    for (i = 0; i < s->_ncars; i++) {
	otherCar = s->cars[i];
	if ((otherCar == car) || (otherCar->_state & RM_CAR_STATE_NO_SIMU)) {
	    continue;
	}
	lgfs2 = dmGetDistToStart(&otherCar->_trkPos);
	dlg = lgfs2 - lgfs;
	if (dlg > (DmTrack->length / 2.0)) dlg -= DmTrack->length;
	if (dlg < -(DmTrack->length / 2.0)) dlg += DmTrack->length;

	dspd = car->_speed_x - otherCar->_speed_x;
	if ((dlg > -(car->_dimension_x + 1.0)) &&
	    ((dlg < (dspd*3.0 + 10.0)) ||
	    (dlg < (car->_dimension_x * 4.0)))) {
	    /* risk of collision */
	    tdble MARGIN = 2.5;
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
		    MaxSpeed[idx] = MIN(MaxSpeed[idx], otherCar->_speed_x * .9);
		}
	    }
	} else {
	    dlg = -dlg;
	    if ((dlg > -(car->_dimension_x * 2.0)) &&
		((dlg < (dspd*12.0 + 20.0)) ||
		 (dlg < (car->_dimension_x * 4.0)))) {
		if (otherCar->_laps > car->_laps) {
		    if (car->_trkPos.toRight < otherCar->_trkPos.toRight) {
			Tright[idx] = 1.0;
		    } else {
			Tright[idx] = seg->width - 1.0;
		    }
		    hold[idx] = Curtime + 5.0;
		}
	    }
	}
    }
    if (offset) Tright[idx] = DmTrack->width / 2.0;

    RELAXATION(Tright[idx], Trightprev[idx], 0.5);

    /* proportionnal */
    Dy = Tright[idx] - trkPos.toRight + offset;

    /* derivation */
    Vy = (Dy - preDy[idx]) / s->deltaTime;
    preDy[idx] = Dy;

    /* angular target */
    Da = RtTrackSideTgAngleL(&trkPos) - car->_yaw;
    NORM_PI_PI(Da);
    
    x = X + (CosA) * Advance[idx];
    y = Y + (SinA) * Advance[idx];
    RtTrackGlobal2Local(trkPos.seg, x, y, &trkPos, TR_LPOS_MAIN);
    Dny = Tright[idx] - trkPos.toRight + offset;

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
    dist = (0.04 * car->_speed_x * car->_speed_x - (Advance3[idx] / (seg->surface->kFriction - 0.4)));
    x = X + (CosA) * dist;
    y = Y + (SinA) * dist;
    RtTrackGlobal2Local(trkPos.seg, x, y, &trkPos, TR_LPOS_MAIN);

    if (dist < (DmTrack->width / 2.0)) {
	dist = DmTrack->width / 2.0;
    }
    Dny = Advance4[idx] * fabs(trkPos.toRight - seg->width /2.0) / dist;
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

static int
pitCmd(int index, tCarElt *car, tSituation *s)
{
    int 	idx = index - 1;
    int		remainLaps = s->_totLaps - car->_laps;
    tdble	fuel;

    PitState[idx] = PIT_STATE_PIT_EXIT;
    fuel = ConsFactor * (remainLaps + 1);
    fuel = MIN(fuel, MaxFuel[idx]);
    car->pitcmd->fuel = fuel - car->_fuel;
    if (remainLaps > 20) {
	car->pitcmd->repair = (int)(car->_dammage);
    } else {
	car->pitcmd->repair = (int)(car->_dammage / 2.0);
    }

    return ROB_PIT_IM;
}
