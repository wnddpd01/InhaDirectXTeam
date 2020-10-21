#include "stdafx.h"
#include "cPyramid.h"


cPyramid::cPyramid()
{
	D3DXMatrixIdentity(&m_matR);
	m_vecPosition = { 0.0f, 0.0f, 0.0f };
}


cPyramid::~cPyramid()
{
}

void cPyramid::Setup(D3DCOLOR c, D3DXMATRIXA16& mat)
{
	m_matR = mat;
	ST_PC_VERTEX v;
	v.c = c;
	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1);
	m_vecVertex.push_back(v);
}

void cPyramid::SetPosition(D3DXVECTOR3& newPos)
{
	m_vecPosition = newPos;
}

void cPyramid::Render()
{
	D3DXMATRIXA16 matWorld, matS, matT;
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);
	D3DXMatrixTranslation(&matT, m_vecPosition.x, m_vecPosition.y, m_vecPosition.z);
	
	matWorld = matS * m_matR * matT;

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
