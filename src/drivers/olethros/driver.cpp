/***************************************************************************

    file                 : driver.cpp
    created              : Thu Dec 20 01:21:49 CET 2002
    copyright            : (C) 2002-2004 Bernhard Wymann
                           (C) 2004 Christos Dimitrakakis
    email                : berniw@bluewin.ch
                           dimitrak@idiap.ch
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

/**
   \file driver.cpp
   
   \brief High-level driver implementation.

   This file is the same as Bernhard's driver.cpp for the BT robot,
   with added bits for learning.
*/
#include "driver.h"
#include "ann_policy.h"
#include "MathFunctions.h"

const float Driver::MAX_UNSTUCK_ANGLE = 15.0/180.0*PI;		// [radians] If the angle of the car on the track is smaller, we assume we are not stuck.
const float Driver::UNSTUCK_TIME_LIMIT = 2.0;				// [s] We try to get unstuck after this time.
const float Driver::MAX_UNSTUCK_SPEED = 5.0;				// [m/s] Below this speed we consider being stuck.
const float Driver::MIN_UNSTUCK_DIST = 3.0;					// [m] If we are closer to the middle we assume to be not stuck.
const float Driver::G = 9.81;								// [m/(s*s)] Welcome on Earth.
const float Driver::FULL_ACCEL_MARGIN = 1.0;				// [m/s] Margin reduce oscillation of brake/acceleration.
const float Driver::SHIFT = 0.9;							// [-] (% of rpmredline) When do we like to shift gears.
const float Driver::SHIFT_MARGIN = 4.0;						// [m/s] Avoid oscillating gear changes.
const float Driver::ABS_SLIP = 2.0;							// [m/s] range [0..10]
const float Driver::ABS_RANGE = 5.0;						// [m/s] range [0..10]
const float Driver::ABS_MINSPEED = 3.0;						// [m/s] Below this speed the ABS is disabled (numeric, division by small numbers).
const float Driver::TCL_SLIP = 2.0;							// [m/s] range [0..10]
const float Driver::TCL_RANGE = 10.0;						// [m/s] range [0..10]
const float Driver::LOOKAHEAD_CONST = 17.0;					// [m]
const float Driver::LOOKAHEAD_FACTOR = 0.33;				// [-]
const float Driver::WIDTHDIV = 3.0;							// [-] Defines the percentage of the track to use (2/WIDTHDIV).
const float Driver::SIDECOLL_MARGIN = 3.0;					// [m] Distance between car centers to avoid side collisions.
const float Driver::BORDER_OVERTAKE_MARGIN = 0.5;			// [m]
const float Driver::OVERTAKE_OFFSET_SPEED = 5.0;			// [m/s] Offset change speed.
const float Driver::PIT_LOOKAHEAD = 6.0;					// [m] Lookahead to stop in the pit.
const float Driver::PIT_BRAKE_AHEAD = 200.0;				// [m] Workaround for "broken" pitentries.
const float Driver::PIT_MU = 0.4;							// [-] Friction of pit concrete.
const float Driver::MAX_SPEED = 84.0;						// [m/s] Speed to compute the percentage of brake to apply.
const float Driver::MAX_FUEL_PER_METER = 0.0008;			// [liter/m] fuel consumtion.
const float Driver::CLUTCH_SPEED = 5.0;						// [m/s]
const float Driver::CENTERDIV = 0.1;						// [-] (factor) [0.01..0.6].
const float Driver::DISTCUTOFF = 200.0;						// [m] How far to look, terminate while loops.
const float Driver::MAX_INC_FACTOR = 5.0;					// [m] Increment faster if speed is slow [1.0..10.0].
const float Driver::CATCH_FACTOR = 10.0;					// [-] select MIN(catchdist, dist*CATCH_FACTOR) to overtake.
const float Driver::CLUTCH_FULL_MAX_TIME = 2.0;				// [s] Time to apply full clutch.
const float Driver::USE_LEARNED_OFFSET_RANGE = 0.2;			// [m] if offset < this use the learned stuff

// Static variables.
Cardata *Driver::cardata = NULL;
double Driver::currentsimtime;


Driver::Driver(int index)
{
	INDEX = index;
	seg_alpha = NULL;
}


Driver::~Driver()
{
	delete opponents;
	delete pit;
	delete [] radius;
	printf ("OK!!\n");
	delete [] seg_alpha;
	printf ("OK2!!\n");
	delete learn;
	printf ("OK3!!\n");
	delete strategy;
	printf ("OK4!!\n");
	if (cardata != NULL) {
		delete cardata;
		printf ("OK5!!\n");
		cardata = NULL;
	}
}


// Called for every track change or new race.
void Driver::initTrack(tTrack* t, void *carHandle, void **carParmHandle, tSituation *s)
{
	track = t;

	const int BUFSIZE = 256;
	char buffer[BUFSIZE];
	// Load a custom setup if one is available.
	// Get a pointer to the first char of the track filename.
	char* trackname = strrchr(track->filename, '/') + 1;

	switch (s->_raceType) {
		case RM_TYPE_PRACTICE:
			snprintf(buffer, BUFSIZE, "drivers/olethros/%d/practice/%s", INDEX, trackname);
			break;
		case RM_TYPE_QUALIF:
			snprintf(buffer, BUFSIZE, "drivers/olethros/%d/qualifying/%s", INDEX, trackname);
			break;
		case RM_TYPE_RACE:
			snprintf(buffer, BUFSIZE, "drivers/olethros/%d/race/%s", INDEX, trackname);
			break;
		default:
			break;
	}

	*carParmHandle = GfParmReadFile(buffer, GFPARM_RMODE_STD);
	if (*carParmHandle == NULL) {
		snprintf(buffer, BUFSIZE, "drivers/olethros/%d/default.xml", INDEX);
		*carParmHandle = GfParmReadFile(buffer, GFPARM_RMODE_STD);
    }

	// Create a pit stop strategy object.
	strategy = new SimpleStrategy();

	// Init fuel.
	strategy->setFuelAtRaceStart(t, carParmHandle, s);

	// Load and set parameters.
	MU_FACTOR = GfParmGetNum(*carParmHandle, OLETHROS_SECT_PRIV, OLETHROS_ATT_MUFACTOR, (char*)NULL, 0.69);

	prepareTrack();
}


