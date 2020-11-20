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

void ColliderSphere::Update()
{
	D3DXMATRIXA16 matS;
	D3DXMATRIXA16 matR;
	D3DXMATRIXA16 matT;

	D3DXMatrixScaling(&matS, (*mScale).x, (*mScale).y, (*mScale).z);
	D3DXMatrixTranslation(&matT, (*mPosition).x, (*mPosition).y, (*mPosition).z);
	D3DXMatrixRotationQuaternion(&matR, mRot);
	
}

void ColliderSphere::Render()
{
}

void ColliderSphere::SetSphereCollider(float radius)
{
	mRadius = radius;
	SAFE_RELEASE(mMesh);
	D3DXCreateSphere(gD3Device, mRadius, 10, 10, &mMesh, NULL);
}
