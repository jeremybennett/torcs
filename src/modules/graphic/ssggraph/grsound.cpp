/***************************************************************************

    file                 : grsound.cpp
    created              : Thu Aug 17 23:57:10 CEST 2000
    copyright            : (C) 2000 by Eric Espie
    email                : torcs@free.fr
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

#include <plib/sl.h>
#include <plib/sm.h>
#include <math.h>

#include <tgf.h>
#include <graphic.h>
#include <racemantools.h>

#include "grsound.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

#ifndef M_PI
#define EX_PI 3.1415926535
#else
#define EX_PI M_PI
#endif

#define NB_CRASH_SOUND	6
static int		curCrashSnd;
static slScheduler	*sched;
static slSample		*engSample;
static slSample		*crashSample[NB_CRASH_SOUND];
static slSample		*skidSample;
static slEnvelope	*pitchEnv;
static slEnvelope	*volEnv;

static int soundInitialized = 0;


void
grInitSound(void)
{
    char	buf[256];
    int		i;

    sched = new slScheduler(44100);
    
    sched->setSafetyMargin(0.128f);

    engSample = new slSample("data/sound/engine-1.wav", sched);
    engSample->adjustVolume(0.1);

    
    pitchEnv = new slEnvelope(1, SL_SAMPLE_ONE_SHOT);
    pitchEnv->setStep(0, 0.0, 1.0);


    sched->loopSample(engSample);
    sched->addSampleEnvelope(engSample, 0, 0, pitchEnv, SL_PITCH_ENVELOPE);

    skidSample = new slSample("data/sound/skid.wav", sched);
    skidSample->adjustVolume(0.3);
    volEnv = new slEnvelope(1, SL_SAMPLE_ONE_SHOT);
    sched->loopSample(skidSample);
    sched->addSampleEnvelope(skidSample, 0, 0, volEnv, SL_VOLUME_ENVELOPE);
    volEnv->setStep(0, 0.0, 0.0);

    for (i = 0; i < NB_CRASH_SOUND; i++) {
	sprintf(buf, "data/sound/crash%d.wav", i+1);
	crashSample[i] = new slSample(buf, sched);
	crashSample[i]->adjustVolume(0.25);
    }
    curCrashSnd = 0;

    soundInitialized = 1;
}


void 
grShutdownSound(void)
{
    int i;

    if (!soundInitialized) {
	return;
    }
    soundInitialized = 0;
    sched->stopSample(skidSample);
    sched->stopSample(engSample);
    sched->stopSample(crashSample[curCrashSnd]);
    sched->addSampleEnvelope(engSample, 0, 0, NULL, SL_PITCH_ENVELOPE);
    delete pitchEnv;
    sched->addSampleEnvelope(skidSample, 0, 0, NULL, SL_VOLUME_ENVELOPE);
    delete volEnv;
    sched->update();
    delete engSample;
    for (i = 0; i < NB_CRASH_SOUND; i++) {
	delete crashSample[i];
    }
    delete skidSample;
    delete sched;
}



void
grRefreshSound(tSituation *s)
{
    float	mpitch;
    float	skvol;
    tCarElt	*car = s->cars[s->current];
    int		i;

    mpitch = (float)(car->_enginerpm) / 600.0;
    pitchEnv->setStep(0, 0.0, mpitch);

    skvol = 0.0;
    if ((car->_speed_x * car->_speed_x + car->_speed_y * car->_speed_y) > 10.0) {
	for(i = 0; i < 4; i++) {
	    if (skvol < car->_skid[i]) {
		skvol = (float)car->_skid[i];
	    }
	}
    }
    volEnv->setStep(0, 0.0, skvol);

    if (car->priv->collision) {
	curCrashSnd++;
	if (curCrashSnd == NB_CRASH_SOUND) {
	    curCrashSnd = 0;
	}
	sched->playSample(crashSample[curCrashSnd]);
	car->priv->collision = 0;
    }

    sched->update();
}
