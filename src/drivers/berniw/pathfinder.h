/***************************************************************************

    file                 : pathfinder.h
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
	should (!) compute a good path
*/

#ifndef _PATHFINDER_H_
#define _PATHFINDER_H_

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
#include "trackdesc.h"
#include "mycar.h"
#include "spline.h"

#define FNPF "drivers/berniw/parameter.dat"
#define FNIS "drivers/berniw/intsinsqr.dat"
#define FNIC "drivers/berniw/intcossqr.dat"
#define AHEAD 500

#define BERNIW_SECT_PRIV	"berniw private"
#define BERNIW_ATT_PITENTRY	"pitentry"
#define BERNIW_ATT_PITEXIT	"pitexit"

class MyCar;
class OtherCar;

typedef struct {
	tdble x;
	tdble pd;
	tdble is;
	tdble ic;
} tParam;

class PathSeg
{
	public:
		inline void set(tdble ispeedsqr, tdble ilength, t3Dd* ip, t3Dd* id) {
			speedsqr = ispeedsqr;
			length = ilength;
			p.x = ip->x; p.y = ip->y; p.z = ip->z;
			if (id != NULL) {
				d.x = id->x; d.y = id->y; d.z = id->z;
			}
		}
		inline void setLoc(t3Dd* ip) { p.x = ip->x; p.y = ip->y; p.z = ip->z; }
		inline void setOpt(t3Dd* ip) { o.x = ip->x; o.y = ip->y; o.z = ip->z; }
		inline void setPit(t3Dd* ip) { l.x = ip->x; l.y = ip->y; l.z = ip->z; }

		inline void setSpeedsqr(tdble spsqr) { speedsqr = spsqr; }
		inline void setWeight(tdble w) { weight = w; }

		inline tdble getSpeedsqr() { return speedsqr; }
		inline tdble getLength() { return length; }
		inline tdble getWeight() { return weight; }

		inline t3Dd* getOptLoc() { return &o; }
		inline t3Dd* getPitLoc() { return &l; }
		inline t3Dd* getLoc() { return &p; }
		inline t3Dd* getDir() { return &d; }

	private:
		tdble speedsqr;	/* max possible speed sqared (speed ist therefore sqrt(speedsqr) */
		tdble length;	/* dist to the next pathseg */
		tdble weight;	/* weight function value for superposition */
		t3Dd p;			/* position in space, dynamic trajectory */
		t3Dd o;			/* position in space, static trajectory */
		t3Dd d;			/* direction vector of dynamic trajectory */
		t3Dd l;			/* trajectory for pit lane */
};

class Pathfinder
{
	public:
		static const tdble g = 9.81;
		static const tdble colldist = 200.0;
		static const int pitpoints = 7;
		static const int NTPARAMS = 1001;				/* # entries in dat files */
		static const tdble TPRES = PI/(NTPARAMS - 1);	/* resolution of the steps */
		tParam cp[NTPARAMS];							/* holds values needed for clothiod */


		Pathfinder(TrackDesc* itrack, tCarElt* car);
		~Pathfinder();
		void plan(int trackSegId, tCarElt* car, tSituation* situation, MyCar* myc, OtherCar* ocar);
		void plan(MyCar* myc);

		void initPit(tCarElt* car);
		inline bool isPitAvailable() { return pit; }
		inline int getPitSegId() { return pitSegId; }
		inline void setPitStop(bool p, int id) {
			if (isPitAvailable() && track->isBetween(e3, (s1 - AHEAD + nPathSeg) % nPathSeg, id) && p)
					pitStop = true ;
				else
					pitStop = false;
		}
		inline bool getPitStop() { return pitStop; }
		inline int segmentsToPit(int id) {
			if (id <= pitSegId) {
				return (pitSegId - id);
			} else {
				return (track->getnTrackSegments() - id + pitSegId);
			}
		}
		void plotPitStopPath(char* filename);
		void plotPath(char* filename);

		inline tdble sqr(tdble a) { return a*a; };
		inline tdble dist(t3Dd* a, t3Dd* b) { return sqrt(sqr(a->x-b->x) + sqr(a->y-b->y) + sqr(a->z-b->z)); }
		inline tdble dist2D(t3Dd* a, t3Dd* b) { return sqrt(sqr(a->x-b->x) + sqr(a->y-b->y)); }
		inline PathSeg* getPathSeg(int pathSegId) { return &ps[pathSegId]; }
		int getCurrentSegment(tCarElt* car);
		int getCurrentSegment(tCarElt* car, int range);
		inline int getnPathSeg() { return nPathSeg; }

	private:
		TrackDesc* track;		/* pointer to track data */
		int lastId;				/* segment id of the last call */
		PathSeg* ps;			/* array with the plan */
		int nPathSeg;			/* # of PathSeg */
		int lastPlan;			/* start of the last plan */
		int lastPlanRange;		/* range of the last plan */
		bool pitStop;			/* pitstop ? */
		bool inPit;				/* internal pit state */

		int s1, s3;				/* pitentrystart, pitentryend */
		int e1, e3;				/* pitexitstart, pitexitend */
		t3Dd *pmypitseg;

		t3Dd pitLoc;			/* location of pit */
		t3Dd pitDir;			/* direction vector of the pit */
		t3Dd toPit;				/* vector pointing perpendicular from the track to the pit */
		int pitSegId;			/* segment id of pit */
		bool pit;
		int pitside;
		int nPitLaneStart;
		int nPitLaneEnd;
		bool optlocreloaded;
		int changed;

		tdble ypit[pitpoints], yspit[pitpoints], spit[pitpoints];
		int snpit[pitpoints];

		tCarElt* thiscar;

		//void initPitSlopes(void);
		void initPitStopPath(void);
		void getPitPoint(int j, int k, tdble slope, tdble dist, t3Dd* r);
		int collision(int trackSegId, tCarElt* mycar, tSituation *s, MyCar* myc, OtherCar* ocar);
		int overtake(int trackSegId, tSituation *s, MyCar* myc, OtherCar* ocar);
		tdble radius(tdble x1, tdble y1, tdble x2, tdble y2, tdble x3, tdble y3);
		double curvature(double xp, double yp, double x, double y, double xn, double yn);
		void adjustRadius(int s, int p, int e, double c, tdble carwidth);
		void stepInterpolate(int iMin, int iMax, int Step);
		void interpolate(int Step);
		void smooth(int Step);

		int correctPath(int id, tCarElt* car, MyCar* myc);

		bool loadClothoidParams(tParam* p);
		tdble intsinsqr(tdble alpha);
		tdble intcossqr(tdble alpha);
		tdble clothparam(tdble alpha);
		tdble clothsigma(tdble beta, tdble y);
		tdble clothlength(tdble beta, tdble y);

		int findStartSegId(int id);
		int findEndSegId(int id);
		int initStraight(int id, tdble w);
		int initLeft(int id, tdble w);
		int initRight(int id, tdble w);
		tdble computeWeight(tdble x, tdble len);
		void setLocWeighted(int id, tdble newweight, t3Dd* newp);
		void smooth(int s, int e, int p, tdble w);
		void smooth(int id, tdble delta, tdble w);
		void optimize(int start, int range, tdble w);
		void optimize2(int start, int range, tdble w);
		void optimize3(int start, int range, tdble w);

		inline tdble pathSlope(int id) {
			tdble dp = track->dotProduct(ps[id].getDir(), track->getSegmentPtr(id)->getToRight());
			tdble alpha = PI/2.0 - acos(dp);
			return sin(alpha);
		}
};

#endif // _PATHFINDER_H_

