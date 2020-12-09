#pragma once
#include "BaseObject.h"

class Room;
class Player;

class RoomCenter :
	public BaseObject
{
	map<string, Room*> mRoomMap;
	Room * mCurRoom;
	Player * mPlayer;
public:
	RoomCenter();
	~RoomCenter();

	void InsertRoom(string & roomName, Room * room)
	{
		mRoomMap.insert(make_pair(roomName, room));
	}

	void SetPlayer(Player * player)
	{
		mPlayer = player;
	}
};