// Start a new race.
void Driver::newRace(tCarElt* car, tSituation *s)
{
	float deltaTime = RCM_MAX_DT_ROBOTS;
	MAX_UNSTUCK_COUNT = int(UNSTUCK_TIME_LIMIT/deltaTime);
	OVERTAKE_OFFSET_INC = OVERTAKE_OFFSET_SPEED*deltaTime;
	stuck = 0;
	alone = 1;
	clutchtime = 0.0;
	oldlookahead = 0.0;
	this->car = car;
	CARMASS = GfParmGetNum(car->_carHandle, SECT_CAR, PRM_MASS, NULL, 1000.0);
	myoffset = 0.0;
	initCa();
	initCw();
	initTireMu();
	initTCLfilter();

	// Create just one instance of cardata shared by all drivers.
	if (cardata == NULL) {
		cardata = new Cardata(s);
	}
	mycardata = cardata->findCar(car);
	currentsimtime = s->currentTime;

	// initialize the list of opponents.
	opponents = new Opponents(s, this, cardata);
	opponent = opponents->getOpponentPtr();

	// Initialize radius of segments.
	radius = new float[track->nseg];
	computeRadius(radius);

	learn = new SegLearn(track);

	// create the pit object.
	pit = new Pit(s, this);
}


// Drive during race.
void Driver::drive(tSituation *s)
{
	memset(&car->ctrl, 0, sizeof(tCarCtrl));

	update(s);

	//pit->setPitstop(true);

	if (isStuck()) {
		car->_steerCmd = -mycardata->getCarAngle() / car->_steerLock;
		car->_gearCmd = -1;		// Reverse gear.
		car->_accelCmd = 1.0;	// 100% accelerator pedal.
		car->_brakeCmd = 0.0;	// No brakes.
		car->_clutchCmd = 0.0;	// Full clutch (gearbox connected with engine).
	} else {
		car->_steerCmd = filterSColl(getSteer()-0.1*learn->predictedError(car));
		car->_gearCmd = getGear();
		float fbrake = filterBrakeSpeed(getBrake());
		car->_brakeCmd = filterABS(filterBrakeSpeed(filterBColl(filterBPit(getBrake()))));
		if (car->_brakeCmd == 0.0) {
			car->_accelCmd = filterTCL(filterTrk(filterOverlap(getAccel())));
		} else {
			fbrake = - filterTrk(-fbrake);
			if (fbrake<0) fbrake = 0;
			fbrake = filterBColl(filterBPit(fbrake));
			car->_brakeCmd = 0.5 * (car->_brakeCmd + fbrake);
			car->_accelCmd = 0.0;
  		}
		car->_clutchCmd = getClutch();
		//printf ("%f %f\n", car->_steerCmd, learn->predictedError(car));
	}
}


// Set pitstop commands.
int Driver::pitCommand(tSituation *s)
{
	car->_pitRepair = strategy->pitRepair(car, s);
	car->_pitFuel = strategy->pitRefuel(car, s);
	// This should be the only place where the pit stop is set to false!
	pit->setPitstop(false);
	return ROB_PIT_IM; // return immediately.
}


// End of the current race.
void Driver::endRace(tSituation *s)
{
	// Nothing at the moment.
}


/***************************************************************************
 *
 * utility functions
 *
***************************************************************************/


void Driver::computeRadius(float *radius)
{
	float lastturnarc = 0.0;
	int lastsegtype = TR_STR;

	tTrackSeg *currentseg, *startseg = track->seg;
	currentseg = startseg;

	do {
		if (currentseg->type == TR_STR) {
			lastsegtype = TR_STR;
			radius[currentseg->id] = FLT_MAX;
		} else {
			if (currentseg->type != lastsegtype) {
				float arc = 0.0;
				tTrackSeg *s = currentseg;
				lastsegtype = currentseg->type;

				while (s->type == lastsegtype && arc < PI/2.0) {
					arc += s->arc;
					s = s->next;
				}
				lastturnarc = arc/(PI/2.0);
			}
			radius[currentseg->id] = (currentseg->radius + currentseg->width/2.0)/lastturnarc;
		}
		currentseg = currentseg->next;
	} while (currentseg != startseg);

}


// Compute the allowed speed on a segment.
float Driver::getAllowedSpeed(tTrackSeg *segment)
{
	float mu = segment->surface->kFriction*TIREMU*MU_FACTOR;
	float r = radius[segment->id];
	float dr = learn->getRadius(segment);
	if ((alone > 0 && fabs(myoffset) < USE_LEARNED_OFFSET_RANGE) ||
		dr < 0.0
	) {
		r += dr;
	}
	return sqrt((mu*G*r)/(1.0 - MIN(1.0, r*CA*mu/mass)));
}


