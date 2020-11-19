#pragma once
class Base3DObject;
class BaseObject;
class ColliderCube;

struct CollisionEvent
{
	Base3DObject * obj1;
	string obj1ColliderTag;
	Base3DObject * obj2;
	string obj2ColliderTag;
};


class ColliderChecker
{
public:
	
	ColliderChecker();
	~ColliderChecker();

	void CheckCollider(map<string, Base3DObject*>& objects);

private:
	bool CheckCubeByOBB(ColliderCube * obj1Cube, ColliderCube * obj2Cube);
	bool CheckCube(Base3DObject* object1, Base3DObject* object2, string& obj1Tag, string& obj2Tag);
	bool CheckSphere(Base3DObject * object1, Base3DObject * object2);
	
public:
	map<string, BaseObject*> mColliderMap;
};