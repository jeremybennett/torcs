/***************************************************************************

    file                 : trackdesc.h
    created              : Tue Oct 9 16:52:00 CET 2001
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
	class TrackSegment:
	describes the properties of approx 1 m on the track, like where the borders are, pysical stuff
	(eg. friction).
	class TrackDesc:
	describes the whole track, the data is stored in an array of Tracksegments.
*/

#ifndef _TRACKDESC_H_
#define _TRACKDESC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tgf.h>
#include <track.h>
#include <car.h>
#include <raceman.h>
#include <robot.h>
#include <robottools.h>
#include <math.h>
#include <ttypes.h>
#include "linalg.h"

#define TRACKRES 1.0
#define RMAX 10000.0

/* magic radius for bumpy roads */
#define RREL 180.0

class TrackSegment
{
	public:
		TrackSegment();
		~TrackSegment();
		void init(int id, const tTrackSeg* s, const v3d* l, const v3d* m, const v3d* r);
		inline void setLength(double len) { length = len; }
		inline void setKbeta(double b) { kbeta = b; }
		inline void setKgamma(double c) { kgamma = c; }

		inline int getType() { return type; }
		inline unsigned int getRaceType() { return raceType; }
		inline tdble getRadius() { return radius; }

		inline tdble getKfriction() { return pTrackSeg->surface->kFriction; }
		inline tdble getKrollres() { return pTrackSeg->surface->kRollRes; }
		inline tdble getKroughness() { return pTrackSeg->surface->kRoughness; }
		inline tdble getKroughwavelen() { return pTrackSeg->surface->kRoughWaveLen; }

		inline tdble getWidth() { return width; }
		inline tdble getKalpha() { return kalpha; }
		inline tdble getKbeta() { return kbeta; }
		inline tdble getKgamma() { return kgamma; }
		inline tdble getLength() { return length; }

		inline v3d* getLeftBorder() { return &l; }
		inline v3d* getRightBorder() { return &r; }
		inline v3d* getMiddle() { return &m; }
		inline v3d* getToRight() { return &tr; }

		inline double sqr(double a) { return a*a; };
		inline double distToLeft2D(double x, double y) { return sqrt(sqr(x-l.x) + sqr(y-l.y)); }
		inline double distToMiddle2D(double x, double y) { return sqrt(sqr(x-m.x) + sqr(y-m.y)); }
		inline double distToRight2D(double x, double y) { return sqrt(sqr(x-r.x) + sqr(y-r.y)); }

		inline double distToRight3D(v3d* p) { return sqrt(sqr(p->x-r.x) + sqr(p->y-r.y) + sqr(p->z-r.z)); }
		inline double distToLeft3D(v3d* p) { return sqrt(sqr(p->x-l.x) + sqr(p->y-l.y) + sqr(p->z-l.z)); }
		inline double distToMiddle3D(double x, double y, double z) { return sqrt(sqr(x-m.x) + sqr(y-m.y) + sqr(z-m.z)); }
		inline double distToMiddle3D(v3d* p) { return sqrt(sqr(p->x-m.x) + sqr(p->y-m.y) + sqr(p->z-m.z)); }

	private:
		tTrackSeg* pTrackSeg;	/* id of the corresponding segment */
		int type;				/* physical type (eg. straight, left or right) */
		unsigned int raceType;	/* race type (eg. pitlane, speedlimit, ...) */
		v3d l, m, r;			/* right, middle and left segment (road) border */
		v3d tr;					/* normalized direction vector to the right side */
		tdble radius;			/* radius */
		tdble width;			/* width of the track segment*/
		tdble kalpha;			/* (roll)factor for the angle (like michigan) */
		tdble kbeta;			/* (curvature)factor for bumps (e-track-3) */
		tdble kgamma;			/* (pitch)factor of road */
		tdble length;			/* distance to the next segment (2-D, not 3-D!) */
};

class TrackDesc
{
	public:
		TrackDesc(const tTrack* track);
		~TrackDesc();
		/* output track data to gnuplot readable file */
		void plot(char* filename);

		inline tTrack* getTorcsTrack() { return torcstrack; }
		inline TrackSegment* getSegmentPtr(int index) { return &ts[index]; }
		inline int getnTrackSegments() { return nTrackSegments; }
		int getCurrentSegment(tCarElt* car, int lastId, int range);
		int getCurrentSegment(tCarElt* car);
		int getNearestId(v3d* p);

		inline int getPitEntryStartId() { return nPitEntryStart; }
		inline int getPitExitEndId() { return nPitExitEnd; }
		inline int getPitType() { return torcstrack->pits.type; }

		static inline void dirVector2D(v3d* a, v3d* b, v3d* r) {
			r->x = a->x - b->x; r->y = a->y - b->y; r->z = 0.0;
		}
		static inline double cosalpha(v3d* a, v3d* b) {
			return (*a)*(*b)/(a->len()*b->len());
		}
		static inline double distGFromPoint(v3d* r1, v3d* rdir, v3d* p) {
			v3d t, s;
			p->dirVector(r1, &t);
			rdir->crossProduct(&t, &s);
			return s.len()/rdir->len();
		}

		/* returns distance to middle: value > 0 is right, value < 0 is left */
		inline double distToMiddle(int id, v3d* p) {
			v3d *r1, *rdir, r12, rdir2, p2;
			double d, dr, dl;

			r1 = ts[id].getMiddle();
			rdir = ts[id].getToRight();
			r12.x = r1->x; r12.y = r1->y; r12.z = 0.0;
			rdir2.x = -rdir->y; rdir2.y = rdir->x; rdir2.z = 0.0;
			p2.x = p->x; p2.y = p->y; p2.z = 0.0;

			dr = ts[id].distToRight2D(p2.x, p2.y);
			dl = ts[id].distToLeft2D(p2.x, p2.y);
			d = (dr > dl) ? -1.0 : 1.0;

			return d*distGFromPoint(&r12, &rdir2, &p2);
		}

		/* returns distance of trajectory point to the middle point of segment */
		inline double distToMiddleOnSeg(int id, v3d* p) {
			v3d d = *p - *ts[id].getMiddle();
			return (d*(*ts[id].getToRight()) >= 0.0) ? d.len() : -d.len();
		}

		inline bool isBetween(int start, int end, int id) {
			if (start <= end) {
				if (id >= start && id <= end) { return true; } else { return false; }
			} else {
				if ((id >= 0 && id <= end) || (id >= start && id < nTrackSegments)) { return true; } else { return false; }
			}
		}

		inline int diffSegId(int id1, int id2) {
			int t;
			if (id1 > id2) { t = id1; id1 = id2; id2 = t; }
			t = (nTrackSegments - id2 + id1) % nTrackSegments;
			return MIN(id2 - id1, t);
		}

	private:
		tTrack *torcstrack;
		TrackSegment* ts;		/* pointer to the array of tracksegments */
		int nTrackSegments;		/* # of track segments */
		int nPitEntryStart;
		int nPitExitEnd;
};

#endif // _TRACKDESC_H_


