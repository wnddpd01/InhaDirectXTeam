#pragma once

#define gSoundManager SoundManager::GetInstance()

using namespace FMOD;
using namespace std;

class SoundManager
{
	Singletone(SoundManager);
	
private:
	System* mSystem;
	Sound** mSound;
	Channel** mChannel;

	UINT mBuffer;
	float mVolume;

	map<string, Sound**> mSounds;
	map<string, Sound**>::iterator it;

	
	
public:
	
	void AddSound(string name, string soundFile, bool loop = false);
	void init();
	
	void Play(string name, float volume = 0.5f);
	void Stop(string name);
	void Pause(string name);
	void Resume(string name);

	bool Playing(string name);
	bool Paused(string name);

	void Volume(string name, float volume);
	float Volume() { return mVolume; }

	void Update();


	void SoundControl();

	void Sound3D(string name,float x, float z);

	
	
};

