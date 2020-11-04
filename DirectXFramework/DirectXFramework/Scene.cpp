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
		D3DCOLOR_XRGB(200, 200, 200),
		1.0F, 0);
	gD3Device->BeginScene();
	
	for (auto gameObject : mGameObjects)
	{
		gameObject.second->Render();
	}
	for (auto gameUI : mGameUIs)
	{
		gameUI.second->Render();
	}

	gD3Device->EndScene();
	gD3Device->Present(NULL, NULL, NULL, NULL);
}
