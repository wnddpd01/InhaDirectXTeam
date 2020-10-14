#include "stdafx.h"
#include "cGrid.h"
#include "cPyramid.h"

cGrid::cGrid()
{
}


cGrid::~cGrid()
{
	for each(auto p in m_vecPyramid)
	{
		SafeDelete(p); 
	}

	m_vecPyramid.clear(); 
}

void cGrid::Setup(int nNumHalfTile, float fInterval)
{
	float fMax = nNumHalfTile * fInterval; 
	float fMin = -fMax; 
	ST_PC_VERTEX v; 
	for (int i = 1; i <= nNumHalfTile; ++i)
	{
		if (i % 5 == 0)
			v.c = D3DCOLOR_XRGB(255, 255, 255); 
		else 
			v.c = D3DCOLOR_XRGB(128,128,128);

		v.p = D3DXVECTOR3(fMin, 0, i*fInterval); m_vecVertex.push_back(v); 
		v.p = D3DXVECTOR3(fMax, 0, i*fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i*fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i*fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i*fInterval , 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval, 0, fMax); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i*fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval, 0, fMax); m_vecVertex.push_back(v);
	}
	{
		ST_PN_VERTEX v;

		for (int x = fMin; x < fMax; x += 1.0f)
		{
			for (int z = fMin; z < fMax; z += 1.0f)
			{
				v.n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				v.p = D3DXVECTOR3(x, -0.01f, z); 
				m_vecBoardVertex.push_back(v);
				v.p = D3DXVECTOR3(x, -0.01f, z + 1.0f); 
				m_vecBoardVertex.push_back(v);
				v.p = D3DXVECTOR3(x + 1.0f, -0.01f, z); 
				m_vecBoardVertex.push_back(v);

				v.p = D3DXVECTOR3(x + 1.0f, -0.01f, z + 1.0f); 
				m_vecBoardVertex.push_back(v);
				v.p = D3DXVECTOR3(x + 1.0f, -0.01f, z); 
				m_vecBoardVertex.push_back(v);
				v.p = D3DXVECTOR3(x, -0.01f, z + 1.0f); 
				m_vecBoardVertex.push_back(v);
			}
		}
	}

	v.c = D3DCOLOR_XRGB(255, 0, 0); 
	v.p = D3DXVECTOR3(fMin, 0, 0); m_vecVertex.push_back(v); 
	v.p = D3DXVECTOR3(fMax, 0, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0,255, 0);
	v.p = D3DXVECTOR3(0,fMin, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0,fMax, 0); m_vecVertex.push_back(v);


	v.c = D3DCOLOR_XRGB(0,0,255);
	v.p = D3DXVECTOR3(0, 0, fMin); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); m_vecVertex.push_back(v);

	cPyramid* pPyramid = NULL; 
	D3DXMATRIXA16 matR; 

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0F); 
	pPyramid->Setup(D3DCOLOR_XRGB(255, 0, 0), matR); 
	m_vecPyramid.push_back(pPyramid); 

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI );
	pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 0 , 255), matR);
	m_vecPyramid.push_back(pPyramid);
}

void cGrid::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false); 
	D3DXMATRIXA16 matI; 
	D3DXMatrixIdentity(&matI); 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI); 
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(ST_PC_VERTEX));

	for each (auto p in m_vecPyramid)
		p->Render(); 

}
