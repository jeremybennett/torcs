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
	n_seg = t->nseg;
	segments_per_quantum = 1;
	n_quantums = 1 + n_seg / segments_per_quantum;
	prev_quantum = n_quantums-1;

	radius = new float[t->nseg];
	updateid = new int[t->nseg];
	accel = new float[n_quantums];
	derror = new float[n_quantums];
	elig = new float[n_quantums];

	tTrackSeg *seg = t->seg;

	// Switch seg to seg 0 for sure.
	while (seg->id != 0) {
		seg = seg->prev;
	}

	for (i=0; i<n_quantums; i++) {
		accel[i] = 1.0;
		derror[i] = 0.0;
		elig[i] = 0.0;
	}

	for (i = 0; i < t->nseg; i++) {
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
}


SegLearn::~SegLearn()
{
	delete [] radius;
	delete [] updateid;
	delete [] accel;
	delete [] derror;
	delete [] elig;
}


void SegLearn::update(tSituation *s, tTrack *t, tCarElt *car, int alone, float offset, float outside, float *r)
{
	// Still on the same segment, alone, offset near 0, check.
	tTrackSeg *seg = car->_trkPos.seg;

	if (seg->type == lastturn || seg->type == TR_STR) {
		if (fabs(offset) < 0.2 &&
			check == true &&
			alone > 0
		) {
			// + to left, - to right
			float tomiddle = car->_trkPos.toMiddle;
			float dr = 0.0;
			if (lastturn == TR_RGT) {
				dr = outside - tomiddle;
			} else if (lastturn == TR_LFT) {
				dr = outside + tomiddle;
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

float SegLearn::updateAccel (tCarElt* car, float taccel, float derr, float dtm)
{
	float alpha = 0.1;
	float gamma = 0.95;
	float lambda = 0.9;
	float lg = lambda*gamma;

	tTrackSeg* seg = car->_trkPos.seg;

	int segid = (seg->id);
	int quantum = segQuantum(segid);
	if (quantum != prev_quantum) {
		elig[prev_quantum] = 1.0;

		float da = alpha * (taccel - accel[prev_quantum]);
		float ds = alpha * (dtm + gamma*derror[quantum] - derror[prev_quantum]);
		for (int i=0; i<n_quantums; i++) {
			accel[i] += elig[i] * da;
			derror[i] += elig[i] * ds;
			elig[i] *= lg;
		}
		prev_quantum = quantum;
	}
	//printf ("%f %f\n", accel[segid], derror[segid]);
	return accel[quantum];
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