// Compute the length to the end of the segment.
float Driver::getDistToSegEnd()
{
	if (car->_trkPos.seg->type == TR_STR) {
		return car->_trkPos.seg->length - car->_trkPos.toStart;
	} else {
		return (car->_trkPos.seg->arc - car->_trkPos.toStart)*car->_trkPos.seg->radius;
	}
}


// Compute fitting acceleration.
float Driver::getAccel()
{
	if (car->_gear > 0) {
		float allowedspeed = getAllowedSpeed(car->_trkPos.seg);
		if (allowedspeed > car->_speed_x + FULL_ACCEL_MARGIN) {
			return 1.0;
		} else {
			float gr = car->_gearRatio[car->_gear + car->_gearOffset];
			float rm = car->_enginerpmRedLine;
			return allowedspeed/car->_wheelRadius(REAR_RGT)*gr /rm;
		}
	} else {
		return 1.0;
	}
}


// If we get lapped reduce accelerator.
float Driver::filterOverlap(float accel)
{
	int i;
	for (i = 0; i < opponents->getNOpponents(); i++) {
		if (opponent[i].getState() & OPP_LETPASS) {
			return MIN(accel, 0.5);
		}
	}
	return accel;
}


// Compute initial brake value.
float Driver::getBrake()
{
	// Car drives backward?
	if (car->_speed_x < -MAX_UNSTUCK_SPEED) {
		// Yes, brake.
		return 1.0;
	} else {
		// We drive forward, normal braking.
		tTrackSeg *segptr = car->_trkPos.seg;
		float mu = segptr->surface->kFriction;
		float maxlookaheaddist = currentspeedsqr/(2.0*mu*G);
		float lookaheaddist = getDistToSegEnd();

		float allowedspeed = getAllowedSpeed(segptr);
		if (allowedspeed < car->_speed_x) {
			return MIN(1.0, (car->_speed_x-allowedspeed)/(FULL_ACCEL_MARGIN));
		}

		segptr = segptr->next;
		while (lookaheaddist < maxlookaheaddist) {
			allowedspeed = getAllowedSpeed(segptr);
			if (allowedspeed < car->_speed_x) {
				if (brakedist(allowedspeed, mu) > lookaheaddist) {
					return 1.0;
				}
			}
			lookaheaddist += segptr->length;
			segptr = segptr->next;
		}
		return 0.0;
	}
}


// Compute gear.
int Driver::getGear()
{
	if (car->_gear <= 0) {
		return 1;
	}
	float gr_up = car->_gearRatio[car->_gear + car->_gearOffset];
	float omega = car->_enginerpmRedLine/gr_up;
	float wr = car->_wheelRadius(2);

	if (omega*wr*SHIFT < car->_speed_x) {
		return car->_gear + 1;
	} else {
		float gr_down = car->_gearRatio[car->_gear + car->_gearOffset - 1];
		omega = car->_enginerpmRedLine/gr_down;
		if (car->_gear > 1 && omega*wr*SHIFT > car->_speed_x + SHIFT_MARGIN) {
			return car->_gear - 1;
		}
	}
	return car->_gear;
}


// Compute steer value.
float Driver::getSteer()
{
	float targetAngle;
	v2d target = getTargetPoint();

	targetAngle = atan2(target.y - car->_pos_Y, target.x - car->_pos_X);
	targetAngle -= car->_yaw;
	NORM_PI_PI(targetAngle);
	return targetAngle / car->_steerLock;
}


// Compute the clutch value.
float Driver::getClutch()
{
	if (car->_gear > 1) {
		clutchtime = 0.0;
		return 0.0;
	} else {
		float drpm = car->_enginerpm - car->_enginerpmRedLine/2.0;
		clutchtime = MIN(CLUTCH_FULL_MAX_TIME, clutchtime);
		float clutcht = (CLUTCH_FULL_MAX_TIME - clutchtime)/CLUTCH_FULL_MAX_TIME;
		if (car->_gear == 1 && car->_accelCmd > 0.0) {
			clutchtime += RCM_MAX_DT_ROBOTS;
		}

		if (drpm > 0) {
			float speedr;
			if (car->_gearCmd == 1) {
				// Compute corresponding speed to engine rpm.
				float omega = car->_enginerpmRedLine/car->_gearRatio[car->_gear + car->_gearOffset];
				float wr = car->_wheelRadius(2);
				speedr = (CLUTCH_SPEED + MAX(0.0, car->_speed_x))/fabs(wr*omega);
				float clutchr = MAX(0.0, (1.0 - speedr*2.0*drpm/car->_enginerpmRedLine));
				return MIN(clutcht, clutchr);
			} else {
				// For the reverse gear.
				clutchtime = 0.0;
				return 0.0;
			}
		} else {
			return clutcht;
		}
	}
}

