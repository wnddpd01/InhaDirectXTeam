#include "stdafx.h"
#include "Base3DObject.h"


Base3DObject::Base3DObject()
	: mScale(0,0,0)
	, mPos(0,0,0)
{
	D3DXQuaternionIdentity(&mRot);
}


Base3DObject::~Base3DObject()
{
}
