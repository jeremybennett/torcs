/***************************************************************************

    file                 : car.cpp
    created              : Sun Mar 19 00:05:43 CET 2000
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



#include <string.h>
#include <stdio.h>

#include "sim.h"

const tdble aMax = 0.35; /*  */

void
SimCarConfig(tCar *car)
{
    void	*hdle = car->params;
    tdble	k;
    tdble	w;
    tdble	gcfrl, gcrrl, gcfr;
    tdble	wf0, wr0;
    tdble	overallwidth;
    int		i;
    tCarElt	*carElt = car->carElt;
    
    car->dimension.x = GfParmGetNum(hdle, SECT_CAR, PRM_LEN, (char*)NULL, 4.7);
    car->dimension.y = GfParmGetNum(hdle, SECT_CAR, PRM_WIDTH, (char*)NULL, 1.9);
    overallwidth     = GfParmGetNum(hdle, SECT_CAR, PRM_OVERALLWIDTH, (char*)NULL, car->dimension.y);
    car->dimension.z = GfParmGetNum(hdle, SECT_CAR, PRM_HEIGHT, (char*)NULL, 1.2);
    car->mass        = GfParmGetNum(hdle, SECT_CAR, PRM_MASS, (char*)NULL, 1500);
    car->Minv        = 1.0 / car->mass;
    gcfr             = GfParmGetNum(hdle, SECT_CAR, PRM_FRWEIGHTREP, (char*)NULL, .5);
    gcfrl            = GfParmGetNum(hdle, SECT_CAR, PRM_FRLWEIGHTREP, (char*)NULL, .5);
    gcrrl            = GfParmGetNum(hdle, SECT_CAR, PRM_RRLWEIGHTREP, (char*)NULL, .5);
    car->statGC.y    = - (gcfr * gcfrl + (1 - gcfr) * gcrrl) * car->dimension.y + car->dimension.y / 2.0;
    car->statGC.z    = GfParmGetNum(hdle, SECT_CAR, PRM_GCHEIGHT, (char*)NULL, .5);
    
    car->tank        = GfParmGetNum(hdle, SECT_CAR, PRM_TANK, (char*)NULL, 80);
    car->fuel        = GfParmGetNum(hdle, SECT_CAR, PRM_FUEL, (char*)NULL, 80);
    k                = GfParmGetNum(hdle, SECT_CAR, PRM_CENTR, (char*)NULL, 1.0);
    carElt->_drvPos_x = GfParmGetNum(hdle, SECT_DRIVER, PRM_XPOS, (char*)NULL, 0.0);
    carElt->_drvPos_y = GfParmGetNum(hdle, SECT_DRIVER, PRM_YPOS, (char*)NULL, 0.0);
    carElt->_drvPos_z = GfParmGetNum(hdle, SECT_DRIVER, PRM_ZPOS, (char*)NULL, 0.0);
    carElt->_bonnetPos_x = GfParmGetNum(hdle, SECT_BONNET, PRM_XPOS, (char*)NULL, carElt->_drvPos_x);
    carElt->_bonnetPos_y = GfParmGetNum(hdle, SECT_BONNET, PRM_YPOS, (char*)NULL, carElt->_drvPos_y);
    carElt->_bonnetPos_z = GfParmGetNum(hdle, SECT_BONNET, PRM_ZPOS, (char*)NULL, carElt->_drvPos_z);

    if (car->fuel > car->tank) {
	car->fuel = car->tank;
    }
    k = k * k;
    car->Iinv.x = 12.0 / (car->mass * (car->dimension.y * car->dimension.y + car->dimension.z * car->dimension.z));
    car->Iinv.y = 12.0 / (car->mass * (car->dimension.x * car->dimension.x + car->dimension.z * car->dimension.z));
    car->Iinv.z = 12.0 / (car->mass * (car->dimension.y * car->dimension.y + k * car->dimension.x * car->dimension.x));
    
    /* configure components */
    w = car->mass * G;

    wf0 = w * gcfr;
    wr0 = w * (1 - gcfr);

    car->wheel[FRNT_RGT].weight0 = wf0 * gcfrl;
    car->wheel[FRNT_LFT].weight0 = wf0 * (1 - gcfrl);
    car->wheel[REAR_RGT].weight0 = wr0 * gcrrl;
    car->wheel[REAR_LFT].weight0 = wr0 * (1 - gcrrl);

    for (i = 0; i < 2; i++) {
	SimAxleConfig(car, i);
    }

    for (i = 0; i < 4; i++) {
	SimWheelConfig(car, i);	    
    }


    SimEngineConfig(car);
    SimTransmissionConfig(car);
    SimSteerConfig(car);
    SimBrakeSystemConfig(car);
    SimAeroConfig(car);
    for (i = 0; i < 2; i++) {
	SimWingConfig(car, i);
    }
    
    /* Set the origin to GC */
    car->wheelbase = car->wheeltrack = 0;
    car->statGC.x = car->wheel[FRNT_RGT].staticPos.x * gcfr + car->wheel[REAR_RGT].staticPos.x * (1 - gcfr);

    carElt->_dimension = car->dimension;
    carElt->_statGC = car->statGC;
    carElt->_tank = car->tank;
    for (i = 0; i < 4; i++) {
	carElt->priv.wheel[i].relPos = car->wheel[i].relPos;
    }

    for (i = 0; i < 4; i++) {
	car->wheel[i].staticPos.x -= car->statGC.x;
	car->wheel[i].staticPos.y -= car->statGC.y;
    }
    car->wheelbase = (car->wheel[FRNT_RGT].staticPos.x 
		      + car->wheel[FRNT_LFT].staticPos.x
		      - car->wheel[REAR_RGT].staticPos.x
		      - car->wheel[REAR_LFT].staticPos.x) / 2.0;
    car->wheeltrack = (-car->wheel[REAR_LFT].staticPos.y 
		       - car->wheel[FRNT_LFT].staticPos.y
		       + car->wheel[FRNT_RGT].staticPos.y
		       + car->wheel[REAR_RGT].staticPos.y) / 2.0;

    /* set corners pos */
    car->corner[FRNT_RGT].pos.x = car->dimension.x * .5 - car->statGC.x;
    car->corner[FRNT_RGT].pos.y = - overallwidth * .5 - car->statGC.y;
    car->corner[FRNT_RGT].pos.z = 0;
    car->corner[FRNT_LFT].pos.x = car->dimension.x * .5 - car->statGC.x;
    car->corner[FRNT_LFT].pos.y = overallwidth * .5 - car->statGC.y;
    car->corner[FRNT_LFT].pos.z = 0;
    car->corner[REAR_RGT].pos.x = - car->dimension.x * .5 - car->statGC.x;
    car->corner[REAR_RGT].pos.y = - overallwidth * .5 - car->statGC.y;
    car->corner[REAR_RGT].pos.z = 0;
    car->corner[REAR_LFT].pos.x = - car->dimension.x * .5 - car->statGC.x;
    car->corner[REAR_LFT].pos.y = overallwidth * .5 - car->statGC.y;
    car->corner[REAR_LFT].pos.z = 0;
}


