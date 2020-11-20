#pragma once
#include "BaseObject.h"
class ColliderCube;
class ColliderSphere;

enum class eObjTag { NON_OBJECT_TAG = 0, PLAYER_CHARACTER, STATIC_OBJECT, MOVE_OBJECT };
enum class eShaderTag { NON_SHADER = 0, PLAYER_CHARACTER, WALL, ITEM };

class Base3DObject :
	public BaseObject
{
public:

protected:
	D3DXVECTOR3 mScale;
	D3DXVECTOR3 mPos;
	D3DXQUATERNION mRot;
	eObjTag mObjectTag;
	
	ColliderSphere* mColliderSphere;
	map<string,ColliderCube*> mColliderCubeMap;
public:
	Base3DObject();
	virtual ~Base3DObject();

	void Render() override;

	void SetObjectTag();
	
	void AddColliderCube(string colliderName);
	void DeleteColliderCube(string colliderName);

	virtual void Update();
	virtual void Setup();

	void SetPos(const D3DXVECTOR3& pos);
	D3DXVECTOR3 GetPos();
	void SetScale(const D3DXVECTOR3& scale);
	D3DXVECTOR3 GetScale();
	void LoadColliderCube();
	void LoadColliderSphere();

	function<void(Base3DObject *, string&, Base3DObject *, string&)> CollideHandle;
	function<void(string&)> DeleteInRoom;
	ColliderSphere* GetColliderSphere() { return mColliderSphere; }
	map<string, ColliderCube*>& GetColliderCube() { return mColliderCubeMap; }

};

