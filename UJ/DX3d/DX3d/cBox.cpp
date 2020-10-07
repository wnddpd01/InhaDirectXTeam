#include "stdafx.h"
#include "cBox.h"


cBox::cBox()
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
}


cBox::~cBox()
{
}

void cBox::Render()
{
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, m_pTextrue);
	D3DXMATRIXA16 matWorld;
	//D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matWorld, 0.1, 0.1, 0.1);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	cCubePNT::Render();
	g_pD3DDevice->SetTexture(0, NULL);
}
