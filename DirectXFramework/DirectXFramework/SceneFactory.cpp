#include "stdafx.h"
#include "SceneFactory.h"
#include "SceneCenter.h"
#include "Scene.h"
#include "QuarterMap.h"
#include "Player.h"
#include "Static3DObject.h"
#include "Room.h"
#include "CollideHandle.h"

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
		key->CollideHandle = KeyColliderHandler;
		room->InsertObject(key);

		
		Static3DObject* wallPart = new Static3DObject;
		wallPart->SetObjectName("wallPart1");
		wallPart->AddColliderCube("wallPart1");
		wallPart->Setup("Resources/XFile/", "Wall_x4.X");
		wallPart->SetPos(D3DXVECTOR3(9.f, 2.f, 0.5f));
		wallPart->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallPart);

		Static3DObject* wallPart2 = new Static3DObject;
		wallPart2->SetObjectName("wallPart2");
		wallPart2->AddColliderCube("wallPart2");
		wallPart2->Setup("Resources/XFile/", "Wall_x4.X");
		wallPart2->SetPos(D3DXVECTOR3(9.f, 2.f, 17.5f));
		wallPart2->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallPart2);


		Static3DObject* wallJoint = new Static3DObject;
		wallJoint->SetObjectName("wallJoint");
		wallJoint->Setup("Resources/XFile/", "Wall_x05.X");
		wallJoint->SetPos(D3DXVECTOR3(0.5f, 2.f, 0.5f));
		room->InsertObject(wallJoint);

		
		
		D3DXQUATERNION temp;
		D3DXQuaternionRotationAxis(&temp, &D3DXVECTOR3(0, 1, 0), D3DX_PI * 0.5);
		
		Static3DObject* wallPart3 = new Static3DObject;
		wallPart3->SetObjectName("wallPart3");
		wallPart3->AddColliderCube("wallPart3");
		wallPart3->Setup("Resources/XFile/", "Wall_x2.X");
		wallPart3->SetRotation(temp);
		wallPart3->SetPos(D3DXVECTOR3(17.5f, 2.f, 9.f));
		wallPart3->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallPart3);

		

		Static3DObject* wallPart4 = new Static3DObject;
		wallPart4->SetObjectName("wallPart4");
		wallPart4->AddColliderCube("wallPart4");
		wallPart4->Setup("Resources/XFile/", "Wall_x4.X");
		wallPart4->SetRotation(temp);
		wallPart4->SetPos(D3DXVECTOR3(0.5f, 2.f, 9.f));
		wallPart4->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallPart4);

		
		
		
		Static3DObject* wallDoor1 = new Static3DObject;
		wallDoor1->SetObjectName("wallDoor1");
		wallDoor1->AddColliderCube("wallDoor1");
		wallDoor1->Setup("Resources/XFile/", "Wall_Door.X");
		wallDoor1->SetRotation(temp);
		wallDoor1->SetPos(D3DXVECTOR3(17.5f, 2.f, 3.f));
		wallDoor1->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallDoor1);
		
		D3DXQuaternionRotationAxis(&temp, &D3DXVECTOR3(0, 1, 0), D3DX_PI * 1.5);
		Static3DObject* wallDoor2 = new Static3DObject;
		wallDoor2->SetObjectName("wallDoor2");
		wallDoor2->AddColliderCube("wallDoor2");
		wallDoor2->Setup("Resources/XFile/", "Wall_Door.X");
		wallDoor2->SetRotation(temp);
		wallDoor2->SetPos(D3DXVECTOR3(17.5f, 2.f, 15.f));
		wallDoor2->CollideHandle = KeyColliderHandler;
		room->InsertObject(wallDoor2);

		
		gShader->LoadAllShader();
	}
	return newScene;
}
