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

void Base3DObject::SetPos(const D3DXVECTOR3& pos)
{
	mPos = pos;	
}

D3DXVECTOR3 Base3DObject::GetPos()
{
	return mPos;
}

void Base3DObject::SetScale(const D3DXVECTOR3& scale)
{
	mScale = scale;
}

D3DXVECTOR3 Base3DObject::GetScale()
{
	return mScale;
}
