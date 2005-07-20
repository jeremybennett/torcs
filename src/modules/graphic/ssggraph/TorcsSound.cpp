// -*- Mode: c++ -*-
/***************************************************************************
    file                 : TorcsSound.cpp
    created              : Tue Apr 5 19:57:35 CEST 2005
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

#include "TorcsSound.h"
#include "SoundInterface.h"

void TorcsSound::setVolume(float vol)
{
	this->volume = vol;
}
void TorcsSound::setPitch(float pitch)
{
	this->pitch = pitch;
}
void TorcsSound::setLPFilter(float lp)
{
	this->lowpass = lp;
}


PlibTorcsSound::PlibTorcsSound(slScheduler* sched,
			       const char* filename,
			       int flags,
			       bool loop) : TorcsSound (flags)
{
	this->sched = sched;
	this->loop = loop;
	MAX_VOL = 1.0f;
	sample = new slSample (filename, sched);
	if (flags & ACTIVE_VOLUME) {
		volume_env = new slEnvelope(1, SL_SAMPLE_ONE_SHOT);
	}
	if (flags & ACTIVE_PITCH) {
		pitch_env = new slEnvelope(1, SL_SAMPLE_ONE_SHOT);
	}
	if (flags & ACTIVE_LP_FILTER) {
		lowpass_env = new slEnvelope(1, SL_SAMPLE_ONE_SHOT);
	}
	if (loop) {
		sched->loopSample (sample);
	}
	if (flags & ACTIVE_VOLUME) {
		sched->addSampleEnvelope (sample, 0, VOLUME_SLOT, volume_env,
					  SL_VOLUME_ENVELOPE);
	}
	if (flags & ACTIVE_PITCH) {
		sched->addSampleEnvelope (sample, 0, PITCH_SLOT, pitch_env,
					  SL_PITCH_ENVELOPE);
	}
	if (flags & ACTIVE_LP_FILTER) {
		sched->addSampleEnvelope(sample, 0, FILTER_SLOT, lowpass_env,
					 SL_FILTER_ENVELOPE);
	}
	if (flags & ACTIVE_VOLUME) {
		volume_env->setStep(0, 0.0f, 0.0f);
	}
	if (flags & ACTIVE_PITCH) {
		pitch_env->setStep(0, 0.0f, 1.0f);
	}
	if (flags & ACTIVE_LP_FILTER) {
		lowpass_env->setStep(0, 0.0, 1.0f);
	}
	volume = 0.0f;
	pitch = 1.0f;
	lowpass = 1.0f;
	playing = false;
	paused = false;
}

PlibTorcsSound::~PlibTorcsSound()
{
	sched->stopSample(sample);
	if (flags & ACTIVE_VOLUME) {
		sched->addSampleEnvelope(sample, 0, VOLUME_SLOT, NULL,
					 SL_NULL_ENVELOPE);
		delete volume_env;
	}
	if (flags & ACTIVE_PITCH) {
		sched->addSampleEnvelope(sample, 0, PITCH_SLOT, NULL,
					 SL_NULL_ENVELOPE);
		delete pitch_env;
	}
	if (flags & ACTIVE_LP_FILTER) {
		sched->addSampleEnvelope(sample, 0, FILTER_SLOT, NULL,
					 SL_NULL_ENVELOPE);
		delete lowpass_env;
	}
	delete sample;
}

void PlibTorcsSound::setVolume(float vol)
{
	if (vol > MAX_VOL) {
		vol = MAX_VOL;
	}
	this->volume = vol;
}

void PlibTorcsSound::play()
{
	start();
}
void PlibTorcsSound::start()
{
	// TODO: consistency check?
	if (loop) {
		if (playing == false) {
			playing = true;
			sched->loopSample (sample);
		}
	} else {
		playing = true;
		sched->playSample (sample);
	}
}
void PlibTorcsSound::stop()
{
	if (playing == true) {
		playing = false;
		sched->stopSample (sample);
	}
}
void PlibTorcsSound::resume()
{
	sched->resumeSample (sample);
	paused = false;
}
void PlibTorcsSound::pause()
{
	sched->pauseSample (sample);
	paused = true;
}




void PlibTorcsSound::update()
{


	if (flags & ACTIVE_VOLUME) {
		volume_env->setStep(0, 0.0f, volume);
	}
	if (flags & ACTIVE_PITCH) {
		pitch_env->setStep(0, 0.0f, pitch);

	}
	if (flags & ACTIVE_LP_FILTER) {
		lowpass_env->setStep(0, 0.0f, lowpass);
	}
}


PlibSoundSource::PlibSoundSource()
{
	a = 0.0;
	f = 1.0;
	lp = 1.0;
}

void PlibSoundSource::update()
{
	// Get relative speed/position vector
	sgVec3 u;
	sgVec3 p;
	float u_rel = 0.0f;
	float u_rel_src = 0.0f;
	float u_rel_lis = 0.0f;
	float p_rel = 0.0f;
	int i;
	for (i=0; i<3; i++) {
		u[i] = u_src[i] - u_lis[i];
		p[i] = p_src[i] -  p_lis[i];
		p_rel += p[i]*p[i];
	}
    
    a = 1.0;
	f = 1.0f;
	lp = 1.0f;

	// Only the vector component on the LOV is significant
	//    u_rel = sqrt(u_rel);
	p_rel = 1.0 + sqrt(p_rel);
	float p_cosx = p[0]/p_rel;
	float p_cosy = p[1]/p_rel;
	float p_cosz = p[2]/p_rel;
	float p_x_comp = u[0]*p_cosx;
	float p_y_comp = u[1]*p_cosy;
	float p_z_comp = u[2]*p_cosz;
	float p_x_src = u_src[0]*p_cosx;
	float p_y_src = u_src[1]*p_cosy;
	float p_z_src = u_src[2]*p_cosz;
	float p_x_lis = u_lis[0]*p_cosx;
	float p_y_lis = u_lis[1]*p_cosy;
	float p_z_lis = u_lis[2]*p_cosz;
	u_rel = (p_y_comp + p_x_comp + p_z_comp);
	u_rel_src = (p_y_src + p_x_src + p_z_src);
	u_rel_lis = (p_y_lis + p_x_lis + p_z_lis);
	if (fabs(u_rel)>=0.9f*SPEED_OF_SOUND) {
		// Cut-off sound when relative speed approaches speed of sound.
		a = 0.0f;
		f = 1.0f;
		lp = 1.0f;
	} else {
		// attenuate and filter sound with distance
		// and shift pitch with speed
		float atten = 10.0f/p_rel;
		//f = SPEED_OF_SOUND/(SPEED_OF_SOUND+u_rel);
		f = (SPEED_OF_SOUND - u_rel_src)/(SPEED_OF_SOUND - u_rel_lis);
		a = atten;
		float atten_filter = MIN (atten, 1.0f);
		lp = exp(atten_filter - 1.0f);
	}

}

void PlibSoundSource::setSource(sgVec3 p, sgVec3 u)
{
	for (int i=0; i<3; i++) {
		p_src[i] = p[i];
		u_src[i] = u[i];
	}
}


void PlibSoundSource::setListener (sgVec3 p, sgVec3 u)
{
	for (int i=0; i<3; i++) {
		p_lis[i] = p[i];
		u_lis[i] = u[i];
	}
}


OpenalTorcsSound::OpenalTorcsSound(const char* filename, int flags, bool loop)
{

	this->loop = loop;
	this->flags = flags;
	volume = 0.0f;
	pitch = 1.0f;
	lowpass = 1.0f;

	MAX_DISTANCE = 10000.0f;
	MAX_DISTANCE_LOW = 5.0f;
	REFERENCE_DISTANCE = 5.0f;
	ROLLOFF_FACTOR = 0.5f;

	for (int i=0; i<3; i++) {
		source_position[i] = 0.0f;
		source_velocity[i] = 0.0f;
		zeroes[i] = 0.0f;
	}
	alGenBuffers (1, &buffer);
	void* wave = NULL;
	ALsizei size;
	ALsizei bits;
	ALsizei freq;
	ALsizei format;

	ALboolean err = alutLoadWAV (filename, &wave, &format, &size, &bits, &freq);
	if (err == AL_FALSE) {
		fprintf (stderr, "Could not load %f\n", filename);
		exit(1);
	}
	
	alBufferData (buffer, format, wave, size, freq);
	free (wave);
	
	alGenSources (1, &source);
	alSourcefv (source, AL_POSITION, source_position);
	alSourcefv (source, AL_VELOCITY, source_velocity);
	alSourcei (source, AL_BUFFER, buffer);
	alSourcei (source, AL_LOOPING, loop);
	alSourcef (source, AL_MAX_DISTANCE, MAX_DISTANCE);
	alSourcef (source, AL_REFERENCE_DISTANCE, REFERENCE_DISTANCE);
	alSourcef (source, AL_ROLLOFF_FACTOR, ROLLOFF_FACTOR);
	alSourcef (source, AL_GAIN, 0.0f);
	playing = false;
	paused = false;
}

OpenalTorcsSound::~OpenalTorcsSound()
{
	alSourceStop (source);
}

void OpenalTorcsSound::setVolume (float vol)
{
	this->volume = vol;
}

void OpenalTorcsSound::setPitch(float pitch)
{
	this->pitch = pitch;
}

void OpenalTorcsSound::setLPFilter(float lp)
{
	this->lowpass = lp;
}


void OpenalTorcsSound::setReferenceDistance(float dist)
{
	alSourcef (source, AL_REFERENCE_DISTANCE, dist);
}


void OpenalTorcsSound::setSource (sgVec3 p, sgVec3 u)
{
	for (int i=0; i<3; i++) {
		source_position[i] = p[i];//*0.1f;
		source_velocity[i] = u[i];
	}
}


void OpenalTorcsSound::getSource(sgVec3 p, sgVec3 u)
{
	for (int i=0; i<3; i++) {
		p[i] = source_position[i];
		u[i] = source_velocity[i];
	}
}


void OpenalTorcsSound::play()
{
	start();
}

void OpenalTorcsSound::start()
{
	if (playing==false) {
		if (loop) {playing = true;}
		//printf ("alSourcePlay()\n");
		alSourcePlay (source);
	}
}
void OpenalTorcsSound::stop()
{
	if (playing==true) {
		playing = false;
		//printf ("alSourceStop()\n");
		alSourceStop (source);
	}
}

void OpenalTorcsSound::resume()
{
	if (paused==true) {
		paused = false;
	}
}
void OpenalTorcsSound::pause()
{
	if (paused==false) {
		paused = true;
	}
}

void OpenalTorcsSound::update ()
{

	alSourcefv (source, AL_POSITION, source_position);
	alSourcefv (source, AL_VELOCITY, source_velocity);
	alSourcef (source, AL_PITCH, pitch);
	alSourcef (source, AL_GAIN, volume);
}


