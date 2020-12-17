#include "stdafx.h"
#include "GameObjectAssemblyLine.h"
#include "Scene.h"
#include "Room.h"
#include "Door.h"
#include "Interactable3DObject.h"
#include "RoomCenter.h"
#include "Player.h"
#include "Portal.h"
#include "ColliderCube.h"
#include "ColliderSphere.h"
#include "FlashLight.h"

Static3DObject* GameObjectAssemblyLine::CreateStatic3DObject(string objectName, string sourceFileName, D3DXVECTOR3 position,
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
		newStaticObject->GetColliderSphere()->SetSphereCollider(D3DXVec3Length(&(D3DXVECTOR3(colliderScale.x / 2, colliderScale.y / 2, colliderScale.z / 2) - D3DXVECTOR3(colliderScale.x, colliderScale.y, colliderScale.z))));
	}

	return newStaticObject;
}

void GameObjectAssemblyLine::LoadObjectFromJson(string objectName, Room* targetRoom)
{
	D3DXVECTOR3 offset;
	Value& JsonOffset = gJSON->mDocument["offset"];
	offset.x = JsonOffset["x"].GetFloat();
	offset.y = JsonOffset["y"].GetFloat();
	offset.z = JsonOffset["z"].GetFloat();

	static int wallCnt = 0;

	Value& object = gJSON->mDocument[objectName.c_str()];
	for (SizeType i = 0; i < object.Size(); ++i)
	{
		D3DXVECTOR3 scale(1, 1, 1);
		D3DXQUATERNION rotation(0, 0, 0, 0);
		Value::ConstMemberIterator itrot = object[i].FindMember("rotation");
		if (itrot != object[i].MemberEnd())
		{
			D3DXVECTOR3 rot(
				object[i]["rotation"]["x"].GetFloat() * D3DX_PI / 180.f,
				object[i]["rotation"]["y"].GetFloat() * D3DX_PI / 180.f,
				object[i]["rotation"]["z"].GetFloat() * D3DX_PI / 180.f);

			D3DXQUATERNION quater;

			D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0, 1, 0), rot.y);
		}

		Value::ConstMemberIterator itscale = object[i].FindMember("scale");
		if (itscale != object[i].MemberEnd())
		{
			scale = D3DXVECTOR3(
				object[i]["scale"]["x"].GetFloat(),
				object[i]["scale"]["y"].GetFloat(),
				object[i]["scale"]["z"].GetFloat());
		}

		D3DXVECTOR3 ColliderScale(1.f, 1.f, 1.f);
		Value::ConstMemberIterator itcol = object[i].FindMember("colliderScale");
		if (itcol != object[i].MemberEnd())
		{
			ColliderScale.x = object[i]["colliderScale"]["height"].GetFloat();
			ColliderScale.y = (object[i]["colliderScale"]["width"].GetFloat() * scale.x) - 1.f;
			ColliderScale.z = object[i]["colliderScale"]["depth"].GetFloat();
		}

		D3DXVECTOR3 Position(0.f, 0.f, 0.f);
		Value::ConstMemberIterator itpos = object[i].FindMember("position");
		if (itpos != object[i].MemberEnd())
		{
			Position.x = (object[i]["position"]["x"].GetFloat() + offset.x);
			Position.y = (object[i]["position"]["y"].GetFloat() + offset.y);
			Position.z = (object[i]["position"]["z"].GetFloat() + offset.z);
		}

		Static3DObject* static3Dobject = CreateStatic3DObject(
			objectName + to_string(wallCnt++),
			object[i]["sourceFileName"].GetString(),
			Position,
			scale,
			ColliderScale,
			rotation
		);
		static3Dobject->SetTypeTag(eTypeTag::WALL);
		targetRoom->InsertObject(static3Dobject);
	}
}

void GameObjectAssemblyLine::LoadFromJson(string fileName, Room* targetRoom)
{
	gJSON->LoadJSON(fileName);
	if(gJSON->mDocument.HasMember("wall"))
	{
		LoadObjectFromJson("wall", targetRoom);
	}
	if (gJSON->mDocument.HasMember("door"))
	{
		LoadObjectFromJson("door", targetRoom);
	}
}

void GameObjectAssemblyLine::CreateStartSceneGameObject(Scene* newScene)
{
}

