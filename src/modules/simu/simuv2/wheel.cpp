/***************************************************************************

    file                 : wheel.cpp
    created              : Sun Mar 19 00:09:06 CET 2000
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

static const char *WheelSect[4] = {SECT_FRNTRGTWHEEL, SECT_FRNTLFTWHEEL, SECT_REARRGTWHEEL, SECT_REARLFTWHEEL};
static const char *SuspSect[4] = {SECT_FRNTRGTSUSP, SECT_FRNTLFTSUSP, SECT_REARRGTSUSP, SECT_REARLFTSUSP};
static const char *BrkSect[4] = {SECT_FRNTRGTBRAKE, SECT_FRNTLFTBRAKE, SECT_REARRGTBRAKE, SECT_REARLFTBRAKE};

void SimWheelConfig(tCar *car, int index)
{
	void *hdle = car->params;
	tCarElt *carElt = car->carElt;
	tWheel *wheel = &(car->wheel[index]);
	tdble rimdiam, tirewidth, tireratio, pressure;
	tdble x0, Ca, RFactor, EFactor, patchLen;

	pressure              = GfParmGetNum(hdle, WheelSect[index], PRM_PRESSURE, (char*)NULL, 275600);
	rimdiam               = GfParmGetNum(hdle, WheelSect[index], PRM_RIMDIAM, (char*)NULL, 0.33f);
	tirewidth             = GfParmGetNum(hdle, WheelSect[index], PRM_TIREWIDTH, (char*)NULL, 0.145f);
	tireratio             = GfParmGetNum(hdle, WheelSect[index], PRM_TIRERATIO, (char*)NULL, 0.75f);
	wheel->mu             = GfParmGetNum(hdle, WheelSect[index], PRM_MU, (char*)NULL, 1.0f);
	wheel->I              = GfParmGetNum(hdle, WheelSect[index], PRM_INERTIA, (char*)NULL, 1.5f);
	wheel->I += wheel->brake.I; // add brake inertia
	wheel->staticPos.y    = GfParmGetNum(hdle, WheelSect[index], PRM_YPOS, (char*)NULL, 0.0f);
	x0                    = GfParmGetNum(hdle, WheelSect[index], PRM_RIDEHEIGHT, (char*)NULL, 0.20f);
	wheel->staticPos.az   = GfParmGetNum(hdle, WheelSect[index], PRM_TOE, (char*)NULL, 0.0f);
	wheel->staticPos.ax   = GfParmGetNum(hdle, WheelSect[index], PRM_CAMBER, (char*)NULL, 0.0f);
	wheel->staticPos.ay   = GfParmGetNum(hdle, WheelSect[index], PRM_CASTER, (char*)NULL, 0.0f);
	Ca                    = GfParmGetNum(hdle, WheelSect[index], PRM_CA, (char*)NULL, 30.0f);
	RFactor               = GfParmGetNum(hdle, WheelSect[index], PRM_RFACTOR, (char*)NULL, 0.8f);
	EFactor               = GfParmGetNum(hdle, WheelSect[index], PRM_EFACTOR, (char*)NULL, 0.7f);
	wheel->lfMax          = GfParmGetNum(hdle, WheelSect[index], PRM_LOADFMAX, (char*)NULL, 1.6f);
	wheel->lfMin          = GfParmGetNum(hdle, WheelSect[index], PRM_LOADFMIN, (char*)NULL, 0.8f);
	wheel->opLoad         = GfParmGetNum(hdle, WheelSect[index], PRM_OPLOAD, (char*)NULL, wheel->weight0 * 1.2f);
	wheel->mass           = GfParmGetNum(hdle, WheelSect[index], PRM_MASS, (char*)NULL, 20.0f);
	
	wheel->lfMin = MIN(0.8f, wheel->lfMin);
	wheel->lfMax = MAX(1.6f, wheel->lfMax);

	// Absolute pressure of cold tire.
	wheel->pressure			= pressure;
	wheel->currentPressure	= pressure;
		
	RFactor = MIN(1.0f, RFactor);
	RFactor = MAX(0.1f, RFactor);
	EFactor = MIN(1.0f, EFactor);

	patchLen = wheel->weight0 / (tirewidth * pressure);

	wheel->staticPos.z = -car->statGC.z;
	
	wheel->radius = rimdiam / 2.0f + tirewidth * tireratio;
	wheel->tireSpringRate = wheel->weight0 / (wheel->radius * (1.0f - cos(asin(patchLen / (2.0f * wheel->radius)))));
	wheel->relPos.x = wheel->staticPos.x = car->axle[index/2].xpos;
	wheel->relPos.y = wheel->staticPos.y;
	wheel->relPos.z = wheel->radius - wheel->susp.spring.x0;
	wheel->relPos.ax = wheel->relPos.ay = wheel->relPos.az = 0.0f;
	wheel->steer = 0.0f;

	/* components */
	SimSuspConfig(hdle, SuspSect[index], &(wheel->susp), wheel->weight0, x0);
	SimBrakeConfig(hdle, BrkSect[index], &(wheel->brake));

	carElt->_rimRadius(index) = rimdiam / 2.0f;
	carElt->_tireHeight(index) = tirewidth * tireratio;
	carElt->_tireWidth(index) = tirewidth;
	carElt->_brakeDiskRadius(index) = wheel->brake.radius;
	carElt->_wheelRadius(index) = wheel->radius;

	wheel->mfC = 2.0f - asin(RFactor) * 2.0f / PI;
	wheel->mfB = Ca / wheel->mfC;
	wheel->mfE = EFactor;

	wheel->lfK = log((1.0f - wheel->lfMin) / (wheel->lfMax - wheel->lfMin));

	wheel->feedBack.I += wheel->I;
	wheel->feedBack.spinVel = 0.0f;
	wheel->feedBack.Tq = 0.0f;
	wheel->feedBack.brkTq = 0.0f;
	wheel->rel_vel = 0.0f;

	// Additional parameters for the tire wear model
	wheel->treadThinkness	= GfParmGetNum(hdle, WheelSect[index], PRM_TREADTHICKNESS, (char*)NULL, 0.005f);		// default 5 [mm]
	tdble rimmass = GfParmGetNum(hdle, WheelSect[index], PRM_RIMMASS, (char*)NULL, 7.0f);							// default 7 [kg]
	wheel->hysteresisFactor = GfParmGetNum(hdle, WheelSect[index], PRM_HYSTERESIS, (char*)NULL, 1.0f);				// default 1.0 [-]
	wheel->wearFactor = GfParmGetNum(hdle, WheelSect[index], PRM_WEAR, (char*)NULL, 1.0f);							// default 1.0 [-]
	wheel->idealTemperature = GfParmGetNum(hdle, WheelSect[index], PRM_IDEALTEMP, (char*)NULL, 95.0f + 273.15f);	// default 95°C

	carElt->info.wheel[index].idealTemperature = wheel->idealTemperature;
	
	const tdble rubberDensity = 930.0f;	// Density of Rubber (NR) in [kg/m^3].	
	wheel->treadMass = (2.0f*wheel->radius - wheel->treadThinkness)*PI*tirewidth*wheel->treadThinkness*rubberDensity;
	wheel->baseMass = wheel->mass - wheel->treadMass - rimmass;
	if (wheel->baseMass < 0.0f) {
		wheel->baseMass = 3.0f;
		GfError("Wheel mass minus tire tread mass minus rim mass is smaller than 0.0kg, setting it to 3.0 kg");
	}
	
	// Surface area for convection model
	tdble innerRadius = rimdiam / 2.0f;
	tdble tireSideArea = PI*(wheel->radius*wheel->radius - innerRadius*innerRadius);
	wheel->tireConvectionSurface = 2.0f*(PI*tirewidth*wheel->radius + tireSideArea);
	
	// Mass of gas in the tire m=P*V/(R*T)
	tdble temperature = 273.15f + 20.0f;		// Kelvin
	tdble volume = tireSideArea*tirewidth;		// meter*meter*meter
	tdble nitrogenR = 296.8f;					// Joule/(kg*Kelvin), N2
	
	wheel->tireGasMass = (wheel->pressure * volume) / (nitrogenR * temperature);	// kg

	wheel->initialTemperature = temperature;
	wheel->currentTemperature = temperature;

	wheel->currentWear = 0.0f;
	wheel->currentGraining = 0.0f;
	wheel->currentGripFactor = 1.0f;
}


