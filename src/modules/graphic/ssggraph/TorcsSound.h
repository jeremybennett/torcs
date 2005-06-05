// -*- Mode: c++ -*-
/***************************************************************************
    file                 : TorcsSound.h
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

#ifndef TORCS_SOUND_H
#define TORCS_SOUND_H

#define VOLUME_SLOT 0
#define PITCH_SLOT 1
#define FILTER_SLOT 2

#include <plib/sg.h>
#include <plib/sl.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include "sound_defines.h"

class SoundInterface;

class TorcsSound {
protected:
	class SoundInterface* iface;
	int flags;
	float MAX_VOL;
	float volume;
	float pitch;
	float lowpass;
	bool loop;
public:
	TorcsSound(int flags = (ACTIVE_VOLUME|ACTIVE_PITCH))
	{
		this->flags = flags;
		
	}
	virtual ~TorcsSound() {}
	virtual void setVolume(float vol);
	virtual void setPitch(float pitch);
	virtual void setLPFilter(float lp);
	virtual void setSource(sgVec3 p, sgVec3 u) {}
	virtual float getVolume() {return volume;}
	virtual float getPitch() {return pitch;}
	virtual float getLPfilter() {return lowpass;}
	virtual void setReferenceDistance (float dist) {}
	virtual void getSource (sgVec3 p, sgVec3 u) {}
	//virtual void setListener(sgVec3 p, sgVec3 u) = 0;
	virtual void play() = 0;
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void resume() = 0;
	virtual void pause() = 0;
	virtual void update() = 0;
	virtual bool isPlaying() = 0;
	virtual bool isPaused() = 0;
};

class PlibTorcsSound : public TorcsSound {
protected:
	slSample* sample;
	slEnvelope* volume_env;
	slEnvelope* pitch_env;
	slEnvelope* lowpass_env;
	slScheduler* sched;
	bool playing, paused;
public:
	PlibTorcsSound(slScheduler* sched,
				   const char* filename,
				   int flags = (ACTIVE_VOLUME|ACTIVE_PITCH),
				   bool loop = false);
	virtual ~PlibTorcsSound();
	virtual void setVolume(float vol);
	//virtual void setSource(sgVec3 p, sgVec3 u);
	//virtual void setListener (sgVec3 p, sgVec3 u);
	virtual void play();
	virtual void start();
	virtual void stop();
	virtual void resume();
	virtual void pause();
	virtual void update();
	virtual bool isPlaying()
	{
		return playing;
	}
	virtual bool isPaused() 
	{
		return paused;
	}
};

class PlibSoundSource {
public:
	sgVec3 p_lis;
	sgVec3 u_lis;
	sgVec3 p_src;
	sgVec3 u_src;
	float a, f, lp;
	PlibSoundSource();
	void update();
	void setSource(sgVec3 p, sgVec3 u);
	void setListener (sgVec3 p, sgVec3 u);
};



class OpenalTorcsSound : public TorcsSound {
protected:
	ALuint buffer;
	ALuint source;
	ALfloat source_position[3];
	ALfloat source_velocity[3];
	ALfloat zeroes[3];
	ALfloat back[6];
	ALfloat front[6];
	bool playing, paused;
	ALfloat MAX_DISTANCE;
	ALfloat MAX_DISTANCE_LOW;
	ALfloat REFERENCE_DISTANCE;
	ALfloat ROLLOFF_FACTOR;
public:
	OpenalTorcsSound(const char* filename,
					 int flags = (ACTIVE_VOLUME|ACTIVE_PITCH),
					 bool loop = false);
	virtual ~OpenalTorcsSound();
	virtual void setVolume(float vol);
	virtual void setPitch(float pitch);
	virtual void setLPFilter(float lp);
	virtual void setSource(sgVec3 p, sgVec3 u);
	virtual void getSource (sgVec3 p, sgVec3 u);
	virtual void setReferenceDistance (float dist);
	//virtual void setListener (sgVec3 p, sgVec3 u);
	virtual void play();
	virtual void start();
	virtual void stop();
	virtual void resume();
	virtual void pause();
	virtual void update();
	virtual bool isPlaying()
	{
		return playing;
	}
	virtual bool isPaused() 
	{
		return paused;
	}
};






#endif
