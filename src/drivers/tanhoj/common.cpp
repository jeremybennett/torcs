/***************************************************************************

    file                 : common.cpp
    created              : Sun Oct 24 14:16:27 CEST 1999
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

void
InitGears(tCarElt* car, int idx)
{
    int i, j;
    tdble rpm;

    for (i = 0; i < MAX_GEARS; i++) {
	j = i + 1;
	if (j < MAX_GEARS) {
	    if ((car->_gearRatio[j] != 0) && (car->_gearRatio[i] != 0)) {
/* 		rpm = car->_enginerpmMaxTq * car->_gearRatio[i] / car->_gearRatio[j]; */
/* 		if (rpm > car->_enginerpmRedLine) { */
		    rpm = car->_enginerpmRedLine;
/* 		} */
		shiftThld[idx][i] = rpm * .95  * car->_wheelRadius(2) / car->_gearRatio[i];
	    } else {
		shiftThld[idx][i] = 10000.0;
	    }
	} else {
	    shiftThld[idx][i] = 10000.0;
	}
    }
}

static tdble lastAccel[10] = {1.0};
static tdble lastBrkCmd[10] = {0};
static tdble lastDv[10] = {0};

void
SpeedStrategy(tCarElt* car, int idx, tdble Vtarget, tSituation *s, tdble aspect)
{
    const tdble Dx  = 0.02f;
    const tdble Dxx = 0.01f;
    const tdble Dxb  = 0.05f;
    const tdble Dxxb = 0.01f;
    tdble	Dv;
    tdble	Dvv;
    tdble 	slip;
    int 	gear;

    gear = car->_gear;
    Dv = Vtarget - car->_speed_x;
    Dvv = Dv - lastDv[idx];
    lastDv[idx] = Dv;

    //RELAXATION(Vtarget, lastTarget[idx], 2.0);
    
    if (Dv > 0.0) {
	/* speed management */
	car->_accelCmd = MIN(Dv * Dx + Dvv * Dxx, 1.0);
	car->_accelCmd = 1.0;
	
	/* anti-slip */
	/* assume SPOOL differential and rwd */
	if (car->_speed_x > 0) {
	    slip = (car->_wheelRadius(3) * car->_wheelSpinVel(3) - car->_speed_x) / car->_speed_x;
	} else {
	    slip = 0;
	}
	if (gear == 1) {
	    car->_accelCmd = car->_accelCmd * exp(-fabs(car->_steerCmd) * 1.0) * exp(-fabs(aspect) * 4.0) + .1;
	} else if ((gear > 1) && (car->_speed_x < 40.0)) {
	    car->_accelCmd = car->_accelCmd * exp(-fabs(aspect) * 4.0) + 0.15;
	}
	
	
	if ((slip > 0.2) && (gear > 1)) {
	    car->_accelCmd *= 0.5;
	} else {
	    RELAXATION(car->_accelCmd, lastAccel[idx], 50.0);
	}
	car->_accelCmd = MIN(car->_accelCmd, fabs(Dv/6.0));
	//lastBrkCmd[idx] = 0.8;
    } else {
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
	car->_brakeCmd = MIN(-Dv * Dxb + Dvv * Dxxb, 1.0);
	if (slip > 0.2) {
	    car->_brakeCmd = MAX(car->_brakeCmd - slip * 0.5, 0);
	} else {
	    RELAXATION(car->_brakeCmd, lastBrkCmd[idx], 50.0);
	}
	car->_brakeCmd = MIN(car->_brakeCmd, fabs(Dv/5.0));
	//lastAccel[idx] = 1.0;
    }

    /* shift */
    gear += car->_gearOffset;
    car->_gearCmd = car->_gear;
    if (car->_speed_x > shiftThld[idx][gear]) {
	car->_gearCmd++;
    } else if ((car->_gearCmd > 1) && (car->_speed_x < (shiftThld[idx][gear-1] - 10.0))) {
	car->_gearCmd--;
    }
    if (car->_gearCmd <= 0) {
	car->_gearCmd++;
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
CollDet(tCarElt* car, int idx, tSituation *s, tdble Curtime, tdble dny)
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

    for (i = 0; i < s->_ncars; i++) {
	otherCar = s->cars[i];
	if ((otherCar == car) || (otherCar->_state & RM_CAR_STATE_NO_SIMU)) {
	    continue;
	}
	lgfs2 = GetDistToStart(otherCar);
	dlg = lgfs2 - lgfs;
	if (dlg > (DmTrack->length / 2.0)) dlg -= DmTrack->length;
	if (dlg < -(DmTrack->length / 2.0)) dlg += DmTrack->length;

	dspd = car->_speed_x - otherCar->_speed_x;
	if (((dlg < maxdlg) && (dlg > -(car->_dimension_x + 1.0))) &&
	    ((dlg < (dspd*4.5)) ||
	    (dlg < (car->_dimension_x * 4.0)))) {

	    maxdlg = dlg;
	    /* risk of collision */
	    tdble MARGIN = /* 0.4 * DmTrack->width */ 7.0;
	    
	    if (fabs(car->_trkPos.toRight - otherCar->_trkPos.toRight) < (MARGIN  - 1.0)) {
		if (car->_trkPos.toRight < otherCar->_trkPos.toRight) {
		    if (otherCar->_trkPos.toRight > MARGIN) {
			Tright[idx] = otherCar->_trkPos.toRight - (MARGIN - 1.0);
			if (dny > 0) {
			    if (otherCar->_trkPos.toRight > (2.0*MARGIN)) {
				MaxSpeed[idx] = otherCar->_speed_x * .99;
			    } else {
				Tright[idx] -= MARGIN/2.0;
			    }
			}
		    } else {
			//Tright[idx] = otherCar->_trkPos.toRight + MARGIN;
			if (dlg > (car->_dimension_x * 2.0)) {
			    MaxSpeed[idx] = otherCar->_speed_x * .99;
			    Tright[idx] = otherCar->_trkPos.toRight + (MARGIN * 2.0);
			}
		    }
		} else {
		    if (otherCar->_trkPos.toRight < seg->width - MARGIN) {
			Tright[idx] = otherCar->_trkPos.toRight + (MARGIN - 1.0);
			if (dny < 0) {
			    if (otherCar->_trkPos.toRight < (seg->width - 2.0*MARGIN)) {
				MaxSpeed[idx] = otherCar->_speed_x * .99;
			    } else {
				Tright[idx] += MARGIN/2.0;
			    }
			}
		    } else {
			//Tright[idx] = otherCar->_trkPos.toRight - MARGIN;
			if (dlg > (car->_dimension_x * 2.0)) {
			    MaxSpeed[idx] = otherCar->_speed_x * .99;
			    Tright[idx] = otherCar->_trkPos.toRight - (MARGIN * 2.0);
			}
		    }
		}
		hold[idx] = Curtime + 1.0;
		if ((dlg > (car->_dimension_x /2.0)) && (dlg < (car->_dimension_x * 3.0)) && (fabs(car->_trkPos.toRight - otherCar->_trkPos.toRight) < 2.0)) {
		    MaxSpeed[idx] = otherCar->_speed_x * .95;
		}
	    }
	}
    }

    if (Tright[idx] < 0.0) {
	Tright[idx] = 0.0;
    } else if (Tright[idx] > seg->width) {
	Tright[idx] = seg->width;
    }
    
    
}
