/***************************************************************************

    file                 : driver.cpp
    created              : Thu Dec 20 01:21:49 CET 2002
    copyright            : (C) 2002 Bernhard Wymann
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

#include "driver.h"

#define BT_SECT_PRIV "bt private"
#define BT_ATT_FUELPERLAP "fuelperlap"
#define BT_ATT_MUFACTOR "mufactor"

const float Driver::MAX_UNSTUCK_ANGLE = 15.0/180.0*PI;		/* [radians] */
const float Driver::UNSTUCK_TIME_LIMIT = 2.0;				/* [s] */
const float Driver::MAX_UNSTUCK_SPEED = 5.0;				/* [m/s] */
const float Driver::MIN_UNSTUCK_DIST = 3.0;					/* [m] */
const float Driver::G = 9.81;								/* [m/(s*s)] */
const float Driver::FULL_ACCEL_MARGIN = 1.0;				/* [m/s] */
const float Driver::SHIFT = 0.9;							/* [-] (% of rpmredline) */
const float Driver::SHIFT_MARGIN = 4.0;						/* [m/s] */
const float Driver::ABS_SLIP = 2.0;							/* [m/s] range [0..10] */
const float Driver::ABS_RANGE = 5.0;						/* [m/s] range [0..10] */
const float Driver::ABS_MINSPEED = 3.0;						/* [m/s] */
const float Driver::TCL_SLIP = 2.0;							/* [m/s] range [0..10] */
const float Driver::TCL_RANGE = 5.0;						/* [m/s] range [0..10] */
const float Driver::LOOKAHEAD_CONST = 17.0;					/* [m] */
const float Driver::LOOKAHEAD_FACTOR = 0.33;				/* [-] */
const float Driver::WIDTHDIV = 3.0;							/* [-] */
const float Driver::SIDECOLL_MARGIN = 2.0;					/* [m] */
const float Driver::BORDER_OVERTAKE_MARGIN = 0.5;			/* [m] */
const float Driver::OVERTAKE_OFFSET_SPEED = 5.0;			/* [m/s] */
const float Driver::PIT_LOOKAHEAD = 6.0;					/* [m] */
const float Driver::PIT_BRAKE_AHEAD = 200.0;				/* [m] */
const float Driver::PIT_MU = 0.4;							/* [-] */
const float Driver::MAX_SPEED = 84.0;						/* [m/s] */
const float Driver::MAX_FUEL_PER_METER = 0.0008;			/* [liter/m] fuel consumtion */
const float Driver::CLUTCH_SPEED = 5.0;						/* [m/s] */
const float Driver::CENTERDIV = 0.1;						/* [-] (factor) [0.01..0.6] */

Driver::Driver(int index)
{
	INDEX = index;
}


Driver::~Driver()
{
	delete opponents;
	delete pit;
}


/* Called for every track change or new race. */
void Driver::initTrack(tTrack* t, void *carHandle, void **carParmHandle, tSituation *s)
{
	track = t;

	char buffer[256];
	/* get a pointer to the first char of the track filename */
	char* trackname = strrchr(track->filename, '/') + 1;

	switch (s->_raceType) {
		case RM_TYPE_PRACTICE:
			sprintf(buffer, "drivers/bt/%d/practice/%s", INDEX, trackname);
			break;
		case RM_TYPE_QUALIF:
			sprintf(buffer, "drivers/bt/%d/qualifying/%s", INDEX, trackname);
			break;
		case RM_TYPE_RACE:
			sprintf(buffer, "drivers/bt/%d/race/%s", INDEX, trackname);
			break;
		default:
			break;
	}

	*carParmHandle = GfParmReadFile(buffer, GFPARM_RMODE_STD);
	if (*carParmHandle == NULL) {
		sprintf(buffer, "drivers/bt/%d/default.xml", INDEX);
		*carParmHandle = GfParmReadFile(buffer, GFPARM_RMODE_STD);
    }

	/* Load and set parameters */
	float fuel = GfParmGetNum(*carParmHandle, BT_SECT_PRIV, BT_ATT_FUELPERLAP, (char*)NULL, t->length*MAX_FUEL_PER_METER);
	fuel *= (s->_totLaps + 1.0);
	GfParmSetNum(*carParmHandle, SECT_CAR, PRM_FUEL, (char*)NULL, MIN(fuel, 100.0));

	MU_FACTOR = GfParmGetNum(*carParmHandle, BT_SECT_PRIV, BT_ATT_MUFACTOR, (char*)NULL, 0.69);
}


