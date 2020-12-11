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
	//D3DLIGHT9 temp;
	//gD3Device->GetLight(0, &temp);
	//temp.Position
	D3DXMatrixInverse(&matInvWorld, nullptr, &matWorld);
	matWVP = matWorld * matView * matProjection;

	mShaders["Toon"]->SetMatrix("gWorldViewProjectionMatrix", &matWVP);
	mShaders["Toon"]->SetMatrix("gInvWorldMatrix", &matInvWorld);
	mShaders["Toon"]->SetVector("gWorldLightPosition", &gWorldLightPosition);
	mShaders["Toon"]->SetVector("gSurfaceColor", &gSurfaceColor);

	UINT numPasses = 0;

	if (FAILED(mShaders["Toon"]->Begin(&numPasses, NULL)))
		MessageBoxA(GetActiveWindow(), "Toon shader Begin 실패", "에러", MB_ICONERROR);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			if (FAILED(mShaders["Toon"]->BeginPass(i)))
				MessageBoxA(GetActiveWindow(), "Toon shader Begin pass 실패", "에러", MB_ICONERROR);
			{
				FunctionPtr();
			}
			if (FAILED(mShaders["Toon"]->EndPass()))
				MessageBoxA(GetActiveWindow(), "Toon shader End pass 실패", "에러", MB_ICONERROR);
		}
	}
	if (FAILED(mShaders["Toon"]->End()))
		MessageBoxA(GetActiveWindow(), "Toon shader End 실패", "에러", MB_ICONERROR);
}

void ShaderManager::RenderWithFireShader(function<void()> FunctionPtr)
{
	
	D3DXMATRIXA16 matView, matProjection, matWorld, matWVP;
	D3DVIEWPORT9 matViewPort;
	
	gD3Device->GetTransform(D3DTS_VIEW, &matView);
	gD3Device->GetTransform(D3DTS_PROJECTION, &matProjection);
	gD3Device->GetTransform(D3DTS_WORLD, &matWorld);
	gD3Device->GetViewport(&matViewPort);
	matWVP = matWorld * matView * matProjection;

	D3DXVECTOR4 resolution = { (float)matViewPort.Width, (float)matViewPort.Height, 0.f, 0.f };
	
	mShaders["Fire"]->SetMatrix("WorldViewProj", &matWVP);
	mShaders["Fire"]->SetVector("Res", &resolution);
	static float time = 0.f;
	mShaders["Fire"]->SetFloat("time", time);
	time += gDeltaTime*0.1;

	UINT numPasses = 0;


	if (FAILED(mShaders["Fire"]->Begin(&numPasses, NULL)))
		MessageBoxA(GetActiveWindow(), "Fire shader Begin 실패", "에러", MB_ICONERROR);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			if (FAILED(mShaders["Fire"]->BeginPass(i)))
				MessageBoxA(GetActiveWindow(), "Fire shader Begin pass 실패", "에러", MB_ICONERROR);
			{
				FunctionPtr();
			}
			if (FAILED(mShaders["Fire"]->EndPass()))
				MessageBoxA(GetActiveWindow(), "Fire shader End pass 실패", "에러", MB_ICONERROR);
		}
	}
	if (FAILED(mShaders["Fire"]->End()))
		MessageBoxA(GetActiveWindow(), "Fire shader End 실패", "에러", MB_ICONERROR);
}

void ShaderManager::RenderWithWallShader(function<void()> FunctionPtr)
{
	D3DXMATRIXA16 matView, matInvWorld, matProjection, matWorld, matViewProj, matViewInvTrans, matWorldViewInverse;

	gD3Device->GetTransform(D3DTS_VIEW, &matView);
	gD3Device->GetTransform(D3DTS_PROJECTION, &matProjection);
	gD3Device->GetTransform(D3DTS_WORLD, &matWorld);
	
	matViewProj = matView * matProjection;

	mShaders["WallShader"]->SetMatrix("gWorld", &matWorld);
	mShaders["WallShader"]->SetMatrix("gViewProj", &matViewProj);
	mShaders["WallShader"]->SetFloat("gOutlineWidth", 0.1f);
	mShaders["WallShader"]->SetTexture("DiffuseMap_Tex", mTexA1);
	mShaders["WallShader"]->SetVector("gLightPos", &D3DXVECTOR4(0,10,0,0));

	UINT numPasses = 0;
	if (FAILED(mShaders["WallShader"]->Begin(&numPasses, NULL)))
		MessageBoxA(GetActiveWindow(), "WallShader shader Begin 실패", "에러", MB_ICONERROR);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			if (FAILED(mShaders["WallShader"]->BeginPass(i)))
				MessageBoxA(GetActiveWindow(), "WallShader shader Begin pass 실패", "에러", MB_ICONERROR);
			{
				FunctionPtr();
			}
			if (FAILED(mShaders["WallShader"]->EndPass()))
				MessageBoxA(GetActiveWindow(), "WallShader shader End pass 실패", "에러", MB_ICONERROR);
		}
	}
	if (FAILED(mShaders["WallShader"]->End()))
		MessageBoxA(GetActiveWindow(), "WallShader shader End 실패", "에러", MB_ICONERROR);
}

