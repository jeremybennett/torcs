/***************************************************************************

    file                 : mycar.cpp
    created              : Mon Oct 10 13:51:00 CET 2001
    copyright            : (C) 2001-2002 by Bernhard Wymann
    email                : berniw@bluewin.ch
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

/*
	this class holds some properties of the car
*/

#include "mycar.h"


MyCar::MyCar(TrackDesc* track, tCarElt* car, tSituation *situation)
{
	/* init pointer to car data */
	setCarPtr(car);

	initCGh();
	updatePos();
	updateDir();

	/* damage and fuel status */
	lastfuel = GfParmGetNum(car->_carHandle, SECT_CAR, PRM_FUEL, NULL, 100.0);
	undamaged = situation->_maxDammage;
	if (undamaged == 0) undamaged = 10000;
	MAXDAMMAGE = undamaged / 2;
	fuelperlap = 0.0;
	lastpitfuel = 0.0;

	/* set up some car properties */
	wheelbase = car->priv->wheel[FRNT_RGT].relPos.x - car->priv->wheel[REAR_RGT].relPos.x;
	wheeltrack = 2* fabs(car->priv->wheel[REAR_RGT].relPos.y);

	carmass = GfParmGetNum(car->_carHandle, SECT_CAR, PRM_MASS, NULL, 0.0);
	mass = carmass + lastfuel;

	/* which wheels are driven */
	char *traintype = GfParmGetStr(car->_carHandle, SECT_DRIVETRAIN, PRM_TYPE, VAL_TRANS_RWD);
	if (strcmp(traintype, VAL_TRANS_RWD) == 0) {
		drivetrain = DRWD;
	} else if (strcmp(traintype, VAL_TRANS_FWD) == 0) {
		drivetrain = DFWD;
	} else if (strcmp(traintype, VAL_TRANS_4WD) == 0) {
		drivetrain = D4WD;
	}

	/* guess aerodynamic downforce coefficient from the wings */
	tdble frontwingarea = GfParmGetNum(car->_carHandle, SECT_FRNTWING, PRM_WINGAREA, (char*)NULL, 0);
    tdble frontwingangle = GfParmGetNum(car->_carHandle, SECT_FRNTWING, PRM_WINGANGLE, (char*)NULL, 0);
	tdble rearwingarea = GfParmGetNum(car->_carHandle, SECT_REARWING, PRM_WINGAREA, (char*)NULL, 0);
    tdble rearwingangle = GfParmGetNum(car->_carHandle, SECT_REARWING, PRM_WINGANGLE, (char*)NULL, 0);

	ca = AEROMAGIC*1.23*(frontwingarea*sin(frontwingangle) + rearwingarea*sin(rearwingangle));

	tdble cx = GfParmGetNum(car->_carHandle, SECT_AERODYNAMICS, PRM_CX, (char*)NULL, 0.0);
	tdble frontarea = GfParmGetNum(car->_carHandle, SECT_AERODYNAMICS, PRM_FRNTAREA, (char*)NULL, 0.0);

	cw = 0.625*cx*frontarea;

	cgcorr_b = 0.46;

	pf = new Pathfinder(track, car);
	currentsegid = destsegid = pf->getCurrentSegment(car);

	currentseg = track->getSegmentPtr(currentsegid);
	destseg = track->getSegmentPtr(destsegid);
	currentpathseg = pf->getPathSeg(currentsegid);
	destpathseg = pf->getPathSeg(destsegid);

	count = 25;
	turnaround = 0.0;
    tr_mode = 0;
	accel = 0;
	fuelchecked = false;
	startmode = true;
	trtime = 0.0;

	/*
		DIST; MAXRELAX; MAXANGLE; ACCELINC; MININVSLIP; SFTUPRATIO; SFTDOWNRATIO; SFTDOWNSTEER;
		SPEEDSQRFACTOR; GCTIME; ACCELLIMIT; PATHERRFACTOR
	*/

	tdble ba[6][12] = {
		{0.5, 0.9, 25.0, 0.1, 0.8, 0.78, 0.7, 0.05, 1.2, 0.2, 1.0, 5.0},
		{0.5, 0.9, 20.0, 0.1, 0.85, 0.8, 0.7, 0.05, 1.1, 0.5, 1.0, 5.0},
		{0.5, 0.9, 15.0, 0.02, 0.85, 0.8, 0.7, 0.05, 1.0, 0.5, 1.0, 5.0},
		{0.9, 0.9, 15.0, 0.02, 0.9, 0.8, 0.7, 0.05, 0.98, 0.5, 1.0, 5.0},
		{1.4, 0.9, 15.0, 0.01, 0.9, 0.75, 0.7, 0.05, 0.95, 0.5, 1.0, 5.0},
		{0.9, 0.9, 45.0, 0.1, 0.75, 0.82, 0.7, 0.05, 1.1, 0.5, 1.0, 1.0}
	};

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 12; j++) {
			behaviour[i][j] = ba[i][j];
		}
	}

	loadBehaviour(NORMAL);

	/* this call is needed! perhaps i shold move it into the constructor of pathfinder. */
	pf->plan(this);
}


MyCar::~MyCar()
{
	delete pf;
}


