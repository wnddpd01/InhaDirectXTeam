#include "stdafx.h"
#include "cBPath.h"
#include "cCubeMan.h"
#include "cPyramid.h"

cBPath::cBPath()
{
}


cBPath::~cBPath()
{
	
}


void cBPath::Setup()
{

	ST_PN_VERTEX v;
	v.n = D3DXVECTOR3(0, 1, 0);
	v.p = D3DXVECTOR3(-2, 0, 1.5);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, 2.5);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, 2.5);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(2, 0, 1.5);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(2, 0, 1.5);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(2, 0, -1.5);
	m_vecVertex.push_back(v);	
	v.p = D3DXVECTOR3(2, 0, -1.5);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, -2.5);
	m_vecVertex.push_back(v);	
	v.p = D3DXVECTOR3(0, 0, -2.5);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-2, 0, -1.5);
	m_vecVertex.push_back(v);	
	v.p = D3DXVECTOR3(-2, 0, -1.5);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-2, 0, 1.5);
	m_vecVertex.push_back(v);

	
	for (int i = 0; i < 6; i++)
	{
		for (float t = 0.0f; t < 2.0f; t += 0.1f)
		{

		}
	}
	//D3DXMatrixLookAtLH(eye at up)   //vector 지정방향으로 회전

}



void cBPath::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);

	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(ST_PN_VERTEX));
	
}

void cBPath::resurlt()
{


	
}
