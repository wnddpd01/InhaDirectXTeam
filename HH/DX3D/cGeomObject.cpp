#include "stdafx.h"
#include "cGeomObject.h"


cGeomObject::cGeomObject()
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
