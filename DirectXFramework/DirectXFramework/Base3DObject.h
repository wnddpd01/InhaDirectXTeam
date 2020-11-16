#pragma once
#include "BaseObject.h"
class ColliderBox;

enum class eObjTag { NON_OBJECT_TAG = 0, PLAYER_CHARACTER, STATIC_OBJECT, MOVE_OBJECT };

class Base3DObject :
	public BaseObject
{
public:
	Base3DObject();
	~Base3DObject();

	void SetObjectTag();
	void Setup();
	
protected:
	D3DXVECTOR3 mScale;
	D3DXVECTOR3 mPos;
	D3DXQUATERNION mRot;
	eObjTag mObjectTag;
	ColliderBox* mColliderBox;
};

