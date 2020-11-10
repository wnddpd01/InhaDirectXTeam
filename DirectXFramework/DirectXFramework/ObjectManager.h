#pragma once
#include <set>
#include "Object.h"

#define	g_pObjectManager ObjectManager::GetInstance()

class ObjectManager : public Singleton<ObjectManager>
{

private:
	std::set<Object*> m_setObject;

public:
	void AddObject(Object* pObject);
	void RemoveObject(Object* pObject);
	void Destroy();

};