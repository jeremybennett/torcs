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
#include "CarSoundData.h"
#include "TorcsSound.h"




OpenalSoundInterface::OpenalSoundInterface(float sampling_rate, int n_channels): SoundInterface (sampling_rate, n_channels)
{
	ALfloat far_away[] = { 0.0f, 0.0f,  1000.0f };
	ALfloat front[]  = { 0.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f };
	dev = alcOpenDevice( NULL );
	if( dev == NULL ) {
		throw ("Could not open device");
	}
		
	cc = alcCreateContext( dev, NULL);
	if(cc == NULL) {
		alcCloseDevice( dev );
		throw ("Could not create context.");
	}

	alcMakeContextCurrent( cc );
	// - these are LOKI extensions
	//fixup_function_pointers();
	//talBombOnError();
	alDistanceModel ( AL_INVERSE_DISTANCE );
	//alDopplerFactor (?);
	alDopplerVelocity (SPEED_OF_SOUND);

	alListenerfv(AL_POSITION, far_away );
	alListenerfv(AL_VELOCITY, far_away );
	alListenerfv(AL_ORIENTATION, front );
	
	engpri = NULL;
	global_gain = 1.0f;
	
	// initialise mappings
	grass.schar = &CarSoundData::grass;
	grass_skid.schar = &CarSoundData::grass_skid;
	road.schar = &CarSoundData::road;
	metal_skid.schar = &CarSoundData::drag_collision;
	backfire_loop.schar = &CarSoundData::engine_backfire;
	turbo.schar = &CarSoundData::turbo;
	axle.schar = &CarSoundData::axle;


	//cars = NULL;
}

OpenalSoundInterface::~OpenalSoundInterface()
{
	for (unsigned int i=0; i<sound_list.size(); i++) {
		delete sound_list[i];
	}
	delete [] engpri;
	//delete [] cars;
	alcDestroyContext (cc);
	alcCloseDevice (dev);
}

void OpenalSoundInterface::setNCars(int n_cars)
{
	engpri = new SoundPri[n_cars];
	//cars = new OpenalSoundSource[n_cars];
}
TorcsSound* OpenalSoundInterface::addSample (const char* filename, int flags, bool loop)
{
	TorcsSound* sound = new OpenalTorcsSound (filename, flags, loop);
	sound_list.push_back (sound);
	return sound;
}
	
