#pragma once
#include "stdafx.h"
#include "Base3DObject.h"
#include "Portal.h"

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

inline void PortalColliderHandler(Base3DObject * myObject, string& myColliderTag, Base3DObject * otherObject, string& otherColliderTag)
{
	Portal * portal = (Portal *)myObject;
	otherObject->SetPos(portal->GetExitPos());
}