#include "stdafx.h"
#include "ColliderChecker.h"



ColliderChecker::ColliderChecker()
{
}


ColliderChecker::~ColliderChecker()
{ 
}

bool ColliderChecker::CheckCubeByOBB(IN Base3DObject * object1,IN Base3DObject * object2, OUT string& obj1Tag, OUT string& obj2Tag)
{
	// Todo:: 모든 박스 비교
	//if()
	return TRUE;
}

bool ColliderChecker::CheckSphere(Base3DObject* object1, Base3DObject* object2)
{
	/*float distance;
	D3DXVECTOR3 diff;

	diff = Center2 - Center1;
	distance = D3DXVec3Length(&diff);

	if (distance <= (radius1 + radius2))
	{
		return TRUE;
	}*/
	return FALSE;
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
				
				if(CheckCubeByOBB((*iter).second,(*iter2).second, obj1Tag, obj2Tag))
				{
					
				}
				else
				{
					
				}
			}
		}
	}
}
