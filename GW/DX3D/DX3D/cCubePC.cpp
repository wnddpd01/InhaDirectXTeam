#include "stdafx.h"
#include "cCubePC.h"


cCubePC::cCubePC()
	:m_vDirection(0, 0, 1)
	, m_vPosition(0, 0, 0)
	, m_fRotY(0.0f)
	, tx(0.0f), ty(0.0f), tz(0.0f)
	, sx(0.5f), sy(0.5f), sz(0.5f), ry(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCubePC::~cCubePC()
{
}

void cCubePC::Setup()
{
	ST_PC_VERTEX v;
	//:front
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0F, 1.0F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0F, 1.0F);
	m_vecVertex.push_back(v);

	//:back
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0f, -1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0F, -1.0F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0F, -1.0F);
	m_vecVertex.push_back(v);

	//:left
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(-1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);

	//:right
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);


	//:top
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(-1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);

	//:bottom
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(-1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);



}

void cCubePC::Update(D3DXMATRIXA16* m_pWorld)
{
	

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matS, matR, matT;

	D3DXMatrixScaling(&matS,sx, sy, sz);

	
	D3DXMatrixRotationY(&matR, m_fRotY+ry);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	
	D3DXMatrixTranslation(&matT, m_vPosition.x+tx, m_vPosition.y+ty, m_vPosition.z+tz);
	m_matWorld = matS*matR*matT;
	
	m_matWorld *= *m_pWorld;


}

void cCubePC::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));

}

D3DXVECTOR3 & cCubePC::GetPosition()
{
	return m_vPosition;
}

void cCubePC::SetTrans(float x, float y, float z)
{
	tx = x;
	ty = y;
	tz = z;
}

void cCubePC::SetScling(float x, float y, float z)
{
	sx = x;
	sy = y;
	sz = z;
}

void cCubePC::SetRotation(float x)
{
	ry = x;
}
