#pragma once
class Base3DObject;

class ColliderChecker
{
public:
	
	ColliderChecker();
	~ColliderChecker();

	void CheckCollider(map<string, Base3DObject*>& objects);
	
private:
	void CheckBoxByOBB(Base3DObject * object1, Base3DObject * object2);
	void CheckSphere(Base3DObject * object1, Base3DObject * object2);
	
public:
	map<string, BaseObject*> mColliderMap;
};