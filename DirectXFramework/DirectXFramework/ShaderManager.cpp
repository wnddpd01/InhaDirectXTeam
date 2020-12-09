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

void ShaderManager::RenderWithOutLineShader(function<void()> FunctionPtr)
{
	//D3DXVECTOR4	gWorldLightPosition = D3DXVECTOR4(500.0f, 500.0f, -500.0f, 1.0f);
	//D3DXVECTOR4	gSurfaceColor = D3DXVECTOR4(0, 1, 0, 1);
	D3DXMATRIXA16 matView, matInvWorld, matProjection, matWorld, matWVP, matViewInvTrans, matWorldViewInverse;

	gD3Device->GetTransform(D3DTS_VIEW, &matView);
	gD3Device->GetTransform(D3DTS_PROJECTION, &matProjection);
	gD3Device->GetTransform(D3DTS_WORLD, &matWorld);
	D3DXMatrixInverse(&matInvWorld, nullptr, &matWorld);
	matWVP = matWorld * matView * matProjection;

	//D3DXMatrixInverse(&matViewInvTrans, NULL, &matView);
	//D3DXMatrixTranspose(&matViewInvTrans, &matViewInvTrans);
	//D3DXMatrixInverse(&matWorldViewInverse, NULL, &(matWorld * matView));

	mShaders["OutLine"]->SetMatrix("gWorldViewProj", &matWVP);
	mShaders["OutLine"]->SetFloat("gOutlineWidth", 0.1f);
	mShaders["OutLine"]->SetTexture("DiffuseMap_Tex", mTexA1);
	/*
	mShaders["OutLine"]->SetMatrix("matViewInverseTranspose", &matViewInvTrans);
	mShaders["OutLine"]->SetMatrix("matProjection", &matProjection);
	mShaders["OutLine"]->SetMatrix("matWorldInverse", &matInvWorld);
	mShaders["OutLine"]->SetMatrix("matWorldViewInverse", &matWorldViewInverse);
	mShaders["OutLine"]->SetVector("OutlineColor", &D3DXVECTOR4(1.f,0.f, 0.f, 0.f));
	mShaders["OutLine"]->SetFloat("OutlineWidth", 1.f);
	*/

	UINT numPasses = 0;

	if (FAILED(mShaders["OutLine"]->Begin(&numPasses, NULL)))
		MessageBoxA(GetActiveWindow(), "OutLine shader Begin 실패", "에러", MB_ICONERROR);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			if (FAILED(mShaders["OutLine"]->BeginPass(i)))
				MessageBoxA(GetActiveWindow(), "OutLine shader Begin pass 실패", "에러", MB_ICONERROR);
			{
				FunctionPtr();
			}
			if (FAILED(mShaders["OutLine"]->EndPass()))
				MessageBoxA(GetActiveWindow(), "OutLine shader End pass 실패", "에러", MB_ICONERROR);
		}
	}
	if (FAILED(mShaders["OutLine"]->End()))
		MessageBoxA(GetActiveWindow(), "OutLine shader End 실패", "에러", MB_ICONERROR);
}

void ShaderManager::RenderWithPointLightShader(function<void()> FunctionPtr)
{
	struct PointLight
	{
		D3DXVECTOR3	color;
		D3DXVECTOR3	position;
		float	range;
	};
	
	PointLight PointLight = {
		{ 1.f, 1.f, 1.f},
		{ 5.f, 5.f, 5.f },
		1000.f };
	
	D3DXMATRIXA16 matView, matProjection, matWorld, matWVP, matWorldInvTrans;
	D3DXVECTOR4 vec4CameraPos = { 0.f, 10.f, -15.f, 0.f };
	D3DXVECTOR4 vec4ObejctColor = { 0.f, 0.8f, 0.f, 1.f };
	D3DXVECTOR4 vec4AmbientLightColor = { 0.8f, 0.f, 0.f, 0.3f };
	
	gD3Device->GetTransform(D3DTS_VIEW, &matView);
	gD3Device->GetTransform(D3DTS_PROJECTION, &matProjection);
	gD3Device->GetTransform(D3DTS_WORLD, &matWorld);
	matWVP = matWorld * matView * matProjection;
	D3DXMatrixInverse(&matWorldInvTrans, NULL, &matWorld);
	D3DXMatrixTranspose(&matWorldInvTrans, &matWorldInvTrans);

	mShaders["PointLight"]->SetMatrix("worldViewProj", &matWVP);
	mShaders["PointLight"]->SetMatrix("world", &matWorld);
	mShaders["PointLight"]->SetMatrix("view", &matView);
	mShaders["PointLight"]->SetMatrix("worldInverseTranspose", &matWorldInvTrans);
	
	mShaders["PointLight"]->SetVector("cameraPosition", &vec4CameraPos);
	mShaders["PointLight"]->SetVector("objectColor", &vec4ObejctColor);
	mShaders["PointLight"]->SetVector("ambientLightColor", &vec4AmbientLightColor);
	mShaders["PointLight"]->SetValue("myPointLight", &PointLight, sizeof(PointLight));

	UINT numPasses = 0;

	if (FAILED(mShaders["PointLight"]->Begin(&numPasses, NULL)))
		MessageBoxA(GetActiveWindow(), "PointLight shader Begin 실패", "에러", MB_ICONERROR);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			if (FAILED(mShaders["PointLight"]->BeginPass(i)))
				MessageBoxA(GetActiveWindow(), "PointLight shader Begin pass 실패", "에러", MB_ICONERROR);
			{
				FunctionPtr();
			}
			if (FAILED(mShaders["PointLight"]->EndPass()))
				MessageBoxA(GetActiveWindow(), "PointLight shader End pass 실패", "에러", MB_ICONERROR);
		}
	}
	if (FAILED(mShaders["PointLight"]->End()))
		MessageBoxA(GetActiveWindow(), "PointLight shader End 실패", "에러", MB_ICONERROR);
	
}

