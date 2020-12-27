#include "stdafx.h"
#include "RoomCenter.h"
#include "Room.h"


RoomCenter::RoomCenter()
	: mCurRoom(nullptr)
	, mPlayer(nullptr)
{
	mObjectName = string("RoomCenter");
}


RoomCenter::~RoomCenter()
{
}

void RoomCenter::Update()
{
	mCurRoom->Update(mPlayer);
}

void RoomCenter::Render()
{
	mCurRoom->Render();
	/*for (map<eRoomName, Room*>::value_type& room : mRoomMap)
	{
		room.second->Render();
	}*/
}
