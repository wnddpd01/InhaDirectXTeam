#include "stdafx.h"
#include "cSeoGroup.h"
#include "cGeomObject.h"


cSeoGroup::cSeoGroup()
{
}


cSeoGroup::~cSeoGroup()
{
	for (auto it : m_vecGeomObject)
	{
		SafeDelete(it);
	}
	for (auto it : m_vecMtlObject)
	{
		SafeDelete(it);
	}
}

void cSeoGroup::Setup()
{
	m_vecPTexture.resize(m_vecMtlObject.size());
	m_vecMtl.resize(m_vecMtlObject.size());
	if (g_pD3DDevice)
	{
		for (int i = 0; i < m_vecPTexture.size(); i++)
			D3DXCreateTextureFromFileA(g_pD3DDevice, m_vecMtlObject[i]->structDiffuse.Bitmap.c_str(), &m_vecPTexture[i]);

		
		for (int i = 0; i < m_vecMtl.size(); i++)
		{
			ZeroMemory(&m_vecMtl[i], sizeof(D3DMATERIAL9));

			m_vecMtl[i].Ambient = D3DXCOLOR(m_vecMtlObject[i]->Ambient.x,
				m_vecMtlObject[i]->Ambient.y, m_vecMtlObject[i]->Ambient.z,  1.f);
			m_vecMtl[i].Diffuse = D3DXCOLOR(m_vecMtlObject[i]->Diffuse.x,
				m_vecMtlObject[i]->Diffuse.y, m_vecMtlObject[i]->Diffuse.z, 1.f);
			m_vecMtl[i].Specular = D3DXCOLOR(m_vecMtlObject[i]->Specular.x,
				m_vecMtlObject[i]->Specular.y, m_vecMtlObject[i]->Specular.z, 1.f);
		}

		
	}
}

void cSeoGroup::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		
		for (auto vec : m_vecGeomObject)
		{
			if(vec->mtl_ref != NULL)
			{
				g_pD3DDevice->SetMaterial(&m_vecMtl[vec->mtl_ref - 1]);
				g_pD3DDevice->SetTexture(0, m_vecPTexture[vec->mtl_ref - 1]);
				vec->Render();
			}
			
		}
	}
}
