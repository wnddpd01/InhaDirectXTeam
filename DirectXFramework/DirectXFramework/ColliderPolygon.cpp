#include "stdafx.h"
#include "ColliderPolygon.h"

ColliderPolygon::ColliderPolygon()
	: mMesh(nullptr)
	, mPosition(0,0,0)
{

}

ColliderPolygon::~ColliderPolygon()
{
	SAFE_DELETE(mMesh);
}

void ColliderPolygon::Update(D3DXVECTOR3 pos)
{
	mPosition = pos;
}
