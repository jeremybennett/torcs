/***************************************************************************

    file                 : aero.cpp
    created              : Sun Mar 19 00:04:50 CET 2000
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

void 
SimAeroConfig(tCar *car)
{
    void *hdle = car->params;
    tdble Cx, FrntArea;
    
    Cx       = GfParmGetNum(hdle, SECT_AERODYNAMICS, PRM_CX, (char*)NULL, 0.4);
    FrntArea = GfParmGetNum(hdle, SECT_AERODYNAMICS, PRM_FRNTAREA, (char*)NULL, 2.5);
    car->aero.Clift[0] = GfParmGetNum(hdle, SECT_AERODYNAMICS, PRM_FCL, (char*)NULL, 0.0);
    car->aero.Clift[1] = GfParmGetNum(hdle, SECT_AERODYNAMICS, PRM_RCL, (char*)NULL, 0.0);
    car->aero.SCx2 = 0.645 * Cx * FrntArea;
    car->aero.Cd += car->aero.SCx2;
}


void 
SimAeroUpdate(tCar *car, tSituation *s)
{
    tdble	hm;
    int		i;	    
    tCar	*otherCar;
    tdble	x, y;
    tdble	yaw, otherYaw, airSpeed, tmpas, spdang, tmpsdpang, dyaw;
    tdble	dragK = 1.0;

    x = car->DynGC.pos.x;
    y = car->DynGC.pos.y;
    yaw = car->DynGC.pos.az;
    airSpeed = car->DynGC.vel.x;
    spdang = atan2(car->DynGCg.vel.y, car->DynGCg.vel.x);

    if (airSpeed > 10.0) {
	for (i = 0; i < s->_ncars; i++) {
	    if (i == car->carElt->index) {
		continue;
	    }
	    otherCar = &(SimCarTable[i]);
	    otherYaw = otherCar->DynGC.pos.az;
	    tmpsdpang = spdang - atan2(y - otherCar->DynGC.pos.y, x - otherCar->DynGC.pos.x);
	    NORM_PI_PI(tmpsdpang);
	    dyaw = yaw - otherYaw;
	    NORM_PI_PI(dyaw);
	    if ((otherCar->DynGC.vel.x > 10.0) &&
		(fabs(dyaw) < 0.1396)) {
		if (fabs(tmpsdpang) > 2.9671) {	    /* 10 degrees */
		    /* behind another car */
		    tmpas = 1.0 - exp(- 2.0 * DIST(x, y, otherCar->DynGC.pos.x, otherCar->DynGC.pos.y) /
				      (otherCar->aero.Cd * otherCar->DynGC.vel.x));
		    if (tmpas < dragK) {
			dragK = tmpas;
		    }
		} else if (fabs(tmpsdpang) < 0.1396) {	    /* 8 degrees */
		    /* before another car */
		    tmpas = 1.0 - exp(- 4.0 * DIST(x, y, otherCar->DynGC.pos.x, otherCar->DynGC.pos.y) /
				      (car->aero.Cd * car->DynGC.vel.x));
		    if (tmpas < dragK) {
			dragK = tmpas;
		    }
		}
	    }
	}
    }
    car->airSpeed2 = airSpeed * airSpeed;
    tdble v2 = car->airSpeed2;
    car->aero.drag = -SIGN(car->DynGC.vel.x) * car->aero.SCx2 * v2 * (1.0 + (tdble)car->dammage / 10000.0) * dragK * dragK;

    hm = 1.5 * (car->wheel[0].rideHeight + car->wheel[1].rideHeight + car->wheel[2].rideHeight + car->wheel[3].rideHeight);
    hm = hm*hm;
    hm = hm*hm;
    hm = 2 * exp(-3.0*hm);
    car->aero.lift[0] = - car->aero.Clift[0] * v2 * hm;
    car->aero.lift[1] = - car->aero.Clift[1] * v2 * hm;

    // Since we have the forces ready, we just multiply. 
    // Should insert constants here.
    // Also, no torque is produced since the effect can be
    // quite dramatic. Interesting idea to make all drags produce
    // torque when the car is damaged.
    v2 = car->DynGC.vel.y;
    car->aero.lateral_drag = -SIGN(v2)*v2*v2*0.7;

    v2 = car->DynGC.vel.z;
    car->aero.vertical_drag = -SIGN(v2)*v2*v2*1.5;
    

}

static char *WingSect[2] = {SECT_FRNTWING, SECT_REARWING};

void
SimWingConfig(tCar *car, int index)
{
    void   *hdle = car->params;
    tWing  *wing = &(car->wing[index]);
    tdble area;

    area              = GfParmGetNum(hdle, WingSect[index], PRM_WINGAREA, (char*)NULL, 0);
	// we need also the angle
	wing->angle       = GfParmGetNum(hdle, WingSect[index], PRM_WINGANGLE, (char*)NULL, 0);
    wing->staticPos.x = GfParmGetNum(hdle, WingSect[index], PRM_XPOS, (char*)NULL, 0);
    wing->staticPos.z = GfParmGetNum(hdle, WingSect[index], PRM_ZPOS, (char*)NULL, 0);

	// wrong, because the angle of attack changes on jumps
	//wing->Kx = -1.23 * area * sin(angle);
	wing->Kx = -1.23 * area;
    wing->Kz = 4.0 * wing->Kx;

    if (index == 1) {
		car->aero.Cd -= wing->Kx*sin(wing->angle);
    }
}


void
SimWingUpdate(tCar *car, int index)
{
    tWing  *wing = &(car->wing[index]);
    tdble vt2 = car->DynGC.vel.x;
    tdble i_flow = 1.0;
    // rear wing should not get any flow.

    // compute angle of attack 
    // we don't  add ay anymore since DynGC.vel.x,z are now in the correct frame of reference (see car.cpp)
    tdble aoa = atan2(car->DynGC.vel.z, car->DynGC.vel.x); //+ car->DynGC.pos.ay;
    // The flow to the rear wing can get cut off at large negative
    // angles of attack.  (so it won't produce lift because it will be
    // completely shielded by the car's bottom)
    // The value -0.4 should depend on the positioning of the wing. 
    if (index==1) {
	i_flow = PartialFlowSmooth (-0.4, aoa);
    } 
    vt2=vt2*i_flow;
    vt2=vt2*vt2;
    aoa += wing->angle;

    // the sinus of the angle of attack
    tdble sinaoa = sin(aoa);

    if (car->DynGC.vel.x > 0.0) {
		wing->forces.x = wing->Kx * vt2 * (1.0 + (tdble)car->dammage / 10000.0) * sinaoa;
		wing->forces.z = wing->Kz * vt2 * sinaoa;
    } else {
		wing->forces.x = wing->forces.z = 0;
    }
}

tdble PartialFlowRectangle(tdble theta, tdble psi)
{
    if (psi>0)
        return 1.0;
    if (fabs(psi)>fabs(2.0*theta))
        return 0.0;
    return (1.0-(1.0-sin(psi)/sin(2.0*theta)));
}
 
tdble PartialFlowSmooth(tdble theta, tdble psi)
{
    if (psi>0)
        return 1.0;
    if (fabs(psi)>fabs(2.0*theta))
        return 0.0;
    return (0.5*(1.0+tanh((theta-psi)/(fabs(1.0-(psi/theta))-1.0))));
}
 
tdble PartialFlowSphere(tdble theta, tdble psi)
{
    if (psi>0)
        return 1.0;
    if (fabs(psi)>fabs(2.0*theta))
        return 0.0;
    return (0.5*(1.0+sin((theta-psi)*M_PI/(2.0*theta))));
}
           