/*
	info for debugging
*/
void MyCar::info(void)
{
	printf("wheelbase: %f\n", wheelbase);
	printf("wheeltrack: %f\n", wheeltrack);
	for (int i = 0; i < MAX_GEARS; i++) {
			printf("%d\t%f\n", i, getCarPtr()->_gearRatio[i]);
	}
	printf("Offset: %d\n", getCarPtr()->_gearOffset);
	printf("#gears: %d\n", getCarPtr()->_gearNb);
	printf("gear: %d\n", getCarPtr()->_gear);
	printf("steerlock: %f rad, %f°\n", getCarPtr()->_steerLock, getCarPtr()->_steerLock * 180 / PI);
	printf("cgcorr_b: %f\n", cgcorr_b);
	printf("car index: %d\n", getCarPtr()->index);
	printf("race nb: %d\n", getCarPtr()->_raceNumber);
}


/*
	updates values needed from driver, pathfinder, etc. the are stored here, that we don't need to compute
	them several times or pass tons of parameters.
*/
void MyCar::update(TrackDesc* track, tCarElt* car, tSituation *situation)
{
	/* update current position */
	updatePos();
	updateDir();

	/* compute current speed */
	speedsqr = (car->_speed_x)*(car->_speed_x) + (car->_speed_y)*(car->_speed_y) + (car->_speed_z)*(car->_speed_z);
	speed = sqrt(speedsqr);

	/* update currentsegment and destination segment id's */
	int searchrange = MAX((int) ceil(situation->deltaTime*speed+1.0) * 2, 4);
	currentsegid = destsegid = pf->getCurrentSegment(car, searchrange);
	tdble l = 0.0;

	while (l < 2.0 * wheelbase) {
		l = l + pf->getPathSeg(destsegid)->getLength();
		destsegid = (destsegid + 1 + pf->getnPathSeg()) % pf->getnPathSeg();
	}

	currentseg = track->getSegmentPtr(currentsegid);
	destseg = track->getSegmentPtr(destsegid);
	currentpathseg = pf->getPathSeg(currentsegid);
	destpathseg = pf->getPathSeg(destsegid);

	mass = carmass + car->priv->fuel;

	/* compute the distance from the current position to the trajectory */
	derror =  track->distGFromPoint(pf->getPathSeg(currentsegid)->getLoc(), pf->getPathSeg(currentsegid)->getDir(), &currentpos);

	trtime += situation->deltaTime;
}


void MyCar::loadBehaviour(int id) {
	bmode = id;
	DIST = behaviour[id][0];
	MAXRELAX = behaviour[id][1];
	MAXANGLE = behaviour[id][2];
	ACCELINC = behaviour[id][3];
	MININVSLIP = behaviour[id][4];
	SFTUPRATIO = behaviour[id][5];
	SFTDOWNRATIO = behaviour[id][6];
	SFTDOWNSTEER = behaviour[id][7];
	SPEEDSQRFACTOR = behaviour[id][8];
	GCTIME = behaviour[id][9];
	ACCELLIMIT = behaviour[id][10];
	PATHERRFACTOR = behaviour[id][11];
}


/*
	compute the inverse of the rear => speed == 0 is allowed
*/
tdble MyCar::queryInverseSlip(tCarElt * car, tdble speed)
{
	tdble s;
	switch (drivetrain) {
		case DRWD:
			s = (car->_wheelSpinVel(REAR_RGT) +
				 car->_wheelSpinVel(REAR_LFT)) * car->_wheelRadius(REAR_LFT) / 2.0;
			break;
		case DFWD:
			s = (car->_wheelSpinVel(FRNT_RGT) +
				 car->_wheelSpinVel(FRNT_LFT)) * car->_wheelRadius(FRNT_LFT) / 2.0;
			break;
		case D4WD:
			s = ((car->_wheelSpinVel(REAR_RGT) +
				  car->_wheelSpinVel(REAR_LFT)) * car->_wheelRadius(REAR_LFT) +
				 (car->_wheelSpinVel(FRNT_RGT) +
				  car->_wheelSpinVel(FRNT_LFT)) * car->_wheelRadius(FRNT_LFT)) / 4.0;
			break;
		default:
			s = speed;
			break;
	}
	if (fabs(s) < TURNSPEED) return 1.0; return fabs(speed / s);
}


/*
	compute an acceleration value for a given speed
*/
tdble MyCar::queryAcceleration(tCarElt * car, tdble speed)
{
	tdble a, gr = car->_gearRatio[car->_gear + car->_gearOffset], rm = car->_enginerpmMax;
	switch (drivetrain) {
		case DRWD:
			a = speed / car->_wheelRadius(REAR_RGT) * gr / rm;
			break;
		case DFWD:
			a = speed / car->_wheelRadius(FRNT_RGT) * gr / rm;
			break;
		case D4WD:
			a = speed / (car->_wheelRadius(REAR_RGT) + car->_wheelRadius(FRNT_RGT)) * 2.0 * gr / rm;
			break;
		default:
			a = 1.0;
			break;
	}
	if (a > 1.0) return 1.0; else return a;
}


void OtherCar::init(TrackDesc* itrack, tCarElt* car, tSituation *situation)
{
	track = itrack;
	dt = situation->deltaTime;
	setCarPtr(car);
	currentsegid = track->getCurrentSegment(car);

	initCGh();
	updatePos();
	updateDir();
	updateSpeedSqr();
	updateSpeed();
}


void OtherCar::update()
{
	updatePos();
	updateDir();
	updateSpeedSqr();
	updateSpeed();

    int searchrange = MAX((int) ceil(dt*speed+1.0) * 2, 4);
	currentsegid = track->getCurrentSegment(getCarPtr(), currentsegid, searchrange);
}

