/***************************************************************************

    file                 : axle.cpp
    created              : Sun Mar 19 00:05:09 CET 2000
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

#include "sim.h"

static char *AxleSect[2] = {SECT_FRNTAXLE, SECT_REARAXLE};

void
SimAxleConfig(tCar *car, int index)
{
    void	*hdle = car->params;
    tdble	rollCenter;
    
    tAxle *axle = &(car->axle[index]);

    axle->xpos = GfParmGetNum(hdle, AxleSect[index], PRM_XPOS, (char*)NULL, 0);
    axle->I    = GfParmGetNum(hdle, AxleSect[index], PRM_INERTIA, (char*)NULL, 0.15f);
    rollCenter = GfParmGetNum(hdle, AxleSect[index], PRM_ROLLCENTER, (char*)NULL, 0.15f);
    car->wheel[index*2].rollCenter = car->wheel[index*2+1].rollCenter = rollCenter;

    if (index == 0) {
	SimSuspConfig(hdle, SECT_FRNTARB, &(axle->arbSusp), 0, 0);
    } else {
	SimSuspConfig(hdle, SECT_REARARB, &(axle->arbSusp), 0, 0);
    }

    axle->arbSusp.spring.K = -axle->arbSusp.spring.K;

    car->wheel[index*2].feedBack.I += axle->I / 2.0;
    car->wheel[index*2+1].feedBack.I += axle->I / 2.0;
}

void
SimAxleUpdate(tCar *car, int index)
{
    tAxle *axle = &(car->axle[index]);
    
    tdble str = car->wheel[index*2].susp.x;
    tdble stl = car->wheel[index*2+1].susp.x;
    tdble delta = stl - str;
    tdble sgn = SIGN(delta);

    axle->arbSusp.x = fabs(delta);
    tSpring *spring = &(axle->arbSusp.spring);

    // use a linear model - damping is done at the main suspension anyway
    tdble F = sgn * spring->K * axle->arbSusp.x ;

    // just use linear model
    axle->arbSusp.force = F;
    car->wheel[index*2].axleFz =  F; // right wheel
    car->wheel[index*2+1].axleFz = - F; // left wheel
}
 
