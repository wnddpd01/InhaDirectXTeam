#include "stdafx.h"
#include "Static3DObject.h"
#include "ModelLoader.h"

void render()
{
	
}

Static3DObject::Static3DObject()
{
}


Static3DObject::~Static3DObject()
{
}

void Static3DObject::Setup(
	string folder, string fileName)
{
	Base3DObject::Setup();
	ModelLoader loader;
	loader.LoadXfile(folder, fileName, mpMesh, &mpMaterials, &mpTextures, mNumMaterials);
	
	mShaderTag = eShaderTag::ITEM;
}

void Static3DObject::Update()
{
	Base3DObject::Update();
}

void Static3DObject::Render()
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

	switch (mShaderTag)
	{
		case eShaderTag::ITEM :
		{
			gShader->GetInstance()->RenderWithToonShader(bind(&Static3DObject::RenderMesh, this));
		}
		break;
		

	}
	
	

	//gShader->GetInstance()->RenderWithToonShader(bind(&Static3DObject::RenderMesh, this));
	
}

void Static3DObject::RenderMesh()
{
	for (DWORD i = 0; i < mNumMaterials; ++i)
	{
		gD3Device->SetMaterial(&mpMaterials[i]);
		gD3Device->SetTexture(0, mpTextures[i]);
		mpMesh->DrawSubset(i);
	}
}


LPD3DXEFFECT Static3DObject::LoadShader(const char* filename)
{
	LPD3DXEFFECT ret = NULL;
	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFileA(gD3Device, filename,
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

	// 쉐이더 로딩에 실패한 경우 output창에 쉐이더
	// 컴파일 에러를 출력한다.
	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();

		/*
		if (ack)
		{
		char* str = new char[size];
		sprintf(str, (const char*)ack, size);
		OutputDebugStringA(str);
		delete[] str;
		}
		*/
	}

	return ret;
}
