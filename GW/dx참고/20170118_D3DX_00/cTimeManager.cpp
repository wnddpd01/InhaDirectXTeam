#include "stdafx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager()
{
	m_dwLastUpdateTime = GetTickCount();
}


cTimeManager::~cTimeManager()
{
}

void cTimeManager::Update()
{
	DWORD dwCurrUpdateTime = GetTickCount();
	m_dwDeltaTime = dwCurrUpdateTime - m_dwLastUpdateTime;
	m_dwLastUpdateTime = dwCurrUpdateTime;
}

float cTimeManager::GetDeltaTime()
{
	return m_dwDeltaTime / 1000.f;
}