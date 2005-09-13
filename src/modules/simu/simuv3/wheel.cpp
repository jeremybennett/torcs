/***************************************************************************

    file                 : wheel.cpp
    created              : Sun Mar 19 00:09:06 CET 2000
    copyright            : (C) 2000-2004 by Eric Espie, Christos Dimitrakakis
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

#define USE_QUATERNIONS 1
#undef FREE_MOVING_WHEELS

#if 0
#define BEGIN_PROFILE(x) double x##_dt = GfTimeClock()
#define END_PROFILE(x) x += GfTimeClock() - x##_dt
#else
#define BEGIN_PROFILE(x) 
#define END_PROFILE(x) 
#endif
static char *WheelSect[4] = {SECT_FRNTRGTWHEEL, SECT_FRNTLFTWHEEL, SECT_REARRGTWHEEL, SECT_REARLFTWHEEL};
static char *SuspSect[4] = {SECT_FRNTRGTSUSP, SECT_FRNTLFTSUSP, SECT_REARRGTSUSP, SECT_REARLFTSUSP};
static char *BrkSect[4] = {SECT_FRNTRGTBRAKE, SECT_FRNTLFTBRAKE, SECT_REARRGTBRAKE, SECT_REARLFTBRAKE};

#define ABSOLUTE_SPEED_CUTOFF 1.0f
#define SKID_SCALE 0.0002f
#define SKID_THRESHOLD 0.01f

double timer_coordinate_transform = 0.0f;
double timer_reaction = 0.0f;
double timer_angles = 0.0f;
double timer_friction = 0.0f;
double timer_temperature = 0.0f;
double timer_force_calculation = 0.0f;
double timer_wheel_to_car = 0.0f;
double access_times = 0.0f;

void
SimWheelConfig(tCar *car, int index)
{
    void   *hdle = car->params;
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
    wheel->I += wheel->brake.I; /* add brake inertia */
    wheel->staticPos.y    = GfParmGetNum(hdle, WheelSect[index], PRM_YPOS, (char*)NULL, 0);
    x0			  = GfParmGetNum(hdle, WheelSect[index], PRM_RIDEHEIGHT, (char*)NULL, 0.20f);
    wheel->staticPos.az   = GfParmGetNum(hdle, WheelSect[index], PRM_TOE, (char*)NULL, 0.0f);
    wheel->staticPos.ax   = GfParmGetNum(hdle, WheelSect[index], PRM_CAMBER, (char*)NULL, 0.0f);
    Ca                    = GfParmGetNum(hdle, WheelSect[index], PRM_CA, (char*)NULL, 30.0f);
    RFactor               = GfParmGetNum(hdle, WheelSect[index], PRM_RFACTOR, (char*)NULL, 0.8f);
    EFactor               = GfParmGetNum(hdle, WheelSect[index], PRM_EFACTOR, (char*)NULL, 0.7f);
    wheel->lfMax          = GfParmGetNum(hdle, WheelSect[index], PRM_LOADFMAX, (char*)NULL, 1.6f);
    wheel->lfMin          = GfParmGetNum(hdle, WheelSect[index], PRM_LOADFMIN, (char*)NULL, 0.8f);
    wheel->opLoad         = GfParmGetNum(hdle, WheelSect[index], PRM_OPLOAD, (char*)NULL, wheel->weight0 * 1.2f);
    wheel->mass           = GfParmGetNum(hdle, WheelSect[index], PRM_MASS, (char*)NULL, 20.0f);

    wheel->condition = 1.0f;
    wheel->T_current = 50.0f;
    wheel->T_operating = 75.0f;
    wheel->T_range = 200.0f;
    wheel->mfT = 1.0f;
	car->carElt->_tyreT_mid(index) = wheel->T_current;
	car->carElt->_tyreCondition(index) = wheel->condition;

    if (index % 2) {
		wheel->relPos.ax = -wheel->staticPos.ax;
    } else {
		wheel->relPos.ax = wheel->staticPos.ax;
    }
    
    wheel->lfMin = MIN(0.8, wheel->lfMin);
    wheel->lfMax = MAX(1.6, wheel->lfMax);
    
    RFactor = MIN(1.0, RFactor);
    RFactor = MAX(0.1, RFactor);
    EFactor = MIN(1.0, EFactor);

    patchLen = wheel->weight0 / (tirewidth * pressure);

    wheel->width = tirewidth;
    wheel->radius = rimdiam / 2.0f + tirewidth * tireratio;
    wheel->tireSpringRate = wheel->weight0 / (wheel->radius * (1.0 - cos(asin(patchLen / (2.0f * wheel->radius)))));
    wheel->relPos.x = wheel->staticPos.x = car->axle[index/2].xpos;
    wheel->relPos.y = wheel->staticPos.y;
    wheel->relPos.z = wheel->radius - wheel->susp.spring.x0;
    wheel->relPos.ay = wheel->relPos.az = 0;
    wheel->steer = 0;

    /* components */
    SimSuspConfig(hdle, SuspSect[index], &(wheel->susp), wheel->weight0, x0);
    SimBrakeConfig(hdle, BrkSect[index], &(wheel->brake));
    
    carElt->_rimRadius(index) = rimdiam / 2.0;
    carElt->_tireHeight(index) = tirewidth * tireratio;
    carElt->_tireWidth(index) = tirewidth;
    carElt->_brakeDiskRadius(index) = wheel->brake.radius;
    carElt->_wheelRadius(index) = wheel->radius;

    wheel->Ca = Ca;
    wheel->mfC = 2.0 - asin(RFactor) * 2.0 / PI;
    wheel->mfB = Ca / wheel->mfC;
    wheel->mfE = EFactor;
    
    wheel->lfK = log((1.0 - wheel->lfMin) / (wheel->lfMax - wheel->lfMin));
    wheel->spinVel = 0.0;
    wheel->feedBack.I += wheel->I;
    wheel->feedBack.spinVel = 0;
    wheel->feedBack.Tq = 0;
    wheel->feedBack.brkTq = 0;
	wheel->rotational_damage_x = 0.0;//urandom()*0.25;
	wheel->rotational_damage_z = 0.0;//urandom()*0.25;
	wheel->bent_damage_x = urandom();
	wheel->bent_damage_z = urandom();

	wheel->Em = 1.0;
	wheel->s_old = 0.0;
	wheel->F_old = 0.0;

