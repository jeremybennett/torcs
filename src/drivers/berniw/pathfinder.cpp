/***************************************************************************

    file                 : pathfinder.cpp
    created              : Tue Oct 9 16:52:00 CET 2001
    copyright            : (C) 2001 by Bernhard Wymann, some Code from Remi Coulom, K1999.cpp
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

#include "pathfinder.h"

/* how many segments can i pass per simulation step, depends on TRACKRES, simulation->_deltaTime and speed */
#define SEGRANGE 3


Pathfinder::Pathfinder(TrackDesc* itrack, tCarElt* car)
{
	track = itrack;
	thiscar = car;
	tTrack* t = track->getTorcsTrack();

	/* the path has to have one point per tracksegment */
	nPathSeg = track->getnTrackSegments();

	/* get memory for trajectory */
	ps = new PathSeg[nPathSeg];
	changed = lastPlan = lastPlanRange = 0;
	optlocreloaded = inPit = pitStop = false;

	/* check if there is a pit type we can use and if for this car is a pit available. */
	pit = false;
	if (t->pits.type == TR_PIT_ON_TRACK_SIDE && car->index < t->pits.nMaxPits) {
		pit = true;
	}

	if (isPitAvailable()) {
		initPit(car);
		s1 = track->getPitEntryStartId();
		s1 = (int) GfParmGetNum(car->_carHandle, BERNIW_SECT_PRIV, BERNIW_ATT_PITENTRY, (char*)NULL, s1);
		s3 = nPitLaneStart;
		e1 = nPitLaneEnd;
		e3 = track->getPitExitEndId();
		e3 = (int) GfParmGetNum(car->_carHandle, BERNIW_SECT_PRIV, BERNIW_ATT_PITEXIT, (char*)NULL, e3);

		pmypitseg = track->getSegmentPtr(pitSegId)->getMiddle();
	}
}


Pathfinder::~Pathfinder()
{
	delete [] ps;
}


/* compute where the pit is, etc */
void Pathfinder::initPit(tCarElt* car) {
	tTrack* t = track->getTorcsTrack();

	if (t->pits.driversPits != NULL && car != NULL) {
		if (isPitAvailable()) {
			tTrackSeg* pitSeg = t->pits.driversPits->pos.seg;
			if (pitSeg->type == TR_STR) {
				t3Dd v1, v2;
				/* v1 points in the direction of the segment */
				v1.x = pitSeg->vertex[TR_EL].x - pitSeg->vertex[TR_SL].x;
				v1.y = pitSeg->vertex[TR_EL].y - pitSeg->vertex[TR_SL].y;
				v1.z = pitSeg->vertex[TR_EL].z - pitSeg->vertex[TR_SL].z;
				track->normalizeVector(&v1);
				pitDir.x = v1.x; pitDir.y = v1.y; pitDir.z = v1.z;

				/* v2 points to the side of the segment */
				pitside = t->pits.side;
				tdble s = (t->pits.side == TR_LFT) ? -1.0 : 1.0 ;
				v2.x = s*(pitSeg->vertex[TR_SR].x - pitSeg->vertex[TR_SL].x);
				v2.y = s*(pitSeg->vertex[TR_SR].y - pitSeg->vertex[TR_SL].y);
				v2.z = s*(pitSeg->vertex[TR_SR].z - pitSeg->vertex[TR_SL].z);
				track->normalizeVector(&v2);
				toPit.x = v2.x; toPit.y = v2.y; toPit.z = v2.z;

				/* loading starting point of segment */
				pitLoc.x = (pitSeg->vertex[TR_SR].x + pitSeg->vertex[TR_SL].x) / 2.0;
				pitLoc.y = (pitSeg->vertex[TR_SR].y + pitSeg->vertex[TR_SL].y) / 2.0;
				pitLoc.z = (pitSeg->vertex[TR_SR].z + pitSeg->vertex[TR_SL].z) / 2.0;

				/* going along the track */
				tdble l = t->pits.len*car->index;

				pitLoc.x = pitLoc.x + (t->pits.driversPits->pos.toStart + l)*v1.x;
				pitLoc.y = pitLoc.y + (t->pits.driversPits->pos.toStart + l)*v1.y;
				pitLoc.z = pitLoc.z + (t->pits.driversPits->pos.toStart + l)*v1.z;

				/* going sideways, minus because of opposite sign of v2 and the value toMiddle */
				tdble m = fabs(t->pits.driversPits->pos.toMiddle);
				pitLoc.x = pitLoc.x + m*v2.x;
				pitLoc.y = pitLoc.y + m*v2.y;
				pitLoc.z = pitLoc.z + m*v2.z;

				pitSegId = track->getNearestId(&pitLoc);

				l = t->pits.len*(car->index+2);
				v2.x = pitLoc.x - l*v1.x;
				v2.y = pitLoc.y - l*v1.y;
				v2.z = pitLoc.z - l*v1.z;
				nPitLaneStart = track->getNearestId(&v2);

				l = t->pits.len*(t->pits.nMaxPits + 1 + 2);
				v2.x = v2.x + l*v1.x;
				v2.y = v2.y + l*v1.y;
				v2.z = v2.z + l*v1.z;
				nPitLaneEnd = track->getNearestId(&v2);
			} else pit = false;
		}
	} else {
		printf("error: pit struct ptr == NULL. call this NOT in inittrack, call it in newrace.\n");
	}
}


