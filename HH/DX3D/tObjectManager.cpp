#include "stdafx.h"
#include "tObjectManager.h"


tObjectManager::tObjectManager()
{
}


tObjectManager::~tObjectManager()
{
}

void tObjectManager::AddObject(tObject* pObject)
{
	m_setObject.insert(pObject);
}

void tObjectManager::RemoveObject(tObject* pObject)
{
	m_setObject.erase(pObject);
}

void tObjectManager::Destroy()
{
	m_setObject.clear();
}