// Compute target point for steering.
v2d Driver::getTargetPoint()
{
	tTrackSeg *seg = car->_trkPos.seg;
	float lookahead;
	float length = getDistToSegEnd();
	float offset = getOffset();
	float alpha = seg_alpha[seg->id];
	if (pit->getInPit()) {
		alpha = 0.5;
		// To stop in the pit we need special lookahead values.
		if (currentspeedsqr > pit->getSpeedlimitSqr()) {
			lookahead = PIT_LOOKAHEAD + car->_speed_x*LOOKAHEAD_FACTOR;
		} else {
			lookahead = PIT_LOOKAHEAD;
		}
	} else {
		// Usual lookahead.
		lookahead = LOOKAHEAD_CONST + car->_speed_x*LOOKAHEAD_FACTOR;
		// Prevent "snap back" of lookahead on harsh braking.
		float cmplookahead = oldlookahead - car->_speed_x*RCM_MAX_DT_ROBOTS;
		if (lookahead < cmplookahead) {
			lookahead = cmplookahead;
		}
	}

	oldlookahead = lookahead;

	// Search for the segment containing the target point.
	while (length < lookahead) {
		seg = seg->next;
		length += seg->length;
	}

	length = lookahead - length + seg->length;
	float fromstart = seg->lgfromstart;
	fromstart += length;

	// Compute the target point.
	offset = myoffset = pit->getPitOffset(offset, fromstart);

	v2d s;


	s.x = alpha * seg->vertex[TR_SL].x + (1-alpha) * seg->vertex[TR_SR].x;
	s.y = alpha * seg->vertex[TR_SL].y + (1-alpha) * seg->vertex[TR_SR].y;

	if ( seg->type == TR_STR) {
		v2d d, n;
		n.x = (seg->vertex[TR_EL].x - seg->vertex[TR_ER].x)/seg->length;
		n.y = (seg->vertex[TR_EL].y - seg->vertex[TR_ER].y)/seg->length;
		n.normalize();
		d.x = (seg->vertex[TR_EL].x - seg->vertex[TR_SL].x)/seg->length;
		d.y = (seg->vertex[TR_EL].y - seg->vertex[TR_SL].y)/seg->length;
		return s + d*length + offset*n;
	} else {
		v2d c, n;
		c.x = seg->center.x;
		c.y = seg->center.y;
		float arc = length/seg->radius;
		float arcsign = (seg->type == TR_RGT) ? -1.0 : 1.0;
		arc = arc*arcsign;
		s = s.rotate(c, arc);

		n = c - s;
		n.normalize();
		return s + arcsign*offset*n;
	}
}


// Compute offset to normal target point for overtaking or let pass an opponent.
float Driver::getOffset()
{
	int i;
	float catchdist, mincatchdist = FLT_MAX, mindist = -1000.0;
	Opponent *o = NULL;

	// Increment speed dependent.
	float incfactor = MAX_INC_FACTOR - MIN(fabs(car->_speed_x)/MAX_INC_FACTOR, (MAX_INC_FACTOR-1.0));

	// Let overlap.
	for (i = 0; i < opponents->getNOpponents(); i++) {
		if (opponent[i].getState() & OPP_LETPASS) {
			// Behind, larger distances are smaller ("more negative").
			if (opponent[i].getDistance() > mindist) {
				mindist = opponent[i].getDistance();
				o = &opponent[i];
			}
		}
	}

	if (o != NULL) {
		tCarElt *ocar = o->getCarPtr();
		float side = car->_trkPos.toMiddle - ocar->_trkPos.toMiddle;
		float w = car->_trkPos.seg->width/WIDTHDIV-BORDER_OVERTAKE_MARGIN;
		if (side > 0.0) {
			if (myoffset < w) {
				myoffset += OVERTAKE_OFFSET_INC*incfactor;
			}
		} else {
			if (myoffset > -w) {
				myoffset -= OVERTAKE_OFFSET_INC*incfactor;
			}
		}
		return myoffset;
	}


	// Overtake.
	for (i = 0; i < opponents->getNOpponents(); i++) {
		if (opponent[i].getState() & OPP_FRONT) {
			catchdist = MIN(opponent[i].getCatchDist(), opponent[i].getDistance()*CATCH_FACTOR);
			if (catchdist < mincatchdist) {
				mincatchdist = catchdist;
				o = &opponent[i];
			}
		}
	}

	if (o != NULL) {
		// Compute the width around the middle which we can use for overtaking.
		float w = o->getCarPtr()->_trkPos.seg->width/WIDTHDIV-BORDER_OVERTAKE_MARGIN;
		// Compute the opponents distance to the middle.
		float otm = o->getCarPtr()->_trkPos.toMiddle;
		// Define the with of the middle range.
		float wm = o->getCarPtr()->_trkPos.seg->width*CENTERDIV;

		if (otm > wm && myoffset > -w) {
			myoffset -= OVERTAKE_OFFSET_INC*incfactor;
		} else if (otm < -wm && myoffset < w) {
			myoffset += OVERTAKE_OFFSET_INC*incfactor;
		} else {
			// If the opponent is near the middle we try to move the offset toward
			// the inside of the expected turn.
			// Try to find out the characteristic of the track up to catchdist.
			tTrackSeg *seg = car->_trkPos.seg;
			float length = getDistToSegEnd();
			float oldlen, seglen = length;
			float lenright = 0.0, lenleft = 0.0;
			mincatchdist = MIN(mincatchdist, DISTCUTOFF);

			do {
				switch (seg->type) {
				case TR_LFT:
					lenleft += seglen;
					break;
				case TR_RGT:
					lenright += seglen;
					break;
				default:
					// Do nothing.
					break;
				}
				seg = seg->next;
				seglen = seg->length;
				oldlen = length;
				length += seglen;
			} while (oldlen < mincatchdist);

			// If we are on a straight look for the next turn.
			if (lenleft == 0.0 && lenright == 0.0) {
				while (seg->type == TR_STR) {
					seg = seg->next;
				}
				// Assume: left or right if not straight.
				if (seg->type == TR_LFT) {
					lenleft = 1.0;
				} else {
					lenright = 1.0;
				}
			}

			// Because we are inside we can go to the border.
			float maxoff = (o->getCarPtr()->_trkPos.seg->width - car->_dimension_y)/2.0-BORDER_OVERTAKE_MARGIN;
			if (lenleft > lenright) {
				if (myoffset < maxoff) {
					myoffset += OVERTAKE_OFFSET_INC*incfactor;
				}
			} else {
				if (myoffset > -maxoff) {
					myoffset -= OVERTAKE_OFFSET_INC*incfactor;
				}
			}
		}
	} else {
		// There is no opponent to overtake, so the offset goes slowly back to zero.
		if (myoffset > OVERTAKE_OFFSET_INC) {
			myoffset -= OVERTAKE_OFFSET_INC;
		} else if (myoffset < -OVERTAKE_OFFSET_INC) {
			myoffset += OVERTAKE_OFFSET_INC;
		} else {
			myoffset = 0.0;
		}
	}

	return myoffset;
}