/* call this after you computed a static racing path with plan() */
void Pathfinder::initPitStopPath(void)
{
	tTrack* t = track->getTorcsTrack();
	t3Dd p, q, *pp, *qq;
	tdble d, dp, sgn;
	tdble delta = t->pits.width;
	int i;

	/* set up point 0 on the track (s1) */
	ypit[0] = track->distToMiddle(s1, ps[s1].getLoc());
	snpit[0] = s1;

	/* set up point 1 pit lane entry (s3) */
	track->dirVector2D(&pitLoc, pmypitseg, &p);
	dp = track->vectorLength(&p);
	d = dp - delta;

	sgn = (pitside == TR_LFT) ? -1.0 : 1.0 ;
	ypit[1] = d*sgn;
	snpit[1] = s3;

	/* set up point 2 before we turn into the pit */
	i = (pitSegId - (int) t->pits.len + nPathSeg) % nPathSeg;
	ypit[2] = d*sgn;
	snpit[2] = i;

	/* set up point 3, the pit, we know this already */
	ypit[3] = dp*sgn;
	snpit[3] = pitSegId;

	/* compute point 4, go from pit back to pit lane */
	i = (pitSegId + (int) t->pits.len + nPathSeg) % nPathSeg;
	ypit[4] = d*sgn;
	snpit[4] = i;

	/* compute point 5, drive to end of pit lane (e1) */
	ypit[5] = d*sgn;
	snpit[5] = e1;

	/* compute point 6, back on the track */
	ypit[6] = track->distToMiddle(e3, ps[e3].getLoc());
	snpit[6] = e3;

	/* compute spit array */
	spit[0] = 0.0;
	for (i = 1; i < pitpoints; i++) {
		d = 0.0;
		for (int j = snpit[i-1]; (j + 1) % nPathSeg !=  snpit[i]; j++) {
			if (snpit[i] > snpit[i-1]) {
				d = (tdble) (snpit[i] - snpit[i-1]);
			} else {
				d = (tdble) (nPathSeg - snpit[i-1] + snpit[i]);
			}
		}
		spit[i] = spit[i-1] + d;
	}

	/* set up slopes */
	yspit[0] = pathSlope(s1);
	yspit[6] = pathSlope(e3);

	for (i = 1; i < pitpoints-1; i++) {
		yspit[i] = 0.0;
	}

	/* compute path to pit */
	tdble l = 0.0;
	for (int i = s1; (i + nPathSeg) % nPathSeg != e3; i++) {
		int j = (i + nPathSeg) % nPathSeg;
		d = spline(pitpoints, l, spit, ypit, yspit);

		pp = track->getSegmentPtr(j)->getMiddle();
		qq = track->getSegmentPtr(j)->getToRight();

		p.x = qq->x; p.y = qq->y; p.z = 0.0;
		track->normalizeVector(&p);

		q.x = pp->x + p.x*d;
		q.y = pp->y + p.y*d;
		q.z = (pitside == TR_LFT) ? track->getSegmentPtr(j)->getLeftBorder()->z: track->getSegmentPtr(j)->getRightBorder()->z;

		ps[j].setPit(&q);
		l += TRACKRES;
	}

	//plotPitStopPath("/home/berni/pit.dat");
}


/* plots pit trajectory to file for gnuplot */
void Pathfinder::plotPitStopPath(char* filename)
{
	FILE* fd = fopen(filename, "w");

	/* plot pit path */
	for (int i = 0; i < nPathSeg; i++) {
		fprintf(fd, "%f\t%f\n", ps[i].getPitLoc()->x, ps[i].getPitLoc()->y);
	}
	fclose(fd);
}


void Pathfinder::plotPath(char* filename)
{
	FILE* fd = fopen(filename, "w");

	/* plot path */
	for (int i = 0; i < nPathSeg; i++) {
		fprintf(fd, "%f\t%f\n", ps[i].getLoc()->x, ps[i].getLoc()->y);
	}
	fclose(fd);
}


/* load parameters for clothoid from the files */
bool Pathfinder::loadClothoidParams(tParam* p)
{
	tdble dummy;
	FILE* fd = fopen(FNPF, "r");

	/* read FNPF */
	if (fd != NULL) {
		for (int i = 0; i < NTPARAMS; i++) {
			fscanf(fd, "%f %f", &p[i].x, &p[i].pd);
		}
	} else {
		printf("error in loadClothoidParams(tParam* p): couldn't open file %s.\n", FNPF);
		return false;
	}
	fclose(fd);

	/* read FNIS */
	fd = fopen(FNIS, "r");
	if (fd != NULL) {
		for (int i = 0; i < NTPARAMS; i++) {
			fscanf(fd, "%f %f", &dummy, &p[i].is);
		}
	} else {
		printf("error in loadClothoidParams(tParam* p): couldn't open file %s.\n", FNIS);
		return false;
	}
	fclose(fd);

	/* read FNIC */
	fd = fopen(FNIC, "r");
	if (fd != NULL) {
		for (int i = 0; i < NTPARAMS; i++) {
			fscanf(fd, "%f %f", &dummy, &p[i].ic);
		}
	} else {
		printf("error in loadClothoidParams(tParam* p): couldn't open file %s.\n", FNIC);
		return false;
	}
	fclose(fd);

	return true;
}


/*
	computes int(sin(u^2), u=0..alpha), where alpha is [0..PI).
*/
tdble Pathfinder::intsinsqr(tdble alpha)
{
	int i = (int) floor(alpha/TPRES), j = i + 1;
	/* linear interpoation between the nearest known two points */
	return cp[i].is + (alpha - cp[i].x)*(cp[j].is - cp[i].is)/TPRES;
}


/*
	computes int(cos(u^2), u=0..alpha), where alpha is [0..PI).
*/
tdble Pathfinder::intcossqr(tdble alpha)
{
	int i = (int) floor(alpha/TPRES), j = i + 1;
	/* linear interpoation between the nearest known two points */
	return cp[i].ic + (alpha - cp[i].x)*(cp[j].ic - cp[i].ic)/TPRES;
}


/*
	computes clothoid parameter pd(look with maple at clothoid.mws), where alpha is [0..PI).
*/
tdble Pathfinder::clothparam(tdble alpha)
{
	int i = (int) floor(alpha/TPRES), j = i + 1;
	/* linear interpoation between the nearest known two points */
	return cp[i].pd + (alpha - cp[i].x)*(cp[j].pd - cp[i].pd)/TPRES;
}


/*
	computes clothoid parameter sigma (look with maple at clothoid.mws), where beta is [0..PI) and y > 0.0.
*/
tdble Pathfinder::clothsigma(tdble beta, tdble y)
{
		tdble a = intsinsqr(sqrt(fabs(beta)))/y;
		return a*a*2.0;
}


/*
	computes the langth of the clothoid(look with maple at clothoid.mws), where beta is [0..PI) and y > 0.0.
*/
tdble Pathfinder::clothlength(tdble beta, tdble y)
{
	return 2.0*sqrt(2.0*beta/clothsigma(beta, y));
}


/*
	searches for the startid of a part, eg. TR_STR
*/

int Pathfinder::findStartSegId(int id)
{

	tdble radius = track->getSegmentPtr(id)->getRadius();
	int type = track->getSegmentPtr(id)->getType();
	int i = (id - 1 + nPathSeg) % nPathSeg, j = id;

	while (track->getSegmentPtr(i)->getType() == type &&
	       track->getSegmentPtr(i)->getRadius() == radius &&
		   i != id) {
		j = i;
		i = (i - 1 + nPathSeg) % nPathSeg;
	}
	return j;
}


/*
	searches for the endid of a part, eg. TR_STR
*/
int Pathfinder::findEndSegId(int id)
{
	tdble radius = track->getSegmentPtr(id)->getRadius();
	int type = track->getSegmentPtr(id)->getType();
	int i = (id + 1 + nPathSeg) % nPathSeg, j = id;

	while (track->getSegmentPtr(i)->getType() == type &&
	       track->getSegmentPtr(i)->getRadius() == radius &&
		   i != id) {
		j = i;
		i = (i + 1 + nPathSeg) % nPathSeg;
	}
	return j;
}


/*
	weight function, x 0..1
*/
tdble Pathfinder::computeWeight(tdble x, tdble len)
{
	return (x <= 0.5) ? (2.0*x)*len : (2.0*(1.0-x))*len;
}


