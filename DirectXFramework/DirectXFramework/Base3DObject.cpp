#include "stdafx.h"
#include "Base3DObject.h"
#include "ColliderBox.h"

Base3DObject::Base3DObject()
	: mScale(0,0,0)
	, mPos(0,0,0)
	, mColliderBox(nullptr)
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

	mColliderBox = new ColliderBox;
	mColliderBox->Setup(mObjectTag);
}

void Base3DObject::SetObjectTag()
{
	string objectName = this->GetObjectName();

	if(objectName == "player")
	{
		mObjectTag = eObjTag::PLAYER_CHARACTER;
	}
	else if(objectName == "key")
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
