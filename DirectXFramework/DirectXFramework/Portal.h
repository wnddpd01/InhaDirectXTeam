#pragma once
#include "Base3DObject.h"


class Portal :
	public Base3DObject
{
	D3DXVECTOR3 mExitPos;
	map<string, pair<Base3DObject *, D3DXVECTOR3>> mObjectsInPortal;
public:
	Portal();
	~Portal();

	void Render() override;
	void Update() override;
	
	void SetExitPos(D3DXVECTOR3 exitPos) { mExitPos = exitPos; }
	D3DXVECTOR3 GetExitPos() const { return mExitPos; }
	void PortalColliderHandler(Base3DObject * myObject, string& myColliderTag, Base3DObject * otherObject, string& otherColliderTag);
};


