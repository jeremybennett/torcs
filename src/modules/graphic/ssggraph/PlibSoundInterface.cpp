/***************************************************************************

    file                 : PlibSoundInterface.cpp
    created              : Thu Apr 7 04:21 CEST 2005
    copyright            : (C) 2005 Christos Dimitrakakis
    email                : dimitrak@idiap.ch
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

#include "SoundInterface.h"
#include "TorcsSound.h"
#include "CarSoundData.h"


void PlibSoundInterface::update(CarSoundData** car_sound_data, int n_cars, sgVec3 p_obs, sgVec3 u_obs, sgVec3 c_obs, sgVec3 a_obs)
{
	// Copy car ID basically.
	for (int i=0; i<n_cars; i++) {
		car_sound_data[i]->copyEngPri(engpri[i]);
	}

    for (int i=0; i<n_cars; i++) {
		int id = engpri[i].id;
		sgVec3 p;
		sgVec3 u;
		car_sound_data[id]->getCarPosition(p);
		car_sound_data[id]->getCarSpeed(u);
		car_src[id].setSource (p, u);
		car_src[id].setListener (p_obs, u_obs);
		car_src[id].update();
		engpri[id].a = car_src[id].a;
	}

	qsort ((void*) engpri, n_cars, sizeof(SoundPri), &sortSndPriority);

    for (int i=0; i<n_cars; i++) {
		int id = engpri[i].id;
		TorcsSound* engine = car_sound_data[id]->getEngineSound();
		if (i>=NB_ENGINE_SOUND) {
			engine->setVolume (0.0f);
			engine->pause();
			//printf ("Pausing %d (%d)\n", id, i);
		} else {
			engine->resume();
			engine->setLPFilter(car_src[id].lp*car_sound_data[id]->engine.lp);
			engine->setPitch(car_src[id].f*car_sound_data[id]->engine.f);
			engine->setVolume(car_src[id].a*car_sound_data[id]->engine.a);
			engine->update();
		}
	}


    sched->update();
}

int sortSndPriority(const void* a, const void* b) 
{
    SoundPri* A = (SoundPri*) a;
    SoundPri* B = (SoundPri*) b;
    if (A->a > B->a) {
		return -1;
    } else {
		return 1;
    }
}


