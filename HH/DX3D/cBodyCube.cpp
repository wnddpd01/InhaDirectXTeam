#include "stdafx.h"
#include "cBodyCube.h"

cBodyCube::cBodyCube(
	D3DXMATRIXA16* BodyWorld, 
	D3DXVECTOR3 Position2Body, 
	D3DXVECTOR3 Scale, 
	D3DXVECTOR3 moveCenter,
	bool moveReverse)
	: m_vPosition2Body(Position2Body)
	, m_fRotY(0.f)
	, m_moveReverse(moveReverse)
{
	m_matWorld = BodyWorld;
	D3DXMatrixScaling(&m_matScale, Scale.x, Scale.y, Scale.z);
	MoveCenter(moveCenter);
}


cBodyCube::~cBodyCube()
{

}

void cBodyCube::Setup()
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

void cBodyCube::Update()
{
	/*
	RECT rc;
	GetClientRect(g_hwnd, &rc);

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;
	*/
	
	// 회전
	static bool moveFront = true;

	if(m_move)
	{
		if (moveFront)
		{
			m_fRotY += 0.001f;
			if (m_fRotY > D3DX_PI / 3.f)
				moveFront = false;
		}
		else
		{
			m_fRotY -= 0.001f;
			if (m_fRotY < -D3DX_PI / 3.f)
				moveFront = true;
		}
	}
}

void cBodyCube::Render()
{
	D3DXMATRIXA16 matT;

	D3DXVECTOR3 matTemp;

	//회전
	D3DXMATRIXA16 matR;
	if(m_moveReverse)
		D3DXMatrixRotationX(&matR, -m_fRotY);
	else
		D3DXMatrixRotationX(&matR, m_fRotY);

	D3DXMatrixTranslation(&matT, m_vPosition2Body.x, m_vPosition2Body.y, m_vPosition2Body.z);
	
	D3DXMATRIXA16 matlocal = m_matScale * m_matChageCenter * matR * matT * (*m_matWorld);
	
	if(m_matWorld)
	{
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matlocal);
		g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0],
			sizeof(ST_PC_VERTEX));
	}

}

void cBodyCube::MoveCenter(D3DXVECTOR3 move)
{
	D3DXMatrixTranslation(&m_matChageCenter, move.x, move.y, move.z);
	m_vPosition2Body -= move;
}

void cBodyCube::OnMove(bool move)
{
	if(move)
		this->m_move = move;
	else
	{
		this->m_move = move;
		m_fRotY = 0.f;
	}
		
}
