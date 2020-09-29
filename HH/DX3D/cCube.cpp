#include "stdafx.h"
#include "cCube.h"


cCube::cCube()
	: m_vDirection(0,0,1)
	, m_vPosition(0,0,0)
	, m_fRotY(0.f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCube::~cCube()
{
}

void cCube::Setup()
{
	ST_PC_VERTEX v;
	// 앞면
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	// 뒤
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);

	// 왼
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);

	//오른
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);

	//위
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);

	//아래
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	
}

void cCube::Update()
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.001f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.001f;
	}
	
	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition += (m_vDirection*0.001f);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition -= (m_vDirection*0.001f);
	}

	RECT rc;
	GetClientRect(g_hwnd, &rc);

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;
	
}

void cCube::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
	
}

D3DXVECTOR3& cCube::GetPosition()
{
	return this->m_vPosition;
}
