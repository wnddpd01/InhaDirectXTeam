#include "stdafx.h"
#include "Room.h"
#include "QuarterMap.h"
#include "Base3DObject.h"
#include "Player.h"


ColliderChecker Room::mColliderChecker;

Room::Room()
{
}

Room::~Room()
{
	for (map<string, Base3DObject*>::value_type objectInRoom : mObjectsInRoom)
	{
		SAFE_DELETE(objectInRoom.second);
	}
	mObjectsInRoom.clear();
}

void Room::Update()
{
	mPlayer->Update();
	for (map<string, Base3DObject*>::value_type objectInRoom : mObjectsInRoom)
	{
		objectInRoom.second->Update();
	}
	mColliderChecker.CheckCollider(mPlayer, mObjectsInRoom);
	mPlayer->ProcessCollisionEventQueue();
}

void Room::Render()
{
	mPlayer->Render();
	for (map<string, Base3DObject*>::value_type objectInRoom : mObjectsInRoom)
	{
		objectInRoom.second->Render();
	}
}

void Room::InsertObject(Base3DObject* object)
{
	if(object->GetObjectName().empty() == true)
	{
		assert("Room Insert ERROR\nObject Name is Empty");
	}
	else if(mObjectsInRoom.find(object->GetObjectName()) != mObjectsInRoom.end())
	{
		assert("Room Insert ERROR\nAlready in Room Object");
	}
	mObjectsInRoom.insert(make_pair(object->GetObjectName(), object));
	object->DeleteInRoom = bind(&Room::DeleteObject, this, placeholders::_1);
}

void Room::DeleteObject(string& name)
{
	mObjectsInRoom.erase(mObjectsInRoom.find(name));
}
