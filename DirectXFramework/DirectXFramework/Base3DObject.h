#pragma once
#include "BaseObject.h"
class ColliderCube;
class ColliderSphere;

enum class eObjTag { NON_OBJECT_TAG = 0, PLAYER_CHARACTER, STATIC_OBJECT, MOVE_OBJECT };
enum class eShaderTag { NON_SHADER_TAG = 0, WALL, ITEM, OBJECT, CHARACTER};

class Base3DObject :
	public BaseObject
{
public:

protected:
	D3DXVECTOR3 mScale;
	D3DXVECTOR3 mPos;
	D3DXQUATERNION mRot;
	eObjTag mObjectTag;
	eShaderTag mShaderTag; 
	
	map<string,ColliderSphere*> mColliderSphereMap;
	map<string,ColliderCube*> mColliderCubeMap;

	

public:
	Base3DObject();
	virtual ~Base3DObject();

	void SetObjectTag();
	
	void AddColliderCube();
	void AddColliderSphere();
	void DeleteColliderCube(string key);
	void DeleteColliderSphere(string key);

	virtual void Setup();
	
	void SetPos(const D3DXVECTOR3& pos);
	D3DXVECTOR3 GetPos();
	void SetScale(const D3DXVECTOR3& scale);
	D3DXVECTOR3 GetScale();
};

