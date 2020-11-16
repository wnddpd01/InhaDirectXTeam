#pragma once
class Base3DObject;
class BaseObject;

class ColliderChecker
{
public:
	
	ColliderChecker();
	~ColliderChecker();

	void CheckCollider(map<string, Base3DObject*>& objects);
	
private:
	bool CheckCubeByOBB(Base3DObject * object1, Base3DObject * object2, string & obj1Tag, string & obj2Tag);
	bool CheckSphere(Base3DObject * object1, Base3DObject * object2);
	
public:
	map<string, BaseObject*> mColliderMap;
};