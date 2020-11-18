#include "stdafx.h"
#include "Base3DObject.h"
#include "ColliderSphere.h"
#include "ColliderCube.h"
#include "CollideHandle.h"

Base3DObject::Base3DObject()
	: mScale(0,0,0)
	, mPos(0,0,0)
	, mObjectTag(eObjTag::NON_OBJECT_TAG)
	, mColliderSphere(nullptr)
{
	D3DXQuaternionIdentity(&mRot);
	CollideHandle = DefaultColliderHandler;
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

void Base3DObject::Render()
{
	D3DXMATRIXA16 matWorld, matS, matR, matT;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, Base3DObject::mScale.x, Base3DObject::mScale.y, Base3DObject::mScale.z);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Base3DObject::mPos.x, Base3DObject::mPos.y, Base3DObject::mPos.z);
	matWorld = matS * matR * matT;

	gD3Device->SetTransform(D3DTS_WORLD, &matWorld);
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