/*
	modify point according to the weights
*/
void Pathfinder::setLocWeighted(int id, tdble newweight, t3Dd* newp)
{
	tdble oldweight = ps[id].getWeight();
	t3Dd* oldp = ps[id].getLoc();
	t3Dd p;

	/* ugly, fix it in init.... */
	if (newweight < 0.001) newweight = 0.001;

	if (oldweight + newweight == 0.0) printf("ops! O: %f, N: %f\n", oldweight, newweight);
	if (oldweight > newweight) {
		tdble d = newweight/(oldweight+newweight);
		p.x = oldp->x + (newp->x - oldp->x)*d;
		p.y = oldp->y + (newp->y - oldp->y)*d;
		p.z = oldp->z + (newp->z - oldp->z)*d;
		ps[id].setLoc(&p);
		ps[id].setWeight(oldweight+newweight);
	} else {
		tdble d = oldweight/(oldweight+newweight);
		p.x = newp->x + (oldp->x - newp->x)*d;
		p.y = newp->y + (oldp->y - newp->y)*d;
		p.z = newp->z + (oldp->z - newp->z)*d;
		ps[id].setLoc(&p);
		ps[id].setWeight(oldweight+newweight);
	}
}

/*
	initializes the path for straight parts of the track.
*/
int Pathfinder::initStraight(int id, tdble w)
{
	int start = findStartSegId(id), end = findEndSegId(id);
	int prev = (start - 1 + nPathSeg) % nPathSeg, next = (end + 1) % nPathSeg;
	int prevtype = track->getSegmentPtr(prev)->getType();
	int nexttype = track->getSegmentPtr(next)->getType();
	int len = track->diffSegId(start, end);

	if (prevtype == nexttype) {
		if (prevtype == TR_RGT) {
			int l = 0;
			for (int i = start; i != next; i++) {
				i = i % nPathSeg;
				if (ps[i].getWeight() == 0.0) {
					t3Dd* p = track->getSegmentPtr(i)->getLeftBorder();
					t3Dd* r = track->getSegmentPtr(i)->getToRight();
					t3Dd np;
					np.x = p->x + w*r->x;
					np.y = p->y + w*r->y;
					np.z = p->z + w*r->z;
					setLocWeighted(i, computeWeight(((tdble) l) / ((tdble) len), len), &np);
					l++;
				}
			}
		} else {
			int l = 0;
			for (int i = start; i != next; i++) {
				i = i % nPathSeg;
				if (ps[i].getWeight() == 0.0) {
					t3Dd* p = track->getSegmentPtr(i)->getRightBorder();
					t3Dd* r = track->getSegmentPtr(i)->getToRight();
					t3Dd np;
					np.x = p->x - w*r->x;
					np.y = p->y - w*r->y;
					np.z = p->z - w*r->z;
					setLocWeighted(i, computeWeight(((tdble) l) / ((tdble) len), len), &np);
					l++;
				}
			}
		}
	} else {
		tdble startwidth = track->getSegmentPtr(start)->getWidth()/2.0 - w;
		tdble endwidth = track->getSegmentPtr(end)->getWidth()/2.0 - w;
		tdble dw = (startwidth + endwidth) / len;
		int l = 0;
		if (prevtype == TR_RGT) {
			for (int i = start; i != next; i++) {
				i = i % nPathSeg;
				t3Dd* p = track->getSegmentPtr(i)->getLeftBorder();
				t3Dd* r = track->getSegmentPtr(i)->getToRight();
				t3Dd np;
				np.x = p->x + (w+dw*l)*r->x;
				np.y = p->y + (w+dw*l)*r->y;
				np.z = p->z + (w+dw*l)*r->z;
				setLocWeighted(i, computeWeight(((tdble) l) / ((tdble) len), len), &np);
				l++;
			}
		} else {
			for (int i = start; i != next; i++) {
				i = i % nPathSeg;
				t3Dd* p = track->getSegmentPtr(i)->getRightBorder();
				t3Dd* r = track->getSegmentPtr(i)->getToRight();
				t3Dd np;
				np.x = p->x - (w+dw*l)*r->x;
				np.y = p->y - (w+dw*l)*r->y;
				np.z = p->z - (w+dw*l)*r->z;
				setLocWeighted(i, computeWeight(((tdble) l) / ((tdble) len), len), &np);
				l++;
			}
		}
	}
	return next;
}


/*
	initializes the path for left turns.
*/
int Pathfinder::initLeft(int id, tdble w)
{
	int start = findStartSegId(id), end = findEndSegId(id);
	int prev = (start - 1 + nPathSeg) % nPathSeg, next = (end + 1) % nPathSeg;
	int len = track->diffSegId(start, end);
	int tseg = (start + (len)/2) % nPathSeg;
	t3Dd* s1 = track->getSegmentPtr(start)->getRightBorder();
	t3Dd* s2 = track->getSegmentPtr(prev)->getRightBorder();
	t3Dd* tr = track->getSegmentPtr(prev)->getToRight();
	t3Dd* tg = track->getSegmentPtr(tseg)->getLeftBorder();
	t3Dd* trtg = track->getSegmentPtr(tseg)->getToRight();
	t3Dd sdir, sp, t;

	tdble beta = acos(track->cosalpha(trtg, tr));

	if (beta < 0.0) printf("error in initLeft: turn > 360° ??\n");

	track->dirVector(s1, s2, &sdir);
	sp.x = s2->x - w*tr->x;
	sp.y = s2->y - w*tr->y;
	sp.z = s2->z - w*tr->z;

	t.x = tg->x + w*trtg->x;
	t.y = tg->y + w*trtg->y;
	t.z = tg->z + w*trtg->z;

	tdble yd = track->distGFromPoint(&sp, &sdir, &t);
	int tlen = (int) ceil(clothlength(beta, yd));

	if (tlen < 0) printf("error in initLeft: tlen < 0 ??\n");

	int startsp = (tseg - tlen/2 + nPathSeg) % nPathSeg;
	int endsp = (startsp + tlen) % nPathSeg;

	tdble s[3], y[3], ys[3];

	ys[0] = ys[1] = ys[2] = 0.0;
	s[0] = 0;
	s[1] = tlen/2;
	s[2] = tlen;
	y[0] = track->getSegmentPtr(startsp)->getWidth()/2.0 - w;
	y[1] = -(track->getSegmentPtr(tseg)->getWidth()/2.0 - w);
	y[2] = track->getSegmentPtr(endsp)->getWidth()/2.0 - w;

	tdble l = 0.0;
	t3Dd q, *pp, *qq;
	for (int i = startsp; (i + nPathSeg) % nPathSeg != endsp; i++) {
		int j = (i + nPathSeg) % nPathSeg;
		tdble d = spline(3, l, s, y, ys);

		pp = track->getSegmentPtr(j)->getMiddle();
		qq = track->getSegmentPtr(j)->getToRight();

		q.x = pp->x + qq->x*d;
		q.y = pp->y + qq->y*d;
		q.z = pp->z + qq->z*d;

		setLocWeighted(j, computeWeight(((tdble) l) / ((tdble) tlen), tlen), &q);

		l += TRACKRES;
	}

	return next;
}


