/***************************************************************************

    file                 : berniw.cpp
    created              : Mon Apr 17 13:51:00 CET 2000
    copyright            : (C) 2000, 2001 by Bernhard Wymann
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


#include "berniw.h"


/* function prototypes */
static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation * situation);
static void drive(int index, tCarElt* car, tSituation *situation);
static void newrace(int index, tCarElt* car, tSituation *situation);
static int  InitFuncPt(int index, void *pt);
static int  pitcmd(int index, tCarElt* car, tSituation *s);
static void shutdown(void);


/* Module entry point */
extern "C" int berniw(tModInfo *modInfo)
{
    char	buffer[BUFSIZE];

    for (int i = 0; i < BOTS; i++) {
		sprintf(buffer, "berniw %d", i+1);
		modInfo[i].name = strdup(buffer);		/* name of the module (short) */
		sprintf(buffer, "berniw %d", i+1);
		modInfo[i].desc    = strdup(buffer);	/* description of the module (can be long) */
		modInfo[i].fctInit = InitFuncPt;		/* init function */
		modInfo[i].gfId    = ROB_IDENT;			/* supported framework version */
		modInfo[i].index   = i+1;
    }
    return 0;
}


/* initialize function pointers for torcs */
static int InitFuncPt(int index, void *pt)
{
    tRobotItf *itf = (tRobotItf *)pt;

    itf->rbNewTrack = initTrack;	/* init new track */
    itf->rbNewRace  = newrace;		/* init new race */
    itf->rbDrive    = drive;		/* drive during race */
	itf->rbShutdown	= shutdown;		/* called for cleanup per driver */
	itf->rbPitCmd   = pitcmd;		/* pit command */
	itf->index      = index;
    return 0;
}


static MyCar* mycar[BOTS] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
static OtherCar* ocar = NULL;
static TrackDesc* myTrackDesc = NULL;
static double currenttime;

static const tdble g = 9.81;
static const tdble waitToTurn = 1.0; /* how long should i wait till i try to turn backwards */


/* release resources when the module gets unloaded */
static void shutdown(void) {
	for (int i = 0; i < BOTS; i++) {
		if (mycar[i] != NULL) {
			delete mycar[i];
			mycar[i] = NULL;
		}
	}
	if (myTrackDesc != NULL) {
		delete myTrackDesc;
		myTrackDesc = NULL;
	}
	if (ocar != NULL) {
		delete ocar;
		ocar = NULL;
	}
}


/* initialize track data */
static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation * situation)
{
	if ((myTrackDesc != NULL) && (myTrackDesc->getTorcsTrack() != track)) {
		delete myTrackDesc;
		myTrackDesc = NULL;
	}
	if (myTrackDesc == NULL) {
		myTrackDesc = new TrackDesc(track);
		//myTrackDesc->plot("/home/berni/new.dat");
	}

	char buffer[BUFSIZE];
	char* trackname = strrchr(track->filename, '/') + 1;

	sprintf(buffer, "drivers/berniw/%d/%s", index, trackname);
    *carParmHandle = GfParmReadFile(buffer, GFPARM_RMODE_STD);
}


/* initialize driver for the race */
static void newrace(int index, tCarElt* car, tSituation *situation)
{
	if (ocar != NULL) delete ocar;
	ocar = new OtherCar[situation->_ncars];
	for (int i = 0; i < situation->_ncars; i++) {
		ocar[i].init(myTrackDesc, situation->cars[i], situation);
	}

	if (mycar[index-1] != NULL) delete mycar[index-1];
	mycar[index-1] = new MyCar(myTrackDesc, car, situation);

	currenttime = situation->currentTime;
}


