#pragma once


class cObjectManager
{
//	cObjectManager();
//public:
//	~cObjectManager();

private :
	Singleton(cObjectManager);

	std::set<cObject*> m_setObject;

public :
	void AddObject(cObject * pObject);
	void RemoveObject(cObject * pObject);
	void Destroy();
	
};

#define g_pObjectManager cObjectManager::GetInstance()
