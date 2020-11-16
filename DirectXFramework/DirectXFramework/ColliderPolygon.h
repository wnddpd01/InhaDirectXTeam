#pragma once
#include "Base3DObject.h"

class Base3DObject;

enum class eColliderTag { NON_COLLIDER = 0, CUBE, SPHERE };

class ColliderPolygon
{
public:
	ColliderPolygon();
	~ColliderPolygon();

	void Setup(eObjTag objTag);
	void Update();
	
	void SetSphereCollider(float radius);

	void SetCubeCollider(float height, float width, float depth);

private:
	eColliderTag mColliderTag;
	LPD3DXMESH mMesh;
	
	float mCubeHeight;
	float mCubeWidth;
	float mCubeDepth;
	float mRadius;
};