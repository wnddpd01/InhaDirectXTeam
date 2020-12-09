#include "stdafx.h"
#include "RoomCenter.h"


RoomCenter::RoomCenter()
	: mCurRoom(nullptr)
	, mPlayer(nullptr)
{
	mObjectName = string("RoomCenter");
}


RoomCenter::~RoomCenter()
{
}
