#include "stdafx.h"
#include "Base3DObject.h"
#include "ColliderSphere.h"
#include "ColliderCube.h"

Base3DObject::Base3DObject()
	: mScale(0,0,0)
	, mPos(0,0,0)
	, mObjectTag(eObjTag::NON_OBJECT_TAG)
	, mColliderSphere(nullptr)
{
	D3DXQuaternionIdentity(&mRot);
}

Base3DObject::~Base3DObject()
{
	SAFE_DELETE(mColliderSphere);
	
	for (auto& element : mColliderCubeMap)
	{
		SAFE_DELETE(element.second);
	}

	mColliderCubeMap.clear();
}

void Base3DObject::Update()
{
	for (auto element : mColliderCubeMap)
	{
		element.second->Update(mPos);
	}
}

void Base3DObject::Setup()
{
	SetObjectTag();

	ColliderCube* colliderCube = new ColliderCube;
	ColliderSphere* colliderSphere = new ColliderSphere;
	
	mColliderCubeMap.insert(make_pair("BasicCube", colliderCube));
}

void Base3DObject::SetObjectTag()
{
	string objectName = this->GetObjectName();

	if (objectName == "player")
	{
		mObjectTag = eObjTag::PLAYER_CHARACTER;
	}
	else if (objectName == "key")
	{
		mObjectTag = eObjTag::STATIC_OBJECT;
	}
	else if (objectName == "door")
	{
		mObjectTag = eObjTag::STATIC_OBJECT;
	}
	else if (objectName == "desk")
	{
		mObjectTag = eObjTag::STATIC_OBJECT;
	}
}

void Base3DObject::AddColliderCube()
{
	ColliderCube* colliderCube = new ColliderCube;
	mColliderCubeMap.insert(make_pair("BasicCube" + to_string(mColliderCubeMap.size()), colliderCube));
}

void Base3DObject::DeleteColliderCube(string key)
{
	mColliderCubeMap.erase(mColliderCubeMap.find(key));
}

void Base3DObject::SetPos(const D3DXVECTOR3& pos)
{
	mPos = pos;
}

D3DXVECTOR3 Base3DObject::GetPos()
{
	return mPos;
}

void Base3DObject::SetScale(const D3DXVECTOR3& scale)
{
	mScale = scale;
}

D3DXVECTOR3 Base3DObject::GetScale()
{
	return mScale;
}
