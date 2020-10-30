#include "stdafx.h"
#include "CFrustum.h"


CFrustum::CFrustum()
{
}


CFrustum::~CFrustum()
{
}

void CFrustum::Setup()
{
	// : near
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, 1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, 1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, -1, 0));


	// : far
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, 1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, 1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, -1, 1));


	m_vecPlane.resize(6);
	m_vecWorldVertex.resize(8);
	
	

}

void CFrustum::Update()
{
	D3DXMATRIXA16 matView, matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	for(size_t i = 0; i<m_vecProjVertex.size(); i++)
	{
		D3DXVec3Unproject(&m_vecWorldVertex[i], &m_vecProjVertex[i], NULL, &matProj, &matView, NULL);
	}
	/*
		시계방향
		0123앞
		4567뒤
	 */

	// : near
	D3DXPlaneFromPoints(&m_vecPlane[0], &m_vecWorldVertex[0], &m_vecWorldVertex[1], &m_vecWorldVertex[2]);

	// : far
	D3DXPlaneFromPoints(&m_vecPlane[1], &m_vecWorldVertex[6], &m_vecWorldVertex[5], &m_vecWorldVertex[4]);

	// : top
	D3DXPlaneFromPoints(&m_vecPlane[2], &m_vecWorldVertex[1], &m_vecWorldVertex[5], &m_vecWorldVertex[6]);

	// : bottom
	D3DXPlaneFromPoints(&m_vecPlane[3], &m_vecWorldVertex[0], &m_vecWorldVertex[3], &m_vecWorldVertex[7]);

	// : left
	D3DXPlaneFromPoints(&m_vecPlane[4], &m_vecWorldVertex[1], &m_vecWorldVertex[0], &m_vecWorldVertex[4]);

	// : right
	D3DXPlaneFromPoints(&m_vecPlane[5], &m_vecWorldVertex[2], &m_vecWorldVertex[6], &m_vecWorldVertex[7]);

	
}

bool CFrustum::IsIn(ST_SPHERE* pSphere)
{
	for each(D3DXPLANE p in m_vecPlane)
	{
		if (D3DXPlaneDotCoord(&p, &pSphere->vCenter) > pSphere->fRadius)
			return false;
	}

	return true;
}

//void CFrustum::Setup_Object()
//{
//
//	
//	D3DXCreateSphere(g_pD3DDevice, 0.5f, 30, 10, &m_pMeshSphere, NULL);
//
//	int objectnum = 20;	
//	for(int i = -objectnum/2; i< objectnum/2; i++)
//	{
//		for (int j = -objectnum/2; j < objectnum/2; j++)
//		{
//			for (int k = -objectnum/2; k < objectnum/2; k++)
//			{
//				ST_SPHERE s;
//				s.fRadius = 0.5f;
//				s.vCenter = D3DXVECTOR3(j,  k, i);
//				m_vecSphere.push_back(s);
//			}
//		}
//	}
//	ZeroMemory(&m_stMtlNone, sizeof(D3DMATERIAL9));
//	m_stMtlNone.Ambient = D3DXCOLOR(5.7f, 0.7f, 0.0f, 1.0f);
//	m_stMtlNone.Diffuse = D3DXCOLOR(5.7f, 0.7f, 0.0f, 1.0f);
//	m_stMtlNone.Specular = D3DXCOLOR(5.7f, 0.7f, 0.0f, 1.0f);
//
//
//	
//}
//
//void CFrustum::Render_Object()
//{
//	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
//	D3DXMATRIXA16 matWorld;
//	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
//	D3DXMatrixIdentity(&matWorld);
//
//	for(int i = 0; i<m_vecSphere.size(); i++)
//	{
//		D3DXMatrixIdentity(&matWorld);
//		matWorld._41 = m_vecSphere[i].vCenter.x;
//		matWorld._42 = m_vecSphere[i].vCenter.y;
//		matWorld._43 = m_vecSphere[i].vCenter.z;
//		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
//		g_pD3DDevice->SetMaterial(&m_stMtlNone);
//		m_pMeshSphere->DrawSubset(0);
//	}
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
//	m_pMeshSphere->DrawSubset(0);
//	
//}
//
//void CFrustum::Setup()
//{
//	D3DVIEWPORT9 ViewPort;
//	D3DXMATRIXA16 Proj;
//	
//	g_pD3DDevice->GetViewport(&ViewPort);
//
//
//	
//
//
//	
//	
//}
//
//
//void CFrustum::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_LBUTTONDOWN:
//
//		break;
//	case WM_RBUTTONDOWN:
//
//		break;
//	}
//
//
//	
//}

/*
D3DXVec3Unproject(vertex1, vertex2, NULL, proj, view, NULL); 공간상 뷰에 위치에서 바라보는 절두체의 면을 생성

D3DXPlaneFromPoints(OUT 면 plane , v1, v2, v3);

D3DXPlaneDotCoord(plane, vC); 값이 양수인가 음수인가 판별 (앞에있는가 뒤에있는가) 이걸로 그릴지 말지 판별
*/
