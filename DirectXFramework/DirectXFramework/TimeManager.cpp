#include "stdafx.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	: deltaTime(NULL)
	, lastTime(system_clock::now())
	, newTime(system_clock::now())
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::SetGameLoopStratTime()
{
	newTime = GetCurTime();
	deltaTime = newTime - lastTime;
	//assert(deltaTime.count() < 0);
}

void TimeManager::SetGameLoopEndTime()
{
	lastTime = newTime;
}

float TimeManager::GetDeltaTime()
{
	//���ʺκ� �ڵ� �߰� �ʿ�

	return deltaTime.count();
}

system_clock::time_point TimeManager::GetCurTime()
{
	return system_clock::now();
}

