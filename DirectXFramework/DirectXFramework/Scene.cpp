#include "stdafx.h"
#include "Scene.h"
#include "BaseObject.h"
#include "OBB.h"
#include "PlayerCharacter.h"
#include "UIImage.h"
#include "UIEventListener.h"
#include "QuarterMap.h"
#include "StaticObject.h"


Scene::Scene()
{
	static D3DXVECTOR3 tempTarget = D3DXVECTOR3(5, 1, -5);
	mCamera = new Camera;
	mCamera->Setup(&tempTarget);
	
	AddEventSubscriberList(eEventName::MOUSE_L_DRAG, 10, mCamera);
	AddEventSubscriberList(eEventName::MOUSE_WHEEL_SCROLL, 10, mCamera);
}

Scene::~Scene()
{
	for (auto gameObject : mGameObjects)
	{
		SAFE_DELETE(gameObject.second);
	}
	for (auto gameUI : mGameUIs)
	{
		SAFE_DELETE(gameUI.second);
	}
	SAFE_DELETE(mCamera);
}

void Scene::AddEventSubscriberList(eEventName eventName, UINT priority, BaseObserver* baseObserver)
{
	mEventSubscriberList[eventName].insert(make_pair(priority, baseObserver));
}

void Scene::AttachAllSubscriberInSubscriberList()
{
	for (auto subscriberList : mEventSubscriberList)
	{
		for(pair<const unsigned, BaseObserver*>& subscriber : subscriberList.second)
		{
			gEventManager->AttachSubscriber(subscriberList.first, subscriber.first, subscriber.second);
		}
	}
}

void Scene::DetachAllSubscriberInSubscriberList()
{
	for (auto subscriberList : mEventSubscriberList)
	{
		for(pair<const unsigned, BaseObserver*>& subscriber : subscriberList.second)
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

	//임시 충돌체크
	for (auto gameObject : mGameObjects)
	{
		if(gameObject.first == "player")
		{
			for (auto checkObject : mGameObjects)
			{
				if ((checkObject.first == "Desk") || (checkObject.first == "Door"))
				{
					if (OBB::IsCollision(
						((PlayerCharacter*)gameObject.second)->GetOBB(),
						((StaticObject*)checkObject.second)->GetOBB()))
					{
						cout << "충돌" << endl;
					}
					else
					{
						
					}
				}
			}
		}
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
	                 D3DCOLOR_XRGB(150, 150, 150),
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
