#pragma once
#include "Base3DObject.h"

class Base3DObject;

class ColliderPolygon
{
public:
	ColliderPolygon();
	virtual ~ColliderPolygon();

	virtual void Setup() = 0;
	void Update();
	
protected:
	LPD3DXMESH mMesh;
	
};