// Update my private data every timestep.
void Driver::update(tSituation *s)
{
	// Update global car data (shared by all instances) just once per timestep.
	if (currentsimtime != s->currentTime) {
		currentsimtime = s->currentTime;
		cardata->update();
	}

	// Update the local data rest.
	speedangle = mycardata->getTrackangle() - atan2(car->_speed_Y, car->_speed_X);
	NORM_PI_PI(speedangle);
	mass = CARMASS + car->_fuel;
	currentspeedsqr = car->_speed_x*car->_speed_x;
	opponents->update(s, this);
	strategy->update(car, s);
	if (!pit->getPitstop()) {
		pit->setPitstop(strategy->needPitstop(car, s));
	}
	pit->update();
	alone = isAlone();
	learn->update(s, track, car, alone, myoffset, car->_trkPos.seg->width/WIDTHDIV-BORDER_OVERTAKE_MARGIN, radius);
}


int Driver::isAlone()
{
	int i;
	for (i = 0; i < opponents->getNOpponents(); i++) {
		if (opponent[i].getState() & (OPP_COLL | OPP_LETPASS)) {
			return 0;	// Not alone.
		}
	}
	return 1;	// Alone.
}


// Check if I'm stuck.
bool Driver::isStuck()
{
	if (fabs(mycardata->getCarAngle()) > MAX_UNSTUCK_ANGLE &&
		car->_speed_x < MAX_UNSTUCK_SPEED &&
		fabs(car->_trkPos.toMiddle) > MIN_UNSTUCK_DIST) {
		if (stuck > MAX_UNSTUCK_COUNT && car->_trkPos.toMiddle*mycardata->getCarAngle() < 0.0) {
			return true;
		} else {
			stuck++;
			return false;
		}
	} else {
		stuck = 0;
		return false;
	}
}


// Compute aerodynamic downforce coefficient CA.
void Driver::initCa()
{
	char *WheelSect[4] = {SECT_FRNTRGTWHEEL, SECT_FRNTLFTWHEEL, SECT_REARRGTWHEEL, SECT_REARLFTWHEEL};
	float rearwingarea = GfParmGetNum(car->_carHandle, SECT_REARWING, PRM_WINGAREA, (char*) NULL, 0.0);
	float rearwingangle = GfParmGetNum(car->_carHandle, SECT_REARWING, PRM_WINGANGLE, (char*) NULL, 0.0);
	float wingca = 1.23*rearwingarea*sin(rearwingangle);

	float cl = GfParmGetNum(car->_carHandle, SECT_AERODYNAMICS, PRM_FCL, (char*) NULL, 0.0) +
			   GfParmGetNum(car->_carHandle, SECT_AERODYNAMICS, PRM_RCL, (char*) NULL, 0.0);
	float h = 0.0;
	int i;
	for (i = 0; i < 4; i++)
		h += GfParmGetNum(car->_carHandle, WheelSect[i], PRM_RIDEHEIGHT, (char*) NULL, 0.20);
	h*= 1.5; h = h*h; h = h*h; h = 2.0 * exp(-3.0*h);
	CA = h*cl + 4.0*wingca;
}


// Compute aerodynamic drag coefficient CW.
void Driver::initCw()
{
	float cx = GfParmGetNum(car->_carHandle, SECT_AERODYNAMICS, PRM_CX, (char*) NULL, 0.0);
	float frontarea = GfParmGetNum(car->_carHandle, SECT_AERODYNAMICS, PRM_FRNTAREA, (char*) NULL, 0.0);
	CW = 0.645*cx*frontarea;
}


// Init the friction coefficient of the the tires.
void Driver::initTireMu()
{
	char *WheelSect[4] = {SECT_FRNTRGTWHEEL, SECT_FRNTLFTWHEEL, SECT_REARRGTWHEEL, SECT_REARLFTWHEEL};
	float tm = FLT_MAX;
	int i;

	for (i = 0; i < 4; i++) {
		tm = MIN(tm, GfParmGetNum(car->_carHandle, WheelSect[i], PRM_MU, (char*) NULL, 1.0));
	}
	TIREMU = tm;
}


// Reduces the brake value such that it fits the speed (more downforce -> more braking).
float Driver::filterBrakeSpeed(float brake)
{
	float weight = (CARMASS + car->_fuel)*G;
	float maxForce = weight + CA*MAX_SPEED*MAX_SPEED;
	float force = weight + CA*currentspeedsqr;
	return brake*force/maxForce;
}


