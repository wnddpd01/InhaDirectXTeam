#pragma once
#include "BaseObject.h"
class Base3DObject :
	public BaseObject
{
protected:
	D3DXVECTOR3 mScale;
	D3DXVECTOR3 mPos;
	D3DXQUATERNION mRot;

public:
	Base3DObject();
	~Base3DObject();
};

