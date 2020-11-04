#include "stdafx.h"
#include "Scene.h"
#include "BaseObject.h"

Scene::Scene(eSceneName SceneName)
{
	SetSceneName(SceneName);
	static D3DXVECTOR3 tempTarget = D3DXVECTOR3(0, 0, 0);
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
		D3DCOLOR_XRGB(60, 60, 60),
		1.0F, 0);
	gD3Device->BeginScene();

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
}
