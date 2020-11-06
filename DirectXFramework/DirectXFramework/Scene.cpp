#include "stdafx.h"
#include "Scene.h"
#include "BaseObject.h"
#include "UIImage.h"
#include "UIEventListener.h"
#include "QuarterMap.h"


Scene::Scene()
{
	static D3DXVECTOR3 tempTarget = D3DXVECTOR3(0, 1, 0);
	mCamera = new Camera;
	mCamera->Setup(&tempTarget);

}

Scene::~Scene()
{
	gEventManager->ClearSubscriber();
	for (auto gameObject : mGameObjects)
	{
		SafeDelete(gameObject.second);
	}
	for (auto gameUI : mGameUIs)
	{
		SafeDelete(gameUI.second);
	}
	SafeDelete(mCamera);
}

void Scene::AddEventSubscriberList(eEventName eventName, UINT priority, BaseObserver* baseObserver)
{
	mEventSubscriberList[eventName].insert(make_pair(priority, baseObserver));
}

void Scene::AttachAllSubscriberInSubscriberList()
{
	for (auto subscriberList : mEventSubscriberList)
	{
		for each (auto subscriber in subscriberList.second)
		{
			gEventManager->AttachSubscriber(subscriberList.first, subscriber.first, subscriber.second);
		}
	}
}

void Scene::DetachAllSubscriberInSubscriberList()
{
	for (auto subscriberList : mEventSubscriberList)
	{
		for each (auto subscriber in subscriberList.second)
		{
			gEventManager->DetachSubscriber(subscriberList.first, subscriber.second);
		}
	}
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

	gSoundManager->Update();}

void Scene::Render()
{
	gD3Device->Clear(0, nullptr,
	                 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	                 D3DCOLOR_XRGB(255, 255, 255),
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
	gD3Device->Present(nullptr, nullptr, nullptr, nullptr);
}