/* Start a new race. */
void Driver::newRace(tCarElt* car, tSituation *s)
{
	float deltaTime = RCM_MAX_DT_ROBOTS;
	MAX_UNSTUCK_COUNT = int(UNSTUCK_TIME_LIMIT/deltaTime);
	OVERTAKE_OFFSET_INC = OVERTAKE_OFFSET_SPEED*deltaTime;
	stuck = 0;
	lastsegtype = TR_STR;
	this->car = car;
	CARMASS = GfParmGetNum(car->_carHandle, SECT_CAR, PRM_MASS, NULL, 1000.0);
	myoffset = 0.0;
	initCa();
	initCw();
	initTireMu();
	initTCLfilter();

	/* initialize the list of opponents */
	opponents = new Opponents(s, this);
	opponent = opponents->getOpponentPtr();

	/* create the pit object */
	pit = new Pit(s, this);
}


/* Drive during race. */
void Driver::drive(tSituation *s)
{
	memset(&car->ctrl, 0, sizeof(tCarCtrl));

	update(s);

	if (isStuck()) {
		car->_steerCmd = -angle / car->_steerLock;
		car->_gearCmd = -1; // reverse gear
		car->_accelCmd = 1.0; // 50% accelerator pedal
		car->_brakeCmd = 0.0; // no brakes
		car->_clutchCmd = 0.0;
	} else {
		car->_steerCmd = filterSColl(getSteer());
		car->_gearCmd = getGear();
		car->_brakeCmd = filterABS(filterBrakeSpeed(filterBColl(filterBPit(getBrake()))));
		if (car->_brakeCmd == 0.0) {
			car->_accelCmd = filterTCL(filterTrk(getAccel()));
			car->_clutchCmd = getClutch();
		} else {
			car->_accelCmd = 0.0;
			car->_clutchCmd = getClutch();
		}
	}
}


/* Set pitstop commands */
int Driver::pitCommand(tSituation *s)
{
	car->_pitRepair = pit->getRepair();
	car->_pitFuel = pit->getFuel();
	pit->setPitstop(false);
	return ROB_PIT_IM; /* return immediately */
}


/* End of the current race */
void Driver::endRace(tSituation *s)
{
}


/***************************************************************************
 *
 * utility functions
 *
***************************************************************************/


/* Compute the allowed speed on a segment */
float Driver::getAllowedSpeed(tTrackSeg *segment)
{
	if (segment->type == TR_STR) {
		lastsegtype = TR_STR;
		return FLT_MAX;
	} else {
		if (segment->type != lastsegtype) {
			float arc = 0.0;
			tTrackSeg *s = segment;
			lastsegtype = segment->type;

			while (s->type == lastsegtype && arc < PI/2.0) {
				arc += s->arc;
				s = s->next;
			}
			lastturnarc = arc/(PI/2.0);

		}
		float mu = segment->surface->kFriction*TIREMU*MU_FACTOR;
		float r = (segment->radius + segment->width/2.0)/lastturnarc;
		return sqrt((mu*G*r)/(1.0 - MIN(1.0, r*CA*mu/mass)));
	}
}


/* Compute the length to the end of the segment */
float Driver::getDistToSegEnd()
{
	if (car->_trkPos.seg->type == TR_STR) {
		return car->_trkPos.seg->length - car->_trkPos.toStart;
	} else {
		return (car->_trkPos.seg->arc - car->_trkPos.toStart)*car->_trkPos.seg->radius;
	}
}


/* Compute fitting acceleration */
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


/* Compute initial brake value */
float Driver::getBrake()
{
	tTrackSeg *segptr = car->_trkPos.seg;
	float mu = segptr->surface->kFriction;//*TIREMU*MU_FACTOR;
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


/* Compute gear */
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


/* Compute steer value */
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
		return 0.0;
	} else {
		float drpm = car->_enginerpm - car->_enginerpmRedLine/2.0;
		if (drpm > 0) {
			float speedr;
			if (car->_gearCmd == 1) {
				// Compute corresponding speed to engine rpm.
				float omega = car->_enginerpmRedLine/car->_gearRatio[car->_gear + car->_gearOffset];
				float wr = car->_wheelRadius(2);
				speedr = (CLUTCH_SPEED + MAX(0.0, car->_speed_x))/fabs(wr*omega);
				return MAX(0.0, (1.0 - speedr*2.0*drpm/car->_enginerpmRedLine));
			} else {
				// For the reverse gear.
				return 0.0;
			}
		} else {
			return 1.0;
		}
	}
}

