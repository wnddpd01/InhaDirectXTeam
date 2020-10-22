#include "stdafx.h"
#include "MapObject.h"
#include "MapObjectCenter.h"

MapObject::MapObject(MapObjectCenter* pCenter)
{
	m_pObjCenter = pCenter;
	if(m_pObjCenter)
		m_pObjCenter->AddMapObj(this);
}


MapObject::~MapObject()
{
}

void MapObject::ToggleMtl()
{
	if (m_boolMtl)
	{
		m_boolMtl = false;
	}
	else
	{
		m_boolMtl = true;
	}
	
}

float MapObject::GetCollisionSize()
{
	return m_collisionSize;
}

D3DXVECTOR3 MapObject::GetPos()
{
	return m_pos;
}
