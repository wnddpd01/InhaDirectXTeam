#include "stdafx.h"
#include "ColliderChecker.h"


ColliderChecker::ColliderChecker()
{
}


ColliderChecker::~ColliderChecker()
{
}

bool ColliderChecker::CheckBoxByOBB(Base3DObject * object1, Base3DObject * object2)
{
}

//void ColliderChecker::CheckSphere(Base3DObject* object1, Base3DObject* object2)
//{
//	float distance;
//	D3DXVECTOR3 diff;
//
//	diff = Center2 - Center1;
//	distance = D3DXVec3Length(&diff);
//
//	if (distance <= (radius1 + radius2))
//	{
//		return TRUE;
//	}
//	return FALSE;
//}

void ColliderChecker::CheckCollider(map<string, Base3DObject*>& objects)
{
}

//void ColliderCheck::CheckSphereIntersect()
//{
//	
//}
