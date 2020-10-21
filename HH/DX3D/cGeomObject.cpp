#include "stdafx.h"
#include "cGeomObject.h"


cGeomObject::cGeomObject()
	:mtl_ref(NULL)
{
}


cGeomObject::~cGeomObject()
{
}

cGeomObject * cGeomObject::GetInstance(std::string nodeName)
{
	if (m_nodeName == nodeName)
		return this;
	else
		return nullptr;
}

void cGeomObject::Render()
{
	
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_geoMesh.vecVertex.size() / 3,
		&m_geoMesh.vecVertex[0],
		sizeof(ST_PNT_VERTEX));
}

void cGeomObject::InverseAllMesh()
{
	D3DXMATRIXA16 matInvTm;
	D3DXMatrixInverse(&matInvTm, NULL, &m_geoNodeTm.tmMat);

	for (int i = 0; i < m_geoMesh.vecVertex.size(); i++)
		D3DXVec3TransformCoord(&m_geoMesh.vecVertex[i].p,
			&m_geoMesh.vecVertex[i].p,
			&matInvTm);
}

