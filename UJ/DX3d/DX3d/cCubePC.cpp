#include "stdafx.h"
#include "cCubePC.h"


cCubePC::cCubePC() : m_vDirection(0, 0, 1), m_vPosition(0, 0, 0), m_fRotY(0.0f), m_fRotX(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}



cCubePC::~cCubePC()
{
}

void cCubePC::Setup(float width, float height, float depth, D3DXCOLOR color)
{
	m_vScale = { width, height, depth };
	width = height = depth = 1;
	ST_PC_VERTEX v;
	//front
	v.c = color;
	v.p = D3DXVECTOR3(-width * 0.5, -height * 0.5, -depth * 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-width * 0.5, height * 0.5, -depth * 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, height * 0.5, -depth* 0.5f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-width * 0.5, -height * 0.5f, -depth * 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, height * 0.5f, -depth * 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, -height * 0.5f, -depth * 0.5f);
	m_vecVertex.push_back(v);

	//back
	v.p = D3DXVECTOR3(-width * 0.5, -height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, height * 0.5f, depth * 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-width * 0.5, height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-width * 0.5, -height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, -height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, height * 0.5f, depth * 0.5f);
	m_vecVertex.push_back(v);

	//left
	v.p = D3DXVECTOR3(-width * 0.5, -height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-width * 0.5, height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-width * 0.5, height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-width * 0.5, -height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-width * 0.5, height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-width * 0.5, -height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);

	//right
	v.p = D3DXVECTOR3(width * 0.5, -height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, height * 0.5f, depth * 0.5f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(width * 0.5, -height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, height * 0.5f, depth * 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, -height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);

	//top
	v.p = D3DXVECTOR3(-width * 0.5, height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-width * 0.5, height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, height * 0.5f, depth * 0.5f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-width * 0.5, height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, height * 0.5f, depth * 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);

	//bottom
	v.p = D3DXVECTOR3(-width * 0.5, -height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-width * 0.5, -height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, -height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-width * 0.5, -height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, -height * 0.5f, -depth* 0.5f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(width * 0.5, -height * 0.5f, depth* 0.5f);
	m_vecVertex.push_back(v);

	Update();
}

void cCubePC::Setup(D3DXVECTOR3& size, D3DXCOLOR color)
{
	Setup(size.x, size.y, size.z, color);
}

void cCubePC::Update()
{
	D3DXMATRIXA16 matS, matR, matT, matRX;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	
	D3DXMatrixRotationX(&matRX, m_fRotX);
	D3DXMatrixRotationY(&matR, m_fRotY);
	matR = matRX * matR;
	
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matR * matT;
}

void cCubePC::Update(D3DXMATRIXA16& mat)
{
	Update();
	m_matWorld *= mat;
}

void cCubePC::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

void cCubePC::KeyCheck()
{
	if (GetKeyState('A') & 0x8000)
		m_fRotY -= 0.1f;
	if (GetKeyState('D') & 0x8000)
		m_fRotY += 0.1f;

	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition += (m_vDirection * 0.1f);
	}
	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition -= (m_vDirection * 0.1f);
	}
}


D3DXVECTOR3& cCubePC::GetPosition()
{
	return m_vPosition;
}

float cCubePC::GetRotY()
{
	return m_fRotY;
}

float cCubePC::GetRotX()
{
	return m_fRotX;
}

D3DXVECTOR3 cCubePC::GetDir()
{
	return m_vDirection;
}

D3DXVECTOR3 cCubePC::GetScale()
{
	return m_vScale;
}


void cCubePC::SetPosition(D3DXVECTOR3 pos)
{
	m_vPosition = pos;
}

void cCubePC::SetRotY(float rotY)
{
	m_fRotY = rotY;
}

void cCubePC::SetRotX(float rotX)
{
	m_fRotX = rotX;
}

void cCubePC::SetVertexY(float y)
{
	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		m_vecVertex[i].p.y += y;
	}
}
