#include "stdafx.h"
#include "StaticObject.h"
#include "cMtlTex.h"
#include "cObjLoader.h"
#include "OBB.h"


OBB* StaticObject::GetOBB()
{
	return mCollider;
}

StaticObject::StaticObject()
	: mCollider(NULL)
{
	
}


StaticObject::~StaticObject()
{
}

void StaticObject::Setup(char* szOBj, char* szTex, D3DXVECTOR3 pos)
{
	D3DXMatrixIdentity(&mMatPos);
	D3DXMatrixIdentity(&mMatRot);
	D3DXMatrixIdentity(&mMatScale);

	D3DXMatrixTranslation(&mMatPos, pos.x, pos.y, pos.z);
	string sTex = string(szTex);

	mTextrue = gTextureManager->GetTexture(sTex);
	
	ZeroMemory(&mMaterial, sizeof(D3DMATERIAL9));
	mMaterial.Ambient = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.f);
	mMaterial.Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.f);
	mMaterial.Specular = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.f);

	mCollider = new OBB;
	mCollider->Setup(pos + D3DXVECTOR3(0.5,0.5,0.5), pos + D3DXVECTOR3(-0.5, -0.5, -0.5));
	
	mCollider->Update(&mMatPos);
	
	if (mMesh)
	{
		mMesh->Release();
		mMesh = NULL;
	}

	cObjLoader loader;
	mMesh = loader.LoadMesh(vecMtlTex, "obj", szOBj);
}

void StaticObject::Update()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	//matWorld = mMatScale *  mMatRot * mMatPos;
	
	if (mCollider)
		mCollider->Update(&matWorld);
}

void StaticObject::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	matWorld = matWorld * mMatScale *  mMatRot * mMatPos;
	gD3Device->SetTransform(D3DTS_WORLD, &matWorld);
	gD3Device->SetMaterial(&mMaterial);
	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	gD3Device->SetTexture(0, mTextrue);
	mMesh->DrawSubset(0);
	if (mCollider)
		mCollider->OBBBOX_Render(D3DCOLOR{ 255 });
}