static void
SimCarUpdateForces(tCar *car)
{
    tForces	F;
    int		i;
    tdble	m, w, minv;
    tdble	Cosz, Sinz;
    tdble	v, R, Rv, Rm, Rx, Ry;
    t3Dd original;
    t3Dd updated;
    t3Dd angles;
    Cosz = car->Cosz = cos(car->DynGCg.pos.az);
    Sinz = car->Sinz = sin(car->DynGCg.pos.az);

    car->preDynGC = car->DynGCg;
 
    /* total mass */
    m = car->mass + car->fuel;
    minv = 1.0 / m;
    w = -m * G;

    /* Weight - Bring weight vector to the car's frame of reference*/
    original.x = 0.0;
    original.y = 0.0;
    original.z = w;
    angles.x = car->DynGCg.pos.ax;
    angles.y = car->DynGCg.pos.ay;
    angles.z = car->DynGCg.pos.az;	
    NaiveRotate (original, angles, &updated);
    F.F.x = updated.x;
    F.F.y = updated.y;
    F.F.z = updated.z;	

    F.M.x = F.M.y = F.M.z = 0;


    /* Wheels */
    for (i = 0; i < 4; i++) {
	/* forces */
	F.F.x += car->wheel[i].forces.x;
	F.F.y += car->wheel[i].forces.y;
	F.F.z += car->wheel[i].forces.z;
	/* moments */
	F.M.x += car->wheel[i].forces.z * car->wheel[i].staticPos.y +
	    car->wheel[i].forces.y * //* (car->wheel[i].rollCenter);
	    (car->statGC.z + car->wheel[i].rideHeight);
	F.M.y -= car->wheel[i].forces.z * car->wheel[i].staticPos.x + 
	    car->wheel[i].forces.x * //car->wheel[i].relPos.z;
	    (car->statGC.z + car->wheel[i].rideHeight);
	F.M.z += -car->wheel[i].forces.x * car->wheel[i].staticPos.y +
	    car->wheel[i].forces.y * car->wheel[i].staticPos.x;
    }

    /* Aero Drag */
    F.F.x += car->aero.drag;
    F.F.y += car->aero.lateral_drag;
    F.F.z += car->aero.vertical_drag;
    /* Wings & Aero Downforce */
    for (i = 0; i < 2; i++) {
	/* forces */
	F.F.z += car->wing[i].forces.z + car->aero.lift[i];
	F.F.x += car->wing[i].forces.x;
	/* moments */
	F.M.y -= (car->wing[i].forces.z + car->aero.lift[i]) * car->wing[i].staticPos.x +
	    car->wing[i].forces.x * car->wing[i].staticPos.z;
    }

    /* Rolling Resistance */
    if (1) {
	v = sqrt(car->DynGC.vel.x * car->DynGC.vel.x + car->DynGC.vel.y * car->DynGC.vel.y);
	
	R = 0;
	for (i = 0; i < 4; i++) {
	    R += car->wheel[i].rollRes;
	}
	if (v > 0.00001) {
	    Rv = R / v;
	    if ((Rv * minv * SimDeltaTime) > v) {
		Rv = v * m / SimDeltaTime;
	    }
	} else {
	    Rv = 0;
	}
	Rx = Rv * car->DynGC.vel.x; //car->DynGCg.vel.x; 
	Ry = Rv * car->DynGC.vel.y; //car->DynGCg.vel.x; 
	
	if ((R * car->wheelbase / 2.0 * car->Iinv.z) > fabs(car->DynGCg.vel.az)) {
	    Rm = car->DynGCg.vel.az / car->Iinv.z;
	} else {
	    Rm = SIGN(car->DynGCg.vel.az) * R * car->wheelbase / 2.0;
	}
    } else {
	Rx = Rv = Rm = Ry = 0;
    }
    /* compute accelerations */

    if (1) {
	/* This should work as long as all forces have been computed for
       the car's frame of reference */
	t3Dd original;
	t3Dd updated;
	t3Dd angles;

	car->DynGC.acc.x = (F.F.x - Rx) * minv;
	car->DynGC.acc.y = (F.F.y - Ry) * minv;
	car->DynGC.acc.z = F.F.z * minv;

	original.x = car->DynGC.acc.x;
	original.y = car->DynGC.acc.y;
	original.z = car->DynGC.acc.z;
	angles.x = car->DynGCg.pos.ax;
	angles.y = car->DynGCg.pos.ay;
	angles.z = car->DynGCg.pos.az;	
	NaiveInverseRotate (original, angles, &updated);
	car->DynGCg.acc.x = updated.x;
	car->DynGCg.acc.y = updated.y;
	car->DynGCg.acc.z = updated.z;
    }
    car->DynGCg.acc.ax = car->DynGC.acc.ax = F.M.x * car->Iinv.x;
    car->DynGCg.acc.ay = car->DynGC.acc.ay = F.M.y * car->Iinv.y;
    car->DynGCg.acc.az = car->DynGC.acc.az = (F.M.z - Rm) * car->Iinv.z;
}


