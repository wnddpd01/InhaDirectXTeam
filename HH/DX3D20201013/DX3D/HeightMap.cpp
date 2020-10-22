#include "stdafx.h"
#include "HeightMap.h"
#include <fstream>
#include <iostream>


HeightMap::HeightMap()
{

}


HeightMap::~HeightMap()
{
	for (auto i : m_vecVertex)
		SafeDelete(i);
}

void HeightMap::LoadRaw(wstring rawFileName)
{
	ifstream fin;
	fin.open(rawFileName, ios_base::binary | ios_base::in);
	if(fin.is_open())
	{
		while (true)
		{
			ST_PNT_VERTEX* newVer = new ST_PNT_VERTEX;
			newVer->p.y = fin.get() / 5.f;
			if (fin.eof())
				break;
			m_vecVertex.push_back(newVer);
		}	
	}
	else
	{
		//파일 오픈 실패
	}
	float offset = m_vecVertex[0]->p.y;
	for(auto i : m_vecVertex)
	{
		i->p.y -= offset;
	}
}


void HeightMap::Setup(wstring rawFileName)
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.f);

	D3DXCreateTextureFromFile(g_pD3DDevice, _T("../HeightMapData/terrain.jpg"), &m_pTexture);
	
	LoadRaw(rawFileName);
	m_height = m_width = sqrtl(m_vecVertex.size());

	int nNumTile = m_height-1;
	int fInterval = 1;

	for (int i = 0; i < nNumTile + 1; i++)
	{
		for (int j = 0; j < nNumTile + 1; j++)
		{
			m_vecVertex[i*(nNumTile + 1) + j]->p.x = j;
			m_vecVertex[i*(nNumTile + 1) + j]->p.z = i;
			
			m_vecVertex[i*(nNumTile + 1) + j]->t.y = i / (float)(nNumTile + 1);
			m_vecVertex[i*(nNumTile + 1) + j]->t.x = j / (float)(nNumTile + 1);
			
		}
	}
	for (int i = 0; i < nNumTile; i++)
	{
		for (int j = 0; j < nNumTile; j++)
		{
			D3DXVECTOR3 a = m_vecVertex[i*(nNumTile + 1) + j]->p - m_vecVertex[(i + 1) *(nNumTile + 1) + j]->p;
			D3DXVECTOR3 b = m_vecVertex[i*(nNumTile + 1) + j]->p - m_vecVertex[i*(nNumTile + 1) + (j + 1)]->p;
			D3DXVECTOR3 n;
			D3DXVec3Cross(&n, &a, &b);
			
			m_vecDrawVertex.push_back(*m_vecVertex[i*(nNumTile + 1) + j]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;
			m_vecDrawVertex.push_back(*m_vecVertex[(i + 1) *(nNumTile + 1) + j]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;
			m_vecDrawVertex.push_back(*m_vecVertex[i*(nNumTile + 1) + (j + 1)]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;

			a = m_vecVertex[(i + 1)*(nNumTile + 1) + (j + 1)]->p - m_vecVertex[i*(nNumTile + 1) + (j + 1)]->p;
			b = m_vecVertex[(i + 1)*(nNumTile + 1) + (j + 1)]->p - m_vecVertex[(i + 1)*(nNumTile + 1) + j]->p;
			D3DXVec3Cross(&n, &a, &b);
			
			m_vecDrawVertex.push_back(*m_vecVertex[(i + 1)*(nNumTile + 1) + (j + 1)]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;
			m_vecDrawVertex.push_back(*m_vecVertex[i*(nNumTile + 1) + (j + 1)]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;
			m_vecDrawVertex.push_back(*m_vecVertex[(i + 1)*(nNumTile + 1) + j]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;
		}
	}
	/*
	for (auto i : m_vecVertex)
		SafeDelete(i);
	m_vecVertex.clear();
	*/
}


void HeightMap::Render()
{
	if(g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		D3DXMATRIXA16 matI;
		D3DXMatrixIdentity(&matI);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->SetMaterial(&m_stMtl);
		g_pD3DDevice->SetTexture(0, m_pTexture);

		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecDrawVertex.size() / 3,
			&m_vecDrawVertex[0],
			sizeof(ST_PNT_VERTEX));

		g_pD3DDevice->SetTexture(0, NULL);
	}
}

float HeightMap::GetHeight(D3DXVECTOR3 pos)
{
	int nNumTile = m_height - 1;
	int fInterval = 1;

	if (pos.x < 0 || pos.z < 0 || pos.z > m_height || pos.x > m_height)
		return -1;

	if(((pos.x - (int)pos.x) < 0.5f) || ((pos.z - (int)pos.z) < 0.5f))
	{
		D3DXVECTOR3 p = m_vecVertex[(int)pos.z*(nNumTile + 1) + (int)pos.x]->p;
		D3DXVECTOR3 u = m_vecVertex[(int)(pos.z + 1)*(nNumTile + 1) + (int)pos.x]->p - m_vecVertex[(int)pos.z*(nNumTile + 1) + (int)pos.x]->p;
		D3DXVECTOR3 v = m_vecVertex[(int)pos.z*(nNumTile + 1) + (int)(pos.x + 1)]->p - m_vecVertex[(int)pos.z*(nNumTile + 1) + (int)pos.x]->p;

		float lerpZ, lerpX;
		
		float t = (pos.z - floor(pos.z));
		lerpX = 0.f - (0.f*t) + (u.y*t);
		t = (pos.x - floor(pos.x));
		lerpZ = 0.f - (0.f*t) + (v.y*t);
		return p.y + lerpZ + lerpX;
	}
	else
	{
		D3DXVECTOR3 p = m_vecVertex[(int)(pos.z + 1) *(nNumTile + 1) + (int)(pos.x + 1)]->p;
		D3DXVECTOR3 u = m_vecVertex[(int)pos.z*(nNumTile + 1) + (int)(pos.x + 1)]->p - m_vecVertex[(int)(pos.z + 1) *(nNumTile + 1) + (int)(pos.x + 1)]->p;
		D3DXVECTOR3 v = m_vecVertex[(int)(pos.z + 1) *(nNumTile + 1) + (int)pos.x]->p - m_vecVertex[(int)(pos.z + 1) *(nNumTile + 1) + (int)(pos.x + 1)]->p;

		float lerpZ, lerpX;
		
		float t = 1.f - (pos.z - floor(pos.z));
		lerpX = 0.f - (0.f*t) + (u.y*t);
		t = 1.f - (pos.x - floor(pos.x));
		lerpZ = 0.f - (0.f*t) + (v.y*t);
		return p.y + lerpZ + lerpX;
	}
}


