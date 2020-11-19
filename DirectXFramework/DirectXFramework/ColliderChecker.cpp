#include "stdafx.h"
#include "ColliderChecker.h"
#include "ColliderCube.h"
#include "ColliderSphere.h"

ColliderChecker::ColliderChecker()
{
}

ColliderChecker::~ColliderChecker()
{
}

void ColliderChecker::CheckCollider(map<string, Base3DObject*>& objects)
{
	for (map<string, Base3DObject*>::iterator iter = objects.begin(); iter != prev(objects.end(),1) ; ++iter)
	{
		for (map<string, Base3DObject*>::iterator iter2 = next(iter,1); iter2 != objects.end(); ++iter2)
		{
			if(CheckSphere((*iter).second, (*iter2).second))
			{
				string obj1Tag = "";
				string obj2Tag = "";
				
				if(CheckCube((*iter).second,(*iter2).second, obj1Tag, obj2Tag))
				{
					cout << "asasd";
				}
				else
				{
					
				}
			}
		}
	}
}

bool ColliderChecker::CheckCube(IN Base3DObject * object1, IN Base3DObject * object2, OUT string& obj1Tag, OUT string& obj2Tag)
{
	for (map<string, ColliderCube*>::iterator iter = object1->GetColliderCube().begin(); iter != object1->GetColliderCube().end(); ++iter)
	{
		for (map<string, ColliderCube*>::iterator iter2 = object2->GetColliderCube().begin(); iter2 != object2->GetColliderCube().end(); ++iter2)
		{
			if(ColliderCube::IsCollision((*iter).second,(*iter2).second))
			{
				return true;
			}
		}
	}
	return false;
}

bool ColliderChecker::CheckSphere(Base3DObject* object1, Base3DObject* object2)
{
	float distance;
	D3DXVECTOR3 diff;
	diff = object1->GetPos() - object2->GetPos();
	
	distance = D3DXVec3Length(&diff);

	if (distance <= object1->GetColliderSphere()->GetRadius() + object2->GetColliderSphere()->GetRadius())
	{
		return true;
	}

	return false;
}