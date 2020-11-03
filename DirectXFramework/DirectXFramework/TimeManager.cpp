#include "stdafx.h"
#include "TimeManager.h"


void TimeManager::Update()
{
	mNewTime = GetCurTime();
	mDeltaTime = mNewTime - mLastTime;
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