// Brake filter for pit stop.
float Driver::filterBPit(float brake)
{
	if (pit->getPitstop() && !pit->getInPit()) {
		float dl, dw;
		RtDistToPit(car, track, &dl, &dw);
		if (dl < PIT_BRAKE_AHEAD) {
			float mu = car->_trkPos.seg->surface->kFriction*TIREMU*PIT_MU;
			if (brakedist(0.0, mu) > dl) {
				return 1.0;
			}
		}
	}

	if (pit->getInPit()) {
		float s = pit->toSplineCoord(car->_distFromStartLine);
		// Pit entry.
		if (pit->getPitstop()) {
			float mu = car->_trkPos.seg->surface->kFriction*TIREMU*PIT_MU;
			if (s < pit->getNPitStart()) {
				// Brake to pit speed limit.
				float dist = pit->getNPitStart() - s;
				if (brakedist(pit->getSpeedlimit(), mu) > dist) {
					return 1.0;
				}
			} else {
				// Hold speed limit.
				if (currentspeedsqr > pit->getSpeedlimitSqr()) {
					return pit->getSpeedLimitBrake(currentspeedsqr);
				}
			}
			// Brake into pit (speed limit 0.0 to stop)
			float dist = pit->getNPitLoc() - s;
			if (pit->isTimeout(dist)) {
				pit->setPitstop(false);
				return 0.0;
			} else {
				if (brakedist(0.0, mu) > dist) {
					return 1.0;
				} else if (s > pit->getNPitLoc()) {
					// Stop in the pit.
			 		return 1.0;
				}
			}
		} else {
			// Pit exit.
			if (s < pit->getNPitEnd()) {
				// Pit speed limit.
				if (currentspeedsqr > pit->getSpeedlimitSqr()) {
					return pit->getSpeedLimitBrake(currentspeedsqr);
				}
			}
		}
	}

	return brake;
}


// Brake filter for collision avoidance.
float Driver::filterBColl(float brake)
{
	float mu = car->_trkPos.seg->surface->kFriction;
	int i;
	for (i = 0; i < opponents->getNOpponents(); i++) {
		if (opponent[i].getState() & OPP_COLL) {
			float delta = brakedist(opponent[i].getSpeed(), mu) - opponent[i].getDistance();
			float y = tanh(delta);
			if (y<0) y=0;
			return SmoothMaxGamma (y, brake, 0.5, 100.0);
		}
	}
	return brake;
}


// Steer filter for collision avoidance.
float Driver::filterSColl(float steer)
{
	int i;
	float sidedist = 0.0, fsidedist = 0.0, minsidedist = FLT_MAX;
	Opponent *o = NULL;

	// Get the index of the nearest car (o).
	for (i = 0; i < opponents->getNOpponents(); i++) {
		if (opponent[i].getState() & OPP_SIDE) {
			sidedist = opponent[i].getSideDist();
			fsidedist = fabs(sidedist);
			if (fsidedist < minsidedist) {
				minsidedist = fsidedist;
				o = &opponent[i];
			}
		}
	}

	// If there is another car handle the situation.
	if (o != NULL) {
		float d = fsidedist - o->getWidth();
		// Near, so we need to look at it.
		if (d < SIDECOLL_MARGIN) {
			/* compute angle between cars */
			tCarElt *ocar = o->getCarPtr();
			float diffangle = ocar->_yaw - car->_yaw;
			NORM_PI_PI(diffangle);
			// We are near and heading toward the car.
			if (diffangle*o->getSideDist() < 0.0) {
				const float c = SIDECOLL_MARGIN/2.0;
				d = d - c;
				if (d < 0.0) {
					d = 0.0;
				}

				float psteer = diffangle/car->_steerLock;
				myoffset = car->_trkPos.toMiddle;

				float w = o->getCarPtr()->_trkPos.seg->width/WIDTHDIV-BORDER_OVERTAKE_MARGIN;
				if (fabs(myoffset) > w) {
					myoffset = (myoffset > 0.0) ? w : -w;
				}

				// Who is outside?
				if (car->_trkPos.seg->type == TR_STR) {
					if (fabs(car->_trkPos.toMiddle) > fabs(ocar->_trkPos.toMiddle)) {
						psteer = steer*(d/c) + 1.5*psteer*(1.0-d/c);
					} else {
						psteer = steer*(d/c) + 2.0*psteer*(1.0-d/c);
					}
				} else {
					float outside = car->_trkPos.toMiddle - ocar->_trkPos.toMiddle;
					float sign = (car->_trkPos.seg->type == TR_RGT) ? 1.0 : -1.0;
					if (outside*sign > 0.0) {
						psteer = steer*(d/c) + 1.5*psteer*(1.0-d/c);
					} else {
						psteer = steer*(d/c) + 2.0*psteer*(1.0-d/c);
					}
				}

				if (psteer*steer > 0.0 && fabs(steer) > fabs(psteer)) {
					return steer;
				} else {
					return psteer;
				}
			}
		}
	}
	return steer;
}


// Antilocking filter for brakes.
float Driver::filterABS(float brake)
{
	if (car->_speed_x < ABS_MINSPEED) return brake;
	int i;
	float slip = 0.0;
	for (i = 0; i < 4; i++) {
		slip += car->_wheelSpinVel(i) * car->_wheelRadius(i);
	}
	slip = car->_speed_x - slip/4.0;
	if (slip > ABS_SLIP) {
		brake = brake - MIN(brake, (slip - ABS_SLIP)/ABS_RANGE);
	}
	return brake;
}


