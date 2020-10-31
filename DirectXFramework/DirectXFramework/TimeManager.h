#pragma once

#include "Singleton.h"

#define gTimeManager TimeManager::GetInstance()
#define gDeltaTime TimeManager::GetInstance()->GetDeltaTime()

using namespace std;
using namespace chrono;

class TimeManager : public Singleton<TimeManager>
{
	private:
		system_clock::time_point	mLastTime;
		system_clock::time_point	mNewTime;
		duration<float>				mDeltaTime;
	public:
		void SetGameLoopStartTime();
		void SetGameLoopEndTime();
		float GetDeltaTime();
		system_clock::time_point GetCurTime();
};