#ifdef USE_THICKNESS
	//wheel->thickness = malloc(sizeof(tdble)*N_THICKNESS_SEGMENTS);
	for (int i=0; i<N_THICKNESS_SEGMENTS; i++) {
		wheel->thickness[i] = 0.0;
		wheel->segtemp[i] = wheel->T_current;
	}
#endif
}


#define MIN_NORMAL_Z 0.1
void
SimWheelUpdateRide(tCar *car, int index)
{
    tWheel *wheel = &(car->wheel[index]);
    tdble Zroad;
    tdble prex;

    /* compute suspension travel */
    RtTrackGlobal2Local(car->trkPos.seg, wheel->pos.x, wheel->pos.y, &(wheel->trkPos), TR_LPOS_SEGMENT);
    wheel->zRoad = Zroad = RtTrackHeightL(&(wheel->trkPos));
    prex = wheel->susp.x;

    
    t3Dd normal;
    t3Dd rel_normal;
    

    tdble dZ;
    // Find normal of track.
    RtTrackSurfaceNormalL(&(wheel->trkPos), &normal);
    
    dZ = wheel->pos.z - Zroad;

	wheel->relPos.az = wheel->steer + wheel->staticPos.az;
    // Transform from world to suspension FOR
    if (index % 2) {
		wheel->relPos.ax = -wheel->staticPos.ax;
    } else {
		wheel->relPos.ax =  wheel->staticPos.ax;
    }
	if (car->options->alignment_damage && wheel->rotational_damage_x>0.0) {
		wheel->relPos.ax += wheel->rotational_damage_x*sin(wheel->relPos.ay + wheel->bent_damage_x);
		wheel->relPos.az += wheel->rotational_damage_z*cos(wheel->relPos.ay + wheel->bent_damage_z);
	}
    //tdble waz = wheel->relPos.az;
	if (USE_QUATERNIONS==0) {
		t3Dd angles;
		angles.x = car->DynGCg.pos.ax + wheel->relPos.ax;
		angles.y = car->DynGCg.pos.ay;
		angles.z = car->DynGCg.pos.az;
		NaiveRotate (normal, angles, &rel_normal);
	} else {
		sgQuat Q;
		sgCopyQuat (Q, car->posQuat);
		sgPreRotQuat (Q, RAD2DEG(wheel->relPos.ax), 1.0f, 0.0f, 0.0f);
		sgVec3 P = {normal.x, normal.y, normal.z};
		sgRotateVecQuat (P, Q);
		sg2t3 (P, rel_normal);
	}
	

    //NaiveRotate (d, angles, &d);
#ifdef USE_THICKNESS
	int seg_id = ((int) ((tdble) N_THICKNESS_SEGMENTS *  (wheel->relPos.ay/(2*M_PI)))) % N_THICKNESS_SEGMENTS;
	if (seg_id<0) seg_id += N_THICKNESS_SEGMENTS;
	tdble adjRadius = wheel->radius + wheel->thickness[seg_id];
#else
	tdble adjRadius = wheel->radius;
#endif
    if (rel_normal.z > MIN_NORMAL_Z) {		
		//tdble dist = dZ*normal.z/rel_normal.z;

		// add a factor as we want to take the *real* wheelpos
		// also used to bounce.
		wheel->susp.fx = adjRadius - adjRadius/rel_normal.z;
		wheel->susp.fy = 0.0;
		wheel->susp.x = wheel->rideHeight =
			adjRadius + ((dZ)*normal.z - adjRadius)/rel_normal.z;
    } else {
		//wheel->susp.x = wheel->rideHeight = (wheel->pos.z - Zroad);
		//	wheel->susp.x = wheel->rideHeight = wheel->susp.spring.packers; 
		wheel->susp.fx = 0.0;
		wheel->state = wheel->state | SIM_SUSP_COMP;
    }

    //wheel->relPos.z = - wheel->susp.x / wheel->susp.spring.bellcrank + wheel->radius; /* center relative to GC */
    /* verify the suspension travel */
    SimSuspCheckIn(&(wheel->susp));
    wheel->rideHeight = wheel->susp.x / wheel->susp.spring.bellcrank;
    if (index % 2) {
		wheel->relPos.ax -= wheel->susp.dynamic_angles.x;
    } else {
		wheel->relPos.ax += wheel->susp.dynamic_angles.x;
    }

    wheel->susp.v = (prex - wheel->susp.x) / SimDeltaTime;
    /* update wheel brake */
    SimBrakeUpdate(car, wheel, &(wheel->brake));
    
}