static void
SimCarUpdateSpeed(tCar *car)
{
    tdble	Cosz, Sinz;
    int		i;
    tdble	mass;
    tdble	vel, Rr, Rm;	/* Rolling Resistance */

    mass = car->mass + car->fuel;

    
    Cosz = car->Cosz;
    Sinz = car->Sinz;

    car->DynGCg.vel.x += car->DynGCg.acc.x * SimDeltaTime;
    car->DynGCg.vel.y += car->DynGCg.acc.y * SimDeltaTime;
    car->DynGCg.vel.z += car->DynGCg.acc.z * SimDeltaTime;

    Rr = 0;
    for (i = 0; i < 4; i++) {
	Rr += car->wheel[i].rollRes;
    }
    
    Rm = Rr * car->wheelbase /*  / 2.0 */ * car->Iinv.z * SimDeltaTime;
    Rr = 2.0 * Rr / mass * SimDeltaTime;
    vel = sqrt(car->DynGCg.vel.x * car->DynGCg.vel.x + car->DynGCg.vel.y * car->DynGCg.vel.y);
    
    if (Rr > vel) {
	Rr = vel;
    }
    if (vel > 0.00001) {
	car->DynGCg.vel.x -= car->DynGCg.vel.x * Rr / vel * SIGN(car->DynGCg.vel.x);
	car->DynGCg.vel.y -= car->DynGCg.vel.y * Rr / vel * SIGN(car->DynGCg.vel.y);
    }

    car->DynGCg.vel.ax += car->DynGCg.acc.ax * SimDeltaTime;
    car->DynGCg.vel.ay += car->DynGCg.acc.ay * SimDeltaTime;
    car->DynGCg.vel.az += car->DynGCg.acc.az * SimDeltaTime;

    if (Rm > fabs(car->DynGCg.vel.az)) {
	Rm = fabs(car->DynGCg.vel.az);
    }
    car->DynGCg.vel.az -= Rm * SIGN(car->DynGCg.vel.az);

    car->DynGC.vel.ax = car->DynGCg.vel.ax;
    car->DynGC.vel.ay = car->DynGCg.vel.ay;
    car->DynGC.vel.az = car->DynGCg.vel.az;


    if (1) {
	/* We need to get the speed on the actual frame of reference
	   for the car. Now we don't need to worry about the world's
	   coordinates anymore when we calculate stuff. I.E check
	   aero.cpp*/
	t3Dd original;
	t3Dd updated;
	t3Dd angles;
	original.x = car->DynGCg.vel.x;
	original.y = car->DynGCg.vel.y;
	original.z = car->DynGCg.vel.z;
	angles.x = car->DynGCg.pos.ax;
	angles.y = car->DynGCg.pos.ay;
	angles.z = car->DynGCg.pos.az;	
	NaiveRotate (original, angles, &updated);
	car->DynGC.vel.x = updated.x;
	car->DynGC.vel.y = updated.y;
	car->DynGC.vel.z = updated.z;
    } else {
	car->DynGC.vel.x = car->DynGCg.vel.x * Cosz + car->DynGCg.vel.y * Sinz;
	car->DynGC.vel.y = -car->DynGCg.vel.x * Sinz + car->DynGCg.vel.y * Cosz;
	car->DynGC.vel.z = car->DynGCg.vel.z;
    }


}

