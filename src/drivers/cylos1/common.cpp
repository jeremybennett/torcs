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

#ifdef DMALLOC
#include "dmalloc.h"
#endif

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

static tdble lastAccel[10] = {1.0};
static tdble lastBrkCmd[10] = {0};

void
SpeedStrategy2(tCarElt* car, int idx, tdble Vtarget, tSituation *s, tdble aspect)
{
    const tdble Dx = 50.0;
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
	} else if ((gear > 1) && (car->_speed_x < 40.0)) {
	    car->ctrl->accelCmd = car->ctrl->accelCmd * exp(-fabs(aspect) * 4.0) + 0.15;
	}
	
	
	if ((slip > 0.2) && (gear > 1)) {
	    car->ctrl->accelCmd *= 0.5;
	} else {
	    RELAXATION(car->ctrl->accelCmd, lastAccel[idx], 1.0);
	}
	lastBrkCmd[idx] = 0.8;
    } else {
	if (car->_speed_x > 0) {
	    slip = (car->_speed_x - car->_wheelRadius(0) * MIN(car->_wheelSpinVel(0), car->_wheelSpinVel(1))) / car->_speed_x;
	} else {
	    slip = 0;
	}
	car->ctrl->brakeCmd = MIN(-(Vtarget+1.0 - car->_speed_x) / Dx, 1.0);
	if (slip > 0.3) {
	    car->ctrl->brakeCmd = 0.0;
	} else {
	    RELAXATION(car->ctrl->brakeCmd, lastBrkCmd[idx], 1.0);
	}
	lastAccel[idx] = 1.0;
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


static tdble lastDv[10] = {0};

void
SpeedStrategy(tCarElt* car, int idx, tdble Vtarget, tSituation *s, tdble aspect)
{
    const tdble Dx  = 0.02;
    const tdble Dxx = 0.01;
    const tdble Dxb  = 0.05;
    const tdble Dxxb = 0.01;
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
	car->ctrl->accelCmd = MIN(Dv * Dx + Dvv * Dxx, 1.0);
	car->ctrl->accelCmd = 1.0;
	
	/* anti-slip */
	/* assume SPOOL differential and rwd */
	if (car->_speed_x > 0) {
	    slip = (car->_wheelRadius(3) * car->_wheelSpinVel(3) - car->_speed_x) / car->_speed_x;
	} else {
	    slip = 0;
	}
	if (gear == 1) {
	    car->ctrl->accelCmd = car->ctrl->accelCmd * exp(-fabs(car->ctrl->steer) * 4.0) * exp(-fabs(aspect) * 4.0) + 0.2;
	} else if ((gear > 1) && (car->_speed_x < 40.0)) {
	    car->ctrl->accelCmd = car->ctrl->accelCmd * exp(-fabs(aspect) * 4.0) + 0.15;
	}
	
	
	if ((slip > 0.2) && (gear > 1)) {
	    car->ctrl->accelCmd *= 0.4;
	} else {
	    RELAXATION(car->ctrl->accelCmd, lastAccel[idx], 50.0);
	}
	//lastBrkCmd[idx] = 0.8;
    } else {
	if (car->_speed_x > 0) {
	    slip = (car->_speed_x - car->_wheelRadius(0) * MIN(car->_wheelSpinVel(0), car->_wheelSpinVel(1))) / car->_speed_x;
	} else {
	    slip = 0;
	}
	car->ctrl->brakeCmd = MIN(-Dv * Dxb + Dvv * Dxxb, 1.0);
	if (slip > 0.2) {
	    car->ctrl->brakeCmd = MAX(car->ctrl->brakeCmd - slip * 0.5, 0);
	} else {
	    RELAXATION(car->ctrl->brakeCmd, lastBrkCmd[idx], 50.0);
	}
	//lastAccel[idx] = 1.0;
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
	    (((dspd > 0)  && (dlg < (dspd*4.0))) ||
	    (dlg < (car->_dimension_x * 2.0)))) {

	    maxdlg = dlg;
	    /* risk of collision */
#define MARGIN 6.0
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
