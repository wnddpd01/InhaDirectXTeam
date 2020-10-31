#include "stdafx.h"
#include "TimeManager.h"


void TimeManager::SetGameLoopStartTime()
{
	mNewTime = GetCurTime();
	mDeltaTime = mNewTime - mLastTime;
	//assert(deltaTime.count() < 0);
}

void TimeManager::SetGameLoopEndTime()
{
	mLastTime = mNewTime;
}

float TimeManager::GetDeltaTime()
{
	// TODO 최초부분 코드 추가 필요

	return mDeltaTime.count();
}

system_clock::time_point TimeManager::GetCurTime()
{
	return system_clock::now();
}

