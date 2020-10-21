#pragma once

#define	g_pObjectManager tObjectManager::GetInstance()

class tObjectManager
{
private:
	Singletone(tObjectManager);

	std::set<tObject*> m_setObject;
	
public:
	void AddObject(tObject* pObject);
	void RemoveObject(tObject* pObject);
	void Destroy();
};

