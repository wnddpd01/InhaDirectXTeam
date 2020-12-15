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
	//gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	//gD3Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//gD3Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//gD3Device->SetTexture(0, nullptr);
	//mMesh->DrawSubset(0);
	//gD3Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//gD3Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void ColliderSphere::SetSphereCollider(float radius)
{
	mRadius = radius;
}
