


#include "learn.h"

SegLearn::SegLearn(tTrack* t)
{
	int i;
	radius = new float[t->nseg];
	updateid = new int[t->nseg];
	tTrackSeg *seg = t->seg;

	// Switch seg to seg 0 for sure.
	while (seg->id != 0) {
		seg = seg->prev;
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
