#pragma once
#include "BaseObject.h"
#include "ColliderChecker.h"

class QuarterMap;
class Base3DObject;
class Player;

class Room :
	public BaseObject, public BaseObserver
{
public :
	Room();
	~Room();
	void Update(Player* player);
	void Render() override;

	bool Update(eEventName eventName, void* parameter) override;
	//void SetPlayer(Player* player) { mPlayer = player; }
	void InsertObject(Base3DObject * object);
	void DeleteObject(string& name);

	map<string, Base3DObject*>& GetObjectsInRoomRef() { return mObjectsInRoom; }
protected:
private:
protected:
private:
	static ColliderChecker mColliderChecker;
	bool mbCheckCollision;
	//Player* mPlayer;
	map<string, Base3DObject*> mObjectsInRoom;
};

