#include "stdafx.h"
#include "Room.h"
#include "QuarterMap.h"
#include "Base3DObject.h"

ColliderChecker Room::mColliderChecker;

Room::Room()
	: mQuarterMap(nullptr)
{
}

Room::~Room()
{
	SAFE_DELETE(mQuarterMap);
	for (map<string, Base3DObject*>::value_type objectInRoom : mObjectsInRoom)
	{
		SAFE_DELETE(objectInRoom.second);
	}
	mObjectsInRoom.clear();
}

void Room::Update()
{
	for (map<string, Base3DObject*>::value_type objectInRoom : mObjectsInRoom)
	{
		objectInRoom.second->Update();
	}
	mColliderChecker.CheckCollider(mObjectsInRoom);
}

void Room::Render()
{
	mQuarterMap->Render();
	for (map<string, Base3DObject*>::value_type objectInRoom : mObjectsInRoom)
	{
		objectInRoom.second->Render();
	}
}

void Room::SetupQuarterMap(char* szFolder, char* szRaw, char* szTex, DWORD dwBytesPerPixel)
{
	mQuarterMap = new QuarterMap;
	mQuarterMap->Setup(szFolder, szRaw, szTex, dwBytesPerPixel);
}

void Room::InsertObject(Base3DObject* object)
{
	mObjectsInRoom.insert(make_pair(object->GetObjectName(), object));
	object->DeleteInRoom = bind(&Room::DeleteObject, this, placeholders::_1);
}

void Room::DeleteObject(string& name)
{
	mObjectsInRoom.erase(mObjectsInRoom.find(name));
}
