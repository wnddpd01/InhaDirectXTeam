#pragma once

class cSkinnedMesh;

class cZealot : public BaseObject, public BaseObserver
{
	cSkinnedMesh* m_pSkinnedMesh;
public:
	void Setup();
	void Update();
	void Render();

	bool Update(eEventName eventName, void* parameter) override;
	
	cZealot();
	virtual ~cZealot();
};

