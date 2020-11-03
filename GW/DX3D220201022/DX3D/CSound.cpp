#include "stdafx.h"
#include "CSound.h"

FMOD_SYSTEM* CSound::gSoundsystem;


CSound::CSound(const char* path, bool loop)
{
	if(loop)
	{
		FMOD_System_CreateSound(gSoundsystem, path, FMOD_LOOP_NORMAL, 0, &mSound);
	}
	else
	{
		FMOD_System_CreateSound(gSoundsystem, path, FMOD_DEFAULT, 0, &mSound);
	}

	mChannel = nullptr;
	mVolume = SOUND_DEFAULT;

}

CSound::~CSound()
{
	FMOD_Sound_Release(mSound);
}


void CSound::Init()
{
	FMOD_System_Create(&gSoundsystem);
	FMOD_System_Init(gSoundsystem, 32, FMOD_INIT_NORMAL, NULL);


}

void CSound::Release()
{
	FMOD_System_Close(gSoundsystem);
	FMOD_System_Release(gSoundsystem);


}

void CSound::Play()
{
	FMOD_System_PlaySound(gSoundsystem, mSound, NULL, false, &mChannel);


}

void CSound::Pause()
{
	FMOD_Channel_SetPaused(mChannel, true);


}

void CSound::Resume()
{
	FMOD_Channel_SetPaused(mChannel, false);


}

void CSound::Stop()
{
	FMOD_Channel_Stop(mChannel);


}

void CSound::VolumeUp()
{
	if(mVolume < SOUND_MAX)
	{
		mVolume += SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(mChannel, mVolume);


}

void CSound::VolumeDown()
{
	if (mVolume > SOUND_MIN)
	{
		mVolume -= SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(mChannel, mVolume);

}

void CSound::Update()
{
	FMOD_Channel_IsPlaying(mChannel, &mBool);

	if(mBool)
	{
		FMOD_System_Update(gSoundsystem);
	}


}

