#include "stdafx.h"
#include "cGrid.h"

#include "cPyramid.h"


cGrid::cGrid()
{
}


cGrid::~cGrid()
{
	for (cPyramid* m_vec_pyramid : m_vecPyramid)
	{
		SafeDelete(m_vec_pyramid);
	}
	m_vecPyramid.clear();
}

void cGrid::Setup(int nNumHalfTime, float fInterval)
{
	float fMax = nNumHalfTime * fInterval;
	float fMin = -fMax;
	ST_PN_VERTEX v;
	v.n = D3DXVECTOR3{ 0, 1,0 };
	//for (int i = 1; i <= nNumHalfTime; i++)
	//{
	//	/*if (i % 5 == 0)
	//		v.c = D3DCOLOR_XRGB(255, 255, 255);
	//	else
	//		v.c = D3DCOLOR_XRGB(128, 128, 128);*/
	//	v.p = D3DXVECTOR3(fMin, 0, i*fInterval);
	//	m_vecVertex.push_back(v);
	//	v.p = D3DXVECTOR3(fMax, 0, i*fInterval);
	//	m_vecVertex.push_back(v);

	//	v.p = D3DXVECTOR3(fMin, 0, -i*fInterval);
	//	m_vecVertex.push_back(v);
	//	v.p = D3DXVECTOR3(fMax, 0, -i*fInterval);
	//	m_vecVertex.push_back(v);

	//	v.p = D3DXVECTOR3(i*fInterval, 0, fMin);
	//	m_vecVertex.push_back(v);
	//	v.p = D3DXVECTOR3(i*fInterval, 0, fMax);
	//	m_vecVertex.push_back(v);

	//	v.p = D3DXVECTOR3(-i*fInterval, 0, fMin);
	//	m_vecVertex.push_back(v);
	//	v.p = D3DXVECTOR3(-i*fInterval, 0, fMax);
	//	m_vecVertex.push_back(v);
	//}
	////v.c = D3DCOLOR_XRGB(255, 0, 0);
	//v.p = D3DXVECTOR3(fMin, 0, 0);
	//m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(fMax, 0, 0);
	//m_vecVertex.push_back(v);


	////v.c = D3DCOLOR_XRGB(0, 255, 0);
	//v.p = D3DXVECTOR3(0, fMin, 0);
	//m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(0, fMax, 0);
	//m_vecVertex.push_back(v);

	////v.c = D3DCOLOR_XRGB(0, 0, 255);
	//v.p = D3DXVECTOR3(0, 0, fMin);
	//m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(0, 0, fMax);
	//m_vecVertex.push_back(v);

	//m_vecVertex.clear();
	//
	//v.p = D3DXVECTOR3(fMin, 0, fMax);
	//m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(fMax, 0, fMax);
	//m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(fMin, 0, fMin);
	//m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(fMin, 0, fMin);
	//m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(fMax, 0, fMax);
	//m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(fMax, 0, fMin);
	//m_vecVertex.push_back(v);

	//for (int i = 0; i < m_vecVertex.size(); i++)
	//{
	//	m_vecVertex[i].n = D3DXVECTOR3(0, 1, 0);
	//}

	for (int i = 0; i < nNumHalfTime * 2; ++i)
	{
		for (int j = 0; j < nNumHalfTime * 2; ++j)
		{
			v.p = D3DXVECTOR3{ fMin + j * fInterval, 0, fMax - i * fInterval };
			m_vecVertex.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval + fInterval, 0, fMax - i * fInterval };
			m_vecVertex.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval, 0, fMax - i * fInterval - fInterval};
			m_vecVertex.push_back(v);

			v.p = D3DXVECTOR3{ fMin + j * fInterval, 0, fMax - i * fInterval - fInterval };
			m_vecVertex.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval + fInterval, 0, fMax - i * fInterval };
			m_vecVertex.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval + fInterval, 0, fMax - i * fInterval - fInterval };
			m_vecVertex.push_back(v);
		}
	}
	
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.2f, 0.5f, 0.4f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	
	cPyramid* pPyramid = NULL;
	D3DXMATRIXA16 matR;

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(255, 0, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 0, 255), matR);
	m_vecPyramid.push_back(pPyramid);
}

void cGrid::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PN_VERTEX));

	for (auto m_vec_pyramid : m_vecPyramid)
	{
		m_vec_pyramid->Render();
	}
}
