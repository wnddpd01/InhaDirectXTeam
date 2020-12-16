#include "stdafx.h"
#include "SceneFactory.h"
#include "SceneCenter.h"
#include "Scene.h"
#include "QuarterMap.h"
#include "Player.h"
#include "Static3DObject.h"
#include "RoomCenter.h"
#include "Room.h"
#include "CollideHandle.h"
#include "Portal.h"
#include "ColliderCube.h"
#include "ColliderSphere.h"
#include "Interactable3DObject.h"
#include "Inventory.h"
#include "UICellGrid.h"
#include "Door.h"
#include "FlashLight.h"

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
	static UICellGrid* uiCellGrid = nullptr;
	if (uiCellGrid == nullptr)
	{
		uiCellGrid = new UICellGrid;
		gEventManager->AttachSubscriber(eEventName::KEY_UP, 10, uiCellGrid);
		uiCellGrid->EventProcess = [=](eEventName eventName, void * parameter, UIBase * uiBase)->bool
		{
			eKeyName key = *(eKeyName*)parameter;
			if(key == eKeyName::KEY_ESC)
			{
				uiCellGrid->SetVisible(!uiCellGrid->IsVisible());
			}
			return false;
		};
	}
	newScene->mGameUIs.insert(make_pair("uiCellGrid", uiCellGrid));
	if (eSceneName == eSceneName::START_SCENE)
	{
		D3DVIEWPORT9 viewPort;
		gD3Device->GetViewport(&viewPort);
		UIImage * uiImage = new UIImage("Resources/UI/Main/Title.png", {20, 4}, 24, 8);
		uiImage->SetObjectName("Title");
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("Title", uiImage));

		uiImage = new UIImage("Resources/UI/Main/NewGame.png", {26,20}, 12, 4);
		uiImage->SetObjectName("BtnStart");
		uiImage->EventProcess = BtnStartEventListen;
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, uiImage);
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("btnStart", uiImage));

		uiImage = new UIImage("Resources/UI/Main/Quit.png", {26, 24}, 12, 4);
		uiImage->SetObjectName("BtnExit");
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
		D3DVIEWPORT9 viewPort;
		gD3Device->GetViewport(&viewPort);

		//>> : UI
		UIImage * uiImage = new UIImage("Resources/UI/Setting/Layer.png", {12, 6}, 40, 24);
		uiImage->SetObjectName("SettingLayer");
		uiImage->EventProcess = BtnSettingEventListen;
		newScene->AddEventSubscriberList(eEventName::KEY_UP, 0, uiImage);
		newScene->AddEventSubscriberList(eEventName::KEY_DOWN, 0, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 0, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 0, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 0, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_DRAG, 0, uiImage);
		uiImage->SetVisible(false);
		newScene->mGameUIs.insert(make_pair("SettingLayer", uiImage));

		UIImage * childUI = new UIImage("Resources/UI/Setting/Exit_off.png", { 14, 28 }, 4, 1);
		childUI->SetObjectName("ExitBtn");
		childUI->SetUIPath("Resources/UI/Setting/Exit_off.png",eStateUI::off);
		childUI->SetUIPath("Resources/UI/Setting/Exit_on.png", eStateUI::on);
		childUI->SetVisible(true);
		uiImage->AddChild("ExitBtn", childUI);

		childUI = new UIImage("Resources/UI/Setting/BGM_off.png", {16, 10} , 6,2);
		childUI->SetObjectName("BGMText");
		childUI->SetUIPath("Resources/UI/Setting/BGM_off.png", eStateUI::off);
		childUI->SetUIPath("Resources/UI/Setting/BGM_on.png", eStateUI::on);
		childUI->SetVisible(true);
		uiImage->AddChild("BGMText",childUI);

		childUI = new UIImage("Resources/UI/Setting/Line.png", {24, 10}, 16, 2);
		childUI->SetObjectName("BGMLine");
		childUI->SetVisible(true);
		uiImage->AddChild("BGMLine",childUI);

		childUI = new UIImage("Resources/UI/Setting/Button_set.png", {30 , 10} , 4,2);
		childUI->SetObjectName("BGMBtn");
		childUI->SetUIPath("Resources/UI/Setting/Button_set.png", eStateUI::off);
		childUI->SetUIPath("Resources/UI/Setting/Button_click.png", eStateUI::on);
		childUI->SetVisible(true);
		uiImage->GetChildUI("BGMLine")->AddChild("BGMBtn", childUI);

		childUI = new UIImage("Resources/UI/Setting/Control_off.png", {16, 14} ,6 ,2);
		childUI->SetObjectName("Control");
		childUI->SetUIPath("Resources/UI/Setting/Control_off.png", eStateUI::off);
		childUI->SetUIPath("Resources/UI/Setting/Control_on.png", eStateUI::on);
		childUI->SetVisible(true);
		uiImage->AddChild("Control", childUI);
		
		childUI = new UIImage("Resources/UI/Setting/OptionText.png", { 36, 26 }, 15, 2);
		childUI->SetObjectName("OptionText");
		childUI->SetVisible(true);
		uiImage->AddChild("OptionText",childUI);

		childUI = new UIImage("Resources/UI/Setting/Control.png", { 12, 6 }, 40, 24);
		childUI->SetObjectName("ControlLayer");
		childUI->SetVisible(false);
		uiImage->AddChild("ControlLayer", childUI);

		childUI = new UIImage("Resources/UI/Setting/Return_off.png", { 14, 28 }, 4, 1);
		childUI->SetObjectName("ReturnBtn");
		childUI->SetUIPath("Resources/UI/Setting/Return_off.png", eStateUI::off);
		childUI->SetUIPath("Resources/UI/Setting/Return_on.png", eStateUI::on);
		childUI->SetVisible(false);
		uiImage->AddChild("ReturnBtn", childUI);
		//<< : UI
		
		RoomCenter* roomCenter = new RoomCenter;
		roomCenter->SetObjectName("RoomCenter");
		newScene->mGameObjects.insert(make_pair("RoomCenter", roomCenter));

		Player* player = new Player;
		player->AddColliderCube("playerCubeCollider");
		player->GetColliderCube()["playerCubeCollider"]->SetCubeCollider(4.f, 1.f, 1.f);
		player->Setup();
		player->SetObjectName("player");
		newScene->mCamera->SetTarget(player->GetPosRef());
		newScene->AddEventSubscriberList(eEventName::KEY_DOWN, 9, player);
		newScene->AddEventSubscriberList(eEventName::KEY_UP, 9, player);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, player);
		roomCenter->SetPlayer(player);

		newScene->mGameObjects.insert(make_pair("Aplayer", player));

		Room* room2A01 = new Room;
		roomCenter->InsertRoom(eRoomName::R2A01, room2A01);
		LoadWallfromJson("Resources/Json/wall3A01.json", room2A01);

		Room * room2A02 = new Room;
		roomCenter->InsertRoom(eRoomName::R2A02, room2A02);
		LoadWallfromJson("Resources/Json/wall3A02.json", room2A02);

		roomCenter->SetCurRoom(eRoomName::R2A07);

		Room* room2A03 = new Room;
		roomCenter->InsertRoom(eRoomName::R2A03, room2A03);
		LoadWallfromJson("Resources/Json/wall3A03.json", room2A03);
		
		Room* room2A04 = new Room;
		roomCenter->InsertRoom(eRoomName::R2A04, room2A04);
		LoadWallfromJson("Resources/Json/wall3A04.json", room2A04);

		Room* room2A05 = new Room;
		roomCenter->InsertRoom(eRoomName::R2A05, room2A05);
		LoadWallfromJson("Resources/Json/wall3A05.json", room2A05);

		Room* room2A06 = new Room;
		roomCenter->InsertRoom(eRoomName::R2A06, room2A06);
		LoadWallfromJson("Resources/Json/wall3A06.json", room2A06);

		Room* room2A07 = new Room;
		roomCenter->InsertRoom(eRoomName::R2A07, room2A07);
		LoadWallfromJson("Resources/Json/wall3A07.json", room2A07);
		
		Room* room2B01 = new Room;
		roomCenter->InsertRoom(eRoomName::R2B01, room2B01);
		LoadWallfromJson("Resources/Json/wall3B01.json", room2B01);

		Room* room2B02 = new Room;
		roomCenter->InsertRoom(eRoomName::R2B02, room2B02);
		LoadWallfromJson("Resources/Json/wall3B02.json", room2B02);

		Room* room2B03 = new Room;
		roomCenter->InsertRoom(eRoomName::R2B03, room2B03);
		LoadWallfromJson("Resources/Json/wall3B03.json", room2B03);

		Room* room2B04 = new Room;
		roomCenter->InsertRoom(eRoomName::R2B04, room2B04);
		LoadWallfromJson("Resources/Json/wall3B04.json", room2B04);

		Room* room2C01 = new Room;
		roomCenter->InsertRoom(eRoomName::R2C01, room2C01);
		LoadWallfromJson("Resources/Json/wall3C01.json", room2C01);

		Room* room2C02 = new Room;
		roomCenter->InsertRoom(eRoomName::R2C02, room2C02);
		LoadWallfromJson("Resources/Json/wall3C02.json", room2C02);

		Room* room2C03 = new Room;
		roomCenter->InsertRoom(eRoomName::R2C03, room2C02);
		LoadWallfromJson("Resources/Json/wall3C03.json", room2C02);
		
		Room* room2D01 = new Room;
		roomCenter->InsertRoom(eRoomName::R2D01, room2D01);
		LoadWallfromJson("Resources/Json/wall3D01.json", room2D01);
		
		
		Static3DObject* key = new Static3DObject;
		key->SetObjectName("key1");
		key->Setup("Resources/Xfile/", "Key.X");
		key->AddColliderCube("basicColliderCube");
		

		Static3DObject* floor = new Static3DObject;
		floor = CreateStatic3DObject("floor", "mapTile.X", D3DXVECTOR3(75, 0, 75), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 0));
		floor->SetTypeTag(eTypeTag::FLOOR);
		newScene->mGameObjects.insert(make_pair("AAfloor", floor));

		Interactable3DObject* box = new Interactable3DObject;
		box->SetObjectName("box");
		box->AddColliderCube("basicColliderCube");
		box->Setup("Resources/XFile/", "DeathDropBox.X");
		box->SetScale(D3DXVECTOR3(0.03f, 0.03f, 0.03f));
		box->SetPos(D3DXVECTOR3(16,0,135));
		box->SetRot(D3DXQUATERNION(0, 0.7f, 0, 1));
		box->SetIsInteractable(true);
		box->AddInteractionCondition(bind(&Interactable3DObject::GetTryInteractionCalled, box));
		box->AddInteractionBehavior([=]()->void
			{
				player->AddItem(eInventorySlot::Key, key);
			});
		box->AddInteractionBehavior(bind(&Interactable3DObject::ChangeToStaticObject, box));
		room2A02->InsertObject(box);

		Interactable3DObject* door = new Interactable3DObject;
		door->SetObjectName("door");
		door->AddColliderCube("basicColliderCube");
		door->Setup("Resources/XFile/", "Door.x", eTypeTag::ITEM);
		door->SetPos(D3DXVECTOR3(3, 1.5, 135));
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
		room2A02->InsertObject(door);


		Portal * portal1 = new Portal(D3DXVECTOR3(1, 0, 0));
		portal1->SetObjectName("portal1");
		portal1->AddColliderCube("portal1ColliderCube");
		portal1->CollideHandle = bind(&Portal::PortalColliderHandler, portal1, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
		portal1->SetPos(D3DXVECTOR3(25, 0 , 123.5));
		portal1->SetExitPos(D3DXVECTOR3(25, 0, 142.5));
		portal1->Setup();
		room2A02->InsertObject(portal1);

		Portal * portal2 = new Portal(D3DXVECTOR3(1,0,0));
		portal2->SetObjectName("portal2");
		portal2->AddColliderCube("portal2ColliderCube");
		portal2->CollideHandle = bind(&Portal::PortalColliderHandler, portal2, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
		portal2->SetPos(D3DXVECTOR3(25, 0, 142.5));
		portal2->SetExitPos(D3DXVECTOR3(25, 0, 123.5));
		portal2->Setup();
		room2A02->InsertObject(portal2);

		

		Door* tempDoor = new Door;
		tempDoor->SetObjectName("tempDoor");
		tempDoor->Setup("Resources/XFile/", "newDoor.x");
		tempDoor->SetRot(D3DXQUATERNION(0,0,0,1));
		tempDoor->SetPos(D3DXVECTOR3(25.f,1.5f,18.5f));
		tempDoor->SetScale(D3DXVECTOR3(0.65f, 1.f, 0.5f));
		tempDoor->AddColliderCube("basicColliderCube");
		tempDoor->GetColliderCube()["basicColliderCube"]->SetCubeCollider(8.f,3.f,0.5f);
		tempDoor->GetColliderSphere()->SetSphereCollider(D3DXVec3Length(&(D3DXVECTOR3(1, 1, 1) - D3DXVECTOR3(1, 1, 1))));

		room2A02->InsertObject(tempDoor);

		FlashLight* onlyFlashLight = new FlashLight;
		onlyFlashLight->Setup(player->GetPosRef(), player->GetRotPt());
		newScene->mGameObjects.insert(make_pair("ZFlashLight", onlyFlashLight));
		
		gSoundManager->Play("BGM");
		gShader->LoadAllShader();
	}

	return newScene;
}

