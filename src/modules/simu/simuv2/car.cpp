/***************************************************************************

    file                 : car.cpp
    created              : Sun Mar 19 00:05:43 CET 2000
    copyright            : (C) 2000-2017 by Eric Espie, Bernhard Wymann
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



#include <stdio.h>

#include "sim.h"

const tdble aMax = 1.04f; // 60 degrees DOF limit

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
	
	car->dimension.x = GfParmGetNum(hdle, SECT_CAR, PRM_LEN, (char*)NULL, 4.7f);
	car->dimension.y = GfParmGetNum(hdle, SECT_CAR, PRM_WIDTH, (char*)NULL, 1.9f);
	overallwidth     = GfParmGetNum(hdle, SECT_CAR, PRM_OVERALLWIDTH, (char*)NULL, car->dimension.y);
	car->dimension.z = GfParmGetNum(hdle, SECT_CAR, PRM_HEIGHT, (char*)NULL, 1.2f);
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
	
	/* Set the origin to GC */
	car->wheelbase = car->wheeltrack = 0;
	car->statGC.x = car->wheel[FRNT_RGT].staticPos.x * gcfr + car->wheel[REAR_RGT].staticPos.x * (1 - gcfr);

	SimAtmosphereConfig(car);
	SimEngineConfig(car);
	SimTransmissionConfig(car);
	SimSteerConfig(car);
	SimBrakeSystemConfig(car);
	SimAeroConfig(car);
	for (i = 0; i < 2; i++) {
		SimWingConfig(car, i);
	}
		
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
	tdble	v, R, Rv, Rm, Rx, Ry, Rz;

	car->preDynGC = car->DynGCg;
	
	/* total mass */
	m = car->mass + car->fuel;
	minv = 1.0 / m;
	w = -m * G;
	
	/* Weight */
	sgMat4 dst;
	sgMakeRotMat4(dst, RAD2DEG(car->DynGC.pos.az), RAD2DEG(car->DynGC.pos.ax), RAD2DEG(car->DynGC.pos.ay));
	sgMat4 dstInv;
	sgTransposeNegateMat4(dstInv, dst);
	sgVec3 weight = {0.0f, 0.0f, w};
	sgXformVec3(weight, dstInv);
	F.F.x = weight[SG_X];
	F.F.y = weight[SG_Y];
	F.F.z = weight[SG_Z];

	F.M.x = F.M.y = F.M.z = 0;
	
	/* Wheels */
	for (i = 0; i < 4; i++) {
		tWheel* wheel = &(car->wheel[i]);
		
		/* forces */
		F.F.x += wheel->forces.x;
		F.F.y += wheel->forces.y;
		F.F.z += wheel->forces.z;
		
		/* moments */
		F.M.x += wheel->forces.z * wheel->staticPos.y +
			wheel->forces.y * wheel->rollCenter;
			// Eventually TODO: activate fix below and make all cars/robots fit.
			//car->wheel[i].forces.y * (car->statGC.z + car->wheel[i].rideHeight);
		F.M.y -= wheel->forces.z * wheel->staticPos.x +
			wheel->forces.x * (car->statGC.z + wheel->rideHeight);
		F.M.z += -wheel->forces.x * wheel->staticPos.y +
			wheel->forces.y * wheel->staticPos.x;
	}
	
	/* Aero Drag */
	F.F.x += car->aero.drag;
	
	/* Wings & Aero Downforce */
	for (i = 0; i < 2; i++) {
		/* forces */
		F.F.z += car->wing[i].forces.z + car->aero.lift[i];
		F.F.x += car->wing[i].forces.x;
		/* moments */
		F.M.y -= car->wing[i].forces.z * car->wing[i].staticPos.x + car->wing[i].forces.x * car->wing[i].staticPos.z;
		F.M.y -= car->aero.lift[i] * (car->axle[i].xpos - car->statGC.x);
	}
		
	/* Rolling Resistance */
	v = car->speed;
	R = 0.0f;
	for (i = 0; i < 4; i++) {
		R += car->wheel[i].rollRes;
	}
	if (v > 0.00001f) {
		Rv = R / v;
		if ((Rv * minv * SimDeltaTime) > v) {
			Rv = v * m / SimDeltaTime;
		}
	} else {
		Rv = 0.0f;
	}
	Rx = Rv * car->DynGC.vel.x;
	Ry = Rv * car->DynGC.vel.y;
	Rz = Rv * car->DynGC.vel.z;
	
	if ((R * car->wheelbase / 2.0 * car->Iinv.z) > fabs(car->DynGCg.vel.az)) {
		Rm = car->DynGCg.vel.az / car->Iinv.z;
	} else {
		Rm = SIGN(car->DynGCg.vel.az) * R * car->wheelbase / 2.0;
	}
	
	/* compute accelerations */
	car->DynGC.acc.x = (F.F.x - Rx) * minv;
	car->DynGC.acc.y = (F.F.y - Ry) * minv;
	car->DynGC.acc.z = (F.F.z - Rz) * minv;
	
	sgVec3 accel = {car->DynGC.acc.x, car->DynGC.acc.y, car->DynGC.acc.z};
	sgXformVec3(accel, dst);
	
	car->DynGCg.acc.x = accel[SG_X];
	car->DynGCg.acc.y = accel[SG_Y];
	car->DynGCg.acc.z = accel[SG_Z];

	car->DynGCg.acc.ax = car->DynGC.acc.ax = F.M.x * car->Iinv.x;
	car->DynGCg.acc.ay = car->DynGC.acc.ay = F.M.y * car->Iinv.y;
	car->DynGCg.acc.az = car->DynGC.acc.az = (F.M.z - Rm) * car->Iinv.z;
}

