// -*- Mode: c++ -*-
/***************************************************************************

    file                 : grsound.h
    created              : Thu Aug 17 23:57:35 CEST 2000
    copyright            : (C) 2000-2004 by Eric Espie, Christos Dimitrakakis
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

#ifndef _GRSOUND_H_
#define _GRSOUND_H_

#include "grcam.h"
#include <raceman.h>
#include <plib/sl.h>

#define OLETHROS_PLIB //define this if you have lpfilter and 16 sounds in plib

extern void grInitSound(tSituation* s, int ncars);
extern void grShutdownSound(int ncars);
extern float grRefreshSound(tSituation *s, cGrCamera *camera);

typedef struct SoundChar_ {
    float f; //frequency modulation
    float a; //amplitude modulation
} SoundChar;


enum SoundPriState {
    None=0x0, Loaded, Playing, Paused, Stopped, Cleared
};

typedef struct SoundPri_ {
    float a; //amplitude
    float f; //freq
    float lp; //low pass (1.0 pass all, 0.0 cut all)
	float rpm;
    int id; // car ID.
    enum SoundPriState state;
} SoundPri;

class SoundInterface {
 public:
    SoundInterface();
    virtual ~SoundInterface();
};

class PlibSoundInterface : public SoundInterface {
protected:
	slScheduler* sched;
public:
	PlibSoundInterface();
	virtual ~PlibSoundInterface();
};

class OpenalSoundInterface : public SoundInterface {
protected:
	slScheduler* sched;
public:
    OpenalSoundInterface();
	virtual ~OpenalSoundInterface();
};

class SampleInterface {
protected:
	float filter;
	float volume;
	float pitch;
	SoundInterface* scheduler;
public:
    SampleInterface();
    ~SampleInterface();
    void loop();
    void setVolume(float a);
    void setPitch(float f);
    void pause();
    void resume();
    void stop();
};

void DopplerShift (SoundChar* sound, float* p_src, float* u_src, float* p, float* u);
int SortSndPriority(const void* a, const void* b);
#endif /* _GRSOUND_H_ */ 