void SimWheelReConfig(tCar *car, int index)
{
	tWheel *wheel = &(car->wheel[index]);

	// Camber
	tCarPitSetupValue* v = &car->carElt->pitcmd.setup.wheelcamber[index];
	if (SimAdjustPitCarSetupParam(v)) {
		wheel->staticPos.ax = v->value;
	}

	// Toe
	v = &car->carElt->pitcmd.setup.wheeltoe[index];
	if (SimAdjustPitCarSetupParam(v)) {
		wheel->staticPos.az = v->value;
	}

	// Caster
	v = &car->carElt->pitcmd.setup.wheelcaster[index];
	if (SimAdjustPitCarSetupParam(v)) {
		wheel->staticPos.ay = v->value;
	}

	// Ride height/suspension
	v = &car->carElt->pitcmd.setup.wheelrideheight[index];
	SimAdjustPitCarSetupParam(v);
	SimSuspReConfig(car, index, &(wheel->susp), wheel->weight0, v->value);
}


void SimWheelUpdateRide(tCar *car, int index)
{
	tWheel *wheel = &(car->wheel[index]);
	tdble Zroad;

	// compute suspension travel
	RtTrackGlobal2Local(car->trkPos.seg, wheel->pos.x, wheel->pos.y, &(wheel->trkPos), TR_LPOS_SEGMENT);
	RtTrackSurfaceNormalL(&(wheel->trkPos), &(wheel->surfaceNormal));
	wheel->zRoad = Zroad = RtTrackHeightL(&(wheel->trkPos));

	// Wheel susp.x is not the wheel movement, look at SimSuspCheckIn, it becomes there scaled with
	// susp->spring.bellcrank, so we invert this here.
	tdble prexwheel = wheel->susp.x / wheel->susp.spring.bellcrank;

	tdble new_susp_x = prexwheel - wheel->rel_vel * SimDeltaTime;
    tdble max_extend = (wheel->pos.z - Zroad)*wheel->surfaceNormal.z;
	wheel->rideHeight = max_extend;
	
	wheel->state &= ~SIM_WH_ONAIR;
	if (max_extend < new_susp_x) {
		new_susp_x = max_extend;
		wheel->rel_vel = 0.0f;
	} else if (new_susp_x < wheel->susp.spring.packers) {
		new_susp_x = wheel->susp.spring.packers;
		wheel->rel_vel = 0.0f;
	}
	
	if (new_susp_x < max_extend) {
		wheel->state |= SIM_WH_ONAIR;
	}
 
	tdble prex = wheel->susp.x;
	wheel->susp.x = new_susp_x;

	// verify the suspension travel, beware, wheel->susp.x will be scaled by SimSuspCheckIn
	SimSuspCheckIn(&(wheel->susp));
	wheel->susp.v = (prex - wheel->susp.x) / SimDeltaTime;
	
	// update wheel brake
	SimBrakeUpdate(car, wheel, &(wheel->brake));
}




