#include "stdafx.h"
#include "Portal.h"
#include "Player.h"

Portal::Portal()
{
}


Portal::~Portal()
{
}

void Portal::Render()
{
	Base3DObject::Render();
	
	for (map<string, pair<Base3DObject*, D3DXVECTOR3>>::value_type& objectInPortal : mObjectsInPortal)
	{
		D3DXVECTOR3 prevPos = objectInPortal.second.first->GetPos();
		objectInPortal.second.first->SetPos(objectInPortal.second.second);
	
		objectInPortal.second.first->Render();
		objectInPortal.second.first->SetPos(prevPos);
	}
}

void Portal::Update()
{
	Base3DObject::Update();
	
	for (map<string, pair<Base3DObject*, D3DXVECTOR3>>::value_type& objectInPortal : mObjectsInPortal)
	{
		objectInPortal.second.second = mExitPos - objectInPortal.second.first->GetPos() + mPos;
	}
}

void Portal::PortalColliderHandler(Base3DObject* myObject, string& myColliderTag, Base3DObject* otherObject, string& otherColliderTag)
{
	if(mObjectsInPortal.find(otherObject->GetObjectName()) == mObjectsInPortal.end())
	{
		mObjectsInPortal.insert(make_pair(otherObject->GetObjectName(), make_pair(otherObject, mExitPos)));
	}
}