void ShaderManager::RenderWithItemShader(function<void()> FunctionPtr)
{
	D3DXMATRIXA16 matView, matInvWorld, matProjection, matWorld, matWorldViewProj, matViewInvTrans, matWorldViewInverse;

	gD3Device->GetTransform(D3DTS_VIEW, &matView);
	gD3Device->GetTransform(D3DTS_PROJECTION, &matProjection);
	gD3Device->GetTransform(D3DTS_WORLD, &matWorld);

	matWorldViewProj = matWorld * matView * matProjection;

	mShaders["ItemShader"]->SetMatrix("gWorldViewProj", &matWorldViewProj);
	mShaders["ItemShader"]->SetFloat("gOutlineWidth", 0.1f);
	mShaders["ItemShader"]->SetTexture("DiffuseMap_Tex", mTexA1);

	UINT numPasses = 0;
	if (FAILED(mShaders["ItemShader"]->Begin(&numPasses, NULL)))
		MessageBoxA(GetActiveWindow(), "ItemShader shader Begin 실패", "에러", MB_ICONERROR);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			if (FAILED(mShaders["ItemShader"]->BeginPass(i)))
				MessageBoxA(GetActiveWindow(), "ItemShader shader Begin pass 실패", "에러", MB_ICONERROR);
			{
				FunctionPtr();
			}
			if (FAILED(mShaders["ItemShader"]->EndPass()))
				MessageBoxA(GetActiveWindow(), "ItemShader shader End pass 실패", "에러", MB_ICONERROR);
		}
	}
	if (FAILED(mShaders["ItemShader"]->End()))
		MessageBoxA(GetActiveWindow(), "ItemShader shader End 실패", "에러", MB_ICONERROR);
}

LPD3DXEFFECT ShaderManager::LoadShader(const char* filename)
{
	LPD3DXEFFECT ret = NULL;
	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif
	dwShaderFlags |= D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY;

	
	if (FAILED(D3DXCreateEffectFromFileA(gD3Device, filename,
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError)))
	{
		string error = *filename + " 파일의 로드를 실패하였습니다.";
		MessageBoxA(GetActiveWindow(), error.c_str(), "shader 로드 실패", MB_ICONERROR);
	}


	// 쉐이더 로딩에 실패한 경우 output창에 쉐이더
	// 컴파일 에러를 출력한다.
	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();

		if (ack)
		{
		char* str = new char[size];
		sprintf_s(str, size, "%s", (const char*)ack);
		OutputDebugStringA(str);
		cout << str;
		delete[] str;
		}
	}
	return ret;
}

LPDIRECT3DTEXTURE9 ShaderManager::LoadTexture(const char* filename)
{
	LPDIRECT3DTEXTURE9 ret = NULL;
	if (FAILED(D3DXCreateTextureFromFileA(gD3Device, filename, &ret)))
	{
		OutputDebugStringA("텍스처 로딩 실패: ");
		OutputDebugStringA(filename);
		OutputDebugStringA("\n");
	}
	return ret;
}

void ShaderManager::LoadAllShader()
{
	mTexA1 = LoadTexture("Resources/XFile/PolygonOffice_Texture_01_A.png");

	//mShaders["Toon"]			= LoadShader("Resources/Shader/test/ToonShader.fx");
	//mShaders["OutLine"]		= LoadShader("Resources/Shader/outLine.fx");
	//mShaders["SpotLight"]		= LoadShader("Resources/Shader/SpotLight.fx");
	//mShaders["PointLight"]	= LoadShader("Resources/Shader/PointLight.fx");
	//mShaders["Item"]			= LoadShader("Resources/Shader/ItemShader.fx");
	//mShaders["Fire"]			= LoadShader("Resources/Shader/Fire.fx");
	mShaders["ItemShader"]		= LoadShader("Resources/Shader/ItemShader.fx");
	mShaders["WallShader"]		= LoadShader("Resources/Shader/WallShader.fx");

}