void SimWheelUpdateForce(tCar *car, int index)
{
	tWheel *wheel = &(car->wheel[index]);
	tdble axleFz = wheel->axleFz;
	tdble vt, v, v2, wrl; // wheel related velocity
	tdble Fn, Ft;
	tdble waz;
	tdble CosA, SinA;
	tdble s, sa, sx, sy; // slip vector
	tdble stmp, F, Bx;
	tdble mu;
	wheel->state = 0;

	// VERTICAL STUFF CONSIDERING SMALL PITCH AND ROLL ANGLES
	// update suspension force
	SimSuspUpdate(&(wheel->susp));

	// check suspension state
	wheel->state |= wheel->susp.state;
	if ((wheel->state & SIM_SUSP_EXT) && wheel->rel_vel <= 0.0f) {
		wheel->forces.z = wheel->rel_vel/SimDeltaTime*wheel->mass;
		wheel->rel_vel = 0.0;
	} else {
		wheel->forces.z = axleFz + wheel->susp.force;
		wheel->rel_vel -= SimDeltaTime * wheel->forces.z / wheel->mass;
	}

	// update wheel coord, center relative to GC
	wheel->relPos.z = - wheel->susp.x / wheel->susp.spring.bellcrank + wheel->radius;

	// Wheel contact with the ground can just push the car upwards, but not drag it towards the ground.
	// Because forces.z includes the inertia of the wheel, the wheel force can act on the car body
	// without interacting with the ground.
	tdble zforce = wheel->forces.z;
	if ((zforce < 0.0f) || (wheel->state & SIM_WH_ONAIR)) {
		zforce = 0.0f;
	}

	// HORIZONTAL FORCES
	waz = wheel->steer + wheel->staticPos.az;
	CosA = cos(waz);
	SinA = sin(waz);

	// tangent velocity.
	vt = wheel->bodyVel.x * CosA + wheel->bodyVel.y * SinA;
	v2 = wheel->bodyVel.x * wheel->bodyVel.x + wheel->bodyVel.y * wheel->bodyVel.y;
	v = sqrt(v2);

	// slip angle
	if (v < 0.000001f) {
		sa = 0.0f;
	} else {
		sa = atan2(wheel->bodyVel.y, wheel->bodyVel.x) - waz;
	}
	NORM_PI_PI(sa);

	wrl = wheel->spinVel * wheel->radius;
	if ((wheel->state & SIM_WH_ONAIR) != 0) {
		sx = sy = 0.0f;
	} else if (v < 0.000001f) {
		sx = wrl;
		sy = 0.0f;
	} else {
		sx = (vt - wrl) / fabs(vt);
		sy = sin(sa);
	}
	
	Ft = 0.0f;
	Fn = 0.0f;
	s = sqrt(sx*sx+sy*sy);

	{
		// calculate _skid and _reaction for sound.
		if (v < 2.0f) {
			car->carElt->_skid[index] = 0.0f;
		} else {
			car->carElt->_skid[index] =  MIN(1.0f, (s*zforce*0.0002f));
		}
	}

	tdble casterCamber = sin(wheel->staticPos.ay)*wheel->steer;
	tdble camberDelta;
	if (index % 2) {
		wheel->relPos.ax = -wheel->staticPos.ax - casterCamber;
		camberDelta = -casterCamber;
	} else {
		wheel->relPos.ax = wheel->staticPos.ax - casterCamber;
		camberDelta = casterCamber;
	}

	stmp = MIN(s, 1.5f);
	
	// MAGIC FORMULA
	Bx = wheel->mfB * stmp;
	F = sin(wheel->mfC * atan(Bx * (1.0f - wheel->mfE) + wheel->mfE * atan(Bx))) * (1.0f + stmp * simSkidFactor[car->carElt->_skillLevel]);

	// load sensitivity
	mu = wheel->mu * (wheel->lfMin + (wheel->lfMax - wheel->lfMin) * exp(wheel->lfK * zforce / wheel->opLoad));

	F *= zforce * mu * wheel->trkPos.seg->surface->kFriction * (1.0f + 0.05f * sin((-wheel->staticPos.ax + camberDelta) * 18.0f));	/* coeff */
	F *= wheel->currentGripFactor;
	
	wheel->rollRes = zforce * wheel->trkPos.seg->surface->kRollRes;
    car->carElt->priv.wheel[index].rollRes = wheel->rollRes;

	if (s > 0.000001f) {
		// wheel axis based
		Ft -= F * sx / s;
		Fn -= F * sy / s;
	}

	RELAXATION2(Fn, wheel->preFn, 50.0f);
	RELAXATION2(Ft, wheel->preFt, 50.0f);

	wheel->relPos.az = waz;
	
	wheel->forces.x = Ft * CosA - Fn * SinA;
	wheel->forces.y = Ft * SinA + Fn * CosA;
	wheel->spinTq = Ft * wheel->radius;
	wheel->sa = sa;
	wheel->sx = sx;

	wheel->tireZForce = zforce;
	wheel->tireSlip = stmp;

	wheel->feedBack.spinVel = wheel->spinVel;
	wheel->feedBack.Tq = wheel->spinTq;
	wheel->feedBack.brkTq = wheel->brake.Tq;

	car->carElt->_wheelSlipSide(index) = sy*v;
	car->carElt->_wheelSlipAccel(index) = sx*v;
	car->carElt->_reaction[index] = zforce;
}