void
SimCarUpdateWheelPos(tCar *car)
{
    int i;
    tdble vx;
    tdble vy;
    tdble Cosz, Sinz;

    Cosz = car->Cosz;
    Sinz = car->Sinz;
    vx = car->DynGC.vel.x;
    vy = car->DynGC.vel.y;
    /* Wheels data */
    if (1) {
	t3Dd angles;
	for (i = 0; i < 4; i++) {
	    t3Dd pos;
	    tWheel *wheel = &(car->wheel[i]);
	    pos.x = wheel->staticPos.x;
	    pos.y = wheel->staticPos.y;
	    pos.z = -car->statGC.z; // or wheel->staticPos.z; ??
	    angles.x = car->DynGC.pos.ax;
	    angles.y = car->DynGC.pos.ay;
	    angles.z = car->DynGC.pos.az;
	    NaiveInverseRotate (pos, angles, &wheel->pos);
	    wheel->pos.x += car->DynGC.pos.x;
	    wheel->pos.y += car->DynGC.pos.y;
	    wheel->pos.z += car->DynGC.pos.z;
	    //	    angles.x += wheel->relPos.ax;
	    //	    angles.z += wheel->steer + wheel->staticPos.az;
	    
	    wheel->bodyVel.x = vx
		- car->DynGC.vel.az * wheel->staticPos.y
		+ car->DynGC.vel.ay * wheel->staticPos.x;
	    wheel->bodyVel.y = vy
		+ car->DynGC.vel.az * wheel->staticPos.x
		- car->DynGC.vel.ax * wheel->staticPos.y;
	}
    } else {
	for (i = 0; i < 4; i++) {
	    tdble x = car->wheel[i].staticPos.x;
	    tdble y = car->wheel[i].staticPos.y;
	    tdble dx = x * Cosz - y * Sinz;
	    tdble dy = x * Sinz + y * Cosz;
	    
	    car->wheel[i].pos.x = car->DynGC.pos.x + dx;
	    car->wheel[i].pos.y = car->DynGC.pos.y + dy;
	    car->wheel[i].pos.z = car->DynGC.pos.z - car->statGC.z - x * sin(car->DynGC.pos.ay) + y * sin(car->DynGC.pos.ax);
	    
	    car->wheel[i].bodyVel.x = vx - car->DynGC.vel.az * y;
	    car->wheel[i].bodyVel.y = vy + car->DynGC.vel.az * x;
	}
    }
}


