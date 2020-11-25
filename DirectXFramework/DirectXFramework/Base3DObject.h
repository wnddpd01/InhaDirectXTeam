#pragma once
#include "BaseObject.h"
class ColliderCube;
class ColliderSphere;

enum class eObjTag { NON_OBJECT_TAG = 0, PLAYER_CHARACTER, STATIC_OBJECT, MOVE_OBJECT };
enum class eTypeTag { PLAYER_CHARACTER, DOOR , WALL, ITEM };
enum class eStateTag { NON_STATE = 0, DOOR_OPEN, DOOR_CLOSE };

class Base3DObject :
	public BaseObject
{
public:

protected:
	D3DXVECTOR3 mScale;
	D3DXVECTOR3 mPos;
	D3DXQUATERNION mRot;
	eObjTag mObjectTag;
	BOOL mbIsInteractable;
	eStateTag mStateTag;
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

	void SetScale(const D3DXVECTOR3& scale);
	D3DXVECTOR3 GetScale();
	void SetRot(const D3DXQUATERNION& rotation);
	D3DXQUATERNION GetRot();
	void SetPos(const D3DXVECTOR3& pos);
	D3DXVECTOR3 GetPos();

	void LoadColliderCube();
	void LoadColliderSphere();

	void SetIsInteractable(const BOOL isInteractable) { mbIsInteractable = isInteractable; }
	BOOL isInteractable() const { return mbIsInteractable; }


	function<void(Base3DObject *, string&, Base3DObject *, string&)> CollideHandle;
	function<void(string&)> DeleteInRoom;
	ColliderSphere* GetColliderSphere() { return mColliderSphere; }
	map<string, ColliderCube*>& GetColliderCube() { return mColliderCubeMap; }

};