void GameObjectAssemblyLine::CreateIngameSceneGameObject(Scene* newScene)
{
	RoomCenter* roomCenter = new RoomCenter;
	roomCenter->SetObjectName("RoomCenter");
	newScene->mGameObjects.insert(make_pair("RoomCenter", roomCenter));

	Player* player = new Player;
	player->AddColliderCube("playerCubeCollider");
	player->GetColliderCube()["playerCubeCollider"]->SetCubeCollider(4.f, 1.f, 1.f);
	player->Setup();
	player->SetObjectName("player");
	newScene->GetCamera()->SetTarget(player->GetPosRef());
	newScene->AddEventSubscriberList(eEventName::KEY_DOWN, 9, player);
	newScene->AddEventSubscriberList(eEventName::KEY_UP, 9, player);
	newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, player);
	roomCenter->SetPlayer(player);

	newScene->mGameObjects.insert(make_pair("Aplayer", player));



	Room* room2A01 = new Room;
	roomCenter->InsertRoom(eRoomName::R2A01, room2A01);
	LoadFromJson("Resources/Json/wall3A01.json", room2A01);
	Base3DObject * portal2A01 = new Base3DObject();
	portal2A01->SetObjectName("portal2A07");
	portal2A01->AddColliderCube("portal2A07ColliderCube");
	portal2A01->Setup();
	portal2A01->SetPos({ 24.5f, 0.f, 17.f });
	portal2A01->CollideHandle = [=](Base3DObject* myObject, string& myColliderTag, Base3DObject* otherObject, string& otherColliderTag)->void
	{
		roomCenter->SetCurRoom(eRoomName::R2A07);
		cout << "i'm in Room2A07" << endl;
	};
	room2A01->InsertObject(portal2A01);
	
	Room * room2A02 = new Room;
	roomCenter->InsertRoom(eRoomName::R2A02, room2A02);
	LoadFromJson("Resources/Json/wall3A02.json", room2A02);

	Room* room2A03 = new Room;
	roomCenter->InsertRoom(eRoomName::R2A03, room2A03);
	LoadFromJson("Resources/Json/wall3A03.json", room2A03);

	Room* room2A04 = new Room;
	roomCenter->InsertRoom(eRoomName::R2A04, room2A04);
	LoadFromJson("Resources/Json/wall3A04.json", room2A04);

	Room* room2A05 = new Room;
	roomCenter->InsertRoom(eRoomName::R2A05, room2A05);
	LoadFromJson("Resources/Json/wall3A05.json", room2A05);

	Room* room2A06 = new Room;
	roomCenter->InsertRoom(eRoomName::R2A06, room2A06);
	LoadFromJson("Resources/Json/wall3A06.json", room2A06);

	Room* room2A07 = new Room;
	roomCenter->InsertRoom(eRoomName::R2A07, room2A07);
	LoadFromJson("Resources/Json/wall3A07.json", room2A07);

	Base3DObject * portal2A07 = new Base3DObject();
	portal2A07->SetObjectName("portal2A07");
	portal2A07->AddColliderCube("portal2A07ColliderCube");
	portal2A07->Setup();
	portal2A07->SetPos({ 25.5f, 0.f, 17.f });
	portal2A07->CollideHandle = [=](Base3DObject* myObject, string& myColliderTag, Base3DObject* otherObject, string& otherColliderTag)->void
	{
		roomCenter->SetCurRoom(eRoomName::R2A01);
		cout << "i'm in Room2A01" << endl;
	};
	room2A07->InsertObject(portal2A07);

	Room* room2B01 = new Room;
	roomCenter->InsertRoom(eRoomName::R2B01, room2B01);
	LoadFromJson("Resources/Json/wall3B01.json", room2B01);

	Room* room2B02 = new Room;
	roomCenter->InsertRoom(eRoomName::R2B02, room2B02);
	LoadFromJson("Resources/Json/wall3B02.json", room2B02);

	Room* room2B03 = new Room;
	roomCenter->InsertRoom(eRoomName::R2B03, room2B03);
	LoadFromJson("Resources/Json/wall3B03.json", room2B03);

	Room* room2B04 = new Room;
	roomCenter->InsertRoom(eRoomName::R2B04, room2B04);
	LoadFromJson("Resources/Json/wall3B04.json", room2B04);

	Room* room2C01 = new Room;
	roomCenter->InsertRoom(eRoomName::R2C01, room2C01);
	LoadFromJson("Resources/Json/wall3C01.json", room2C01);

	Room* room2C02 = new Room;
	roomCenter->InsertRoom(eRoomName::R2C02, room2C02);
	LoadFromJson("Resources/Json/wall3C02.json", room2C02);

	Room* room2C03 = new Room;
	roomCenter->InsertRoom(eRoomName::R2C03, room2C02);
	LoadFromJson("Resources/Json/wall3C03.json", room2C02);

	Room* room2D01 = new Room;
	roomCenter->InsertRoom(eRoomName::R2D01, room2D01);
	LoadFromJson("Resources/Json/wall3D01.json", room2D01);

	roomCenter->SetCurRoom(eRoomName::R2A07);

	Static3DObject* floor = CreateStatic3DObject("floor", "mapTile.x", D3DXVECTOR3(75, 0, 75), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 0));
	floor->SetTypeTag(eTypeTag::FLOOR);
	newScene->mGameObjects.insert(make_pair("AAfloor", floor));

	Static3DObject* key = new Static3DObject;
	key->SetObjectName("key1");
	key->Setup("Resources/Xfile/", "Key.X");
	key->AddColliderCube("basicColliderCube");

	Interactable3DObject* box = new Interactable3DObject;
	box->SetObjectName("box");
	box->AddColliderCube("basicColliderCube");
	box->Setup("Resources/XFile/", "DeathDropBox.X");
	box->SetScale(D3DXVECTOR3(0.03f, 0.03f, 0.03f));
	box->SetPos(D3DXVECTOR3(16, 0, 135));
	box->SetRot(D3DXQUATERNION(0, 0.7f, 0, 1));
	box->SetIsInteractable(true);
	box->AddInteractionCondition(bind(&Interactable3DObject::GetTryInteractionCalled, box));
	box->AddInteractionBehavior([=]()->void
	{
		player->AddItem(eInventorySlot::Key, key);
	});
	box->AddInteractionBehavior(bind(&Interactable3DObject::ChangeToStaticObject, box));
	room2A02->InsertObject(box);

	Portal * portal1 = new Portal(D3DXVECTOR3(1, 0, 0));
	portal1->SetObjectName("portal1");
	portal1->AddColliderCube("portal1ColliderCube");
	portal1->CollideHandle = bind(&Portal::PortalColliderHandler, portal1, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
	portal1->SetPos(D3DXVECTOR3(25, 0, 123.5));
	portal1->SetExitPos(D3DXVECTOR3(25, 0, 142.5));
	portal1->Setup();
	room2A02->InsertObject(portal1);

	Portal * portal2 = new Portal(D3DXVECTOR3(1, 0, 0));
	portal2->SetObjectName("portal2");
	portal2->AddColliderCube("portal2ColliderCube");
	portal2->CollideHandle = bind(&Portal::PortalColliderHandler, portal2, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
	portal2->SetPos(D3DXVECTOR3(25, 0, 142.5));
	portal2->SetExitPos(D3DXVECTOR3(25, 0, 123.5));
	portal2->Setup();
	room2A02->InsertObject(portal2);

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
	door->AddInteractionBehavior([=]()->void
	{
		portal1->CollideHandle = [=](Base3DObject* myObject, string& myColliderTag, Base3DObject* otherObject, string& otherColliderTag)->void
		{
			roomCenter->SetCurRoom(eRoomName::R2A01);
		};
		portal2->CollideHandle = [=](Base3DObject* myObject, string& myColliderTag, Base3DObject* otherObject, string& otherColliderTag)->void
		{
			roomCenter->SetCurRoom(eRoomName::R2A01);
		};
	});
	door->AddInteractionBehavior(bind(&Interactable3DObject::ChangeToStaticObject, door));
	room2A02->InsertObject(door);

	Door* tempDoor = new Door;
	tempDoor->SetObjectName("tempDoor");
	tempDoor->Setup("Resources/XFile/", "newDoor.x");
	tempDoor->SetRot(D3DXQUATERNION(0, 0, 0, 1));
	tempDoor->SetPos(D3DXVECTOR3(25.f, 1.5f, 18.5f));
	tempDoor->SetScale(D3DXVECTOR3(0.65f, 1.f, 0.5f));
	tempDoor->AddColliderCube("basicColliderCube");
	tempDoor->GetColliderCube()["basicColliderCube"]->SetCubeCollider(8.f, 3.f, 0.5f);
	tempDoor->GetColliderSphere()->SetSphereCollider(D3DXVec3Length(&(D3DXVECTOR3(1, 1, 1) - D3DXVECTOR3(1, 1, 1))));

	room2A02->InsertObject(tempDoor);

	FlashLight* onlyFlashLight = new FlashLight;
	onlyFlashLight->Setup(player->GetPosRef(), player->GetRotPt());
	newScene->mGameObjects.insert(make_pair("ZFlashLight", onlyFlashLight));

}

void GameObjectAssemblyLine::MakeGameObject(Scene* newScene)
{
	switch (newScene->GetSceneName())
	{
		case eSceneName::START_SCENE :
			{
			}
			break;
		case eSceneName::INGAME_SCENE :
			{
				CreateIngameSceneGameObject(newScene);
			}
			break;
		default :
			{}
			break;
	}
}
