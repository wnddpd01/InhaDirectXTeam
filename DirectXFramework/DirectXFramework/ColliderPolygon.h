#pragma once
#include "Base3DObject.h"

class Base3DObject;

class ColliderPolygon
{
public:
	ColliderPolygon();
	~ColliderPolygon();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	
protected:
	LPD3DXMESH mMesh;
	
};