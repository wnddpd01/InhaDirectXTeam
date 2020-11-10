#include "stdafx.h"
#include "ObjectManager.h"

void ObjectManager::AddObject(Object* pObject)
{
	m_setObject.insert(pObject);
}

void ObjectManager::RemoveObject(Object* pObject)
{
	m_setObject.erase(pObject);
}

void ObjectManager::Destroy()
{
	m_setObject.clear();
}