// TCL filter for accelerator pedal.
float Driver::filterTCL(float accel)
{
	float slip = (this->*GET_DRIVEN_WHEEL_SPEED)() - car->_speed_x;
	if (slip > TCL_SLIP) {
		accel = accel - MIN(accel, (slip - TCL_SLIP)/TCL_RANGE);
	}
	return accel;
}


// Traction Control (TCL) setup.
void Driver::initTCLfilter()
{
	char *traintype = GfParmGetStr(car->_carHandle, SECT_DRIVETRAIN, PRM_TYPE, VAL_TRANS_RWD);
	if (strcmp(traintype, VAL_TRANS_RWD) == 0) {
		GET_DRIVEN_WHEEL_SPEED = &Driver::filterTCL_RWD;
	} else if (strcmp(traintype, VAL_TRANS_FWD) == 0) {
		GET_DRIVEN_WHEEL_SPEED = &Driver::filterTCL_FWD;
	} else if (strcmp(traintype, VAL_TRANS_4WD) == 0) {
		GET_DRIVEN_WHEEL_SPEED = &Driver::filterTCL_4WD;
	}
}


// TCL filter plugin for rear wheel driven cars.
float Driver::filterTCL_RWD()
{
	return (car->_wheelSpinVel(REAR_RGT) + car->_wheelSpinVel(REAR_LFT)) *
			car->_wheelRadius(REAR_LFT) / 2.0;
}


// TCL filter plugin for front wheel driven cars.
float Driver::filterTCL_FWD()
{
	return (car->_wheelSpinVel(FRNT_RGT) + car->_wheelSpinVel(FRNT_LFT)) *
			car->_wheelRadius(FRNT_LFT) / 2.0;
}


// TCL filter plugin for all wheel driven cars.
float Driver::filterTCL_4WD()
{
	return ((car->_wheelSpinVel(FRNT_RGT) + car->_wheelSpinVel(FRNT_LFT)) *
			car->_wheelRadius(FRNT_LFT) +
		   (car->_wheelSpinVel(REAR_RGT) + car->_wheelSpinVel(REAR_LFT)) *
			car->_wheelRadius(REAR_LFT)) / 4.0;
}


// Hold car on the track.
float Driver::filterTrk(float accel)
{
	tTrackSeg* seg = car->_trkPos.seg;
	float dtm = -getSteer();//(car->_trkPos.toMiddle);
	float tm = fabs(dtm);

	if (car->_speed_x < MAX_UNSTUCK_SPEED ||		// Too slow.
		pit->getInPit() ||							// Pit stop.
		car->_trkPos.toMiddle*speedangle > 0.0)		// Speedvector points to the inside of the turn.
	{
		float w = (seg->width - car->_dimension_y)/2.0 ;
		accel = learn->updateAccel (car, accel, tm-w,dtm);
	}

	if (seg->type == TR_STR) {
		float w = (seg->width - car->_dimension_y)/2.0 ;
		if (tm > w) {
			accel = learn->updateAccel (car, 0.0f, tm-w,dtm);
		} else {
			accel = learn->updateAccel (car, 1.0f, tm-w,dtm);
		}
		return accel;
	} else {
		float sign = (seg->type == TR_RGT) ? -1.0 : 1.0;
		if (car->_trkPos.toMiddle*sign > 0.0) {
			float w = seg->width/WIDTHDIV;
			return  learn->updateAccel (car, 1.0f, tm-w,dtm);
		} else {
			float w = seg->width/WIDTHDIV;
			if (tm > w) {
				accel = learn->updateAccel (car, 0.0f, tm-w,dtm);
			} else {
				accel = learn->updateAccel (car, 1.0f, tm-w,dtm);
			}
			return accel;
		}
	}
}


// Compute the needed distance to brake.
float Driver::brakedist(float allowedspeed, float mu)
{
	float c = mu*G;
	float d = (CA*mu + CW)/mass;
	float v1sqr = currentspeedsqr;
	float v2sqr = allowedspeed*allowedspeed;
	return -log((c + v2sqr*d)/(c + v1sqr*d))/(2.0*d);
}



