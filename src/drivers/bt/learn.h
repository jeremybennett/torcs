



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
