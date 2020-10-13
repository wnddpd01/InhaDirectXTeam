#include "stdafx.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::AddObject(cObject * _pObj)
{
	m_setObject.insert(_pObj);
}

void cObjectManager::RemoveObject(cObject * _pObj)
{
	m_setObject.erase(_pObj);
}

void cObjectManager::Destroy()
{
	g_pAutoReleasePool->Drain();
	assert(m_setObject.empty() && "개체가 지워지지않은게 잇습니다" );
}
