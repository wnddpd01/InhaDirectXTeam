#include "stdafx.h"
#include "Portal.h"
#include "Player.h"

Portal::Portal(D3DXVECTOR3 portalDir)
	: mExitPos(0,0,0)
{
	for (int i = 0; i < 2; ++i)
	{
		mPortalLine[i] = D3DXVECTOR3(0, 0, 0);
	}
}


Portal::~Portal()
{
}

void Portal::Render()
{
	Base3DObject::Render();

	D3DXQUATERNION rotY;
	D3DXQuaternionRotationYawPitchRoll(&rotY, D3DX_PI, 0, 0);
	
	for (map<string, pair<Base3DObject*, D3DXVECTOR3>>::value_type& objectInPortal : mObjectsInPortal)
	{
		D3DXVECTOR3 prevPos = objectInPortal.second.first->GetPos();
		D3DXQUATERNION prevRot = objectInPortal.second.first->GetRot();
		
		objectInPortal.second.first->SetPos(objectInPortal.second.second);
		objectInPortal.second.first->SetRot(prevRot * rotY);
		
		objectInPortal.second.first->Render();
		
		objectInPortal.second.first->SetPos(prevPos);
		objectInPortal.second.first->SetRot(prevRot);
	}
}

void Portal::Update()
{
	Base3DObject::Update();
	
	for (map<string, pair<Base3DObject*, D3DXVECTOR3>>::value_type& objectInPortal : mObjectsInPortal)
	{
		objectInPortal.second.second = mExitPos + mPos - objectInPortal.second.first->GetPos();
	}
}

void Portal::PortalColliderHandler(Base3DObject* myObject, string& myColliderTag, Base3DObject* otherObject, string& otherColliderTag)
{
	if(mObjectsInPortal.find(otherObject->GetObjectName()) == mObjectsInPortal.end())
	{
		mObjectsInPortal.insert(make_pair(otherObject->GetObjectName(), make_pair(otherObject, mExitPos + mPos - otherObject->GetPos())));
	}
}
