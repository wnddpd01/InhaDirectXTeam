#pragma once
#include "BaseObject.h"
#include "ColliderChecker.h"

class QuarterMap;
class Base3DObject;

class Room :
	public BaseObject
{
public :
	Room();
	~Room();
	void Update() override;
	void Render() override;
	void SetupQuarterMap(char* szFolder, char* szRaw, char* szTex, DWORD dwBytesPerPixel = 1);
	void InsertObject(Base3DObject * object);
	void DeleteObject(string& name);
protected:
private:
protected:
private:
	static ColliderChecker mColliderChecker;
	QuarterMap* mQuarterMap;
	map<string, Base3DObject*> mObjectsInRoom;
};