void ShaderManager::RenderWithSpotLightShader(function<void()> FunctionPtr)
{
	float multiflier = 5.f;
	
	struct SpotLight
	{
		D3DXVECTOR3	color = { 1.f,1.f,1.f };
		D3DXVECTOR3	position;
		float		range = 5.f;
		D3DXVECTOR3	direction = {0,-1.f,0};
		float		innerConeAngle = D3DX_PI / 32.f;
		float		outerConeAngle = D3DX_PI / 32.f;
	};

	SpotLight mySpotLight;
	mySpotLight.color = { multiflier, multiflier,multiflier };
	mySpotLight.position = { 5.f, 5.f, 1.4f };

	D3DXMATRIXA16 matView, matProjection, matWorld, matWVP, matWorldInvTrans;
	D3DXVECTOR4 vec4ObejctColor = { 0.f, 0.8f, 0.f, 1.f };
	D3DXVECTOR4 vec4AmbientLightColor = { 0.8f, 0.f, 0.f, 0.3f };

	gD3Device->GetTransform(D3DTS_VIEW, &matView);
	gD3Device->GetTransform(D3DTS_PROJECTION, &matProjection);
	gD3Device->GetTransform(D3DTS_WORLD, &matWorld);
	matWVP = matWorld * matView * matProjection;
	D3DXMatrixInverse(&matWorldInvTrans, NULL, &matWorld);
	D3DXMatrixTranspose(&matWorldInvTrans, &matWorldInvTrans);

	mShaders["SpotLight"]->SetMatrix("WorldViewProj", &matWVP);
	mShaders["SpotLight"]->SetMatrix("World", &matWorld);
	mShaders["SpotLight"]->SetMatrix("View", &matView);
	mShaders["SpotLight"]->SetMatrix("WorldInverseTranspose", &matWorldInvTrans);

	mShaders["SpotLight"]->SetVector("ObjectColor", &vec4ObejctColor);
	mShaders["SpotLight"]->SetVector("AmbientLightColor", &vec4AmbientLightColor);
	mShaders["SpotLight"]->SetValue("mySpotLight", &mySpotLight, sizeof(SpotLight));
	
	
	UINT numPasses = 0;

	if (FAILED(mShaders["SpotLight"]->Begin(&numPasses, NULL)))
		MessageBoxA(GetActiveWindow(), "SpotLight shader Begin 실패", "에러", MB_ICONERROR);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			if (FAILED(mShaders["SpotLight"]->BeginPass(i)))
				MessageBoxA(GetActiveWindow(), "SpotLight shader Begin pass 실패", "에러", MB_ICONERROR);
			{
				FunctionPtr();
			}
			if (FAILED(mShaders["SpotLight"]->EndPass()))
				MessageBoxA(GetActiveWindow(), "SpotLight shader End pass 실패", "에러", MB_ICONERROR);
		}
	}
	if (FAILED(mShaders["SpotLight"]->End()))
		MessageBoxA(GetActiveWindow(), "SpotLight shader End 실패", "에러", MB_ICONERROR);
	
}

void ShaderManager::RenderWithItemShader(function<void()> FunctionPtr)
{
	
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


LPD3DXEFFECT ShaderManager::LoadShader(const char* filename)
{
	LPD3DXEFFECT ret = NULL;
	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif
	dwShaderFlags |= D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY;

	HRESULT hr;
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
	mShaders["Toon"]		= LoadShader("Resources/Shader/ToonShader.fx");
	mShaders["OutLine"]		= LoadShader("Resources/Shader/outLine.fx");
	mShaders["SpotLight"]	= LoadShader("Resources/Shader/SpotLight.fx");
	mShaders["PointLight"]	= LoadShader("Resources/Shader/PointLight.fx");
	//mShaders["Item"]		= LoadShader("Resources/Shader/ItemShader.fx");
	//mShaders["Fire"]		= LoadShader("Resources/Shader/Fire.fx");


}

