#pragma once
#include "Base3DObject.h"

class Base3DObject;

class ColliderPolygon
{
public:
	ColliderPolygon();
	virtual ~ColliderPolygon();

	virtual void Setup() = 0;
	void Update(D3DXVECTOR3 pos);
	D3DXVECTOR3& GetPosition() { return mPosition; }
protected:
	LPD3DXMESH mMesh;
	D3DXVECTOR3 mPosition;
};