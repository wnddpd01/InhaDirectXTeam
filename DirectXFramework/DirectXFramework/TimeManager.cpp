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
	// TODO ���ʺκ� �ڵ� �߰� �ʿ�

	return mDeltaTime.count();
}

system_clock::time_point TimeManager::GetCurTime()
{
	return system_clock::now();
}

