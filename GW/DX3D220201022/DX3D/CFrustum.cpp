#include "stdafx.h"
#include "CFrustum.h"


CFrustum::CFrustum()
{
}


CFrustum::~CFrustum()
{
}

void CFrustum::Setup_Object()
{

	
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 30, 10, &m_pMeshSphere, NULL);

	int objectnum = 20;	
	for(int i = -objectnum/2; i< objectnum/2; i++)
	{
		for (int j = -objectnum/2; j < objectnum/2; j++)
		{
			for (int k = -objectnum/2; k < objectnum/2; k++)
			{
				ST_SPHERE s;
				s.fRadius = 0.5f;
				s.vCenter = D3DXVECTOR3(j,  k, i);
				m_vecSphere.push_back(s);
			}
		}
	}
	ZeroMemory(&m_stMtlNone, sizeof(D3DMATERIAL9));
	m_stMtlNone.Ambient = D3DXCOLOR(5.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Diffuse = D3DXCOLOR(5.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Specular = D3DXCOLOR(5.7f, 0.7f, 0.0f, 1.0f);


	
}

void CFrustum::Render_Object()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matWorld;
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	D3DXMatrixIdentity(&matWorld);

	for(int i = 0; i<m_vecSphere.size(); i++)
	{
		D3DXMatrixIdentity(&matWorld);
		matWorld._41 = m_vecSphere[i].vCenter.x;
		matWorld._42 = m_vecSphere[i].vCenter.y;
		matWorld._43 = m_vecSphere[i].vCenter.z;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlNone);
		m_pMeshSphere->DrawSubset(0);
	}
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pMeshSphere->DrawSubset(0);
	
}

void CFrustum::Setup()
{
	D3DVIEWPORT9 ViewPort;
	D3DXMATRIXA16 Proj;
	
	g_pD3DDevice->GetViewport(&ViewPort);


	


	
	
}


void CFrustum::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:

		break;
	case WM_RBUTTONDOWN:

		break;
	}


	
}

/*
D3DXVec3Unproject(vertex1, vertex2, NULL, proj, view, NULL); 공간상 뷰에 위치에서 바라보는 절두체의 면을 생성

D3DXPlaneFromPoints(OUT 면 plane , v1, v2, v3);

D3DXPlaneDotCoord(plane, vC); 값이 양수인가 음수인가 판별 (앞에있는가 뒤에있는가) 이걸로 그릴지 말지 판별
*/