static void
SimCarUpdateSpeed(tCar *car)
{
	car->DynGCg.vel.x += car->DynGCg.acc.x * SimDeltaTime;
	car->DynGCg.vel.y += car->DynGCg.acc.y * SimDeltaTime;
	car->DynGCg.vel.z += car->DynGCg.acc.z * SimDeltaTime;

	car->DynGCg.vel.ax += car->DynGCg.acc.ax * SimDeltaTime;
	car->DynGCg.vel.ay += car->DynGCg.acc.ay * SimDeltaTime;
	car->DynGCg.vel.az += car->DynGCg.acc.az * SimDeltaTime;
	
	/* spin limitation */
	if (fabs(car->DynGCg.vel.az) > 9.0) {
		car->DynGCg.vel.az = SIGN(car->DynGCg.vel.az) * 9.0;
	}
		
	car->DynGC.vel.ax = car->DynGCg.vel.ax;
	car->DynGC.vel.ay = car->DynGCg.vel.ay;
	car->DynGC.vel.az = car->DynGCg.vel.az;
	
	sgMat4 dst;
	sgMakeRotMat4(dst, RAD2DEG(car->DynGC.pos.az), RAD2DEG(car->DynGC.pos.ax), RAD2DEG(car->DynGC.pos.ay));
	sgTransposeNegateMat4(dst);
	sgVec3 vel;
	sgXformVec3(vel, (float *) &(car->DynGCg.vel), dst);
	car->DynGC.vel.x = vel[SG_X];
	car->DynGC.vel.y = vel[SG_Y];
	car->DynGC.vel.z = vel[SG_Z];
}

void
SimCarUpdateWheelPos(tCar *car)
{	
	sgMat4 dst;
	sgMakeRotMat4(dst, RAD2DEG(car->DynGC.pos.az), RAD2DEG(car->DynGC.pos.ax), RAD2DEG(car->DynGC.pos.ay));
		
	int i;
		
	/* Wheels data */
	for (i = 0; i < 4; i++) {
		tWheel* wheel = &(car->wheel[i]);
		sgVec3 dstVec;
		sgXformVec3(dstVec, (float *) &(wheel->staticPos.x), dst);

		wheel->pos.x = car->DynGCg.pos.x + dstVec[0];
		wheel->pos.y = car->DynGCg.pos.y + dstVec[1];
		wheel->pos.z = car->DynGCg.pos.z + dstVec[2];
		
		wheel->bodyVel.x = car->DynGC.vel.x - car->DynGC.vel.az * car->wheel[i].staticPos.y;
		wheel->bodyVel.y = car->DynGC.vel.y + car->DynGC.vel.az * car->wheel[i].staticPos.x;
	}
}

