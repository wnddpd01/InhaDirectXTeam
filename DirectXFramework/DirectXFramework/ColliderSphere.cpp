#include "stdafx.h"
#include "ColliderSphere.h"


ColliderSphere::ColliderSphere()
	: mRadius(1.0f)
{
}


ColliderSphere::~ColliderSphere()
{
}

void ColliderSphere::Setup()
{
	D3DXCreateSphere(gD3Device, mRadius, 10, 10, &mMesh, NULL);
}

void ColliderSphere::SetSphereCollider(float radius)
{
	mRadius = radius;
	SAFE_RELEASE(mMesh);
	D3DXCreateSphere(gD3Device, mRadius, 10, 10, &mMesh, NULL);
}
