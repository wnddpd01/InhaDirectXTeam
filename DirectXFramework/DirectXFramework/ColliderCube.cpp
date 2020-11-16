#include "stdafx.h"
#include "ColliderCube.h"


ColliderCube::ColliderCube()
	: mCubeWidth(1.0f)
	, mCubeHeight(1.0f)
	, mCubeDepth(1.0f)
{
}


ColliderCube::~ColliderCube()
{
}

void ColliderCube::Setup()
{
	D3DXCreateBox(gD3Device, mCubeWidth, mCubeHeight, mCubeDepth, &mMesh, NULL);
}


void ColliderCube::SetCubeCollider(float height, float width, float depth)
{
	mCubeWidth = width;
	mCubeHeight = height;
	mCubeDepth = depth;

	SAFE_RELEASE(mMesh);
	D3DXCreateBox(gD3Device, mCubeWidth, mCubeHeight, mCubeDepth, &mMesh, NULL);
}
