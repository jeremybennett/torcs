// -*- Mode: c++ -*-
/***************************************************************************

    file                 : learn.h
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


#ifndef _SEGLEARN_H_
#define _SEGLEARN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <tgf.h>
#include <track.h>
#include <car.h>
#include <raceman.h>
#include <robottools.h>
#include <robot.h>



class SegLearn {
public:
	SegLearn(tTrack* t);
	~SegLearn();

	float getRadius(tTrackSeg *s) { return radius[s->id]; }
	void update(tSituation *s, tTrack *t, tCarElt *car, int alone, float offset, float outside, float *r, float alpha=0.5);
	float updateAccel (tSituation* s, tCarElt* car, float taccel, float derr, float dtm);
	float predictedError (tCarElt* car);
	void AdjustFriction (tTrackSeg* s, float G, float mass_, float CA_, float CW_, float u_, float brake_);
	float GetFrictionDm(tTrackSeg* s) {
		if (s->id >= track->nseg) {
			printf ("Warning: %d>%d\n", s->id, track->nseg);
		}
		return dm + segdm[s->id];
	}
	float GetFrictionDm2(tTrackSeg* s) {return dm2 + segdm2[s->id];}
private:
	class Averages {
	public:
		Averages ()
		{
			k=0;
			taccel = derr = dtm = 0.0;
		}
		int k;
		float taccel;
		float derr;
		float dtm;
		void Measure(float taccel_, float derr_, float dtm_)
		{
			float r = (float) k;
			float d = 1.0/(1.0 + (float) k);
			taccel = d *(taccel * r + taccel_);
			derr = d *(derr * r + derr_);
			dtm = d *(dtm * r + dtm_);
			k++;
		}
	};
	Averages averages;
	tTrack* track;
	int n_quantums;
	int segments_per_quantum;
	int prev_quantum;
	float prev_accel;
	double previous_time;
	int segQuantum (int segid);
	float *radius;
	int *updateid;
	float* accel;
	float* derror;
	float* elig;
	
	// estimates for friction
	float* segdm;
	float* segdm2;
	int prevsegid;
	float dm;
	float dm2;
	float mu;
	float mass;
	float CA;
	float CW;
	float u;
	float brake;
	double prev_time;
	double delta_time;

	bool check;
	float rmin;
	int lastturn;
	int prevtype;

	int n_seg;
};


#endif //_SEGLEARN_H_
