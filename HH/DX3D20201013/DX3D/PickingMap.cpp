#include "stdafx.h"
#include "PickingMap.h"


PickingMap::PickingMap()
{
	m_Point.p = { 0.f ,0.f ,0.f };
}


PickingMap::~PickingMap()
{
}

void PickingMap::SetupBoard()
{
	int nNumHalfTile = 10;
	int fInterval = 5;
	ST_PNT_VERTEX GR;
	
	for (int i = -nNumHalfTile; i < nNumHalfTile; i += fInterval)
	{
		for (int j = -nNumHalfTile; j < nNumHalfTile; j += fInterval)
		{
			GR.p = D3DXVECTOR3(j, 0, i);  m_vecMap.push_back(GR);
			GR.p = D3DXVECTOR3(j + fInterval, 0, i + fInterval); m_vecMap.push_back(GR);
			GR.p = D3DXVECTOR3(j + fInterval, 0, i); m_vecMap.push_back(GR);

			GR.p = D3DXVECTOR3(j, 0, i); m_vecMap.push_back(GR);
			GR.p = D3DXVECTOR3(j, 0, i + fInterval); m_vecMap.push_back(GR);
			GR.p = D3DXVECTOR3(j + fInterval, 0, i + fInterval); m_vecMap.push_back(GR);
		}
	}
	
	D3DXCreateBox(g_pD3DDevice, 0.2f, 0.2f, 0.2f, &BoxMesh, NULL);
}

void PickingMap::RenderBoard()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecMap.size() / 3,
		&m_vecMap[0],
		sizeof(ST_PNT_VERTEX));


	D3DXMATRIXA16 matP;
	D3DXMatrixTranslation(&matP, m_Point.p.x, m_Point.p.y, m_Point.p.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matP);
	BoxMesh->DrawSubset(0);
}

vector<ST_PNT_VERTEX>& PickingMap::GetVecMap()
{
	return m_vecMap;
}

D3DXVECTOR3 PickingMap::GetWayPoint()
{
	return m_Point.p;
}

void PickingMap::SetWayPoint(D3DXVECTOR3 pos)
{
	m_Point.p = pos;
}
