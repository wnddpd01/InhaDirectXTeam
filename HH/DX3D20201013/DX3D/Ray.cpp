#include "stdafx.h"
#include "Ray.h"

#include "MapObject.h"


Ray::Ray()
{
	m_vStart = D3DXVECTOR3(0.f, 0.f, 0.f);
}


Ray::~Ray()
{
	
}

void Ray::SetDir(D3DXVECTOR3 dir)
{
	m_vDir = dir;
	D3DXVec3Normalize(&m_vDir, &m_vDir);
}

void Ray::SetStart(D3DXVECTOR3 start)
{
	m_vStart = start;
}

bool Ray::CheckCollisionMesh(MapObject& mapObj)
{
	//m_vDir.z = 1.f;
	D3DXVECTOR3 subtract = m_vStart - mapObj.GetPos();
	float b = 2.f * D3DXVec3Dot(&m_vDir, &subtract);
	float c = D3DXVec3Dot(&subtract, &subtract) - pow(mapObj.GetCollisionSize(),2);
	
	float discriminant = (b * b) - (4.0f * c);
	
	if (discriminant < 0.0f)
		return false;
	discriminant = sqrtf(discriminant);
	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;
	
	if ((s0 >= 0.0f) || (s1 >= 0.0f))
		return true;
	return false;
}

void Ray::CheckCollisionBoard(PickingMap& pickingMap)
{
	float u, v;
	for(size_t i = 0; i < pickingMap.GetVecMap().size(); i += 3)
	{
		if(D3DXIntersectTri(
			&pickingMap.GetVecMap()[i].p,
			&pickingMap.GetVecMap()[i+1].p,
			&pickingMap.GetVecMap()[i+2].p,
			&m_vStart,
			&m_vDir,
			&u,
			&v,
			nullptr))
		{
			pickingMap.SetWayPoint(
				(pickingMap.GetVecMap()[i].p + 
				(pickingMap.GetVecMap()[i + 1].p - pickingMap.GetVecMap()[i].p) * u +
				(pickingMap.GetVecMap()[i + 2].p - pickingMap.GetVecMap()[i].p) * v	)
			);
		}
	}
	
}