// Note that this differs in the calculation of sx, sy, sa
// from simuv2, but is exactly the same when everything is horizontal.
// I changed the implementation so that what happens is mathematically
// clearer, though the code is not very clear :/
void
SimWheelUpdateForce(tCar *car, int index)
{
    tWheel 	*wheel = &(car->wheel[index]);
    tdble 	axleFz = wheel->axleFz;
    //    tdble 	vt, v, v2;
    tdble       wrl; /* wheel related velocity */
    tdble 	Fn, Ft, Ft2;
    tdble 	waz;
    tdble 	CosA, SinA;
    tdble	s = 0.0;
    tdble       sa, sx, sy; /* slip vector */
    tdble	stmp, F, Bx;
    tdble	mu;
    tdble       reaction_force;
    tdble f_z = 0.0;
    t3Dd angles;
    t3Dd normal;
    t3Dd rel_normal;
    bool right_way_up = true;
    static long wcnt = 0;

#ifdef USE_THICKNESS
	int seg_id = (int) ((tdble) N_THICKNESS_SEGMENTS *  (wheel->relPos.ay/(2*M_PI))) % N_THICKNESS_SEGMENTS;
	if (seg_id<0) seg_id += N_THICKNESS_SEGMENTS;
	tdble adjRadius = wheel->radius + wheel->thickness[seg_id];
#else
	tdble adjRadius = wheel->radius;
#endif	


	wheel->T_current = car->carElt->_tyreT_mid(index);
	wheel->condition = car->carElt->_tyreCondition(index);

    waz = wheel->relPos.az;//wheel->steer + wheel->staticPos.az;
    /* Get normal of road relative to the wheel's axis 
	   This should help take into account the camber.*/

	BEGIN_PROFILE(timer_coordinate_transform);
    
    RtTrackSurfaceNormalL(&(wheel->trkPos), &normal);
    
	if (USE_QUATERNIONS==0) {
		angles.x = car->DynGCg.pos.ax + wheel->relPos.ax;
		angles.y = car->DynGCg.pos.ay;
		angles.z = car->DynGCg.pos.az + waz;
		NaiveRotate (normal, angles, &rel_normal);
	} else {
		sgQuat Q;
		sgCopyQuat (Q, car->posQuat);
		sgPreRotQuat (Q, RAD2DEG(wheel->relPos.ax), 1.0f, 0.0f, 0.0f);
		sgPreRotQuat (Q, RAD2DEG(waz), 0.0f, 0.0f, 1.0f);
		sgVec3 P = {normal.x, normal.y, normal.z};
		sgRotateVecQuat (P, Q);
		sg2t3 (P, rel_normal);
	}
    wheel->state = 0;
	END_PROFILE(timer_coordinate_transform);

	BEGIN_PROFILE(timer_reaction);
    Ft = 0.0;
    Fn = 0.0;
    wheel->forces.x = 0.0;
    wheel->forces.y = 0.0;
    wheel->forces.z = 0.0;

	
    /* Now uses the normal, so it should work */
    /* update suspension force */
    SimSuspUpdate(&(wheel->susp));
    /* check suspension state */
    wheel->state |= wheel->susp.state;
    reaction_force = 0.0;

    wheel->forces.z = 0;
    Ft = Fn = 0;
    reaction_force = 0.0;
    if ((wheel->state & SIM_SUSP_EXT) == 0) {
		f_z  = axleFz + wheel->susp.force;

		if ((f_z < 0)) {
			f_z = 0;
		}
		/* project the reaction force. Only wheel->forces.z is
		   actually interesting for friction. The rest is just
		   reaction. Now we have included the reaction from the sides
		   which is fake.
		   The suspension pushes the wheel down with f_z, but the reaction
		   of the surface is just f_z*rel_normal.z;!
		*/
		if ((right_way_up) && (rel_normal.z > MIN_NORMAL_Z)) {
			// reaction force on track z axis should be equal to
			// suspension reaction if suspension is perpendicular
			// to the track plane. We assume other reaction forces
			// proportional, but things break down when car is 
			// tilted a lot with respect to the track plane.
			tdble invrel_normal = 1.0/rel_normal.z;
			if (invrel_normal>= 4.0) {
				invrel_normal = 4.0;
			} else if (invrel_normal<=-4.0) {
				invrel_normal = -4.0;
			}
			reaction_force = f_z * invrel_normal;
			// the other reactions are then:
			Ft = reaction_force*rel_normal.x;//*invrel_normal;
			Fn = reaction_force*rel_normal.y;//*invrel_normal;
		} else {
			f_z = 0;
			wheel->susp.force = 0;
			wheel->forces.z = 0;
			Ft = Fn = 0;
			reaction_force = 0.0;
		}

    }

    wheel->relPos.z = - wheel->susp.x / wheel->susp.spring.bellcrank + adjRadius; /* center relative to GC */
	END_PROFILE(timer_reaction);


	BEGIN_PROFILE(timer_angles);
    /* HORIZONTAL FORCES */

    CosA = cos(waz);
    SinA = sin(waz);

    /* tangent velocity */
    // This is speed of the wheel relative to the track, so we have
    // to take the projection to the track.
    tdble rel_normal_xz = sqrt (rel_normal.z*rel_normal.z
								+ rel_normal.x*rel_normal.x);
    tdble rel_normal_yz = sqrt (rel_normal.z*rel_normal.z
								+ rel_normal.y*rel_normal.y);
    //tdble rel_normal_xy = sqrt (rel_normal.x*rel_normal.x
	//							+ rel_normal.y*rel_normal.y);


	END_PROFILE(timer_angles);

#ifndef FREE_MOVING_WHEELS
    wheel->bodyVel.z = 0.0;
#endif
    wrl = (wheel->spinVel + car->DynGC.vel.ay) * adjRadius;
    {
		// this thing here should be faster than quat?
		t3Dd angles = {wheel->relPos.ax, 0.0, waz};
		NaiveRotate (wheel->bodyVel, angles, &wheel->bodyVel);
    }

    tdble wvx = wheel->bodyVel.x * rel_normal_yz;
    tdble wvy = wheel->bodyVel.y * rel_normal_xz;
    tdble absolute_speed = sqrt(wvx*wvx + wvy*wvy);
    wvx -= wrl;
    wheel->bodyVel.x = wvx;
    wheel->bodyVel.y = wvy;

	BEGIN_PROFILE(timer_friction);
    tdble relative_speed = sqrt(wvx*wvx + wvy*wvy);
    if ((wheel->state & SIM_SUSP_EXT) != 0) {
	    sx = sy = sa = 0;
    } else if (absolute_speed < ABSOLUTE_SPEED_CUTOFF) {
	    sx = wvx/ABSOLUTE_SPEED_CUTOFF;
	    sy = wvy/ABSOLUTE_SPEED_CUTOFF;
	    sa = atan2(wvy, wvx);
    } else {
		// the division with absolute_speed is a bit of a hack. The
		// real solution is to use a first or second-order integration
		// model to update both the forces on the car and the
		// appropriate spin velocity.
		sx = wvx/absolute_speed;
		sy = wvy/absolute_speed;
		sa = atan2(wvy, wvx);
    }

	s = sqrt(sx*sx+sy*sy);

	wcnt++;
	access_times = (float) wcnt;
	//if (index==0) {
	//wcnt--;
	//}

	if (wcnt<0) {
		//printf ("%f", reaction_force);
		if (index==3) {
			wcnt = 10;
			//printf ("#RCT\n");
		} else {
			//printf (" ");
		}
	}

    if (right_way_up) {
		if (fabs(absolute_speed) < 2.0f && fabs(wrl) < 2.0f) {
			car->carElt->_skid[index] = 0.0f;
		} else {
			car->carElt->_skid[index] =  MIN(1.0f, (s*reaction_force*0.0002f));
		}
		//0.0002*(MAX(0.2, MIN(s, 1.2)) - 0.2)*reaction_force;
		car->carElt->_reaction[index] = reaction_force;
    } else {
		car->carElt->_skid[index] = 0.0f;
		car->carElt->_reaction[index] = 0.0f;
    }
    
    stmp = MIN(s, 1.5);

    /* MAGIC FORMULA */
    Bx = wheel->mfB * stmp;
    tdble dynamic_grip = wheel->mfT * sin(wheel->mfC * atan(Bx * (1 - wheel->mfE) + wheel->mfE * atan(Bx))) * (1.0f + stmp * simSkidFactor[car->carElt->_skillLevel]);

	//printf ("%f\n", simSkidFactor[car->carElt->_skillLevel]);

	/* load sensitivity */
    mu = wheel->mu * (wheel->lfMin + (wheel->lfMax - wheel->lfMin) * exp(wheel->lfK * reaction_force / wheel->opLoad));
    
	tdble static_grip = wheel->condition * reaction_force * mu * wheel->trkPos.seg->surface->kFriction;

    F = dynamic_grip * static_grip;

	{
		tdble Bx = wheel->mfB * sa;
		car->carElt->_wheelFy(index) =  cos(sa)*wheel->mfT * sin(wheel->mfC * atan(Bx * (1 - wheel->mfE) + wheel->mfE * atan(Bx))) * (1.0 + stmp * simSkidFactor[car->carElt->_skillLevel]) * static_grip;
	}
	END_PROFILE(timer_friction);

	BEGIN_PROFILE(timer_temperature);
	if (car->options->tyre_temperature) {
    	// heat transfer function with air
		tdble htrf = (0.002 + fabs(absolute_speed)*0.0005)*SimDeltaTime;
		tdble T_current = wheel->T_current;
		tdble T_operating = wheel->T_operating;
		tdble T_range = wheel->T_range;
		tdble mfT;
		// friction heat transfer
		T_current += 0.00003*((fabs(relative_speed)+0.1*fabs(wrl))*reaction_force)*SimDeltaTime;
		T_current = T_current * (1.0-htrf) + htrf * 25.0;	
		tdble dist = (T_current - T_operating)/T_range;
		//mfT = 100.0f * exp(-0.5f*(dist*dist))/T_range;
		mfT = 0.85f + 3.0f * exp(-0.5f*(dist*dist))/T_range;
		if (T_current>200.0) T_current=200.0;
		wheel->mfT = mfT;
		wheel->T_current = T_current;
	
    }

    if (car->options->tyre_damage > 0.0f && s>0.01f) {
		tdble compound_melt_point = wheel->T_operating + wheel->T_range;
		tdble adherence = wheel->Ca * 500.0f; 
		tdble melt = (exp (2.0f*(wheel->T_current - compound_melt_point)/compound_melt_point)) * car->options->tyre_damage;
		tdble removal = exp (2.0f*(F - adherence)/adherence);
		tdble wheel_damage = 0.001f* melt * relative_speed * removal / (2.0f * M_PI * wheel->radius * wheel->width * wheel->Ca);

		if (wheel_damage>0.01f) {
			wheel_damage = 0.01f;
		}
		tdble delta_dam = wheel_damage * SimDeltaTime;
		wheel->condition -= 0.5f*delta_dam;
		if (wheel->condition < 0.5f) wheel->condition = 0.5f;
    } else {
		wheel->mfT = 1.0f;
	}
	END_PROFILE(timer_temperature);

	BEGIN_PROFILE(timer_force_calculation);

    wheel->rollRes = reaction_force * wheel->trkPos.seg->surface->kRollRes;
    car->carElt->priv.wheel[index].rollRes = wheel->rollRes;

    // Calculate friction forces
    Ft2 = 0.0f;
    tdble Fn2 = 0.0f;
	tdble epsilon = 0.00001f;
	if (s > epsilon) {
		/* wheel axis based - no control after an angle*/
		if (rel_normal.z > MIN_NORMAL_Z) {
			// When the tyre is tilted there is less surface
			// touching the road. Modelling effect simply with rel_normal_xz.
			// Constant 1.05f for equality with simuv2.
			tdble sur_f = 1.05f * rel_normal_xz;
			sur_f = 1.0;
			Ft2 = - sur_f*F*sx/s;
			Fn2 = - sur_f*F*sy/s;
		} else {
			Ft2 = 0.0f;
			Fn2 = 0.0f;
		}
    } else {
		tdble sur_f = rel_normal_xz;
		Ft2 = - sur_f*F*sx/epsilon;
		Fn2 = - sur_f*F*sy/epsilon;
	}
	Ft2 -= tanh(wrl) * fabs(wheel->rollRes);
	wheel->forces.x = Ft2 * rel_normal_yz;
	wheel->forces.y = Fn2 * rel_normal_xz; 
	wheel->forces.z = Ft2 * rel_normal.x + Fn2 * rel_normal.y;

	END_PROFILE(timer_force_calculation);
	
	if (0) {
		// EXPERIMENTAL code - estimate amount of mass linked to this
		// wheel. Maybe useful for adjusting the slope of the 
		// static friction function. Currently not used.
		tdble Ftot = sqrt(Ft2*Ft2 + Fn2*Fn2);
		tdble ds = wheel->s_old-s;
		tdble EF = wheel->Em * ds;
		tdble dF = wheel->F_old - EF;
		wheel->Em += 0.1 * dF*ds;
		wheel->F_old = Ftot;
		wheel->s_old = s;
	}

    wheel->relPos.az = waz;
    if (rel_normal.z > MIN_NORMAL_Z) {
		right_way_up = true;
    } else {
		right_way_up = false;
    }


    if (right_way_up==false) {
		Fn = 0.0f;
		Ft = 0.0f;
		wheel->forces.x = 0.0f;
		wheel->forces.y = 0.0f;
		wheel->forces.z = 0.0f;
		Ft2 = 0.0f;
		wheel->spinTq = 0.0f;
    } else {
		BEGIN_PROFILE (timer_wheel_to_car);
		t3Dd f;
		// send friction and reaction forces to the car
		// normally we would not need to add f.z here, as that
		// would be purely coming from the suspension. However
		// that would only be the case if the wheels were really
		// independent objects. Right now their position is determined
		// in update ride, so we have no choice but to transmit the
		// suspension-parallel friction forces magically to the car.
		f.x = wheel->forces.x;
		f.y = wheel->forces.y;
		f.z = wheel->forces.z;

		// TODO: Check whether this is correct.
		angles.x = wheel->relPos.ax + asin(rel_normal.x);
		angles.y = asin(rel_normal.y);
		angles.z = waz;
		NaiveInverseRotate (f, angles, &wheel->forces);
		// transmit reaction forces to the car	
		wheel->forces.x +=(Ft* CosA - Fn * SinA);
		wheel->forces.y +=(Ft* SinA + Fn * CosA);

		RELAXATION2(wheel->forces.x, wheel->preFn, 50.0f);
		RELAXATION2(wheel->forces.y, wheel->preFt, 50.0f);

		wheel->forces.z = f_z; // only suspension acts on z axis.
		car->carElt->_wheelFx(index) = wheel->forces.x;
		car->carElt->_wheelFz(index) = wheel->forces.z;

		wheel->spinTq = Ft2 * adjRadius;
		wheel->sa = sa;
		wheel->sx = sx;
		END_PROFILE (timer_wheel_to_car);
    }
    wheel->feedBack.spinVel = wheel->spinVel;
    wheel->feedBack.Tq = wheel->spinTq;
    wheel->feedBack.brkTq = wheel->brake.Tq;
	car->carElt->_tyreT_mid(index) = wheel->T_current;
	car->carElt->_tyreCondition(index) = wheel->condition;
	car->carElt->_wheelSlipSide(index) = wvy;
	car->carElt->_wheelSlipAccel(index) = wvx;

}


void
SimWheelUpdateRotation(tCar *car)
{
    int			i;
    tWheel 		*wheel;

    for (i = 0; i < 4; i++) {
		wheel = &(car->wheel[i]);
		wheel->spinVel = wheel->in.spinVel;
	
		RELAXATION2(wheel->spinVel, wheel->prespinVel, 50.0f);
	
		wheel->relPos.ay += wheel->spinVel * SimDeltaTime;
		car->carElt->_wheelSpinVel(i) = wheel->spinVel;
    }
}


void
SimUpdateFreeWheels(tCar *car, int axlenb)
{
    int			i;
    tWheel 		*wheel;
    tdble		BrTq;		/* brake torque */
    tdble		ndot;		/* rotation acceleration */
    tdble		I;
    
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