/* controls the car */
static void drive(int index, tCarElt* car, tSituation *situation)
{
    tdble	angle;
    tdble	tmp;
	tdble b1;							/* brake value in case we are to fast HERE and NOW */
	tdble b2;							/* brake value for some brake point in front of us */
	tdble b3;							/* brake value for control (avoid loosing control) */
    tdble	rpm;
	tdble	abs[4], abs_mean;
	tdble steer, targetAngle, shiftaccel;

	MyCar* myc = mycar[index-1];
	Pathfinder* mpf = myc->pf;

	b1 = 0.0; b2 = 0.0; b3 = 0.0; shiftaccel = 0.0;

	/* update some values needed */
	myc->update(myTrackDesc, car, situation);

	/* decide how we want to drive */
	if ( car->_dammage < myc->undamaged/3 && myc->bmode != myc->NORMAL) {
		myc->loadBehaviour(myc->NORMAL);
	} else if (car->_dammage > myc->undamaged/3 && car->_dammage < (myc->undamaged*2)/3 && myc->bmode != myc->CAREFUL) {
		myc->loadBehaviour(myc->CAREFUL);
	} else if (car->_dammage > (myc->undamaged*2)/3 && myc->bmode != myc->SLOW) {
		myc->loadBehaviour(myc->SLOW);
	}

	/* update the other cars just once */
	if (currenttime != situation->currentTime) {
		currenttime = situation->currentTime;
		for (int i = 0; i < situation->_ncars; i++) ocar[i].update();
	}

	/* startmode */
	if (myc->trtime < 5.0 && myc->bmode != myc->START) {
		myc->loadBehaviour(myc->START);
		myc->startmode = true;
	}
	if (myc->startmode && myc->trtime > 5.0) {
		myc->startmode = false;
		myc->loadBehaviour(myc->NORMAL);
	}

	/* compute path according to the situation */
	mpf->plan(myc->currentsegid, car, situation, myc, ocar);

	/* clear ctrl structure with zeros and set the current gear */
	memset(car->ctrl, 0, sizeof(tCarCtrl));
	car->ctrl->gear = car->_gear;

	/* uncommenting the following line causes pitstop on every lap */
	//if (!mpf->getPitStop()) mpf->setPitStop(true, myc->currentsegid);
	/* compute fuel consumption */
	if (myc->currentsegid >= 0 && myc->currentsegid < 5 && !myc->fuelchecked) {
		if (car->race->laps > 0) {
			myc->fuelperlap = MAX(myc->fuelperlap, (myc->lastfuel+myc->lastpitfuel-car->priv->fuel));
		}
		myc->lastfuel = car->priv->fuel;
		myc->lastpitfuel = 0.0;
		myc->fuelchecked = true;
	} else if (myc->currentsegid > 5) {
		myc->fuelchecked = false;
	}

	/* decide if we need a pit stop */
	if (!mpf->getPitStop() && car->_remainingLaps > 0 && (car->_dammage > myc->MAXDAMMAGE ||
		(car->priv->fuel < 1.5*myc->fuelperlap &&
		 car->priv->fuel < (car->_remainingLaps-car->_lapsBehindLeader)*myc->fuelperlap)))
	{
		mpf->setPitStop(true, myc->currentsegid);
	}

	if (myc->speedsqr > myc->currentpathseg->getSpeedsqr()) {
		b1 = (myc->speedsqr - myc->currentpathseg->getSpeedsqr()) / (myc->speedsqr);
	}
	if (mpf->getPitStop()) {
		car->ctrl->raceCmd = RM_CMD_PIT_ASKED;
		//printf("berniw %d, time: %f\n", index, situation->currentTime);
	}

	/* steer to next target point */
	targetAngle = atan2(myc->destpathseg->getLoc()->y - car->_pos_Y, myc->destpathseg->getLoc()->x - car->_pos_X);
    targetAngle -= car->_yaw;
	NORM_PI_PI(targetAngle);
    steer = targetAngle / car->_steerLock;

	/* brakes */
    tdble brakecoeff = 1.0/(2.0*g*myc->currentseg->getKfriction()/**myc->cgcorr_b*/);
    tdble brakespeed, brakedist;
	tdble lookahead = 0.0;
	int i = myc->currentsegid;
	tmp = 0.0;

	while (lookahead < brakecoeff * myc->speedsqr) {
		lookahead += mpf->getPathSeg(i)->getLength();
		brakespeed = myc->speedsqr - mpf->getPathSeg(i)->getSpeedsqr();
		if (brakespeed > 0.0) {
			tdble gm, qb, qs;
			gm = myTrackDesc->getSegmentPtr(myc->currentsegid)->getKfriction();
			qs = mpf->getPathSeg(i)->getSpeedsqr();
			brakedist = brakespeed*(myc->mass/(2.0*gm*g*myc->mass + (qs)*(gm*myc->ca + myc->cw)));

			if (brakedist > lookahead - myc->wheeltrack) {
				qb = brakespeed*brakecoeff/brakedist;
				if (qb > b2) {
					b2 = qb;
				}
			}
		}
		i = (i + 1 + mpf->getnPathSeg()) % mpf->getnPathSeg();
	}

	/* check if we are on the way */
	tdble ax = myc->currentpathseg->getDir()->x;
	tdble ay = myc->currentpathseg->getDir()->y;
	tdble bx = cos(car->_yaw), by = sin(car->_yaw);
	tdble back = (ax*bx + ay*by) / (sqrt(ax*ax + ay*ay)*sqrt(bx*bx + by*by));

	if (myc->speed > myc->TURNSPEED && myc->tr_mode == 0) {
		targetAngle = atan2(myc->destpathseg->getDir()->y, myc->destpathseg->getDir()->x);
		targetAngle -= car->_yaw;
		NORM_PI_PI(targetAngle);
		if (myc->derror > myc->PATHERR) {
			b3 = (myc->speed/myc->STABLESPEED)*(myc->derror-myc->PATHERR)/myc->currentseg->getWidth();
			tdble de = (myc->derror-myc->PATHERR) > myc->MAXRELAX ? -myc->MAXRELAX : -(myc->derror-myc->PATHERR);
			steer = steer * exp(de) + (1.0 - exp(de)) * targetAngle / car->_steerLock;
			if (acos(back) > PI*myc->MAXANGLE/180.0) {
				b3 += (myc->speed/myc->STABLESPEED)*acos(back-PI*myc->MAXANGLE/180.0);
			}
		}
	}

	if (b1 > b2) tmp = b1; else tmp = b2;
	if (tmp < b3) tmp = b3;


	abs_mean = 0.0;
	for (int i = 0; i < 4; i++) {
			abs[i] = (car->_wheelSpinVel(i) * car->_wheelRadius(i)) / myc->speed;
			abs_mean += abs[i];
		}
	abs_mean /= 4;
    tmp = tmp * abs_mean * abs_mean;

	rpm = (car->_enginerpm / car->_enginerpmMax);

	bx = cos(car->_yaw), by = sin(car->_yaw);
	tdble cx = myc->currentseg->getMiddle()->x - car->_pos_X, cy = myc->currentseg->getMiddle()->y - car->_pos_Y;
	tdble parallel = (cx*bx + cy*by) / (sqrt(cx*cx + cy*cy)*sqrt(bx*bx + by*by));

	//tdble cx = mpf->getPathSeg(myc->currentsegid)->getDir()->x;
	//tdble cy = mpf->getPathSeg(myc->currentsegid)->getDir()->y;
	//tdble parallel = (cx*bx + cy*by) / (sqrt(cx*cx + cy*cy)*sqrt(bx*bx + by*by));

	if (((car->_gear + car->_gearOffset) <= 1) && (myc->tr_mode == 0) && (myc->count >= 25)) {
		car->ctrl->gear++;
	}

	if ((rpm > myc->SFTUPRATIO) && (myc->count >= 25) && (myc->tr_mode == 0)) {
		if (car->_gear < car->_gearNb - 1) {
			shiftaccel = myc->speed / car->_wheelRadius(REAR_RGT) * car->_gearRatio[car->_gear + car->_gearOffset + 1] / car->_enginerpmMax;
			car->ctrl->gear++;
			myc->count = 0;
		}
	} else if ((myc->speed < myc->SFTDOWNRATIO * car->_wheelRadius(REAR_RGT) * car->_enginerpmMax/car->_gearRatio[car->_gear + car->_gearOffset - 1]) && (myc->count >= 25) && (myc->tr_mode == 0)) {
		if (car->_gear > 1) {
			shiftaccel = (myc->speed * car->_gearRatio[car->_gear + car->_gearOffset - 1]) / (car->_wheelRadius(REAR_RGT) * car->_enginerpm);
	        if (fabs(steer) < myc->SFTDOWNSTEER) {
				car->ctrl->gear--;
				myc->count = 0;
			}
		}
	}

	if (myc->tr_mode == 0) {
		if (tmp > 0.0) {
			myc->accel = 0.0;
			car->ctrl->accelCmd = myc->accel;
			car->ctrl->brakeCmd = tmp;
		} else {
			tdble invslip = myc->queryInverseSlip(car, myc->speed);
			if (invslip < myc->MININVSLIP) {
				tdble at = myc->queryAcceleration(car, myc->speed);
				if (myc->accel > at) myc->accel = at;
				car->ctrl->accelCmd = myc->accel;
			} else {
				if (myc->speedsqr < mpf->getPathSeg(myc->currentsegid)->getSpeedsqr()) {
					if (myc->accel < myc->ACCELLIMIT) myc->accel += myc->ACCELINC;
					car->ctrl->accelCmd = myc->accel;
				} else {
					if (myc->accel > 0.0) myc->accel -= myc->ACCELINC;
					car->ctrl->accelCmd = myc->accel = MIN(myc->accel, shiftaccel);
				}
			}
		}
    }

	if ((myc->speed < myc->TURNSPEED) && (parallel < cos(90.0*PI/180.0))  && (mpf->dist2D(&myc->currentpos, mpf->getPathSeg(myc->currentsegid)->getLoc()) > myc->TURNTOL)) {
		myc->turnaround += situation->deltaTime;
	} else myc->turnaround = 0.0;
	if ((myc->turnaround >= waitToTurn) || (myc->tr_mode >= 1)) {
		if (myc->tr_mode == 0) {
			myc->tr_mode = 1;
		}
        if ((car->_gear > -1) && (myc->tr_mode < 2)) {
			car->ctrl->accelCmd = 0.0;
			if (myc->tr_mode == 1) {
				car->ctrl->gear--;
			}
			car->ctrl->brakeCmd = 1.0;
		} else {
			myc->tr_mode = 2;
			if (parallel < cos(90.0*PI/180.0) && (mpf->dist2D(&myc->currentpos, mpf->getPathSeg(myc->currentsegid)->getLoc()) > myc->TURNTOL)) {
				angle = queryAngleToTrack(car);
				car->ctrl->steer = ( -angle > 0.0) ? 1.0 : -1.0;
				car->ctrl->brakeCmd = 0.0;
				tdble invslip = myc->queryInverseSlip(car, myc->speed);

				if (invslip < myc->MININVSLIP) {
					myc->accel = myc->queryAcceleration(car, myc->speed);
					car->ctrl->accelCmd = myc->accel;
				} else {
					if (myc->accel < 1.0) myc->accel += myc->ACCELINC;
					car->ctrl->accelCmd = myc->accel;
				}
			} else {
				if (myc->speed < 1.0) {
					myc->turnaround = 0;
					myc->tr_mode = 0;
					myc->loadBehaviour(myc->START);
					myc->startmode = true;
					myc->trtime = 0.0;
				}
				car->ctrl->brakeCmd = 1.0;
				car->ctrl->steer = 0.0;
				car->ctrl->accelCmd = 0.0;
			}
		}
	}

	if (myc->count < 25) myc->count++;
	if (myc->tr_mode == 0) car->ctrl->steer = steer;
}

static int pitcmd(int index, tCarElt* car, tSituation *s)
{
	MyCar* myc = mycar[index-1];
	Pathfinder* mpf = myc->pf;

	car->pitcmd->fuel = MAX(MIN((car->_remainingLaps+1.0)*myc->fuelperlap - car->_fuel, car->_tank - car->_fuel), 0.0);
	myc->lastpitfuel = MAX(car->pitcmd->fuel, 0.0);
	car->pitcmd->repair = car->_dammage;
	mpf->setPitStop(false, myc->currentsegid);
	myc->loadBehaviour(myc->START);
	myc->startmode = true;
	myc->trtime = 0.0;

	return ROB_PIT_IM; /* return immediately */
}

