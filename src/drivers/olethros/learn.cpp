/***************************************************************************

    file                 : learn.cpp
    created              : Wed Aug 28 16:36:00 CET 2004
    copyright            : (C) 2004 by Bernhard Wymann
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


#include "learn.h"

SegLearn::SegLearn(tTrack* t)
{
	int i;
	track = t;
	n_seg = t->nseg;
	segments_per_quantum = 1;
	n_quantums = 1 + n_seg / segments_per_quantum;
	prev_quantum = n_quantums-1;

	radius = new float[t->nseg];
	updateid = new int[t->nseg];
	accel = new float[n_quantums];
	derror = new float[n_quantums];
	elig = new float[n_quantums];
	
	segdm = new float[t->nseg];
	segdm2 = new float[t->nseg];

	tTrackSeg *seg = t->seg;

	// Switch seg to seg 0 for sure.
	while (seg->id != 0) {
		seg = seg->prev;
	}

	for (i=0; i<n_quantums; i++) {
		accel[i] = 0.0;
		derror[i] = 0.0;
		elig[i] = 0.0;
	}

	for (i = 0; i < t->nseg; i++) {
		segdm[i] = 0.0;
		segdm2[i] = 0.0;
		radius[i] = 0.0;
		updateid[i] = i;
		// Search the last turn in case of a straight.
		if (seg->type == TR_STR) {
			tTrackSeg *cs = seg;
			while (cs->type == TR_STR) {
				cs = cs->prev;
			}
			updateid[seg->id] = cs->id;
		}
		seg = seg->next;
	}

	check = false;
	rmin = t->width/2.0;
	prevtype = lastturn = TR_STR;
	mu = 1.0;
	mass = 1000.0;
	CA =0.5;
	CW = 0.5;
	u = 0.0;
	brake = 0.0;
	previous_time = 0;
	prev_time = 0;
	prevsegid = 0;
}


SegLearn::~SegLearn()
{
	delete [] radius;
	delete [] updateid;
	delete [] accel;
	delete [] derror;
	delete [] elig;
	delete [] segdm;
	delete [] segdm;
}


void SegLearn::update(tSituation *s, tTrack *t, tCarElt *car, int alone, float offset, float outside, float *r, float alpha)
{
	// Still on the same segment, alone, offset near 0, check.
	tTrackSeg *seg = car->_trkPos.seg;
	if (prev_time!=s->currentTime) {
		delta_time = s->currentTime - prev_time;
		prev_time = s->currentTime;
	}
	if (seg->type == lastturn || seg->type == TR_STR) {
		if (fabs(offset) < 0.2 &&
			check == true &&
			alone > 0
		) {
			// + to left, - to right
			float dr = 0.0;
			float tomiddle = car->_trkPos.toMiddle;
			// adjusted tomiddle

			float beta = 1.0;
			// manage beta?
			// beta = 1.0/(1.0+.25*car->_laps);
			//if (car->_laps<10) {
			//				beta = 0.5;
			//			} else {
			//				beta = 0.1;
			//			}
			tomiddle = tomiddle;
			float target_toLeft = seg->width * (1-alpha);
			// if negative then we are to the right of our target.
			// if positive then we are to the left of our target.
			// theta is a simple threshold
			float target_error = fabs(target_toLeft - car->_trkPos.toLeft);
			float theta = .5*seg->width;//car->_dimension_y;
			if (lastturn == TR_RGT) {
				float dtheta = theta-target_error;
				if (car->_trkPos.toLeft - car->_dimension_y<0) {
					dtheta = car->_trkPos.toLeft - car->_dimension_y;
				}
				if (car->_trkPos.toLeft - .5*car->_dimension_y<0) {
					dtheta = -10;
					//printf ("DTH %d %f\n", seg->id, radius[seg->id]);
				} 
				dr = (1-beta) * (outside - tomiddle)
					+ beta * (dtheta);
			} else if (lastturn == TR_LFT) {
				float dtheta = theta - target_error;
				if (car->_trkPos.toRight - car->_dimension_y<0) {
					dtheta = car->_trkPos.toRight - car->_dimension_y;
				}
				if (car->_trkPos.toRight - .5*car->_dimension_y<0) {
					dtheta = -10;
					//printf ("DTH %d %f\n", seg->id, radius[seg->id]);
				}
				dr = (1-beta) * (outside + tomiddle)
					+ beta * (dtheta);
				//printf ("%f %f\n", target_error, dr);
			}
			

			if (dr < rmin) {
				rmin = dr;
			}
		} else {
			check = false;
		}
	}

	if (seg->type != prevtype) {
		prevtype = seg->type;
		if (seg->type != TR_STR) {
			if (check == true) {
				tTrackSeg *cs = seg->prev;
				// Skip straights.
				while (cs->type == TR_STR) {
					cs = cs->prev;
				}

				while (cs->type == lastturn) {
					if (radius[updateid[cs->id]] + rmin < 0.0) {
						rmin = MAX(cs->radius - r[cs->id], rmin);
					}
					radius[updateid[cs->id]] += rmin;
					radius[updateid[cs->id]] = MIN(radius[updateid[cs->id]], 1000.0);
					cs = cs->prev;
				}
			}
			check = true;
			rmin = MIN(seg->width/2.0, seg->radius/10.0);
			lastturn = seg->type;
		}
	}
}

float SegLearn::updateAccel (tSituation* s, tCarElt* car, float taccel, float derr, float dtm)
{
	float alpha = 0.1;
	float beta = 1.0;
	float lambda = 0.9;
	tTrackSeg* seg = car->_trkPos.seg;
	
	
	if (car->_trkPos.toRight - car->_dimension_y<0) {
		dtm = 2*(car->_trkPos.toRight - car->_dimension_y);
		//printf ("R:%f %f\n", car->_steerCmd, dtm);
	}
	if (car->_trkPos.toLeft - car->_dimension_y<0) {
		dtm = -2*(car->_trkPos.toLeft - car->_dimension_y);
		//printf ("L:%f %f\n", car->_steerCmd, dtm);
	}
	int segid = (seg->id);
	int quantum = segQuantum(segid);
	float prev_quantum_accel = accel[prev_quantum];
	if (quantum != prev_quantum) {
		float dt = s->currentTime - previous_time;
		previous_time = s->currentTime;
		float gamma =exp(-dt*beta);
		float lg = lambda*gamma;

		//printf ("%f g%f\n", dt, gamma);
		elig[prev_quantum] = 1.0;

		float da = alpha * (taccel-  accel[prev_quantum]);
		float ds = alpha * (dtm + gamma*derror[quantum] - derror[prev_quantum]);
		for (int i=0; i<n_quantums; i++) {
			accel[i] += elig[i] * da;
			derror[i] += elig[i] * ds;
			elig[i] *= lg;
		}
		prev_quantum = quantum;
		prev_accel = taccel;
		averages.k = 0;
	} 
		
	averages.Measure(taccel, derr, dtm);
	
	//printf ("%f %f\n", accel[segid], derror[segid]);
	return  taccel;//accel[quantum];//+ prev_quantum_accel);
}

float SegLearn::predictedError (tCarElt* car)
{
	tTrackSeg* seg = car->_trkPos.seg;
	int segid = seg->id;
	return derror[segid];
}

int SegLearn::segQuantum (int segid)
{
	int q = segid/segments_per_quantum;
	assert (q<n_quantums);
	return q;
}

void SegLearn::AdjustFriction (tTrackSeg* s, float G, float mass_, float CA_, float CW_, float u_, float brake_)
{

	float mu_ = s->surface->kFriction;
	float du = (u_ - u)*delta_time;
	float pdu = -delta_time*SIGN(u)*brake*(mu*G + dm+segdm[prevsegid]
										   +((CA*mu+CW+dm2+segdm2[prevsegid])/mass)*u*u);
	float delta = (du-pdu);
	float der_dm = -SIGN(u)*brake;
	float der_dm2 = -SIGN(u)*u*u*brake/mass;
	dm += delta * der_dm;
	dm2 += delta* der_dm2;
	segdm[prevsegid] += delta * der_dm;
	segdm2[prevsegid] += delta* der_dm2;
	mu=.5*mu_;
	mass=mass_;
	CA=.5*CA_;
	CW=.5*CW_;
	u=u_;
#if 0
	if (brake>0){
		printf ("%f %f %f %f %f\n",
				dm, segdm[prevsegid],
				dm2, segdm2[prevsegid], delta);
	}
#endif
	brake=brake_;
	prevsegid = s->id;
}
