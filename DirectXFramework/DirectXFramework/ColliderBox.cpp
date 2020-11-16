#include "stdafx.h"
#include "ColliderBox.h"

ColliderBox::ColliderBox()
	: mMesh(nullptr)
	, mCubeWidth(1.0f)
	, mCubeHeight(1.0f)
	, mCubeDepth(1.0f)
	, mRadius(1.0f)
	, mColliderTag(eColliderTag::NON_COLLIDER)
{

}

ColliderBox::~ColliderBox()
{
	SAFE_DELETE(mMesh);
}

void ColliderBox::Setup(eObjTag objTag)
{
	if(objTag == eObjTag::PLAYER_CHARACTER || objTag == eObjTag::STATIC_OBJECT || objTag == eObjTag::MOVE_OBJECT)
	{
		mColliderTag = eColliderTag::CUBE;
	}
	
	if(mColliderTag == eColliderTag::CUBE)
	{
		D3DXCreateBox(gD3Device, mCubeWidth, mCubeHeight, mCubeDepth, &mMesh, NULL);
	}

	if(mColliderTag == eColliderTag::SPHERE)
	{
		D3DXCreateSphere(gD3Device, mRadius, 10, 10, &mMesh, NULL);
	}
}

void ColliderBox::Update()
{
	D3DXCreateSphere(gD3Device, radius, 10, 10, &mMesh, NULL);

	D3DXCreateBox(gD3Device, width, height, depth, &mMesh, NULL);
}

void ColliderBox::SetSphereCollider(float radius)
{
	mRadius = mRadius;
	
}

void ColliderBox::SetCubeCollider(float width, float height, float depth)
{
	mCubeWidth = width;
	mCubeHeight = height;
	mCubeDepth = depth;
}