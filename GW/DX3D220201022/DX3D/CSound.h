#pragma once
#ifndef _CSOUND_H_
#define _CSOUND_H_

#include <fmod.h>

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.2f
#define SOUND_WEIGHT 0.1f


class CSound
{
private:
	static FMOD_SYSTEM *gSoundsystem;

	FMOD_SOUND *mSound;
	FMOD_CHANNEL *mChannel;

	float mVolume;
	FMOD_BOOL mBool;
	
public:
	CSound(const char* path, bool loop);
	~CSound();

	static void Init();
	static void Release();

	void Play();
	void Pause();
	void Resume();
	void Stop();
	void VolumeUp();
	void VolumeDown();

	void Update();
	
};



#endif