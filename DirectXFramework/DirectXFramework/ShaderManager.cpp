#include "stdafx.h"
#include "ShaderManager.h"


void ShaderManager::RenderWithToonShader(function<void()> FunctionPtr)
{
	D3DXVECTOR4	gWorldLightPosition = D3DXVECTOR4(500.0f, 500.0f, -500.0f, 1.0f);
	D3DXVECTOR4	gSurfaceColor = D3DXVECTOR4(0, 1, 0, 1);
	D3DXMATRIXA16 matView, matInvWorld, matProjection, matWorld, matWVP;

	gD3Device->GetTransform(D3DTS_VIEW, &matView);
	gD3Device->GetTransform(D3DTS_PROJECTION, &matProjection);
	gD3Device->GetTransform(D3DTS_WORLD, &matWorld);
	D3DXMatrixInverse(&matInvWorld, nullptr, &matWorld);
	matWVP = matWorld * matView * matProjection;

	mShaders["Toon"]->SetMatrix("gWorldViewProjectionMatrix", &matWVP);
	mShaders["Toon"]->SetMatrix("gInvWorldMatrix", &matInvWorld);
	mShaders["Toon"]->SetVector("gWorldLightPosition", &gWorldLightPosition);
	mShaders["Toon"]->SetVector("gSurfaceColor", &gSurfaceColor);

	UINT numPasses = 0;
	mShaders["Toon"]->Begin(&numPasses, NULL);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			mShaders["Toon"]->BeginPass(i);
			{
				FunctionPtr();
			}
			mShaders["Toon"]->EndPass();
		}
	}
	mShaders["Toon"]->End();
}

void ShaderManager::RenderWithOutLineShader(function<void()> FunctionPtr)
{
	D3DXVECTOR4	gWorldLightPosition = D3DXVECTOR4(500.0f, 500.0f, -500.0f, 1.0f);
	D3DXVECTOR4	gSurfaceColor = D3DXVECTOR4(0, 1, 0, 1);
	D3DXMATRIXA16 matView, matInvWorld, matProjection, matWorld, matWVP, matViewInvTrans, matWorldViewInverse;

	gD3Device->GetTransform(D3DTS_VIEW, &matView);
	gD3Device->GetTransform(D3DTS_PROJECTION, &matProjection);
	gD3Device->GetTransform(D3DTS_WORLD, &matWorld);
	D3DXMatrixInverse(&matInvWorld, nullptr, &matWorld);
	matWVP = matWorld * matView * matProjection;

	D3DXMatrixInverse(&matViewInvTrans, NULL, &matView);
	D3DXMatrixTranspose(&matViewInvTrans, &matViewInvTrans);

	D3DXMatrixInverse(&matWorldViewInverse, NULL, &(matWorld * matView));

	mShaders["OutLine"]->SetMatrix("matViewProjection", &matWVP);
	mShaders["OutLine"]->SetMatrix("matViewInverseTranspose", &matViewInvTrans);
	mShaders["OutLine"]->SetMatrix("matProjection", &matProjection);
	mShaders["OutLine"]->SetMatrix("matWorldInverse", &matInvWorld);
	mShaders["OutLine"]->SetMatrix("matWorldViewInverse", &matWorldViewInverse);
	mShaders["OutLine"]->SetVector("OutlineColor", &D3DXVECTOR4(1.f,0.f, 0.f, 0.f));
	mShaders["OutLine"]->SetFloat("OutlineWidth", 1.f);
	
	UINT numPasses = 0;
	mShaders["OutLine"]->Begin(&numPasses, NULL);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			mShaders["OutLine"]->BeginPass(i);
			{
				FunctionPtr();
			}
			mShaders["OutLine"]->EndPass();
		}
	}
	mShaders["OutLine"]->End();
}


LPD3DXEFFECT ShaderManager::LoadShader(const char* filename)
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

void ShaderManager::LoadAllShader()
{
	mShaders["Toon"] = LoadShader("Resources/Shader/ToonShader.fx");
	mShaders["OutLine"] = LoadShader("Resources/Shader/outLine.fx");
}

