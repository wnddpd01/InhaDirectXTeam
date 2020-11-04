#include "stdafx.h"
#include "Scene.h"
#include "BaseObject.h"

Scene::Scene(eSceneName SceneName)
{
	SetSceneName(SceneName);
	static D3DXVECTOR3 tempTarget = D3DXVECTOR3(0, 1, 0);
	mCamera = new Camera;
	mCamera->Setup(&tempTarget);
}

Scene::~Scene()
{
	SafeDelete(mCamera);
}

void Scene::Update()
{
	mCamera->Update();
	for (auto gameObject : mGameObjects)
	{
		gameObject.second->Update();
	}

	for (auto gameUI : mGameUIs)
	{
		gameUI.second->Update();
	}
}

void Scene::Render()
{
	gD3Device->Clear(0, nullptr,
	                 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	                 D3DCOLOR_XRGB(200, 255, 255),
	                 1.0F, 0);
	gD3Device->BeginScene();

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DMATERIAL9 m_stmtl;
	ZeroMemory(&m_stmtl, sizeof(D3DMATERIAL9));
	m_stmtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stmtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stmtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stmtl.Power = 1.f;
	gD3Device->SetTransform(D3DTS_WORLD, &matWorld);
	gD3Device->SetMaterial(&m_stmtl);
	gD3Device->SetTexture(0, nullptr);
	LPD3DXMESH tepotMesh;
	D3DXCreateTeapot(gD3Device, &tepotMesh, nullptr);
	tepotMesh->DrawSubset(0);

	for (auto gameObject : mGameObjects)
	{
		gameObject.second->Render();
	}
	for (auto gameUI : mGameUIs)
	{
		gameUI.second->Render();
	}

	gD3Device->EndScene();
	gD3Device->Present(nullptr, nullptr, nullptr, nullptr);
}
