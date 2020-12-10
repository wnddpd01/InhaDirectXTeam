#pragma once
#include "BaseObject.h"
#include "ColliderChecker.h"

class QuarterMap;
class Base3DObject;
class Player;

class Room :
	public BaseObject
{
public :
	Room();
	~Room();
	//void Update() override;
	void Update(Player* player);
	void Render() override;
	//void SetPlayer(Player* player) { mPlayer = player; }
	void InsertObject(Base3DObject * object);
	void DeleteObject(string& name);
protected:
private:
protected:
private:
	static ColliderChecker mColliderChecker;
	//Player* mPlayer;
	map<string, Base3DObject*> mObjectsInRoom;
};

