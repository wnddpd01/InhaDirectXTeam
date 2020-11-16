#include "stdafx.h"
#include "Base3DObject.h"
#include "ColliderPolygon.h"

Base3DObject::Base3DObject()
	: mScale(0,0,0)
	, mPos(0,0,0)
	, mColliderPolygon(nullptr)
	, mObjectTag(eObjTag::NON_OBJECT_TAG)
{
	D3DXQuaternionIdentity(&mRot);
}


Base3DObject::~Base3DObject()
{
}

void Base3DObject::Setup()
{
	SetObjectTag();

	mColliderPolygon = new ColliderPolygon;
	mColliderPolygon->Setup(mObjectTag);
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