void
SimWheelUpdateRotation(tCar *car)
{
	int i;
	tWheel *wheel;

	for (i = 0; i < 4; i++) {
		wheel = &(car->wheel[i]);
		wheel->spinVel = wheel->in.spinVel;

		RELAXATION2(wheel->spinVel, wheel->prespinVel, 50.0f);

		wheel->relPos.ay += wheel->spinVel * SimDeltaTime;
		NORM_PI_PI(wheel->relPos.ay);
		car->carElt->_wheelSpinVel(i) = wheel->spinVel;
	}
}


void
SimUpdateFreeWheels(tCar *car, int axlenb)
{
	int i;
	tWheel *wheel;
	tdble BrTq;		// brake torque
	tdble ndot;		// rotation acceleration
	tdble I;

	for (i = axlenb * 2; i < axlenb * 2 + 2; i++) {
		wheel = &(car->wheel[i]);

		I = wheel->I + car->axle[axlenb].I / 2.0f;

		ndot = SimDeltaTime * wheel->spinTq / I;
		wheel->spinVel -= ndot;

		BrTq = - SIGN(wheel->spinVel) * wheel->brake.Tq;
		ndot = SimDeltaTime * BrTq / I;

		if (fabs(ndot) > fabs(wheel->spinVel)) {
			ndot = -wheel->spinVel;
		}

		wheel->spinVel += ndot;
		wheel->in.spinVel = wheel->spinVel;
	}
}


