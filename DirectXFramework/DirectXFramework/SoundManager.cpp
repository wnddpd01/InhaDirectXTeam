#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager()
	:mSystem(nullptr)
	, mChannel(nullptr)
	, mSound(nullptr)
	, mBuffer(5)
	, mVolume(0.3f)
{
}


SoundManager::~SoundManager()
{
	if (mChannel != nullptr || mSound != nullptr)
	{
		for (UINT i = 0; i<mBuffer; i++)
		{
			if (mChannel != nullptr && mChannel[i])
			{
				mChannel[i]->stop();
			}

			if (mSound != nullptr && mSound[i])
			{
				mSound[i]->release();
			}

		}
	}

	SafeDelete(mChannel);
	SafeDelete(mSound);

	if (mSystem != nullptr)
	{
		mSystem->release();
		mSystem->close();
	}

	mSounds.clear();

}

void SoundManager::AddSound(string name, string soundFile, bool loop)
{
	if (loop == true)
	{
		if (name == "BGM")
		{
			mSystem->createSound(
				soundFile.c_str(),
				FMOD_LOOP_NORMAL,
				nullptr,
				&mSound[mSounds.size()]);
		}
		else
		{
			mSystem->createSound(
				soundFile.c_str(),
				FMOD_3D,
				nullptr,
				&mSound[mSounds.size()]);
		}

	}
	else
	{
		mSystem->createSound(
			soundFile.c_str(),
			FMOD_DEFAULT,
			nullptr,
			&mSound[mSounds.size()]);
	}

	mSounds.insert(make_pair(name, &mSound[mSounds.size()]));
}

void SoundManager::SoundSet()
{
	System_Create(&mSystem);

	mSystem->init(mBuffer, FMOD_INIT_NORMAL, 0);
	mSound = new Sound*[mBuffer];
	mChannel = new Channel*[mBuffer];

	memset(mSound, 0, sizeof(Sound*)*(mBuffer));
	memset(mChannel, 0, sizeof(Channel*)*(mBuffer));

	
	AddSound("BGM", "./sounds/Sonata.mp3", true);
	AddSound("DIE", "./sounds/start.wav", true);

}

void SoundManager::Play(string name, float volume)
{
	int count = 0;

	it = mSounds.begin();
	for (it; it != mSounds.end(); it++)
	{
		count++;

		if (name == it->first)
		{
			mSystem->playSound(
				FMOD_CHANNEL_FREE,
				*it->second,
				false,
				&mChannel[count]
			);

			mChannel[count]->setVolume(volume);

			mChannel[count]->set3DMinMaxDistance(0.1, 10000);
		}
	}

}

void SoundManager::Stop(string name)
{
	int count = 0;
	it = mSounds.begin();

	for (it; it != mSounds.end(); it++)
	{
		count++;

		if (name == it->first)
		{
			mChannel[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(string name)
{
	int count = 0;
	it = mSounds.begin();

	for (it; it != mSounds.end(); it++)
	{
		count++;
		if (name == it->first)
		{
			mChannel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::Resume(string name)
{
	int count = 0;
	it = mSounds.begin();

	for (it; it != mSounds.end(); it++)
	{
		count++;

		if (name == it->first)
		{
			mChannel[count]->setPaused(false);
			break;
		}
	}

}

bool SoundManager::Playing(string name)
{
	bool bPaly = false;
	int count = 0;
	it = mSounds.begin();

	for (it; it != mSounds.end(); it++)
	{
		count++;

		if (name == it->first)
		{
			mChannel[count]->isPlaying(&bPaly);
			break;
		}
	}

	return bPaly;
}

bool SoundManager::Paused(string name)
{
	bool bPause = false;
	int count = 0;
	it = mSounds.begin();

	for (it; it != mSounds.end(); it++)
	{
		count++;

		if (name == it->first)
		{
			mChannel[count]->setPaused(&bPause);
			break;
		}
	}

	return bPause;


}

void SoundManager::Volume(string name, float volume)
{
	int count = 0;
	it = mSounds.begin();

	for (it; it != mSounds.end(); it++)
	{
		count++;

		if (name == it->first)
		{
			mChannel[count]->setVolume(volume);
			break;
		}
	}
}

void SoundManager::Update()
{
	mSystem->update();
}

void SoundManager::SoundControl()
{

	if (GetKeyState('Q') & 0x8000)
	{
		Play("BGM", 0.9f);

	}

	if (GetKeyState('E') & 0x8000)
	{
		Play("DIE", 0.2f);
	}

	if (GetKeyState('M') & 0x8000)
	{
		Stop("BGM");
		Stop("DIE");
	}

	if (GetKeyState('Z') & 0x8000)
	{
		Playing("DIE");
	}

	if (GetKeyState('P') & 0x8000)
	{
		Paused("BGM");
	}

	if (GetKeyState('R') & 0x8000)
	{
		Resume("BGM");
	}


	if (GetKeyState('U') & 0x8000)
	{
		if (mVolume <= 1.0f)
		{
			mVolume += 0.1f;
			Volume("BGM", mVolume);
		}
	}

	if (GetKeyState('J') & 0x8000)
	{
		if (mVolume >= 0.0f)
		{
			mVolume -= 0.1f;
			Volume("BGM", mVolume);
		}

	}


}

void SoundManager::Sound3D(string name, float x, float z)
{
	FMOD_VECTOR listenervel = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR listenerpos = { x, 0.0f, z };



	mSystem->set3DListenerAttributes(0, &listenerpos, &listenerpos, 0, 0);

	if (mChannel)
	{
		FMOD_VECTOR sourcePos = { 0.0f,0.0f,0.0f };
		(*mChannel)->set3DAttributes(&sourcePos, 0);
	}




	//======REVERB
	//FMOD_REVERB_PROPERTIES prop1 = FMOD_PRESET_MOUNTAINS;
	//mSystem->setReverbAmbientProperties(&prop1);

	//FMOD::Reverb *reverb;
	//mSystem->createReverb(&reverb);
	//FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_UNDERWATER;
	//reverb->setProperties(&prop);
	//FMOD_VECTOR pos = { 10.0f,0.0f,10.0f };
	//float mindist = 100.0f;
	//float maxdist = 150.0f;
	//reverb->set3DAttributes(&pos, mindist, maxdist);

	//reverb->setActive(true);

	//FMOD_REVERB_PROPERTIES myReverbProp = {
	//	0,22,1.00f,
	//	-0, 0, 0,
	//	1.49f, 0.10f, 1.0f,
	//	-449, 0.15f,
	//	-5700, 0.011f,
	//	1.18f, 0.348f,
	//	5000.0f, 250.0f,
	//	100.0f, 100.0f,
	//	0x3f	};

	//======


}
