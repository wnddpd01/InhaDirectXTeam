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
<<<<<<< HEAD
	eObjTag mObjectTag;
	ColliderBox* mColliderBox;
=======

public:
	Base3DObject();
	~Base3DObject();

	
	void SetPos(const D3DXVECTOR3& pos);
	D3DXVECTOR3 GetPos();

	void SetScale(const D3DXVECTOR3& scale);
	D3DXVECTOR3 GetScale();
	
>>>>>>> 59f2883c7af54656128b3913df272da3941c73e8
};

