#pragma once
#define gTimeManager TimeManager::GetInstance()
#define gDeltaTime TimeManager::GetInstance()->GetDeltaTime()

using namespace std;
using namespace chrono;

class TimeManager
{
	Singletone(TimeManager);

	private:
		system_clock::time_point	lastTime;
		system_clock::time_point	newTime;
		duration<float>				deltaTime;
	public:
		void SetGameLoopStratTime();
		void SetGameLoopEndTime();
		float GetDeltaTime();
		system_clock::time_point GetCurTime();
};

