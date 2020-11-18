#pragma once
#include "Base3DObject.h"

class Base3DObject;

class ColliderPolygon
{
public:
	ColliderPolygon();
	virtual ~ColliderPolygon();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	
	D3DXVECTOR3 * GetPosition() { return mPosition; }
	
	void SetPosition(D3DXVECTOR3 * pos) { mPosition = pos; }
	void SetRotation(D3DXQUATERNION * rot) { mRot = rot; }
	void SetScale(D3DXVECTOR3 * scale) { mScale = scale; }

	LPD3DXMESH& GetMash() { return mMesh; }
protected:
	LPD3DXMESH mMesh;
	D3DXVECTOR3 * mPosition;
	D3DXVECTOR3 * mScale;
	D3DXQUATERNION * mRot;
	D3DXMATRIXA16 m_matWorldTM;
	
};