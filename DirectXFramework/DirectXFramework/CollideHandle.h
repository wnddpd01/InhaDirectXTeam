#pragma once
#include "stdafx.h"
#include "Base3DObject.h"

inline void DefaultColliderHandler(Base3DObject * myObject, string& myColliderTag, Base3DObject * otherObject, string& otherColliderTag)
{
	return;
}

inline void KeyColliderHandler(Base3DObject * myObject, string& myColliderTag, Base3DObject * otherObject, string& otherColliderTag)
{
	if(otherColliderTag == "playerCubeCollider")
	{
	}
	return;
}