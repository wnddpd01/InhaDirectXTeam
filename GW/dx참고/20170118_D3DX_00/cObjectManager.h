#pragma once

#define g_pObjectManager cObjectManager::GetInstance()



class cObjectManager
{
	SINGLETON(cObjectManager);

private:
	set<cObject*> m_setObject;
public:
	void AddObject(cObject* _pObj);
	void RemoveObject(cObject* _pObj);
	void Destroy();
};