static void
SimCarUpdatePos(tCar *car)
{
    tdble vx, vy;
    tdble accx, accy;

    vx = car->DynGCg.vel.x;
    vy = car->DynGCg.vel.y;
    
    accx = car->DynGCg.acc.x;
    accy = car->DynGCg.acc.y;

    car->DynGCg.pos.x += vx * SimDeltaTime;
    car->DynGCg.pos.y += vy * SimDeltaTime;
    car->DynGCg.pos.z += car->DynGCg.vel.z * SimDeltaTime;
    
    car->DynGCg.pos.ax += car->DynGCg.vel.ax * SimDeltaTime;
    car->DynGCg.pos.ay += car->DynGCg.vel.ay * SimDeltaTime;
    car->DynGCg.pos.az += car->DynGCg.vel.az * SimDeltaTime;

    NORM_PI_PI(car->DynGCg.pos.ax);
    NORM_PI_PI(car->DynGCg.pos.ay);
    NORM_PI_PI(car->DynGCg.pos.az);
    
    //    if (car->DynGCg.pos.ax > aMax) car->DynGCg.pos.ax = aMax;
    //    if (car->DynGCg.pos.ax < -aMax) car->DynGCg.pos.ax = -aMax;
    //    if (car->DynGCg.pos.ay > aMax) car->DynGCg.pos.ay = aMax;
    //    if (car->DynGCg.pos.ay < -aMax) car->DynGCg.pos.ay = -aMax;

    car->DynGC.pos.x = car->DynGCg.pos.x;
    car->DynGC.pos.y = car->DynGCg.pos.y;
    car->DynGC.pos.z = car->DynGCg.pos.z;

    car->DynGC.pos.ax = car->DynGCg.pos.ax;
    car->DynGC.pos.ay = car->DynGCg.pos.ay;
    car->DynGC.pos.az = car->DynGCg.pos.az;

    RtTrackGlobal2Local(car->trkPos.seg, car->DynGCg.pos.x, car->DynGCg.pos.y, &(car->trkPos), TR_LPOS_MAIN);
}

static void
SimCarUpdateCornerPos(tCar *car)
{
    tdble Cosz = car->Cosz;
    tdble Sinz = car->Sinz;
    tdble vx = car->DynGCg.vel.x;
    tdble vy = car->DynGCg.vel.y;
    int i;

    for (i = 0; i < 4; i++) {
	tdble x = car->corner[i].pos.x;
	tdble y = car->corner[i].pos.y;
	
	tdble dx = x * Cosz - y * Sinz;
	tdble dy = x * Sinz + y * Cosz;
	
	car->corner[i].pos.ax = car->DynGCg.pos.x + dx;
	car->corner[i].pos.ay = car->DynGCg.pos.y + dy;
	/*car->corner[i].pos.az = car->DynGC.pos.z - car->statGC.z + x * sin(car->DynGC.pos.ay) + y * sin(car->DynGC.pos.ax);*/

	car->corner[i].vel.x = vx - car->DynGCg.vel.az * y;
	car->corner[i].vel.y = vy + car->DynGCg.vel.az * x;
    }
}

