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
		UIImage * uiImage = new UIImage("Resources/UI/Title.png");
		uiImage->SetObjectName("Title");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5f,
			uiImage->GetPos().y, 0.0f));
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("Title", uiImage));

		uiImage = new UIImage("Resources/UI/NewGame.png");
		uiImage->SetObjectName("BtnStart");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5f,
			uiImage->GetPos().y + viewPort.Height * 0.4f + uiImage->GetHeight() * 0.5, 0.0f));
		uiImage->EventProcess = BtnStartEventListen;
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, uiImage);
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("btnStart", uiImage));

		uiImage = new UIImage("Resources/UI/Quit.png");
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

		D3DVIEWPORT9 viewPort;
		gD3Device->GetViewport(&viewPort);
		UIImage * uiImage = new UIImage("Resources/UI/Inventory.png");
		uiImage->SetObjectName("inventory");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x ,
			uiImage->GetPos().y, 0.0f));
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("inventory", uiImage));

		uiImage = new UIImage("Resources/UI/Inventory.png");
		uiImage->SetObjectName("inventory2");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x+ uiImage->GetWidth(),
			uiImage->GetPos().y, 0.0f));
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("inventory2", uiImage));

		uiImage = new UIImage("Resources/UI/Inventory.png");
		uiImage->SetObjectName("inventory3");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + uiImage->GetWidth()*2.f,
			uiImage->GetPos().y, 0.0f));
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("inventory3", uiImage));

		Player* player = new Player;
		player->AddColliderCube("playerCubeCollider");
		player->Setup();
		player->SetObjectName("player");
		newScene->mCamera->SetTarget(player->GetPosRef());
		newScene->AddEventSubscriberList(eEventName::KEY_DOWN, 9, player);
		newScene->AddEventSubscriberList(eEventName::KEY_UP, 9, player);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, player);
		room->SetPlayer(player);


		Static3DObject* key = new Static3DObject;
		key->SetObjectName("key");
		key->AddColliderCube("basicColliderCube");
		key->Setup("Resources/XFile/", "DeathDropBox.X");
		key->SetScale(D3DXVECTOR3(0.03f, 0.03f, 0.03f));
		key->SetPos(D3DXVECTOR3(16,0,10));
		key->SetRot(D3DXQUATERNION(0, 0.7f, 0, 1));
		key->SetIsInteractable(true);
		key->CollideHandle = KeyColliderHandler;
		room->InsertObject(key);

		Portal * portal1 = new Portal(D3DXVECTOR3(1, 0, 0));
		portal1->SetObjectName("portal1");
		portal1->AddColliderCube("portal1ColliderCube");
		portal1->CollideHandle = bind(&Portal::PortalColliderHandler, portal1, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
		portal1->SetPos(D3DXVECTOR3(18.5f, 0 ,4));
		portal1->SetExitPos(D3DXVECTOR3(18, 0,14));
		portal1->Setup();
		room->InsertObject(portal1);

		Portal * portal2 = new Portal(D3DXVECTOR3(1,0,0));
		portal2->SetObjectName("portal2");
		portal2->AddColliderCube("portal2ColliderCube");
		portal2->CollideHandle = bind(&Portal::PortalColliderHandler, portal2, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
		portal2->SetPos(D3DXVECTOR3(18.5f, 0, 14));
		portal2->SetExitPos(D3DXVECTOR3(18, 0, 4));
		portal2->Setup();
		room->InsertObject(portal2);


		Static3DObject* wallPart = new Static3DObject;
		wallPart->SetObjectName("wallPart1");
		wallPart->AddColliderCube("wallPart");
		wallPart->Setup("Resources/XFile/", "Wall_x4.X");
		wallPart->SetPos(D3DXVECTOR3(9.f, 2.f, 0.5f));
		wallPart->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallPart);

		Static3DObject* wallPart2 = new Static3DObject;
		wallPart2->SetObjectName("wallPart2");
		wallPart2->AddColliderCube("wallPart");
		wallPart2->Setup("Resources/XFile/", "Wall_x4.X");
		wallPart2->SetPos(D3DXVECTOR3(9.f, 2.f, 17.5f));
		wallPart2->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallPart2);

		Static3DObject* wallJoint = new Static3DObject;
		wallJoint->SetObjectName("wallJoint");
		wallJoint->Setup("Resources/XFile/", "Wall_x05.X");
		wallJoint->SetPos(D3DXVECTOR3(0.5f, 2.f, 0.5f));
		room->InsertObject(wallJoint);

		D3DXQUATERNION rotation;
		D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0, 1, 0), D3DX_PI * 0.5);
		
		Static3DObject* wallPart3 = new Static3DObject;
		wallPart3->SetObjectName("wallPart3");
		wallPart3->AddColliderCube("wallPart");
		wallPart3->Setup("Resources/XFile/", "Wall_x2.X");
		wallPart3->SetRot(rotation);
		wallPart3->SetPos(D3DXVECTOR3(17.5f, 2.f, 9.f));
		wallPart3->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallPart3);

		Static3DObject* wallPart4 = new Static3DObject;
		wallPart4->SetObjectName("wallPart4");
		wallPart4->AddColliderCube("wallPart");
		wallPart4->Setup("Resources/XFile/", "Wall_x4.X");
		wallPart4->SetRot(rotation);
		wallPart4->SetPos(D3DXVECTOR3(0.5f, 2.f, 9.f));
		wallPart4->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallPart4);
		
		Static3DObject* wallDoor1 = new Static3DObject;
		wallDoor1->SetObjectName("wallDoor1");
		wallDoor1->AddColliderCube("wallDoor");
		wallDoor1->Setup("Resources/XFile/", "Wall_Door.X");
		wallDoor1->SetRot(rotation);
		wallDoor1->SetPos(D3DXVECTOR3(17.5f, 2.f, 3.f));
		wallDoor1->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallDoor1);
		
		D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0, 1, 0), D3DX_PI * 1.5);
		Static3DObject* wallDoor2 = new Static3DObject;
		wallDoor2->SetObjectName("wallDoor2");
		wallDoor2->AddColliderCube("wallDoor");
		wallDoor2->Setup("Resources/XFile/", "Wall_Door.X");
		wallDoor2->SetRot(rotation);
		wallDoor2->SetPos(D3DXVECTOR3(17.5f, 2.f, 15.f));
		wallDoor2->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallDoor2);

		gShader->LoadAllShader();
	}
	return newScene;
}
