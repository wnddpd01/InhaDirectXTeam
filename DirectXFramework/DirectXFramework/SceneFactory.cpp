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
#include "ColliderCube.h"
#include "ColliderSphere.h"
#include "Interactable3DObject.h"
#include "Inventory.h"
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
		UIImage * uiImage = new UIImage("Resources/UI/Main/Title.png");
		uiImage->SetObjectName("Title");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5f,
			uiImage->GetPos().y, 0.0f));
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("Title", uiImage));

		uiImage = new UIImage("Resources/UI/Main/NewGame.png");
		uiImage->SetObjectName("BtnStart");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5f,
			uiImage->GetPos().y + viewPort.Height * 0.4f + uiImage->GetHeight() * 0.5, 0.0f));
		uiImage->EventProcess = BtnStartEventListen;
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, uiImage);
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("btnStart", uiImage));

		uiImage = new UIImage("Resources/UI/Main/Quit.png");
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

		Player* player = new Player;
		player->AddColliderCube("playerCubeCollider");
		player->GetColliderCube()["playerCubeCollider"]->SetCubeCollider(4.f, 1.f, 1.f);
		player->Setup();
		player->SetObjectName("player");
		newScene->mCamera->SetTarget(player->GetPosRef());
		newScene->AddEventSubscriberList(eEventName::KEY_DOWN, 9, player);
		newScene->AddEventSubscriberList(eEventName::KEY_UP, 9, player);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, player);
		room->SetPlayer(player);

		// >> : UI
		UIImage * uiImage = new UIImage("Resources/UI/Setting/Layer3.png");
		uiImage->SetObjectName("SettingLayer");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5f,
			uiImage->GetPos().y + viewPort.Height * 0.5f - uiImage->GetHeight() * 0.5f, 0.0f));
		uiImage->EventProcess = BtnSettingEventListen;
		newScene->AddEventSubscriberList(eEventName::KEY_UP, 0, uiImage);
		newScene->AddEventSubscriberList(eEventName::KEY_DOWN, 0, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 0, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 0, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 0, uiImage);
		uiImage->SetVisible(false);
		newScene->mGameUIs.insert(make_pair("SettingLayer", uiImage));
		
		UIImage * childUI = new UIImage("Resources/UI/Setting/Exit_off.png");
		childUI->SetObjectName("ExitBtn");
		childUI->SetPos(D3DXVECTOR3(childUI->GetPos().x + viewPort.Width * 0.22f - childUI->GetWidth() * 0.5f,
			childUI->GetPos().y + viewPort.Height * 0.82f - childUI->GetHeight() * 0.5f, 0.0f));
		childUI->SetVisible(true);
		uiImage->AddChild("ExitBtn", childUI);

		childUI = new UIImage("Resources/UI/Setting/BGM_off1.png");
		childUI->SetObjectName("BGMText");
		childUI->SetPos(D3DXVECTOR3(childUI->GetPos().x + viewPort.Width * 0.25f - childUI->GetWidth() * 0.5f,
			childUI->GetPos().y + viewPort.Height * 0.25f - childUI->GetHeight() * 0.5f, 0.0f));
		childUI->SetVisible(true);
		uiImage->AddChild("BGMText", childUI);

		childUI = new UIImage("Resources/UI/Setting/Lines1.png");
		childUI->SetObjectName("BGMLine");
		childUI->SetPos(D3DXVECTOR3(childUI->GetPos().x + viewPort.Width * 0.5f - childUI->GetWidth() * 0.5f,
			childUI->GetPos().y + viewPort.Height * 0.25f - childUI->GetHeight() * 0.5f, 0.0f));
		childUI->SetVisible(true);
		uiImage->AddChild("BGMLine", childUI);

		UIImage* childUIBtn = new UIImage("Resources/UI/Setting/Button_set.png");
		childUIBtn->SetObjectName("BGMBtn");
		childUIBtn->SetPos(D3DXVECTOR3(childUI->GetPos().x + childUI->GetWidth()*0.4f,
			childUI->GetPos().y - childUIBtn->GetHeight()*0.25f, 0.0f));
		childUIBtn->SetVisible(true);
		uiImage->GetChildUI("BGMLine")->AddChild("BGMBtn", childUIBtn);

		childUI = new UIImage("Resources/UI/Setting/Control_off.png");
		childUI->SetObjectName("Control");
		childUI->SetPos(D3DXVECTOR3(childUI->GetPos().x + viewPort.Width * 0.25f - childUI->GetWidth() * 0.5f,
			childUI->GetPos().y + viewPort.Height * 0.5f - childUI->GetHeight() * 0.5f, 0.0f));
		childUI->SetVisible(true);
		uiImage->AddChild("Control", childUI);

		childUI = new UIImage("Resources/UI/Setting/OptionText1.png");
		childUI->SetObjectName("OptionText");
		childUI->SetPos(D3DXVECTOR3(childUI->GetPos().x + viewPort.Width * 0.73f - childUI->GetWidth() * 0.5f,
			childUI->GetPos().y + viewPort.Height * 0.8f - childUI->GetHeight() * 0.5f, 0.0f));
		childUI->SetVisible(true);
		uiImage->AddChild("OptionText", childUI);

		childUI = new UIImage("Resources/UI/Setting/Control.png");
		childUI->SetObjectName("ControlLayer");
		childUI->SetPos(D3DXVECTOR3(childUI->GetPos().x + viewPort.Width * 0.5f - childUI->GetWidth() * 0.5f,
			childUI->GetPos().y + viewPort.Height * 0.5f - childUI->GetHeight() * 0.5f, 0.0f));
		childUI->SetVisible(false);
		uiImage->AddChild("ControlLayer", childUI);
		// << : UI

		Static3DObject* key = new Static3DObject;
		key->SetObjectName("key1");
		key->Setup("Resources/Xfile/", "Key.X");
		key->AddColliderCube("basicColliderCube");
		
		Interactable3DObject* box = new Interactable3DObject;
		box->SetObjectName("box");
		box->AddColliderCube("basicColliderCube");
		box->Setup("Resources/XFile/", "DeathDropBox.X");
		box->SetScale(D3DXVECTOR3(0.03f, 0.03f, 0.03f));
		box->SetPos(D3DXVECTOR3(16,0,10));
		box->SetRot(D3DXQUATERNION(0, 0.7f, 0, 1));
		box->SetIsInteractable(true);
		box->AddInteractionCondition(bind(&Interactable3DObject::GetTryInteractionCalled, box));
		box->AddInteractionBehavior([=]()->void
			{
				player->AddItem(eInventorySlot::Key, key);
			});
		box->AddInteractionBehavior(bind(&Interactable3DObject::ChangeToStaticObject, box));
		room->InsertObject(box);

		Interactable3DObject* door = new Interactable3DObject;
		door->SetObjectName("door");
		door->AddColliderCube("basicColliderCube");
		door->Setup("Resources/XFile/", "Door.x", eTypeTag::DOOR);
		door->SetPos(D3DXVECTOR3(3, 1.5, 9));
		door->SetIsInteractable(true);
		door->AddInteractionCondition([=]()->bool
			{
				return player->HasItem(eInventorySlot::Key, "key1");
			});
		door->AddInteractionCondition(bind(&Interactable3DObject::GetTryInteractionCalled, door));
		door->AddInteractionBehavior([=]()->void
			{
				D3DXQUATERNION rotY;
				D3DXQuaternionRotationAxis(&rotY, &D3DXVECTOR3(0, 1, 0), D3DX_PI * 0.5f);
				door->SetRot(rotY);
			});
		door->AddInteractionBehavior([=]()->void
			{
				player->UseItem(eInventorySlot::Key);
			});
		door->AddInteractionBehavior(bind(&Interactable3DObject::ChangeToStaticObject, door));
		room->InsertObject(door);


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


		gJSON->LoadJSON("Resources/Json/wallTest.json");
		Value& walls = gJSON->mDocument["wall"];
		for (SizeType i = 0; i < walls.Size(); ++i)
		{
			D3DXQUATERNION rotation(0, 0, 0, 0);
			Value::ConstMemberIterator itrot = walls[i].FindMember("rotation");
			if (itrot != walls[i].MemberEnd())
			{
				D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(
					walls[i]["rotation"]["x"].GetFloat(),
					walls[i]["rotation"]["y"].GetFloat(),
					walls[i]["rotation"]["z"].GetFloat()
				), walls[i]["rotation"]["w"].GetFloat() * D3DX_PI);
			}

			D3DXVECTOR3 ColliderScale(1.f,1.f,1.f);
			Value::ConstMemberIterator itcol = walls[i].FindMember("colliderScale");
			if (itcol != walls[i].MemberEnd())
			{
				ColliderScale.x = walls[i]["colliderScale"]["height"].GetFloat();
				ColliderScale.y = walls[i]["colliderScale"]["width"].GetFloat();
				ColliderScale.z = walls[i]["colliderScale"]["depth"].GetFloat();
			}
			
			Static3DObject* wall = CreateStatic3DObject(
				string("wall") + to_string(i),
				walls[i]["sourceFileName"].GetString(),
				{
					walls[i]["position"]["x"].GetFloat(),
					walls[i]["position"]["y"].GetFloat(),
					walls[i]["position"]["z"].GetFloat()
				},
				ColliderScale,
				rotation
			);
			
			room->InsertObject(wall);
		}
		gSoundManager->Play("BGM");
		gShader->LoadAllShader();
	}
	return newScene;
}

Static3DObject * SceneFactory::CreateStatic3DObject(string objectName, string sourceFileName, D3DXVECTOR3 position, D3DXVECTOR3 colliderScale, D3DXQUATERNION rotation, string colliderName)
{
	Static3DObject* newStaticObject = new Static3DObject;
	newStaticObject->SetObjectName(objectName);
	newStaticObject->Setup("Resources/XFile/", sourceFileName);
	newStaticObject->SetRot(rotation);
	newStaticObject->SetPos(position);
	
	if ((colliderScale.x <= 0) || (colliderScale.y <= 0) || (colliderScale.z <= 0))
	{
	}
	else
	{
		newStaticObject->AddColliderCube(colliderName);
		newStaticObject->GetColliderCube()["basicColliderCube"]->SetCubeCollider(
			colliderScale.x,
			colliderScale.y,
			colliderScale.z);
		newStaticObject->GetColliderSphere()->SetSphereCollider(D3DXVec3Length(&(D3DXVECTOR3(colliderScale.x/2, colliderScale.y/2, colliderScale.z/2)-D3DXVECTOR3(colliderScale.x, colliderScale.y, colliderScale.z))));
	}

	return newStaticObject;
}