/*
	initializes the path for right turns.
*/
int Pathfinder::initRight(int id, tdble w)
{
	int start = findStartSegId(id), end = findEndSegId(id);
	int prev = (start - 1 + nPathSeg) % nPathSeg, next = (end + 1) % nPathSeg;
	int len = track->diffSegId(start, end);
	int tseg = (start + (len)/2) % nPathSeg;
	t3Dd* s1 = track->getSegmentPtr(start)->getLeftBorder();
	t3Dd* s2 = track->getSegmentPtr(prev)->getLeftBorder();
	t3Dd* tr = track->getSegmentPtr(prev)->getToRight();
	t3Dd* tg = track->getSegmentPtr(tseg)->getRightBorder();
	t3Dd* trtg = track->getSegmentPtr(tseg)->getToRight();
	t3Dd sdir, sp, t;

	tdble beta = acos(track->cosalpha(trtg, tr));

	if (beta < 0.0) printf("error in initRight: turn > 360° ??\n");

	track->dirVector(s1, s2, &sdir);
	sp.x = s2->x + w*tr->x;
	sp.y = s2->y + w*tr->y;
	sp.z = s2->z + w*tr->z;

	t.x = tg->x - w*trtg->x;
	t.y = tg->y - w*trtg->y;
	t.z = tg->z - w*trtg->z;

	tdble yd = track->distGFromPoint(&sp, &sdir, &t);
	int tlen = (int) ceil(clothlength(beta, yd));

	if (tlen < 0) printf("error in initRight: tlen < 0 ??\n");

	int startsp = (tseg - tlen/2 + nPathSeg) % nPathSeg;
	int endsp = (startsp + tlen) % nPathSeg;

	tdble s[3], y[3], ys[3];

	ys[0] = ys[1] = ys[2] = 0.0;
	s[0] = 0;
	s[1] = tlen/2;
	s[2] = tlen;
	y[0] = -(track->getSegmentPtr(startsp)->getWidth()/2.0 - w);
	y[1] = track->getSegmentPtr(tseg)->getWidth()/2.0 - w;
	y[2] = -(track->getSegmentPtr(endsp)->getWidth()/2.0 - w);

	tdble l = 0.0;
	t3Dd q, *pp, *qq;
	for (int i = startsp; (i + nPathSeg) % nPathSeg != endsp; i++) {
		int j = (i + nPathSeg) % nPathSeg;
		tdble d = spline(3, l, s, y, ys);

		pp = track->getSegmentPtr(j)->getMiddle();
		qq = track->getSegmentPtr(j)->getToRight();

		q.x = pp->x + qq->x*d;
		q.y = pp->y + qq->y*d;
		q.z = pp->z + qq->z*d;

		setLocWeighted(j, computeWeight(((tdble) l) / ((tdble) tlen), tlen), &q);

		l += TRACKRES;
	}

	return next;
}


/*
	plans a static route ignoring current situation
*/
void Pathfinder::plan(MyCar* myc)
{
	tdble r, length, speedsqr;
	int u, v, w;
	t3Dd dir;

	/* basic initialisation */
	for (int i = 0; i < nPathSeg; i++) {
		ps[i].set(0.0, 0.0, track->getSegmentPtr(i)->getMiddle(), NULL);
		ps[i].setWeight(0.0);
	}

	for (int Step = 128; (Step /= 2) > 0;) {
		for (int i = 100 * int(sqrt(Step)); --i >= 0;) smooth(Step);
		interpolate(Step);
	}


	/* read parameter files and compute trajectory */
/*	if (loadClothoidParams(cp)) {
		int i = 0, k = 0;
		while (k < nPathSeg) {
			int j = k % nPathSeg;
			switch (track->getSegmentPtr(j)->getType()) {
			case TR_STR:
				i = initStraight(j, myc->CARWIDTH/2.0+myc->MARGIN);
				break;
			case TR_LFT:
				i = initLeft(j, myc->CARWIDTH/2.0+myc->MARGIN);
				break;
			case TR_RGT:
				i = initRight(j, myc->CARWIDTH/2.0+myc->MARGIN);
				break;
			default:
				printf("error in plan(MyCar* myc): segment is of unknown type.\n");
				break;
			}
			k = k + (i - k + nPathSeg) % nPathSeg;
		}
	}

	optimize3(0, nPathSeg, 1.0);
	optimize3(2, nPathSeg, 1.0);
	optimize3(1, nPathSeg, 1.0);

	optimize2(0, 10*nPathSeg, 0.5);
	optimize(0, 80*nPathSeg, 1.0);

	for (int k = 0; k < 10; k++) {
		const int step = 65536*64;
		for (int j = 0; j < nPathSeg; j++) {
			for (int i = step; i > 0; i /=2) {
				smooth(j, (tdble) i / (step / 2), myc->CARWIDTH/2.0);
			}
		}
	}
*/

	for (int i = 0; i < nPathSeg; i++) {
		ps[i].setOpt(ps[i].getLoc());
		ps[i].setPit(ps[i].getLoc());
	}

	optlocreloaded = true;

	u = nPathSeg - 1; v = 0; w = 1;

	for (int i = 0; i < nPathSeg; i++) {
		r = radius(ps[u].getLoc()->x, ps[u].getLoc()->y,
			ps[v].getLoc()->x, ps[v].getLoc()->y, ps[w].getLoc()->x, ps[w].getLoc()->y);

		length = dist(ps[v].getLoc(), ps[w].getLoc());

		tdble mu = track->getSegmentPtr(i)->getKfriction()*track->getSegmentPtr(i)->getKalpha()*track->getSegmentPtr(i)->getKbeta();
		speedsqr = myc->SPEEDSQRFACTOR*r*g*mu/(1.0 - MIN(1.0, (mu*myc->ca*r/myc->mass)));

		dir.x = ps[w].getLoc()->x - ps[u].getLoc()->x;
		dir.y = ps[w].getLoc()->y - ps[u].getLoc()->y;
		dir.z = ps[w].getLoc()->z - ps[u].getLoc()->z;
		track->normalizeVector(&dir);

		ps[i].set(speedsqr, length, ps[v].getLoc(), &dir);

		u = (u + 1 + nPathSeg) % nPathSeg;
		v = (v + 1 + nPathSeg) % nPathSeg;
		w = (w + 1 + nPathSeg) % nPathSeg;
	}

	if (isPitAvailable()) initPitStopPath();
	//plotPath("/home/berni/path.dat");
}


