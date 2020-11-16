#include "stdafx.h"
#include "ColliderCheck.h"


ColliderCheck::ColliderCheck()
{
}


ColliderCheck::~ColliderCheck()
{
}

void ColliderCheck::OBB()
{
	
}

void ColliderCheck::CheckSphereIntersect()
{
	float distance;
	D3DXVECTOR3 diff;

	diff = Center2 - Center1;
	distance = D3DXVec3Length(&diff);

	if( distance <= (radius1 + radius2))
	{
		return TRUE;
	}
	return FALSE;
}
