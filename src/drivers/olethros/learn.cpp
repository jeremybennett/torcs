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
#include "ANN.h"
#include "string_utils.h"
#include <iostream>

#ifdef USE_OLETHROS_NAMESPACE
namespace olethros
{
#endif

/// Check that tags match
inline bool CheckMatchingToken (char* tag, StringBuffer* buf, FILE* f)
{
	int l = 1+strlen(tag);
	buf = SetStringBufferLength (buf, l);
	if (buf==NULL) {
		free(tag);
		return false;
	}
	fread(buf->c, sizeof(char), l, f);

	if (strcmp(tag,buf->c)) {
		fprintf (stderr, "Expected tag <%s>, found <%s>.\n", tag, buf->c);
		free(tag);
		return false;
	}
	free(tag);
	return true;
}

/// Write a token
inline void WriteToken (char* tag, FILE* f)
{
	fwrite (tag, sizeof(char), 1+strlen(tag), f);
}

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
	segdm3 = new float[t->nseg];
	dm = 0.0;
	dm2 = 0.0;
	dm3 = 0.0;

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
		segdm3[i] = 0.0;
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
	delete [] segdm2;
	delete [] segdm3;

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
			check == true 
			&& alone > 0
		) {
			//printf ("%d %f\n", alone, offset);
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
			float target_toRight = seg->width * (alpha);
			// if negative then we are to the right of our target.
			// if positive then we are to the left of our target.
			// theta is a simple threshold
			float target_error = fabs(target_toLeft - car->_trkPos.toLeft);
			float theta = 0.5*seg->width;//car->_dimension_y;
			if (lastturn == TR_RGT) {
				float dtheta = theta-target_error;
				if (target_toRight > car->_trkPos.toRight) {
					dtheta = theta;
				}
				if (car->_trkPos.toLeft < 1.5*car->_dimension_y) {
					float a = 1.5*car->_dimension_y - car->_trkPos.toLeft;
					dtheta = (1-a) * dtheta;
				}
				if (car->_trkPos.toLeft - car->_dimension_y<0) {
					dtheta = car->_trkPos.toLeft - car->_dimension_y;// - 1;
				}
				if ((car->_trkPos.toLeft - .5*car->_dimension_y<0)
					|| (car->_speed_x < 0)) {
 					dtheta = -10;
					PropagateUpdateBackwards (seg, -10, 0.02, 100.0);
					//printf ("DTH %d\n ", seg->id);
				}

				dr = (1-beta) * (outside - tomiddle)
					+ beta * (dtheta);
			} else if (lastturn == TR_LFT) {
				float dtheta = theta - target_error;
				if (target_toLeft > car->_trkPos.toLeft) {
					dtheta = theta;
				}
				if (car->_trkPos.toRight < 1.5*car->_dimension_y) {
					float a = 1.5*car->_dimension_y - car->_trkPos.toRight;
					dtheta = (1-a) * dtheta;
				}
				if (car->_trkPos.toRight - car->_dimension_y<0) {
					dtheta = car->_trkPos.toRight - car->_dimension_y;// - 1;
				}
				if ((car->_trkPos.toRight - .5*car->_dimension_y < 0)
					|| (car->_speed_x < 0)) {
					dtheta = -10;
					PropagateUpdateBackwards (seg, -10, 0.02, 100.0);
					//printf ("DTH %d\n", seg->id);
				}
				dr = (1-beta) * (outside + tomiddle)
					+ beta * (dtheta);
			}
			
			//printf ("%f %f %f %f \n", target_error, dr, rmin, r[seg->id]);

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

void SegLearn::PropagateUpdateBackwards (tTrackSeg* pseg, float d, float beta, float max_length)
{

	//printf ("back: %d->", pseg->id);
	for (float length = 0; length<max_length;) {
		length += pseg->length;
		pseg = pseg->prev;
		radius[updateid[pseg->id]] += d*exp(-beta*length);
	}
	//printf ("%d\n", pseg->id);
}

float SegLearn::updateAccel (tSituation* s, tCarElt* car, float taccel, float derr, float dtm)
{
	float alpha = 0.05;
	float beta = 1.0;
	float lambda = 0.9;
	tTrackSeg* seg = car->_trkPos.seg;
	
	float in_track = 1.0;
	if (car->_trkPos.toRight - car->_dimension_y<0) {
		in_track = 1-fabs(tanh(0.5*(car->_trkPos.toRight - car->_dimension_y)));
		dtm = 2.0*(car->_trkPos.toRight - car->_dimension_y);
		//printf ("R:%f %f\n", car->_steerCmd, dtm);
	}
	if (car->_trkPos.toLeft - car->_dimension_y<0) {
		in_track = 1-fabs(tanh(0.5*(car->_trkPos.toLeft - car->_dimension_y)));
		dtm = -2.0*(car->_trkPos.toLeft - car->_dimension_y);
		//printf ("L:%f %f\n", car->_steerCmd, dtm);
	}
	if (car->_speed_x < 0) {
		in_track = 0;
		taccel = -1;
	}
	int segid = (seg->id);
	int quantum = segQuantum(segid);
	//float prev_quantum_accel = accel[prev_quantum];
	if (quantum != prev_quantum) {
		float dt = s->currentTime - previous_time;
		previous_time = s->currentTime;
		float gamma =exp(-dt*beta);
		float lg = lambda*gamma;

		//printf ("%f g%f\n", dt, gamma);
		elig[prev_quantum] = 1.0;

		float da = alpha * (taccel - accel[prev_quantum]);
		float ds = alpha * in_track * (dtm + gamma*derror[quantum] - derror[prev_quantum]);
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
	return  accel[quantum];//+ prev_quantum_accel);
}

float SegLearn::predictedError (tCarElt* car)
{
	tTrackSeg* seg = car->_trkPos.seg;
	int segid = seg->id;
	return derror[segid];
}

float SegLearn::predictedAccel (tTrackSeg* seg)
{
	int segid = seg->id;
	return derror[segid];
}

int SegLearn::segQuantum (int segid)
{
	int q = segid/segments_per_quantum;
	assert (q<n_quantums);
	return q;
}

/**
   Model the system
   \f[
   \frac{du}{dt}=
   s_{brake} (
     \mu G + w_1 +
	 \frac{(C_A \mu + C_W + w_2) u^2}{m} 
   )
   \f]
 */
void SegLearn::AdjustFriction (tTrackSeg* s, float G, float mass_, float CA_, float CW_, float u_, float brake_, float learning_rate)
{

	float mu_ = s->surface->kFriction;
	float du = (u_ - u)*delta_time;
	float pdu = -delta_time*(SIGN(u)*(
									  brake*(mu*G + dm+segdm[prevsegid]+
											 ((CA*mu+CW+dm2+segdm2[prevsegid])/mass)*u*u)
									  //+ u*u*(CW+dm3+segdm3[prevsegid])/mass
									  )
							 );
	float delta = learning_rate * (du-pdu);
	float der_dm = -SIGN(u)*brake;
	float der_dm2 = -SIGN(u)*u*u*brake/mass;
	float der_dm3 = -SIGN(u)*u*u/mass;
	dm += delta * der_dm;
	dm2 += delta* der_dm2;
	//dm3 += delta* der_dm3;
	segdm[prevsegid] += delta * der_dm;
	segdm2[prevsegid] += delta* der_dm2;
	//segdm3[prevsegid] += delta* der_dm3;
	mu=0.5*mu_; 
	mass=mass_;
	CA=0.5*CA_; 
	CW=0.5*CW_; 
	u=u_;
#if 0
	if (1) {
		printf ("%f | %f %f | %f %f | %f %f | %f\n", brake,
				dm, segdm[prevsegid],
				dm2, segdm2[prevsegid],
				dm3, segdm3[prevsegid],
				delta);
	}
#endif
	brake=brake_;
	prevsegid = s->id;
}



void SegLearn::loadParameters (char* fname)
{
	std::cout << "Maybe load parameters from " << fname << std::endl;
	FILE* f = fopen(fname,"r");
	if (!f) { // no error here.
		return;
	}
	
	StringBuffer* rtag = NewStringBuffer (256);
	CheckMatchingToken(make_message("OLETHROS_LEARN"), rtag, f);
	int local_n_quantums;
	fread (&local_n_quantums, sizeof(int), 1, f);
	if (local_n_quantums!=n_quantums) {
		std::cerr << "Number of quantums " << local_n_quantums << " does not agree with current (" << n_quantums << "). Aborting read.\n";
		fclose(f);
		return;
	}
	CheckMatchingToken(make_message("RADI"), rtag, f);
	fread (radius, n_seg, sizeof(float), f);

	CheckMatchingToken(make_message("DM FRICTION"), rtag, f);
	fread (segdm, sizeof(float), n_seg,  f);
	fread (segdm2, sizeof(float), n_seg, f);
	fread (segdm3, sizeof(float), n_seg, f);
	fread (&dm, sizeof(float), 1, f);
	fread (&dm2, sizeof(float), 1, f);
	fread (&dm3, sizeof(float), 1, f);

	CheckMatchingToken(make_message("PRED ACCEL"), rtag, f);
	fread (accel, sizeof(float), n_quantums,  f);
	CheckMatchingToken(make_message("PRED STEER"), rtag, f);
	fread (derror, sizeof(float), n_quantums,  f);
	
	CheckMatchingToken(make_message("END"),rtag, f);
	FreeStringBuffer(&rtag);
	fclose(f);
	std::cout << "Parameters loaded\n";
}

/// Save
void SegLearn::saveParameters (char* fname)
{
	FILE* f = fopen(fname,"w");
	std::cout << "Maybe save parameters to " << fname << std::endl;
	if (!f) {
		std::cerr << "Could not open " << fname << " for writing. Check permissions\n";
		return;
	}

	//StringBuffer* rtag = NewStringBuffer (256);
	WriteToken(make_message("OLETHROS_LEARN"), f);

	fwrite (&n_quantums, sizeof(int), 1, f);

	WriteToken(make_message("RADI"), f);
	fwrite (radius, n_seg, sizeof(float), f);

	WriteToken(make_message("DM FRICTION"), f);
	fwrite (segdm, sizeof(float), n_seg,  f);
	fwrite (segdm2, sizeof(float), n_seg, f);
	fwrite (segdm3, sizeof(float), n_seg, f);
	fwrite (&dm, sizeof(float), 1, f);
	fwrite (&dm2, sizeof(float), 1, f);
	fwrite (&dm3, sizeof(float), 1, f);

	WriteToken(make_message("PRED ACCEL"), f);
	fwrite (accel, sizeof(float), n_quantums,  f);
	WriteToken(make_message("PRED STEER"), f);
	fwrite (derror, sizeof(float), n_quantums,  f);
	
	WriteToken(make_message("END"), f);
	//FreeStringBuffer(&rtag);
	fclose(f);
	std::cout << "Parameters saved\n";
}

#ifdef USE_OLETHROS_NAMESPACE
}
#endif