void OpenalSoundInterface::update(CarSoundData** car_sound_data, int n_cars, sgVec3 p_obs, sgVec3 u_obs, sgVec3 c_obs, sgVec3 a_obs)
{
	
	ALfloat listener_pos[3];
	ALfloat listener_speed[3];
	ALfloat listener_orientation[6];
	
	for (int i=0; i<3; i++) {
		listener_pos[i] = p_obs[i];
		listener_speed[i] = u_obs[i];
		listener_orientation[i] = c_obs[i];
		listener_orientation[i+3] = a_obs[i];
	}

	alListenerfv(AL_POSITION, listener_pos );
	alListenerfv(AL_VELOCITY, listener_speed );
	alListenerfv(AL_ORIENTATION, listener_orientation );
	alListenerf(AL_GAIN, getGlobalGain());

	for (int i=0; i<n_cars; i++) {
		car_sound_data[i]->copyEngPri(engpri[i]);
	}


	qsort ((void*) engpri, n_cars, sizeof(SoundPri), &sortSndPriority);

	for (int i=0; i<n_cars; i++) {
		int id = engpri[i].id;
		sgVec3 p;
		sgVec3 u;
		CarSoundData* sound_data = car_sound_data[id];
		sound_data->getCarPosition(p);
		sound_data->getCarSpeed(u);
		TorcsSound* engine = sound_data->getEngineSound();
		engine->setSource(p, u);
		engine->setPitch (sound_data->engine.f);
		engine->setVolume (sound_data->engine.a*(0.2f + 0.8f*sound_data->engine.lp));
		//engine->setLPFilter(sound_data->engine.lp);

		engine->update();
		if (i < n_engine_sounds) {
			engine->start();
		} else {
			engine->stop();
		}
	}
	

	float max_skid_vol[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	int max_skid_id[4] = {0,0,0,0};
	for (int id=0; id<n_cars; id++) {
		CarSoundData* sound_data = car_sound_data[id];
		for (int j=0; j<4; j++) {
			float skvol=sound_data->attenuation*sound_data->wheel[j].skid.a;
			if (skvol > max_skid_vol[j]) {
				max_skid_vol[j] = skvol;
				max_skid_id[j] = id;
			}
		}
	}


	for (int i=0; i<4; i++) {
		int id = max_skid_id[i];
		WheelSoundData* sound_data = car_sound_data[id]->wheel;
		skid_sound[i]->setSource (sound_data[i].p, sound_data[i].u);
		skid_sound[i]->setVolume (sound_data[i].skid.a);
		skid_sound[i]->setPitch (MIN(sound_data[i].skid.f, 1.0f));
		skid_sound[i]->update();
		if (sound_data[i].skid.a > VOLUME_CUTOFF) {
			skid_sound[i]->start();
		} else {
			skid_sound[i]->stop();
		}
	}

	
	// other looping sounds
	road.snd = road_ride_sound;
	SortSingleQueue (car_sound_data, &road, n_cars);
	SetMaxSoundCar (car_sound_data, &road);

	grass.snd = grass_ride_sound;
	SortSingleQueue (car_sound_data, &grass, n_cars);
	SetMaxSoundCar (car_sound_data, &grass);

	grass_skid.snd = grass_skid_sound;
	SortSingleQueue (car_sound_data, &grass_skid, n_cars);
	SetMaxSoundCar (car_sound_data, &grass_skid);

	metal_skid.snd = metal_skid_sound;
	SortSingleQueue (car_sound_data, &metal_skid, n_cars);
	SetMaxSoundCar (car_sound_data, &metal_skid);

	backfire_loop.snd = backfire_loop_sound;
	SortSingleQueue (car_sound_data, &backfire_loop, n_cars);
	SetMaxSoundCar (car_sound_data, &backfire_loop);

	backfire_loop.snd = backfire_loop_sound;
	SortSingleQueue (car_sound_data, &backfire_loop, n_cars);
	SetMaxSoundCar (car_sound_data, &backfire_loop);

	turbo.snd = turbo_sound;
	SortSingleQueue (car_sound_data, &turbo, n_cars);
	SetMaxSoundCar (car_sound_data, &turbo);

	axle.snd = axle_sound;
	SortSingleQueue (car_sound_data, &axle, n_cars);
	SetMaxSoundCar (car_sound_data, &axle);

	// One-off sounds
	for (int id=0; id<n_cars; id++) {
		CarSoundData* sound_data = car_sound_data[id];
		sgVec3 p;
		sgVec3 u;
		if (sound_data->crash) {
			if (++curCrashSnd>=NB_CRASH_SOUND) {
				curCrashSnd = 0;
			}
			car_sound_data[id]->getCarPosition(p);
			car_sound_data[id]->getCarSpeed(u);
			crash_sound[curCrashSnd]->setSource (p, u);
			crash_sound[curCrashSnd]->setVolume (1.0f);
			crash_sound[curCrashSnd]->setPitch (1.0f);
			crash_sound[curCrashSnd]->update();
			crash_sound[curCrashSnd]->start();
		}

		if (sound_data->bang) {
			car_sound_data[id]->getCarPosition(p);
			car_sound_data[id]->getCarSpeed(u);
			bang_sound->setSource (p, u);
			bang_sound->setVolume (1.0f);
			bang_sound->setPitch (1.0f);
			bang_sound->update();
			bang_sound->start();
		}

		if (sound_data->bottom_crash) {
			car_sound_data[id]->getCarPosition(p);
			car_sound_data[id]->getCarSpeed(u);
			bottom_crash_sound->setSource (p, u);
			bottom_crash_sound->setVolume (1.0f);
			bottom_crash_sound->setPitch (1.0f);
			bottom_crash_sound->update();
			bottom_crash_sound->start();
		}

		if (sound_data->gear_changing) {
			car_sound_data[id]->getCarPosition(p);
			car_sound_data[id]->getCarSpeed(u);
			gear_change_sound->setSource (p, u);
			gear_change_sound->setReferenceDistance (1.0f);
			gear_change_sound->setVolume (1.0f);
			gear_change_sound->setPitch (1.0f);
			gear_change_sound->update();
			gear_change_sound->start();
		}
	}
	
}