void SimWheelUpdateTire(tCar *car, int index) {
	if (!(rulesTireFactor > 0.0f) || car->carElt->info.skillLevel != 3) {
		return;
	}
	
	tWheel *wheel = &(car->wheel[index]);
	
	tdble normalForce = wheel->tireZForce;
	tdble slip = wheel->tireSlip;
	
	tdble wheelSpeed = fabs(wheel->spinVel*wheel->radius);
	tdble deltaTemperature = wheel->currentTemperature - car->localTemperature;
	
	// Calculate factor for energy which is turned into heat, according papers this seems to be pretty constant
	// for a specific construction and constant slip (empiric value with model validation, called hysteresis).
	// A value of 0.1 is available in papers, so for 10% slip I head for 0.1, where 0.05 come from rolling and
	// the other 0.05 from slip. Additionaly the hysteresis goes down with wear.	
	tdble elasticity = (wheel->pressure - car->localPressure)/(wheel->currentPressure - car->localPressure);
	tdble hysteresis = (0.05f*(sqrt(1.0f - wheel->currentWear))*elasticity + 0.5f*slip)*wheel->hysteresisFactor;
	
	// Calculate energy input for the tire
	tdble energyGain = normalForce*wheelSpeed*SimDeltaTime*hysteresis;
	
	// Calculate energy loss of the tire (convection, convection model approximation from papers, 
	// 5.9f + airspeed*3.7f [W/(meter*meter*Kelvin)]). Because the model is linear it is reasonable to apply
	// it to the whole tire at once (no subdivision in elements).
	tdble energyLoss = (5.9f + wheelSpeed*3.7f)*deltaTemperature*wheel->tireConvectionSurface*SimDeltaTime;
	
	tdble deltaEnergy = energyGain - energyLoss;
	
	// Calculate heat capacity. Basically the heat capacity of the gas in the tire accounts for a "normal" TORCS tire
	// around 2 percent of the whole tire heat capacity, so one could neglect this. I put it into the model because it:
	// - is more than 1 percent
	// - you could think of some tire build where this ratio is significantly higher (e.g. 4 percent)
	//
	// Because the tire is a sufficiently rigid volume we assume for the isochoric process (constant volume, variable
	// pressure and temperature).
	//
	// Material properties: The heat capacity of nitorgen N2 is "almost" constant over our temperature ranges:
	// 29.1 (at 25°C) vs 29.3 (at 100°C) [J/(mol*Kelvin)]. So this is assumed constant, error less than 1 percent.
	// But this does not apply for Rubber (NR):
	// 1.982 (at 20°C) [J/(g*Kelvin)] vs 2.121 (at 100°C), so this is more than 6 percent.
	tdble tireCelsius = wheel->currentTemperature - 273.15f;
	tdble cpRubber = 2009.0f - 1.962f*tireCelsius + 3.077f*tireCelsius*tireCelsius/100.0f;
	
	// Calculate the actual rubber mass. This is some base mass (constant) plus the mass of the tread (dynamic,
	// wears down).
	tdble actualRubberMass = wheel->treadMass*(1.0f - wheel->currentWear) + wheel->baseMass;
	
	// Calculate actual heat capacity
	const tdble cvNitrogen = 1041.0f - 296.8f;	// cv = cp - R, [J/(kg*Kelvin)]
	tdble heatCapacity = cpRubber * actualRubberMass + cvNitrogen * wheel->tireGasMass;
	
	// Energy transfer into the tire
	wheel->currentTemperature += deltaEnergy/heatCapacity;
	wheel->currentPressure = wheel->currentTemperature/wheel->initialTemperature*wheel->pressure;
	
	// Wear
	double deltaWear = (wheel->currentPressure - car->localPressure)*slip*wheelSpeed*SimDeltaTime*normalForce*wheel->wearFactor*0.00000000000009;
	
	wheel->currentWear += deltaWear*rulesTireFactor;
	if (wheel->currentWear > 1.0f) wheel->currentWear = 1.0f;
	
	// Graining
	tdble grainTemperature = (wheel->idealTemperature - wheel->initialTemperature)*3.0f/4.0f + wheel->initialTemperature;
	tdble deltaGraining = (grainTemperature - wheel->currentTemperature)*deltaWear;
	if (deltaGraining > 0.0f) {
		deltaGraining *= wheel->currentWear; 
	}
	
	wheel->currentGraining += deltaGraining;
	if (wheel->currentGraining > 1.0f) {
		wheel->currentGraining = 1.0f;
	} else if(wheel->currentGraining < 0.0f) {
		wheel->currentGraining = 0.0f;
	}
	
	tdble di = (wheel->currentTemperature - wheel->idealTemperature)/(wheel->idealTemperature - wheel->initialTemperature);
	wheel->currentGripFactor = ((1.0f-(MIN((di*di), 1.0f)))/4.0f + 3.0f/4.0f)*(1.0f - wheel->currentGraining/10.0f);
}


void
SimWheelResetWear(tCar *car, int index)
{
	tWheel *wheel = &(car->wheel[index]);
	
	wheel->currentPressure = wheel->pressure;
	wheel->currentTemperature = car->localTemperature;
	wheel->currentWear = 0.0f;
	wheel->currentGraining = 0.0f;
	wheel->currentGripFactor = 1.0f;
}