/*
	plans a route according to the situation
*/
void Pathfinder::plan(int trackSegId, tCarElt* car, tSituation *situation, MyCar* myc, OtherCar* ocar)
{
	tdble r, length, speedsqr;
	int u, v, w;
	t3Dd dir;

	int start;

	if (myc->derror > myc->PATHERR*myc->PATHERRFACTOR) {
		start = trackSegId;
	} else {
		start = lastPlan+lastPlanRange-SEGRANGE;
	}

	if (track->isBetween(e3, s1, trackSegId)) inPit = false;
	/* relies on that pitstop dosen't get enabled between s1, e3 */
	if (track->isBetween(s1, e3, trackSegId) && (pitStop)) inPit = true;

	/* load precomputed trajectory */
	if (!pitStop && !inPit) {
		for (int i = start; i < trackSegId+AHEAD; i++) {
			int j = (i+nPathSeg) % nPathSeg;
			/* setting more than one, because somtimes we pass more than one per simulation step */
			ps[j].setLoc(ps[j].getOptLoc());
			optlocreloaded = true;
		}
	} else {
		for (int i = start; i < trackSegId+AHEAD; i++) {
			int j = (i+nPathSeg) % nPathSeg;
			/* setting more than one, because somtimes we pass more than one per simulation step */
			ps[j].setLoc(ps[j].getPitLoc());
			optlocreloaded = true;
		}
	}

	/* are we on the trajectory or do i need a correction */
	if (!inPit && myc->derror > myc->PATHERR*myc->PATHERRFACTOR) {
		changed += correctPath(trackSegId, car, myc);
	}

	/* overtaking */
	if (!inPit && !pitStop && changed == 0) {
		changed += overtake(trackSegId, situation, myc, ocar);
	}

	/* recompute speed and direction of new trajectory */
	if (changed > 0) {
		start = trackSegId;
	}

	u = start - 1; v = start; w = start+1;
	u = (u + nPathSeg) % nPathSeg;
	v = (v + nPathSeg) % nPathSeg;
	w = (w + nPathSeg) % nPathSeg;

	for (int i = start; i < trackSegId+AHEAD; i++) {
		int j = (i+nPathSeg) % nPathSeg;
		r = radius(ps[u].getLoc()->x, ps[u].getLoc()->y,
			ps[v].getLoc()->x, ps[v].getLoc()->y, ps[w].getLoc()->x, ps[w].getLoc()->y);

		r = MIN(r, RMAX);

		length = dist(ps[v].getLoc(), ps[w].getLoc());

		/* move that to ELSE path later */
		tdble mu = track->getSegmentPtr(j)->getKfriction()*track->getSegmentPtr(j)->getKalpha()*track->getSegmentPtr(j)->getKbeta();
		speedsqr = myc->SPEEDSQRFACTOR*r*g*mu/(1.0 - MIN(1.0, (mu*myc->ca*r/myc->mass)));
		if (pitStop && track->isBetween(s3, pitSegId, j)) {
			tdble speedsqrpit = ((tdble) segmentsToPit(j) / TRACKRES) *2.0*g*track->getSegmentPtr(j)->getKfriction()*myc->cgcorr_b;
			if (speedsqr > speedsqrpit) speedsqr = speedsqrpit;
		}

		dir.x = ps[w].getLoc()->x - ps[u].getLoc()->x;
		dir.y = ps[w].getLoc()->y - ps[u].getLoc()->y;
		dir.z = ps[w].getLoc()->z - ps[u].getLoc()->z;
		track->normalizeVector(&dir);

		ps[j].set(speedsqr, length, ps[v].getLoc(), &dir);

		u = (u + 1 + nPathSeg) % nPathSeg;
		v = (v + 1 + nPathSeg) % nPathSeg;
		w = (w + 1 + nPathSeg) % nPathSeg;
	}

	changed = 0;

	/* set speed limits on the path, in case there is an obstacle (other car) */
	changed += collision(trackSegId, car, situation, myc, ocar);

	lastPlan = trackSegId; lastPlanRange = AHEAD;
	optlocreloaded = false;
}


/* get the segment on which the car is, searching ALL the segments */
int Pathfinder::getCurrentSegment(tCarElt* car)
{
	lastId = track->getCurrentSegment(car);
	return lastId;
}


/* get the segment on which the car is, searching from the position of the last call within range */
int Pathfinder::getCurrentSegment(tCarElt* car, int range)
{
	lastId = track->getCurrentSegment(car, lastId, range);
	return lastId;
}


void Pathfinder::smooth(int id, tdble delta, tdble w)
{
	int ids[5] = {id-2, id-1, id, id+1, id+2};
	tdble x[5], y[5], r, rmin = RMAX;
	TrackSegment* t = track->getSegmentPtr(id);
	t3Dd* tr = t->getToRight();

	for (int i = 0; i < 5; i++) {
		ids[i] = (ids[i] + nPathSeg) % nPathSeg;
		x[i] = ps[ids[i]].getLoc()->x;
		y[i] = ps[ids[i]].getLoc()->y;
	}

	for (int i = 0; i < 3; i++) {
		r = radius(x[i], y[i], x[i+1], y[i+1], x[i+2], y[i+2]);
		if (r < rmin) rmin = r;
	}

	/* no optimisation needed */
	if (rmin == RMAX) return;

	tdble xp, yp, xm, ym, xo = x[2], yo = y[2], rp = RMAX, rm = RMAX;

	xp = x[2] = xo + delta*tr->x; yp = y[2] = yo + delta*tr->y;
	for (int i = 0; i < 3; i++) {
		r = radius(x[i], y[i], x[i+1], y[i+1], x[i+2], y[i+2]);
		if (r < rp) rp = r;
	}

	xm = x[2] = xo - delta*tr->x; ym = y[2] = yo - delta*tr->y;
	for (int i = 0; i < 3; i++) {
		r = radius(x[i], y[i], x[i+1], y[i+1], x[i+2], y[i+2]);
		if (r < rm) rm = r;
	}

	if (rp > rmin && rp > rm) {
		t3Dd n;
		n.x = xp;
		n.y = yp;
		n.z = ps[id].getLoc()->z + delta*tr->z;
		ps[id].setLoc(&n);
	} else if (rm > rmin && rm > rp) {
		t3Dd n;
		n.x = xm;
		n.y = ym;
		n.z = ps[id].getLoc()->z - delta*tr->z;
		ps[id].setLoc(&n);
	}
}

void Pathfinder::smooth(int s, int p, int e, tdble w)
{
	TrackSegment* t = track->getSegmentPtr(p);
	t3Dd *rgh = t->getToRight();
	t3Dd *rs = ps[s].getLoc(), *rp = ps[p].getLoc(), *re = ps[e].getLoc(), n;

	tdble rgx = (re->x - rs->x), rgy = (re->y - rs->y);
	tdble m = (rs->x * rgy + rgx * rp->y - rs->y * rgx - rp->x * rgy) / (rgy * rgh->x - rgx * rgh->y);

	n.x = rp->x + rgh->x * m*w;
	n.y = rp->y + rgh->y * m*w;
	n.z = rp->z + rgh->z * m*w;

	ps[p].setLoc(&n);
}