/**
   \brief prepare an initial path through the track.

   This function uses a simple linear filter to set up a rough path
   through the track. Initially the path is set up so that target
   lookahead points are adjusted towards the left or right of the
   track depending on whether we are on a curve, a straight, exiting a
   curve or entering a curve. This is saved onto the targets[] array,
   which contains the proportion by which the target point is adjusted
   towards the left. There are a number of variables that control how
   the targets generation works:

   \c aleft, \c aright control the targets for when we are in the peak
   of a curve. Normally this is set up so that aleft points to the
   left and aright points to the right, but the overall effect is
   influenced by the lookahead.

   \c exitleft, \c exitright control the targets for when we are
   exiting a curve. Normally we want to exit a left curve on the right
   and a right curve on the left.

   \c entryleft, \c entryright control the targets for when we are
   entering a curve.

   \c adjust_entry, if true, adds the constraint that alpha is 0 or 1
   in the middle of the straight, depending on whether a left or right
   turn follows. Then the car follows a slightly better trajectory
   to the entry point, which should be closer to the center.

   The result is then passed through a backwards-forwards filter, with
   coefficients \c gamma_curve, \c gamma_straight, depending on
   whether the current segment is a curve or straight.

   The final result is squashed down towards 0.5 by the variable \c
   squash. Note that the costraints added by \c adjust_entry are not
   affected by squashing.
*/
void Driver::prepareTrack()
{
	int N=track->nseg;
	float aleft = 0.8;
	float aright= 0.2;
	float exitleft=0.0;
	float exitright=1.0;
	float entryleft=0.1;
	float entryright=0.9;
	bool adjust_entry = false;
	float gamma_curve = 0.95;
	float gamma_straight = 0.99;
	float squash = 0.5;


	seg_alpha = new float [N];
	float* targets = new float [N];
	for (int i=0; i<N; i++) {
		seg_alpha[i] = 0.0;
		targets[i] = 0.0;
	}

	tTrackSeg* seg = track->seg;
	//	s.x = alpha * seg->vertex[TR_SL].x + (1-alpha) * seg->vertex[TR_SR].x;
	//	s.y = alpha * seg->vertex[TR_SL].y + (1-alpha) * seg->vertex[TR_SR].y;
	for (int i=0; i<N; i++, seg=seg->next) {
		tTrackSeg* cs = seg;
		tTrackSeg* ce = seg;
		float lend = 0.0;
		float lstart = 0.0;
		float target_end = 0.5;
		float target_start = 0.5;

		while(cs->type==seg->type) {
			cs = cs->prev;
			lstart += cs->length;
		}
		while(ce->type==seg->type) {
			ce = ce->next;
			lend += ce->length;
		}

		float target_mean = 0.5;

		if (seg->type==TR_LFT) {
			target_mean = aleft;
			if (cs->type==TR_STR) {
				target_start = 0.5;//entryleft;
			} else if (cs->type==TR_RGT) {
				target_start = 0.5;
			}
			if (ce->type==TR_STR) {
				target_end = 0.5;//exitleft;
			} else if (ce->type==TR_RGT) {
				target_end = 0.5;
			}
		} else if (seg->type==TR_RGT) {
			target_mean = aright;
			if (cs->type==TR_STR) {
				target_start = 0.5;//entryright;
			} else if (cs->type==TR_LFT) {
				target_start = 0.5;
			}
			if (ce->type==TR_STR) {
				target_end = 0.5;//exitright;
			} else if (ce->type==TR_LFT) {
				target_end = 0.5;
			}
		} else {
			if (cs->type==TR_LFT) {
				target_start = exitleft;
			} else if (cs->type==TR_RGT) {
				target_start = exitright;
			}
			if (ce->type==TR_LFT) {
				target_end = entryleft;
				target_mean = - 0.5 * squash/(1.0-squash);
			} else if (ce->type==TR_RGT) {
				target_end = entryright;
				target_mean = 1.0 + 0.5 * squash / (1.0-squash);
			}
			if (adjust_entry==false) {
				target_mean = 0.5 *  (target_start+target_end);
			}
		}
		float lm = .5 * (lstart + lend);
		float beta;
		float target_p = target_mean;
		if (lstart<lend) {
			beta  = lstart/lm;
			target_p = target_start;
		} else {
			beta = lend/lm;
			target_p = target_end;
		}
		if (seg->type!=TR_STR) {
			targets[i] = target_mean * beta*beta + target_p * (1-beta*beta);
		} else {
			targets[i] = target_mean * beta + target_p * (1-beta);
		}
	}
		

	// Smooth targets
	float d = 0.01;
	for (int iter=0; iter<10000; iter++) {
		float err = 0.0;
		seg = track->seg;
		for (int i=0; i<N; i++, seg=seg->next) {
			float alpha = seg_alpha[i];
			float alpha_next = seg_alpha[seg->next->id];
			float alpha_prev = seg_alpha[seg->prev->id];
			float gamma = gamma_curve;
			float target = targets[i];
			if (seg->type==TR_STR) {
				gamma = gamma_straight;
			}
			target = alpha_next * gamma + target * (1-gamma);
			alpha += d * (target - alpha);
			target = targets[i];
			target = alpha_prev * gamma + target * (1-gamma);
			alpha += 0.5 * d * (target - alpha);
			err += (seg_alpha[i] - alpha)*(seg_alpha[i]-alpha);
			seg_alpha[i] = alpha;
		}

		for (int i=N-1; i>=0; i--, seg=seg->prev) {
			float alpha = seg_alpha[i];
			float alpha_next = seg_alpha[seg->next->id];
			float alpha_prev = seg_alpha[seg->prev->id];
			float gamma = gamma_curve;
			float target = targets[i];
			if (seg->type==TR_STR) {
				gamma = gamma_straight;
			}
			target = alpha_next * gamma + target * (1-gamma);
			alpha += d * (target - alpha);
			err += (seg_alpha[i] - alpha)*(seg_alpha[i]-alpha);
			seg_alpha[i] = alpha;
		}
	}
#if 1
	for (int i=0; i<N; i++) {
		seg_alpha[i] = (1-squash) * seg_alpha[i] + 0.5 * squash;
	}
#endif
	FILE* f = fopen ("alphas", "w");
	seg = track->seg;
	for (int i=0; i<N; i++, seg=seg->next) {
		fprintf (f, "%f ", seg_alpha[i]);
		if (seg->type==TR_STR) {
			fprintf (f,"0.5");
		} else if (seg->type==TR_LFT) {
			fprintf (f,"1.0");
		} else if (seg->type==TR_RGT) {
			fprintf (f,"0.0");
		}
		fprintf (f, " %f\n", targets[i]);
	}
	fclose(f);

	delete [] targets;

}