/* Compute target point for steering */
v2d Driver::getTargetPoint()
{
	tTrackSeg *seg = car->_trkPos.seg;
	float lookahead = LOOKAHEAD_CONST + car->_speed_x*LOOKAHEAD_FACTOR;
	float length = getDistToSegEnd();
	float offset = getOvertakeOffset();

	if (pit->getInPit()) {
		if (currentspeedsqr > pit->getSpeedlimitSqr()) {
			lookahead = PIT_LOOKAHEAD + car->_speed_x*LOOKAHEAD_FACTOR;
		} else {
			lookahead = PIT_LOOKAHEAD;
		}
	}

	while (length < lookahead) {
		seg = seg->next;
		length += seg->length;
	}

	length = lookahead - length + seg->length;
	float fromstart = seg->lgfromstart;
	fromstart += length;
	offset = pit->getPitOffset(offset, fromstart);

	v2d s;
	s.x = (seg->vertex[TR_SL].x + seg->vertex[TR_SR].x)/2.0;
	s.y = (seg->vertex[TR_SL].y + seg->vertex[TR_SR].y)/2.0;

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


/* Compute offset to normal target point for overtaking */
float Driver::getOvertakeOffset()
{
	int i;
	float catchdist, mincatchdist = FLT_MAX;
	Opponent *o = NULL;

	for (i = 0; i < opponents->getNOpponents(); i++) {
		if (opponent[i].getState() & OPP_FRONT) {
			catchdist = opponent[i].getCatchDist();
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
			myoffset -= OVERTAKE_OFFSET_INC;
		} else if (otm < -wm && myoffset < w) {
			myoffset += OVERTAKE_OFFSET_INC;
		} else {
			// If the opponent is near the middle we try to move the offset toward
			// the inside of the expected turn.
			// Try to find out the characteristic of the track up to catchdist.
			tTrackSeg *seg = car->_trkPos.seg;
			float length = getDistToSegEnd();
			float oldlen, seglen = length;
			float lenright = 0.0, lenleft = 0.0;
			mincatchdist = MIN(mincatchdist, 200.0);

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
					myoffset += OVERTAKE_OFFSET_INC;
				}
			} else {
				if (myoffset > -maxoff) {
					myoffset -= OVERTAKE_OFFSET_INC;
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


/* Update my private data every timestep */
void Driver::update(tSituation *s)
{
	trackangle = RtTrackSideTgAngleL(&(car->_trkPos));
	angle = trackangle - car->_yaw;
	NORM_PI_PI(angle);
	mass = CARMASS + car->_fuel;
	currentspeedsqr = car->_speed_x*car->_speed_x;
	speed = Opponent::getSpeed(car);
	opponents->update(s, this);
	pit->update();
}


/* Check if I'm stuck */
bool Driver::isStuck()
{
	if (fabs(angle) > MAX_UNSTUCK_ANGLE &&
		car->_speed_x < MAX_UNSTUCK_SPEED &&
		fabs(car->_trkPos.toMiddle) > MIN_UNSTUCK_DIST) {
		if (stuck > MAX_UNSTUCK_COUNT && car->_trkPos.toMiddle*angle < 0.0) {
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


/* Compute aerodynamic downforce coefficient CA */
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


/* Compute aerodynamic drag coefficient CW */
void Driver::initCw()
{
	float cx = GfParmGetNum(car->_carHandle, SECT_AERODYNAMICS, PRM_CX, (char*) NULL, 0.0);
	float frontarea = GfParmGetNum(car->_carHandle, SECT_AERODYNAMICS, PRM_FRNTAREA, (char*) NULL, 0.0);
	CW = 0.645*cx*frontarea;
}


/* Init the friction coefficient of the the tires */
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


/* Reduces the brake value such that it fits the speed */
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
		// pit entry
		if (pit->getPitstop()) {
			float mu = car->_trkPos.seg->surface->kFriction*TIREMU*PIT_MU;
			if (s < pit->getNPitStart()) {
				// brake to pit speed limit
				float dist = pit->getNPitStart() - s;
				if (brakedist(pit->getSpeedlimit(), mu) > dist) {
					return 1.0;
				}
			} else {
				// hold speed limit
				if (currentspeedsqr > pit->getSpeedlimitSqr()) {
					return pit->getSpeedLimitBrake(currentspeedsqr);
				}
			}
			// brake into pit (speed limit 0.0 to stop )
			float dist = pit->getNPitLoc() - s;
			if (pit->isTimeout(dist)) {
				pit->setPitstop(false);
				return 0.0;
			} else {
				if (brakedist(0.0, mu) > dist) {
					return 1.0;
				} else if (s > pit->getNPitLoc()) {
					// hold in the pit
			 		return 1.0;
				}
			}
		} else {
			/* pit exit */
			if (s < pit->getNPitEnd()) {
				/* pit speed limit */
				if (currentspeedsqr > pit->getSpeedlimitSqr()) {
					return pit->getSpeedLimitBrake(currentspeedsqr);
				}
			}
		}
	}

	return brake;
}


/* Brake filter for collision avoidance */
float Driver::filterBColl(float brake)
{
	float mu = car->_trkPos.seg->surface->kFriction;//*TIREMU*MU_FACTOR;
	int i;

	for (i = 0; i < opponents->getNOpponents(); i++) {
		if (opponent[i].getState() & OPP_COLL) {
			if (brakedist(opponent[i].getSpeed(), mu) > opponent[i].getDistance()) {
				return 1.0;
			}
		}
	}
	return brake;
}


/* Steer filter for collision avoidance */
float Driver::filterSColl(float steer)
{
	int i;
	float sidedist = 0.0, fsidedist = 0.0, minsidedist = FLT_MAX;
	Opponent *o = NULL;

	/* get the index of the nearest car (o) */
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

	/* if there is another car handle the situation */
	if (o != NULL) {
		float d = fsidedist - o->getWidth();
		/* near enough */
		if (d < SIDECOLL_MARGIN) {
			/* compute angle between cars */
			tCarElt *ocar = o->getCarPtr();
			float diffangle = ocar->_yaw - car->_yaw;
			NORM_PI_PI(diffangle);
			/* we are near and heading toward the car */
			if (diffangle*o->getSideDist() < 0.0) {
				const float c = SIDECOLL_MARGIN/2.0;
				d = d - c;
				if (d < 0.0) d = 0.0;
				float psteer = diffangle/car->_steerLock;

				myoffset = car->_trkPos.toMiddle;
				float w = o->getCarPtr()->_trkPos.seg->width/WIDTHDIV-BORDER_OVERTAKE_MARGIN;
				if (fabs(myoffset) > w) {
					myoffset = (myoffset > 0) ? w : -w;
				}

				psteer = steer*(d/c) + 2.0*psteer*(1.0-d/c);
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


/* Antilocking filter for brakes */
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


/* TCL filter for accelerator pedal */
float Driver::filterTCL(float accel)
{
	float slip = (this->*GET_DRIVEN_WHEEL_SPEED)() - car->_speed_x;
	if (slip > TCL_SLIP) {
		accel = accel - MIN(accel, (slip - TCL_SLIP)/TCL_RANGE);
	}
	return accel;
}


/* Traction Control (TCL) setup */
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


/* TCL filter plugin for rear wheel driven cars */
float Driver::filterTCL_RWD()
{
	return (car->_wheelSpinVel(REAR_RGT) + car->_wheelSpinVel(REAR_LFT)) *
			car->_wheelRadius(REAR_LFT) / 2.0;
}


/* TCL filter plugin for front wheel driven cars */
float Driver::filterTCL_FWD()
{
	return (car->_wheelSpinVel(FRNT_RGT) + car->_wheelSpinVel(FRNT_LFT)) *
			car->_wheelRadius(FRNT_LFT) / 2.0;
}


/* TCL filter plugin for all wheel driven cars */
float Driver::filterTCL_4WD()
{
	return ((car->_wheelSpinVel(FRNT_RGT) + car->_wheelSpinVel(FRNT_LFT)) *
			car->_wheelRadius(FRNT_LFT) +
		   (car->_wheelSpinVel(REAR_RGT) + car->_wheelSpinVel(REAR_LFT)) *
			car->_wheelRadius(REAR_LFT)) / 4.0;
}


/* Hold car on the track */
float Driver::filterTrk(float accel)
{
	tTrackSeg* seg = car->_trkPos.seg;
	float speedangle = trackangle - atan2(car->_speed_Y, car->_speed_X);
	NORM_PI_PI(speedangle);

	if (car->_speed_x < MAX_UNSTUCK_SPEED ||
		pit->getInPit() ||
		car->_trkPos.toMiddle*speedangle > 0.0)
	{
		return accel;
	}

	if (seg->type == TR_STR) {
		float tm = fabs(car->_trkPos.toMiddle);
		float w = (seg->width - car->_dimension_y)/2.0 ;
		if (tm > w) {
			return 0.0;
		} else {
			return accel;
		}
	} else {
		float sign = (seg->type == TR_RGT) ? -1.0 : 1.0;
		if (car->_trkPos.toMiddle*sign > 0.0) {
			return accel;
		} else {
			float tm = fabs(car->_trkPos.toMiddle);
			float w = seg->width/WIDTHDIV;
			if (tm > w) {
				return 0.0;
			} else {
				return accel;
			}
		}
	}
}


float Driver::brakedist(float allowedspeed, float mu)
{
	float c = mu*G;
    float d = (CA*mu + CW)/mass;
    float v1sqr = currentspeedsqr;
    float v2sqr = allowedspeed*allowedspeed;
    return -log((c + v2sqr*d)/(c + v1sqr*d))/(2.0*d);
}