void Pathfinder::optimize(int start, int range, tdble w)
{
        for (int p = start; p < start + range; p = p + 1) {
                int j = (p) % nPathSeg;
                int k = (p+1) % nPathSeg;
                int l = (p+2) % nPathSeg;
                smooth(j, k, l, w);
        }
}


void Pathfinder::optimize2(int start, int range, tdble w)
{
        for (int p = start; p < start + range; p = p + 1) {
                int j = (p) % nPathSeg;
                int k = (p+1) % nPathSeg;
                int l = (p+2) % nPathSeg;
				int m = (p+3) % nPathSeg;
                smooth(j, k, m, w);
				smooth(j, l, m, w);
        }
}


void Pathfinder::optimize3(int start, int range, tdble w)
{
        for (int p = start; p < start + range; p = p + 3) {
                int j = (p) % nPathSeg;
                int k = (p+1) % nPathSeg;
                int l = (p+2) % nPathSeg;
				int m = (p+3) % nPathSeg;
                smooth(j, k, m, w);
				smooth(j, l, m, w);
        }
}



int Pathfinder::collision(int trackSegId, tCarElt* mycar, tSituation* s, MyCar* myc, OtherCar* ocar)
{
	tCarElt* car;
	int seg;
	int end = (trackSegId + (int) colldist + nPathSeg) % nPathSeg;
	int didsomething = 0;

	tdble dst;
	tdble tspeed;
	int dists[s->_ncars];
	tdble speedsqr[s->_ncars];
	tdble speed[s->_ncars];
	OtherCar* collcar[s->_ncars];
	int norder = 0;

	for (int i = 0; i < s->_ncars; i++) {
		dists[i] = INT_MAX;
		car = ocar[i].me;
		/* is it me ? */
		if (car != mycar) {
			/* is it near enough to care about ? */
			dst = dist(&myc->currentpos, &ocar[i].currentpos);
			if (dst < colldist) {
				tspeed = ocar[i].speed*track->cosalpha(&myc->dir, &ocar[i].dir);
				seg = ocar[i].currentsegid;

				/* is this guy on the track or abroad ? */
				if (/*(track->getSegmentPtr(seg)->distToMiddle3D(&ocar[i].currentpos) < track->getSegmentPtr(seg)->getWidth()/2.0) &&*/
				/* is he faster and behind us */
				   (/*(track->isBetween(start, trackSegId, seg) && myc->speed < speed) ||*/
				/* in front of us and slower */
				   (track->isBetween(trackSegId, end, seg) /*&& myc->speed > tspeed*/)))
				{
					dists[norder] = track->diffSegId(trackSegId, seg);
					collcar[norder] = &ocar[i];
					speedsqr[norder] = tspeed*tspeed;
					speed[norder] = tspeed;
					norder++;
				}
			}
		}
	}

	for (int i = 0; i < norder; i++) {
		PathSeg* opseg = getPathSeg(collcar[i]->currentsegid);
		int spsegid = (collcar[i]->currentsegid - (int) myc->CARLEN + nPathSeg) % nPathSeg;
		PathSeg* spseg = getPathSeg(spsegid);
		TrackSegment* otseg = track->getSegmentPtr(collcar[i]->currentsegid);
		/* compute cosalpha of angle between path and other car */
		tdble cosa = collcar[i]->dir.x * opseg->getDir()->x +
					 collcar[i]->dir.y * opseg->getDir()->y +
					 collcar[i]->dir.z * opseg->getDir()->z;
		/* compute minimal space requred */
		tdble d = myc->CARWIDTH + myc->CARLEN/2.0*sin(acos(cosa)) + myc->DIST;
		/* compute distance to path */
		tdble dtp = dist(opseg->getLoc(), &collcar[i]->currentpos);

		/* not enough space, perhaps we have to do something */
		if (dtp < d) {
			tdble gm = otseg->getKfriction();
			tdble qs = speedsqr[i];
			tdble s = (myc->speedsqr - speedsqr[i])*(myc->mass/(2.0*gm*g*myc->mass + (qs)*(gm*myc->ca + myc->cw)));

			if (dists[i] < myc->CARLEN + myc->DIST) {
				tdble t = speed[i] - myc->SLOWDOWN;
				t *= t;
				if (spseg->getSpeedsqr() > t) {
					spseg->setSpeedsqr(t);
					didsomething = 1;
				}
				if (opseg->getSpeedsqr() > t) {
					opseg->setSpeedsqr(t);
					didsomething = 1;
				}
			} else if (s <= dists[i] + myc->CARLEN + myc->DIST) {
				if (spseg->getSpeedsqr() > speedsqr[i]) {
					spseg->setSpeedsqr(speedsqr[i]);
					didsomething = 1;
				}
				if (opseg->getSpeedsqr() > speedsqr[i]) {
					opseg->setSpeedsqr(speedsqr[i]);
					didsomething = 1;
				}
			}
		}
	}
	return didsomething;
}


/* compute the radius given three points */
inline tdble Pathfinder::radius(tdble x1, tdble y1, tdble x2, tdble y2, tdble x3, tdble y3)
{
	tdble dx1 = x2 - x1;
	tdble dy1 = y2 - y1;
	tdble dx2 = x3 - x2;
	tdble dy2 = y3 - y2;

	tdble z = (dy1*dx2 - dx1*dy2);

	if (z != 0.0) {
		tdble k = (dx2*(x3-x1) - dy2*(y1-y3))/z;
		return sqrt((1.0+k*k)*(dx1*dx1+dy1*dy1))/2.0;
	} else {
		return FLT_MAX;
	}
}


/* computes curvature, from Remi Coulom, K1999.cpp */
inline double Pathfinder::curvature(double xp, double yp, double x, double y, double xn, double yn)
{
	double x1 = xn - x;
	double y1 = yn - y;
	double x2 = xp - x;
	double y2 = yp - y;
	double x3 = xn - xp;
	double y3 = yn - yp;

	double det = x1 * y2 - x2 * y1;
	double n1 = x1 * x1 + y1 * y1;
	double n2 = x2 * x2 + y2 * y2;
	double n3 = x3 * x3 + y3 * y3;
	double nnn = sqrt(n1 * n2 * n3);
	return 2 * det / nnn;
}


