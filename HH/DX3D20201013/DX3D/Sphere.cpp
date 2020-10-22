#include "stdafx.h"
#include "Sphere.h"
#include "MapObjectCenter.h"


Sphere::Sphere(MapObjectCenter* p, D3DXVECTOR3 pos)
	: MapObject(p)
{
	m_pos = pos;
	m_collisionSize = 0.5f;
}

Sphere::~Sphere()
{
}

void Sphere::Setup()
{

	D3DXCreateSphere(g_pD3DDevice, m_collisionSize, 10, 10, &m_pMesh, NULL);
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_mtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_mtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	
	m_boolMtl = true;
	ZeroMemory(&m_arrMtl[0], sizeof(D3DMATERIAL9));
	m_arrMtl[0].Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_arrMtl[0].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_arrMtl[0].Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	ZeroMemory(&m_arrMtl[1], sizeof(D3DMATERIAL9));
	m_arrMtl[1].Ambient = D3DXCOLOR(0.7f, 0.0f, 0.7f, 1.0f);
	m_arrMtl[1].Diffuse = D3DXCOLOR(0.7f, 0.0f, 0.7f, 1.0f);
	m_arrMtl[1].Specular = D3DXCOLOR(0.7f, 0.0f, 0.7f, 1.0f);
}

void Sphere::Update()
{
	
}

void Sphere::Render()
{

	D3DXMATRIXA16 matT, matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	matWorld *= matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	if(m_boolMtl)
		g_pD3DDevice->SetMaterial(&m_arrMtl[0]);
	else
		g_pD3DDevice->SetMaterial(&m_arrMtl[1]);
	m_pMesh->DrawSubset(0);
}