void 
SimTelemetryOut(tCar *car)
{
    int i;
    tdble Fzf, Fzr;
    
    printf("-----------------------------\nCar: %d %s ---\n", car->carElt->index, car->carElt->_name);
    printf("Seg: %d (%s)  Ts:%f  Tr:%f\n",
	   car->trkPos.seg->id, car->trkPos.seg->name, car->trkPos.toStart, car->trkPos.toRight);
    printf("---\nMx: %f  My: %f  Mz: %f (N/m)\n", car->DynGC.acc.ax, car->DynGC.acc.ay, car->DynGC.acc.az);
    printf("Wx: %f  Wy: %f  Wz: %f (rad/s)\n", car->DynGC.vel.ax, car->DynGC.vel.ay, car->DynGC.vel.az);
    printf("Ax: %f  Ay: %f  Az: %f (rad)\n", car->DynGC.pos.ax, car->DynGC.pos.ay, car->DynGC.pos.az);
    printf("---\nAx: %f  Ay: %f  Az: %f (Gs)\n", car->DynGC.acc.x/9.81, car->DynGC.acc.y/9.81, car->DynGC.acc.z/9.81);
    printf("Vx: %f  Vy: %f  Vz: %f (m/s)\n", car->DynGC.vel.x, car->DynGC.vel.y, car->DynGC.vel.z);
    printf("Px: %f  Py: %f  Pz: %f (m)\n---\n", car->DynGC.pos.x, car->DynGC.pos.y, car->DynGC.pos.z);
    printf("As: %f\n---\n", sqrt(car->airSpeed2));
    for (i = 0; i < 4; i++) {
	printf("wheel %d - RH:%f susp:%f zr:%.2f ", i, car->wheel[i].rideHeight, car->wheel[i].susp.x, car->wheel[i].zRoad);
	printf("sx:%f sa:%f w:%f ", car->wheel[i].sx, car->wheel[i].sa, car->wheel[i].spinVel);
	printf("fx:%f fy:%f fz:%f\n", car->wheel[i].forces.x, car->wheel[i].forces.y, car->wheel[i].forces.z);
    }
    Fzf = (car->aero.lift[0] + car->wing[0].forces.z) / 9.81;
    Fzr = (car->aero.lift[1] + car->wing[1].forces.z) / 9.81;
    printf("Aero Fx:%f Fz:%f Fzf=%f Fzr=%f ratio=%f\n", car->aero.drag / 9.81, Fzf + Fzr,
	   Fzf, Fzr, (Fzf + Fzr) / (car->aero.drag + 0.1) * 9.81);
    
}

void
SimCarUpdate(tCar *car, tSituation * /* s */)
{
    SimCarUpdateForces(car);
    CHECK(car);
    SimCarUpdateSpeed(car);
    CHECK(car);
    SimCarUpdateCornerPos(car);
    CHECK(car);
    SimCarUpdatePos(car);
    CHECK(car);
    SimCarCollideZ(car);
    CHECK(car);
    SimCarCollideXYScene(car);
    CHECK(car);
}

void
SimCarUpdate2(tCar *car, tSituation * /* s */)
{
    if (SimTelemetry == car->carElt->index) SimTelemetryOut(car);
}

/* Original coords, angle, new coords */
/* This is a naive implementation. It should also work with A(BxC),
   with the angles being represented as a normal vector. That'd be a
   bit faster too. */
void NaiveRotate (t3Dd v, t3Dd u, t3Dd* v0)
{
    tdble cosx = cos(u.x);
    tdble cosy = cos(u.y);
    tdble cosz = cos(u.z);
    tdble sinx = sin(u.x);
    tdble siny = sin(u.y);
    tdble sinz = sin(u.z);
    tdble vx_z = v.x * cosz + v.y * sinz;
    tdble vy_z = v.y * cosz - v.x * sinz;
    tdble vx_0 = vx_z * cosy - v.z * siny;
    tdble vz_y = v.z * cosy + vx_z * siny;
    tdble vy_0 = vy_z * cosx + vz_y * sinx;
    tdble vz_0 = vz_y * cosx - vy_z * sinx;
    v0->x = vx_0;
    v0->y = vy_0;
    v0->z = vz_0;
}

/* Original coords, angle, new coords */
/* This is a naive implementation. It should also work with A(BxC),
   with the angles being represented as a normal vector. That'd be a
   bit faster too. */
void NaiveInverseRotate (t3Dd v, t3Dd u, t3Dd* v0)
{
    tdble cosx = cos(-u.x);
    tdble cosy = cos(-u.y);
    tdble cosz = cos(-u.z);
    tdble sinx = sin(-u.x);
    tdble siny = sin(-u.y);
    tdble sinz = sin(-u.z);

    tdble vy_x = v.y * cosx + v.z* sinx;
    tdble vz_x = v.z * cosx - v.y * sinx;
    tdble vx_y = v.x * cosy - vz_x * siny;
    tdble vz_0 = vz_x * cosy + v.x * siny;
    tdble vx_0 = vx_y * cosz + vy_x * sinz;
    tdble vy_0 = vy_x * cosz - vx_y * sinz;

    v0->x = vx_0;
    v0->y = vy_0;
    v0->z = vz_0;
    //        printf ("..(%f %f %f)\n..[%f %f %f]\n->[%f %f %f]\n",
    //    	    u.x, u.y, u.z,
    //    	    v.x, v.y, v.z,
    //    	    v0->x, v0->y, v0->z);
}
