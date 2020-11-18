#pragma once
#include "Base3DObject.h"

class Base3DObject;

class ColliderPolygon
{
public:
	ColliderPolygon();
	virtual ~ColliderPolygon();

	virtual void Setup() = 0;
	D3DXVECTOR3 * GetPosition() { return mPosition; }
	void SetPosition(D3DXVECTOR3 * pos) { mPosition = pos; }

protected:
	LPD3DXMESH mMesh;
	D3DXVECTOR3 * mPosition;
};