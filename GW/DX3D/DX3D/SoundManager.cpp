#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
	:mSystem(nullptr)
	,mChannel(nullptr)
	,mSound(nullptr)
	,mBuffer(5)
	,mVolume(0.3f)
{
	System_Create(&mSystem);

	mSystem->init(mBuffer, FMOD_INIT_NORMAL, 0);
	mSound = new Sound*[mBuffer];
	mChannel = new Channel*[mBuffer];

	memset(mSound, 0, sizeof(Sound*)*(mBuffer));
	memset(mChannel, 0, sizeof(Channel*)*(mBuffer));
}


SoundManager::~SoundManager()
{
	if(mChannel != nullptr || mSound != nullptr)
	{
		for(UINT i = 0; i<mBuffer; i++)
		{
			if(mChannel != nullptr && mChannel[i])
			{
				mChannel[i]->stop();
			}

			if(mSound != nullptr && mSound[i])
			{
				mSound[i]->release();
			}
			
		}
	}

	SafeDelete(mChannel);
	SafeDelete(mSound);

	if(mSystem != nullptr)
	{
		mSystem->release();
		mSystem->close();
	}

	mSounds.clear();
	
}

void SoundManager::AddSound(string name, string soundFile, bool loop)
{
	if(loop == true)
	{
		mSystem->createStream(
			soundFile.c_str(),
			FMOD_LOOP_NORMAL, 
			nullptr, 
			&mSound[mSounds.size()]);
	}
	else
	{
		mSystem->createStream(
			soundFile.c_str(),
			FMOD_DEFAULT,
			nullptr,
			&mSound[mSounds.size()]);
	}

	mSounds.insert(make_pair(name, &mSound[mSounds.size()]));
}

void SoundManager::init()
{
	gSoundManager->AddSound("BGM", "./sounds/Sonata.mp3", true);
	gSoundManager->AddSound("DIE", "./sounds/die.wav", false);

	(*mChannel)->set3DMinMaxDistance(50, 1000);
}

void SoundManager::Play(string name, float volume)
{
	int count = 0;

	it = mSounds.begin();
	for(it; it != mSounds.end(); it++)
	{
		count++;

		if(name == it->first)
		{
			mSystem->playSound(
				FMOD_CHANNEL_FREE,
				*it->second,
				false,
				&mChannel[count]
			);

			mChannel[count]->setVolume(volume);	
		}
	}
	
}

void SoundManager::Stop(string name)
{
	int count = 0;
	it = mSounds.begin();

	for(it; it != mSounds.end(); it++)
	{
		count++;

		if(name == it->first)
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

	for(it; it != mSounds.end(); it++)
	{
		count++;
		if(name==it->first)
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

	for(it; it != mSounds.end(); it++)
	{
		count++;

		if(name==it->first)
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

	if(GetKeyState('K') & 0x8000)
	{
		Play("DIE", 0.2f);
	}

	if (GetKeyState('S') & 0x8000)
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

	if (GetKeyState('D') & 0x8000)
	{
		if (mVolume >= 0.0f)
		{
			mVolume -= 0.1f;
			Volume("BGM", mVolume);
		}

	}
	
	
}
