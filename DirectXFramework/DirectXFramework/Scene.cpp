#include "stdafx.h"
#include "Scene.h"
#include "BaseObject.h"
#include "UIImage.h"

void Scene::LoadUI()
{
	D3DVIEWPORT9 viewPort;
	gD3Device->GetViewport(&viewPort);
	if (mSceneName == eSceneName::START_SCENE)
	{
		UIImage * uiImage = new UIImage("Resources/UI/BasePanel.png");
		uiImage->SetObjectName("BasePanel");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5,
			uiImage->GetPos().y + viewPort.Height * 0.5f - uiImage->GetHeight() * 0.5
			, 0));
		mGameUIs.insert(make_pair("BasePanel", uiImage));
	}
}

void Scene::LoadObject()
{
}

Scene::Scene(eSceneName SceneName)
{
	SetSceneName(SceneName);
	static D3DXVECTOR3 tempTarget = D3DXVECTOR3(0, 1, 0);
	mCamera = new Camera;
	mCamera->Setup(&tempTarget);

	LoadUI();
	LoadObject();
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

	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	
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