/* optimize point p ala k1999 (curvature), Remi Coulom, K1999.cpp */
inline void Pathfinder::adjustRadius(int s, int p, int e, double c, tdble security) {
	const double sidedistext = 2.0;
	const double sidedistint = 1.2;

	TrackSegment* t = track->getSegmentPtr(p);
	t3Dd *rgh = t->getToRight();
	t3Dd *left = t->getLeftBorder();
	t3Dd *right = t->getRightBorder();
	t3Dd *rs = ps[s].getLoc(), *rp = ps[p].getLoc(), *re = ps[e].getLoc(), n;
	double oldlane = track->distToMiddleOnSeg(p, rp)/t->getWidth() + 0.5;

	tdble rgx = (re->x - rs->x), rgy = (re->y - rs->y);
	tdble m = (rs->x * rgy + rgx * rp->y - rs->y * rgx - rp->x * rgy) / (rgy * rgh->x - rgx * rgh->y);

	n.x = rp->x + rgh->x * m;
	n.y = rp->y + rgh->y * m;
	n.z = rp->z + rgh->z * m;
	ps[p].setLoc(&n);
	double newlane = track->distToMiddleOnSeg(p, rp)/t->getWidth() + 0.5;

	/* get an estimate how much the curvature changes by moving the point 1/10000 of track width */
	const double delta = 0.0001;
	double dx = delta * (right->x - left->x);
	double dy = delta * (right->y - left->y);
	double deltacurvature = curvature(rs->x, rs->y, rp->x + dx, rp->y + dy, re->x, re->y);

	if (deltacurvature > 0.000000001) {
		newlane += (delta / deltacurvature) * c;
		double ExtLane = (sidedistext + security) / t->getWidth();
		double IntLane = (sidedistint + security) / t->getWidth();

		if (ExtLane > 0.5) ExtLane = 0.5;
		if (IntLane > 0.5) IntLane = 0.5;

		if (c >= 0.0) {
			if (newlane < IntLane) newlane = IntLane;
			if (1 - newlane < ExtLane) {
    			if (1 - oldlane < ExtLane) newlane = MIN(oldlane, newlane);
    			else newlane = 1 - ExtLane;
			}
		} else {
			if (newlane < ExtLane) {
    			if (oldlane < ExtLane) newlane = MAX(oldlane, newlane);
    			else newlane = ExtLane;
			}
			if (1 - newlane < IntLane) newlane = 1 - IntLane;
		}

		tdble d = (newlane - 0.5) * t->getWidth();
		t3Dd* trackmiddle = t->getMiddle();

		n.x = trackmiddle->x + rgh->x * d;
		n.y = trackmiddle->y + rgh->y * d;
		n.z = trackmiddle->z + rgh->z * d;
		ps[p].setLoc(&n);
	}
}


/* interpolation step from Remi Coulom, K1999.cpp */
void Pathfinder::stepInterpolate(int iMin, int iMax, int Step)
{
	int next = (iMax + Step) % nPathSeg;
	if (next > nPathSeg - Step) next = 0;

	int prev = (((nPathSeg + iMin - Step) % nPathSeg) / Step) * Step;
	if (prev > nPathSeg - Step)
	prev -= Step;

	t3Dd *pp = ps[prev].getLoc();
	t3Dd *p = ps[iMin].getLoc();
	t3Dd *pn = ps[iMax % nPathSeg].getLoc();
	t3Dd *pnn = ps[next].getLoc();

	double ir0 = curvature(pp->x, pp->y, p->x, p->y, pn->x, pn->y);
	double ir1 = curvature(p->x, p->y, pn->x, pn->y, pnn->x, pnn->y);

	for (int k = iMax; --k > iMin;) {
		double x = double(k - iMin) / double(iMax - iMin);
		double TargetRInverse = x * ir1 + (1 - x) * ir0;
		adjustRadius(iMin, k, iMax % nPathSeg, TargetRInverse, 0.0);
	}
}


/* interpolating from Remi Coulom, K1999.cpp */
void Pathfinder::interpolate(int Step)
{
	if (Step > 1) {
		int i;
		for (i = Step; i <= nPathSeg - Step; i += Step) stepInterpolate(i - Step, i, Step);
		stepInterpolate(i - Step, nPathSeg, Step);
	}
}


/* smoothing from Remi Coulom, K1999.cpp */
void Pathfinder::smooth(int Step)
{
	int prev = ((nPathSeg - Step) / Step) * Step;
	int prevprev = prev - Step;
	int next = Step;
	int nextnext = next + Step;

	t3Dd *pp, *p, *n, *nn, *cp;

	for (int i = 0; i <= nPathSeg - Step; i += Step) {
		pp = ps[prevprev].getLoc();
		p = ps[prev].getLoc();
		cp = ps[i].getLoc();
		n = ps[next].getLoc();
		nn = ps[nextnext].getLoc();

		double ir0 = curvature(pp->x, pp->y, p->x, p->y, cp->x, cp->y);
		double ir1 = curvature(cp->x, cp->y, n->x, n->y, nn->x, nn->y);
		double dx, dy;
		dx = cp->x - p->x; dy = cp->y - p->y;
		double lPrev = sqrt(dx*dx + dy*dy);
		dx = cp->x - n->x; dy = cp->y - n->y;
		double lNext = sqrt(dx*dx + dy*dy);

		double TargetRInverse = (lNext * ir0 + lPrev * ir1) / (lNext + lPrev);

		double Security = lPrev * lNext / (8.0 * 100.0);
		adjustRadius(prev, i, next, TargetRInverse, Security);

		prevprev = prev;
		prev = i;
		next = nextnext;
		nextnext = next + Step;
		if (nextnext > nPathSeg - Step) nextnext = 0;
	}
}


/* compute a path back to the planned path */
int Pathfinder::correctPath(int id, tCarElt* car, MyCar* myc)
{
	tdble s[2], y[2], ys[2];

	tdble d = track->distToMiddle(id, &myc->currentpos);
	tdble factor = MIN(myc->CORRLEN*fabs(d), nPathSeg/2.0);
	int endid = (id + (int) (factor) + nPathSeg) % nPathSeg;

	if (fabs(d) > (track->getSegmentPtr(id)->getWidth() - myc->CARWIDTH)/2.0) {
		d = d/fabs(d)*(track->getSegmentPtr(id)->getWidth() - myc->CARWIDTH)/2.0;
	}

	tdble ed = track->distToMiddle(endid, ps[endid].getLoc());

	/* set up points */
	y[0] = d;
	s[0] = 0.0;
	ys[0] = 0.0;

	y[1] = ed;
	ys[1] = pathSlope(endid);

	if ( endid > id) {
		s[1] = (tdble) (endid - id);
	} else {
		s[1] = (tdble) (nPathSeg - id + endid);
	}

	/* modify path */
	tdble l = 0.0;
	t3Dd q, *pp, *qq;
	for (int i = id; (i + nPathSeg) % nPathSeg != endid; i++) {
		int j = (i + nPathSeg) % nPathSeg;
		d = spline(2, l, s, y, ys);

		if (fabs(d) > (track->getSegmentPtr(id)->getWidth() - myc->CARWIDTH)/2.0) {
			d = d/fabs(d)*(track->getSegmentPtr(id)->getWidth() - myc->CARWIDTH)/2.0;
		}

		pp = track->getSegmentPtr(j)->getMiddle();
		qq = track->getSegmentPtr(j)->getToRight();

		q.x = pp->x + qq->x*d;
		q.y = pp->y + qq->y*d;
		q.z = pp->z + qq->z*d;

		ps[j].setLoc(&q);
		l += TRACKRES;
	}

	for (int i = 5; i > 0; i--) {
		optimize(id, l+i, 1.0);
	}

	return 1;
}


