#include "stdafx.h"
#include "ColliderPolygon.h"

ColliderPolygon::ColliderPolygon()
	: mMesh(nullptr)
{

}

ColliderPolygon::~ColliderPolygon()
{
	SAFE_DELETE(mMesh);
}
