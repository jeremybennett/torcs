/***************************************************************************

    file                 : trackdesc.h
    created              : Tue Oct 9 16:52:00 CET 2001
    copyright            : (C) 2001 by Bernhard Wymann
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

#define TRACKRES 1.0
#define RMAX 10000.0

/* magic radius for bumpy roads */
#define RREL 180.0

class TrackSegment
{
	public:
		/*
			int id is segment id
			tTrackSeg* s points to array of tracksegments
			l, m, r are pointers to left, middle and right point
		*/
		TrackSegment();
		~TrackSegment();
		void init(int id, const tTrackSeg* s, const t3Dd* l, const t3Dd* m, const t3Dd* r);
		inline void setLength(tdble len) { length = len; }
		inline void setKbeta(tdble b) { kbeta = b; }

		inline int getSegmentId() { return segID; }
		inline int getType() { return type; }
		inline unsigned int getRaceType() { return raceType; }
		inline tdble getRadius() { return radius; }
		inline tdble getKfriction() { return kfriction; }
		inline tdble getKrollres() { return krollres; }
		inline tdble getKroughness() { return kroughness; }
		inline tdble getKroughwavelen() { return kroughwavelen; }
		inline tdble getWidth() { return width; }
		inline tdble getKalpha() { return kalpha; }
		inline tdble getKbeta() { return kbeta; }
		inline tdble getLength() { return length; }

		inline t3Dd* getLeftBorder() { return &l; }
		inline t3Dd* getRightBorder() { return &r; }
		inline t3Dd* getMiddle() { return &m; }
		inline t3Dd* getToRight() { return &tr; }

		inline tdble sqr(tdble a) { return a*a; };
		inline tdble distToLeft2D(tdble x, tdble y) { return sqrt(sqr(x-l.x) + sqr(y-l.y)); }
		inline tdble distToMiddle2D(tdble x, tdble y) { return sqrt(sqr(x-m.x) + sqr(y-m.y)); }
		inline tdble distToRight2D(tdble x, tdble y) { return sqrt(sqr(x-r.x) + sqr(y-r.y)); }

		inline tdble distToRight3D(t3Dd* p) {
			return sqrt(sqr(p->x-r.x) + sqr(p->y-r.y) + sqr(p->z-r.z));
		}
		inline tdble distToLeft3D(t3Dd* p) {
			return sqrt(sqr(p->x-l.x) + sqr(p->y-l.y) + sqr(p->z-l.z));
		}
		inline tdble distToMiddle3D(tdble x, tdble y, tdble z) {
			return sqrt(sqr(x-m.x) + sqr(y-m.y) + sqr(z-m.z));
		}
		inline tdble distToMiddle3D(t3Dd* p) {
			return sqrt(sqr(p->x-m.x) + sqr(p->y-m.y) + sqr(p->z-m.z));
		}

	private:
		int segID;				/* id of the corresponding segment */
		int type;				/* physical type (eg. straight, left or right) */
		unsigned int raceType;	/* race type (eg. pitlane, speedlimit, ...) */
		t3Dd l, m, r;			/* right, middle and left segment (road) border */
		t3Dd tr;				/* normalized direction vector to the right side */
		tdble radius;			/* radius */
		tdble kfriction;		/* friction */
		tdble krollres;			/* rolling resistance */
		tdble kroughness;		/* roughness */
		tdble kroughwavelen;	/* wavelen */
		tdble width;			/* width of the track segment*/
		tdble kalpha;			/* factor for the angle (like michigan) */
		tdble kbeta;			/* factor for bumps (e-track-3) */
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
		int getNearestId(t3Dd* p);

		void getNormalVector(int index, t3Dd* normal);

		inline int getPitEntryStartId() { return nPitEntryStart; }
		inline int getPitExitEndId() { return nPitExitEnd; }
		inline int getPitType() { return torcstrack->pits.type; }

		static inline tdble vectorLength(t3Dd* p) {
			return sqrt(p->x*p->x + p->y*p->y + p->z*p->z);
		}
		static inline void normalizeVector(t3Dd* p) {
			tdble l = vectorLength(p);
			p->x /= l; p->y /= l; p->z /= l;
		}
		static inline tdble dotProduct(t3Dd* a, t3Dd* b) {
			return (a->x*b->x + a->y*b->y + a->z*b->z);
		}
		static inline void crossProduct(t3Dd* a, t3Dd* b, t3Dd* r) {
			r->x = a->y*b->z - a->z*b->y;
			r->y = a->z*b->x - a->x*b->z;
			r->z = a->x*b->y - a->y*b->x;
		}
		static inline void dirVector(t3Dd* a, t3Dd* b, t3Dd* r) {
			r->x = a->x - b->x; r->y = a->y - b->y; r->z = a->z - b->z;
		}
		static inline void dirVector2D(t3Dd* a, t3Dd* b, t3Dd* r) {
			r->x = a->x - b->x; r->y = a->y - b->y; r->z = 0.0;
		}
		static inline tdble cosalpha(t3Dd* a, t3Dd* b) {
			normalizeVector(a);
			normalizeVector(b);
			return dotProduct(a, b);
		}
		static inline tdble distGFromPoint(t3Dd* r1, t3Dd* rdir, t3Dd* p) {
			t3Dd t, s;
			dirVector(p, r1, &t);
			crossProduct(rdir, &t, &s);
			return (vectorLength(&s)/vectorLength(rdir));
		}

		/* returns distance to middle: value > 0 is right, value < 0 is left */
		inline tdble distToMiddle(int id, t3Dd* p) {
			t3Dd *r1, *rdir, r12, rdir2, p2;
			tdble d, dr, dl;

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
		inline tdble distToMiddleOnSeg(int id, t3Dd* p) {
			tdble d = ts[id].distToMiddle3D(p);
			tdble dr = ts[id].distToRight3D(p);
			tdble dl = ts[id].distToLeft3D(p);
			return (dr <= dl) ? d : -d;
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