/* compute path for overtaking the "next colliding" car */
int Pathfinder::overtake(int trackSegId, tSituation *s, MyCar* myc, OtherCar* ocar)
{
	for (int i = 0; i <= (int) myc->MINOVERTAKERANGE; i += 10) {
		if (track->getSegmentPtr((trackSegId+i) % nPathSeg)->getRadius() < myc->OVERTAKERADIUS) return 0;
	}

	tCarElt* car;
	int seg;
	int end = (trackSegId + (int) colldist/4 + nPathSeg) % nPathSeg;

	tdble dst;
	tdble tspeed;
	tdble minTime = FLT_MAX;
	int minIndex = 0;
	OtherCar* nearestCar = NULL;	/* car near in time, not in space ! (next reached car) */
	tdble cosa;

	int dists[s->_ncars];
	tdble speedsqr[s->_ncars];
	tdble speed[s->_ncars];
	tdble time[s->_ncars];			/* estimate of time to catch up the car */
	OtherCar* collcar[s->_ncars];
	tdble cosalpha[s->_ncars];

	int norder = 0;

	for (int i = 0; i < s->_ncars; i++) {
		dists[i] = INT_MAX;
		car = ocar[i].me;
		/* is it me ? */
		if (car != myc->getCarPtr()) {
			/* is it near enough to care about ? */
			dst = dist(&myc->currentpos, &ocar[i].currentpos);
			if (dst < colldist) {
				cosa = track->cosalpha(&myc->dir, &ocar[i].dir);
				tspeed = ocar[i].speed*cosa;
				seg = ocar[i].currentsegid;

				/* get the next car to catch up */
				if (track->isBetween(trackSegId, end, seg) && myc->speed > tspeed)
				{
					dists[norder] = track->diffSegId(trackSegId, seg);
					collcar[norder] = &ocar[i];
					speedsqr[norder] = tspeed*tspeed;
					speed[norder] = tspeed;
					cosalpha[norder] = cosa;
					time[norder] = dists[norder]/(myc->speed + myc->OVERTAKESPEED - speed[norder]);

					if (time[norder] < minTime) {
						minTime = time[norder];
						minIndex = norder;
						nearestCar = collcar[norder];
					}
					norder++;
				}
			}
		}
	}

	if (norder == 0) return 0;
	/* is he on my trajectory */
	PathSeg* opseg = getPathSeg(nearestCar->currentsegid);
	/* compute minimal space requred */
	tdble d = myc->CARWIDTH + myc->CARLEN/2.0*sin(acos(cosalpha[minIndex])) + myc->DIST;
	/* compute distance to path */
	tdble dtp = dist(opseg->getLoc(), &nearestCar->currentpos);

	/* not enough space, so we try to overtake */
	if (dtp < d && minTime < myc->TIMETOCATCH) {
		if (!optlocreloaded) {
			int start = (trackSegId+nPathSeg-SEGRANGE) % nPathSeg;
			for (int i = start; i < trackSegId+AHEAD; i ++) {
				int j = (i+nPathSeg) % nPathSeg;
				ps[j].setLoc(ps[j].getOptLoc());
			}
		}

		/* compute estimate to catch up */
		int overtakerange = (int) MIN(MAX((3*minTime*myc->speed), myc->MINOVERTAKERANGE), AHEAD-50);

		/* compute new path */
		tdble y[3], ys[3], s[3];
		/* set up point 0 */
		y[0] = track->distToMiddle(trackSegId, &myc->currentpos);
		tdble dp = track->dotProduct(&myc->dir, track->getSegmentPtr(trackSegId)->getToRight());
		tdble alpha = PI/2.0 - acos(dp);
		ys[0] = sin(alpha);

		/* set up point 1 */
		int trackSegId1 = (trackSegId + overtakerange/2) % nPathSeg;
		/* is me, he left or right on the track */
		d = track->distToMiddle(nearestCar->currentsegid, &nearestCar->currentpos);
		tdble sgn = (d >= 0) ? 1.0 : -1.0 ;
		tdble mydisttomiddle = track->distToMiddle(myc->currentsegid, &myc->currentpos);
		tdble mysgn = (mydisttomiddle >= 0) ? 1.0 : -1.0 ;
		y[1] = 0.0;

		/* are we on the same lane */
		if(mysgn == sgn) {
			if (fabs(mydisttomiddle) > fabs(d)) {
				tdble w = track->getSegmentPtr(nearestCar->currentsegid)->getWidth() / 2;
				if ((w - fabs(d) - 2.5*(myc->CARWIDTH+myc->DIST)) > 0.0) {
					y[1] = sgn*(track->getSegmentPtr(trackSegId1)->getWidth() - 3*myc->CARWIDTH)/2.0;
				} else {
					y[1] = -sgn*(track->getSegmentPtr(trackSegId1)->getWidth() - 4*myc->CARWIDTH)/2.0;
				}
			}
		} else {
			y[1] = -sgn*(track->getSegmentPtr(trackSegId1)->getWidth() - 4*myc->CARWIDTH)/2.0;
		}
		ys[1] = 0.0;

		/* set up point 2 */
		int trackSegId2 = (trackSegId + overtakerange) % nPathSeg;
		y[2] = track->distToMiddleOnSeg(trackSegId2, ps[trackSegId2].getLoc());
		ys[2] = pathSlope(trackSegId2);

		/* set up parameter s */
		s[0] = 0.0;
		if ( trackSegId1 > trackSegId) {
			s[1] = (tdble) ( trackSegId1 - trackSegId);
		} else {
			s[1] = (tdble) (nPathSeg - trackSegId + trackSegId1);
		}
		if ( trackSegId2 > trackSegId1) {
			s[2] = s[1] + (tdble) ( trackSegId2 - trackSegId1);
		} else {
			s[2] = s[1] + (tdble) (nPathSeg - trackSegId1 + trackSegId2);
		}

		/* compute path */
		tdble l = 0.0; t3Dd q, *pp, *qq;
		for (int i = trackSegId; (i + nPathSeg) % nPathSeg != trackSegId2; i++) {
			int j = (i + nPathSeg) % nPathSeg;
			d = spline(3, l, s, y, ys);

			pp = track->getSegmentPtr(j)->getMiddle();
			qq = track->getSegmentPtr(j)->getToRight();

			q.x = pp->x + qq->x*d;
			q.y = pp->y + qq->y*d;
			q.z = pp->z + qq->z*d;

			ps[j].setLoc(&q);
			l += TRACKRES;
		}

		for (int i = 20; i > 0; i--) {
			optimize((trackSegId2-i+nPathSeg) % nPathSeg, 2*i, 1.0);
		}

		return 1;
	} else {
		return 0;
	}
}