Static3DObject * SceneFactory::CreateStatic3DObject(string objectName, string sourceFileName, D3DXVECTOR3 position,
	D3DXVECTOR3 scale, D3DXVECTOR3 colliderScale, D3DXQUATERNION rotation, string colliderName)
{
	Static3DObject* newStaticObject = new Static3DObject;
	newStaticObject->SetObjectName(objectName);
	newStaticObject->Setup("Resources/XFile/", sourceFileName);
	newStaticObject->SetRot(rotation);
	newStaticObject->SetPos(position);
	newStaticObject->SetScale(scale);

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

void SceneFactory::LoadWallfromJson(string fileName, Room* targetRoom)
{
	gJSON->LoadJSON(fileName);
	
	D3DXVECTOR3 offset;
	Value& JsonOffset = gJSON->mDocument["offset"];
	offset.x = JsonOffset["x"].GetFloat();
	offset.y = JsonOffset["y"].GetFloat();
	offset.z = JsonOffset["z"].GetFloat();
	
	static int wallCnt = 0;
	
	Value& walls = gJSON->mDocument["wall"];
	for (SizeType i = 0; i < walls.Size(); ++i)
	{
		D3DXVECTOR3 scale(1, 1, 1);
		D3DXQUATERNION rotation(0, 0, 0, 0);
		Value::ConstMemberIterator itrot = walls[i].FindMember("rotation");
		if (itrot != walls[i].MemberEnd())
		{
			D3DXVECTOR3 rot(
				walls[i]["rotation"]["x"].GetFloat() * D3DX_PI / 180.f,
				walls[i]["rotation"]["y"].GetFloat() * D3DX_PI / 180.f,
				walls[i]["rotation"]["z"].GetFloat() * D3DX_PI / 180.f);

			D3DXQUATERNION quater;

			D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0,1,0), rot.y);
		}

		Value::ConstMemberIterator itscale = walls[i].FindMember("scale");
		if (itscale != walls[i].MemberEnd())
		{
			scale = D3DXVECTOR3(
				walls[i]["scale"]["x"].GetFloat(),
				walls[i]["scale"]["y"].GetFloat(),
				walls[i]["scale"]["z"].GetFloat());
		}

		D3DXVECTOR3 ColliderScale(1.f, 1.f, 1.f);
		Value::ConstMemberIterator itcol = walls[i].FindMember("colliderScale");
		if (itcol != walls[i].MemberEnd())
		{
			ColliderScale.x = walls[i]["colliderScale"]["height"].GetFloat();
			ColliderScale.y = (walls[i]["colliderScale"]["width"].GetFloat() * scale.x) - 1.f;
			ColliderScale.z = walls[i]["colliderScale"]["depth"].GetFloat();
		}

		D3DXVECTOR3 Position(0.f, 0.f, 0.f);
		Value::ConstMemberIterator itpos = walls[i].FindMember("position");
		if (itpos != walls[i].MemberEnd())
		{
			Position.x = (walls[i]["position"]["x"].GetFloat() + offset.x);
			Position.y = (walls[i]["position"]["y"].GetFloat() + offset.y);
			Position.z = (walls[i]["position"]["z"].GetFloat() + offset.z);
		}


		Static3DObject* wall = CreateStatic3DObject(
			string("wall") + to_string(wallCnt++),
			walls[i]["sourceFileName"].GetString(),
			Position,
			scale,
			ColliderScale,
			rotation
		);
		wall->SetTypeTag(eTypeTag::WALL);
		targetRoom->InsertObject(wall);
	}
}
