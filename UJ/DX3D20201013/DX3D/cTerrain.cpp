#include "stdafx.h"
#include "cTerrain.h"
#include "cTextureManager.h"
#include <iostream>


cTerrain::cTerrain() : m_texture(NULL)
{
}


cTerrain::~cTerrain()
{
}

cTerrain * cTerrain::LoadFromRawFile(char* fileDir)
{
	cTerrain * new_terrain = new cTerrain;
	float cell_length = 1.f;
	UINT i = 0;
	UINT j = 0;
	CHAR c;
	float mapHeight[257][257];
	
	FILE *fp = fopen(fileDir, "rb");
	while(( c = fgetc(fp)) != EOF)
	{
		new_terrain->m_arrMapVertex[256 - i][j++] = (BYTE)c * 0.1f;
		if(j == 257)
		{
			i++;
			j = 0;
		}
	}
	for (int i_ = 0; i_ < 255; ++i_)
	{
		for (int j_ = 0; j_ < 255; ++j_)
		{
			ST_PNT_VERTEX v;
			v.n = { 0, 1, 0 };
			
			v.t = { (float)j_ / 255, 1.0f - (float)i_ / 255 };
			v.p = D3DXVECTOR3(j_ * cell_length, new_terrain->m_arrMapVertex[i_][j_] - new_terrain->m_arrMapVertex[0][0], i_ * cell_length);
			new_terrain->m_vecVertex.push_back(v);
			
			v.t = { float(j_) / 255, 1.0f - float(i_ + 1) / 255 };
			v.p = D3DXVECTOR3(j_ * cell_length, new_terrain->m_arrMapVertex[i_ + 1][j_] - new_terrain->m_arrMapVertex[0][0], (i_ + 1) * cell_length);
			new_terrain->m_vecVertex.push_back(v);
			
			v.t = { float(j_ + 1) / 255, 1.0f - float(i_ + 1) / 255 };
			v.p = D3DXVECTOR3((j_ + 1) * cell_length, new_terrain->m_arrMapVertex[i_ + 1][j_ + 1] - new_terrain->m_arrMapVertex[0][0], (i_ + 1) * cell_length);
			new_terrain->m_vecVertex.push_back(v);


			v.t = { (float)j_ / 255, 1.0f - (float)i_ / 255 };
			v.p = D3DXVECTOR3(j_ * cell_length, new_terrain->m_arrMapVertex[i_][j_] - new_terrain->m_arrMapVertex[0][0], i_ * cell_length);
			new_terrain->m_vecVertex.push_back(v);

			v.t = { float(j_ + 1) / 255, 1.0f - float(i_ + 1) / 255 };
			v.p = D3DXVECTOR3((j_ + 1) * cell_length, new_terrain->m_arrMapVertex[i_ + 1][j_ + 1] - new_terrain->m_arrMapVertex[0][0], (i_ + 1) * cell_length);
			new_terrain->m_vecVertex.push_back(v);;

			v.t = { float(j_ + 1) / 255, 1.0f - float(i_) / 255 };
			v.p = D3DXVECTOR3((j_ + 1) * cell_length, new_terrain->m_arrMapVertex[i_][j_ + 1] - new_terrain->m_arrMapVertex[0][0], (i_) * cell_length);
			new_terrain->m_vecVertex.push_back(v);
		}
	}

	D3DXCreateMeshFVF(new_terrain->m_vecVertex.size() / 3, new_terrain->m_vecVertex.size(), D3DXMESH_MANAGED |D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDevice, &new_terrain->m_mesh);
	
	
	return new_terrain;
}

void cTerrain::SetTextureFromFile(char* fileDir)
{
	m_texture = g_pTextureManager->GetTexture(fileDir);
}

void cTerrain::Render()
{
	D3DXMATRIXA16 matWorld;

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_texture);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PNT_VERTEX));
}
