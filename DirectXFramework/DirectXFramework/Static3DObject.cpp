#include "stdafx.h"
#include "Static3DObject.h"
#include "ModelLoader.h"

Static3DObject::Static3DObject()
{
}


Static3DObject::~Static3DObject()
{
}

void Static3DObject::Setup(
	string folder, string fileName)
{
	ModelLoader loader;
	loader.LoadXfile(folder, fileName, mpMesh, &mpMaterials, &mpTextures, mNumMaterials);
}

void Static3DObject::Update()
{
	
}

void Static3DObject::Render()
{

	D3DXMATRIXA16 matWorld, matS, matR, matT;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	matWorld = matS * matR * matT;

	gD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	for (DWORD i = 0; i < mNumMaterials; ++i)
	{
		gD3Device->SetMaterial(&mpMaterials[i]);
		gD3Device->SetTexture(0, mpTextures[i]);
		mpMesh->DrawSubset(i);
	}


	
}
