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
		void update(tSituation *s, tTrack *t, tCarElt *car, int alone, float offset, float outside, float *r);

	private:
		float *radius;
		int *updateid;

		bool check;
		float rmin;
		int lastturn;
		int prevtype;
};


#endif //_SEGLEARN_H_