static void
SimCarUpdatePos(tCar *car)
{
	tdble vx, vy;
	
	vx = car->DynGCg.vel.x;
	vy = car->DynGCg.vel.y;
	
	car->DynGCg.pos.x += vx * SimDeltaTime;
	car->DynGCg.pos.y += vy * SimDeltaTime;
	car->DynGCg.pos.z += car->DynGCg.vel.z * SimDeltaTime;
	
	car->DynGCg.pos.ax += car->DynGCg.vel.ax * SimDeltaTime;
	car->DynGCg.pos.ay += car->DynGCg.vel.ay * SimDeltaTime;
	car->DynGCg.pos.az += car->DynGCg.vel.az * SimDeltaTime;
		
	NORM_PI_PI(car->DynGCg.pos.az);
	
	if (car->DynGCg.pos.ax > aMax) car->DynGCg.pos.ax = aMax;
	if (car->DynGCg.pos.ax < -aMax) car->DynGCg.pos.ax = -aMax;
	if (car->DynGCg.pos.ay > aMax) car->DynGCg.pos.ay = aMax;
	if (car->DynGCg.pos.ay < -aMax) car->DynGCg.pos.ay = -aMax;
	
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
	sgMat4 dst;
	sgMakeRotMat4(dst, RAD2DEG(car->DynGC.pos.az), RAD2DEG(car->DynGC.pos.ax), RAD2DEG(car->DynGC.pos.ay));

	tdble Cosz = car->Cosz;
	tdble Sinz = car->Sinz;
	int i;
	
	for (i = 0; i < 4; i++) {
		tPosd* corner = &(car->corner[i].pos);
		sgVec3 localPos;
		
		localPos[0] = corner->x + car->statGC.x;
		localPos[1] = corner->y + car->statGC.y;
		localPos[2] = corner->z - car->statGC.z;

		sgVec3 dstVec;
		sgXformVec3(dstVec, localPos, dst);
		
		car->corner[i].pos.ax = car->DynGCg.pos.x + dstVec[0];
		car->corner[i].pos.ay = car->DynGCg.pos.y + dstVec[1];
		car->corner[i].pos.az = car->DynGCg.pos.z + dstVec[2];

		/* add the body rotation to the corner       */
		/* the speed is vel.az * r                   */
		/* where r = sqrt(x*x + y*y)                 */
		/* the tangent vector is -y / r and x / r    */
		// compute corner velocity at local frame
		car->corner[i].vel.ax = - car->DynGC.vel.az * localPos[1];
		car->corner[i].vel.ay = car->DynGC.vel.az * localPos[0];
		car->corner[i].vel.az = car->DynGC.vel.ax * localPos[1] - car->DynGC.vel.ay * localPos[0];
		
		// rotate to global and add global center of mass velocity
		// note: global to local.
		car->corner[i].vel.x = car->DynGCg.vel.x
			+ car->corner[i].vel.ax * Cosz - car->corner[i].vel.ay * Sinz;
		car->corner[i].vel.y = car->DynGCg.vel.y
			+ car->corner[i].vel.ax * Sinz + car->corner[i].vel.ay * Cosz;
		car->corner[i].vel.z = car->DynGCg.vel.z + car->corner[i].vel.az;

		// add local center of mass velocity
		car->corner[i].vel.ax += car->DynGC.vel.x;
		car->corner[i].vel.ay += car->DynGC.vel.y;
		car->corner[i].vel.az += car->DynGC.vel.z;
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
	printf("Ax: %f  Ay: %f  Az: %f (rad)\n", car->DynGCg.pos.ax, car->DynGCg.pos.ay, car->DynGCg.pos.az);
	printf("---\nAx: %f  Ay: %f  Az: %f (Gs)\n", car->DynGC.acc.x/9.81, car->DynGC.acc.y/9.81, car->DynGC.acc.z/9.81);
	printf("Vx: %f  Vy: %f  Vz: %f (m/s)\n", car->DynGC.vel.x, car->DynGC.vel.y, car->DynGC.vel.z);
	printf("Px: %f  Py: %f  Pz: %f (m)\n---\n", car->DynGCg.pos.x, car->DynGCg.pos.y, car->DynGCg.pos.z);
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
	car->speed = sqrt(car->DynGC.vel.x*car->DynGC.vel.x + car->DynGC.vel.y*car->DynGC.vel.y + car->DynGC.vel.z*car->DynGC.vel.z);
}

void
SimCarUpdate2(tCar *car, tSituation * /* s */)
{
    if (SimTelemetry == car->carElt->index) SimTelemetryOut(car);
}

