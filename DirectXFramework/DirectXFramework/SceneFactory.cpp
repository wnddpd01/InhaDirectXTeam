#include "stdafx.h"
#include "SceneFactory.h"
#include "SceneCenter.h"
#include "Scene.h"
#include "QuarterMap.h"
#include "Player.h"
#include "Static3DObject.h"
#include "Room.h"
#include "CollideHandle.h"
#include "Portal.h"

SceneFactory::SceneFactory()
{
}


SceneFactory::~SceneFactory()
{
}

Scene* SceneFactory::CreateScene(eSceneName eSceneName)
{
	Scene * newScene = new Scene;
	newScene->SetSceneName(eSceneName);
	if (eSceneName == eSceneName::START_SCENE)
	{
		D3DVIEWPORT9 viewPort;
		gD3Device->GetViewport(&viewPort);
		UIImage * uiImage = new UIImage("Resources/UI/BasePanel.png");
		uiImage->SetObjectName("BasePanel");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5f,
			uiImage->GetPos().y + viewPort.Height * 0.5f - uiImage->GetHeight() * 0.5f, 0.0f));
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("basePanel", uiImage));

		uiImage = new UIImage("Resources/UI/BtnIdle.png");
		uiImage->SetObjectName("BtnStart");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5f,
			uiImage->GetPos().y + viewPort.Height * 0.55f + uiImage->GetHeight() * 0.5, 0.0f));
		uiImage->EventProcess = BtnStartEventListen;
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, uiImage);
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("btnStart", uiImage));

		uiImage = new UIImage("Resources/UI/BtnIdle.png");
		uiImage->SetObjectName("BtnExit");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5f,
			uiImage->GetPos().y + viewPort.Height * 0.65f + uiImage->GetHeight() * 0.5f, 0.0f));
		uiImage->EventProcess = BtnExitEventListen;
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, uiImage);
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("btnExit", uiImage));

		gSoundManager->SoundSet();
	}
	else if(eSceneName == eSceneName::INGAME_SCENE)
	{
		Room * room = new Room;
		room->SetupQuarterMap("HeightMapData/", "HeightMap.raw", "StoneTiles.jpg");
		newScene->mGameObjects.insert({ "room", room });

		Player* player = new Player;
		player->AddColliderCube("playerCubeCollider");
		player->Setup();
		player->SetObjectName("player");
		newScene->mCamera->SetTarget(player->GetPosRef());
		newScene->AddEventSubscriberList(eEventName::KEY_DOWN, 9, player);
		newScene->AddEventSubscriberList(eEventName::KEY_UP, 9, player);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, player);
		room->InsertObject(player);


		Static3DObject* key = new Static3DObject;
		key->SetObjectName("key");
		key->AddColliderCube("keyCubeCollider");
		key->Setup("Resources/XFile/", "Key.X");
		key->SetPos(D3DXVECTOR3(5,0,1.4));
		key->SetScale(D3DXVECTOR3(1.f, 1.f, 1.f));
		key->CollideHandle = KeyColliderHandler;
		room->InsertObject(key);

		Portal * portal1 = new Portal;
		portal1->SetObjectName("portal1");
		portal1->AddColliderCube("portal1CubeCollider");
		portal1->CollideHandle = PortalColliderHandler;
		portal1->SetPos(D3DXVECTOR3(19, 0 ,4));
		portal1->SetExitPos(D3DXVECTOR3(17, 0,14));
		portal1->Setup();
		room->InsertObject(portal1);

		Portal * portal2 = new Portal;
		portal2->SetObjectName("portal2");
		portal2->AddColliderCube("portal2CubeCollider");
		portal2->CollideHandle = PortalColliderHandler;
		portal2->SetPos(D3DXVECTOR3(19, 0, 14));
		portal2->SetExitPos(D3DXVECTOR3(17, 0, 4));
		portal2->Setup();
		room->InsertObject(portal2);

		
		/*Static3DObject* wallPart = new Static3DObject;
		wallPart->AddColliderCube("wallCollider");
		wallPart->Setup("Resources/XFile/", "Cube.X");
		wallPart->SetPos(D3DXVECTOR3(4.5f, 2.f, 8.5f));
		wallPart->SetScale(D3DXVECTOR3(1.f, 4.f, 17.f));
		wallPart->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallPart);*/

		gShader->LoadAllShader();
	}
	return newScene;
}
