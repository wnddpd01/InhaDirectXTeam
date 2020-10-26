#include "stdafx.h"
#include "cMainGame.h"

#include <iostream>

#include "cDeviceManager.h"
#include "cCamera.h"
#include "cCubePC.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cObjMap.h"	// << : 

#include "cAseLoader.h"
#include "cBigShip.h"
#include "cFrame.h"
#include "cRay.h"
#include "cHeightMap.h"
#include "cSkinnedMesh.h"

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL) 
	, m_pTexture(NULL)
	, m_pMap(NULL) 
	, m_pRootFrame(NULL) 
	, m_pMeshSphere(NULL)
	, m_pMeshTeapot(NULL)
	, m_pObjMesh(NULL)
	, m_pBigShip(NULL)
	, m_pSkinnedMesh(NULL)
{
}


cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC); 
	SafeDelete(m_pCamera); 
	SafeDelete(m_pGrid); 
	SafeDelete(m_pCubeMan); 
	SafeDelete(m_pMap);
	SafeDelete(m_pSkinnedMesh);
	SafeRelease(m_pTexture); 
	SafeRelease(m_pMeshSphere); 
	SafeRelease(m_pMeshTeapot); 
	SafeRelease(m_pObjMesh);

	for each(auto p in m_vecObjMtlTex)
		SafeRelease(p); 


	for each(auto p in m_vecGroup)
	{
		SafeRelease(p); 
	}
	m_vecGroup.clear(); 

	if(m_pRootFrame)
		m_pRootFrame->Destroy(); 
	g_pObjectManager->Destroy(); 

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	//m_pCubePC = new cCubePC; 
	//m_pCubePC->Setup(); 

	m_pCubeMan = new cCubeMan; 
	m_pCubeMan->Setup(); 

	m_pCamera = new cCamera; 
	m_pCamera->Setup(&m_pCubeMan->GetPosition()); 
	// &m_pCubePC->GetPosition());

	m_pGrid = new cGrid; 
	m_pGrid->Setup(); 

	//m_pBigShip = new cBigShip;
	//m_pBigShip->Setup();
	//{
	//	cAseLoader l; 
	//	m_pRootFrame = l.Load("woman/woman_01_all.ASE"); 
	//}

	//Setup_Texture(); 
	//Setup_Obj(); 
	Set_Light(); 
	Setup_HeightMap();
	Setup_MeshObject(); 
	//Setup_PickingObj();
	int numSphere = 30;
	for (int x = 0; x < numSphere; ++x)
	{
		for (int y = 0; y < numSphere; ++y)
		{
			for (int z = 0; z < numSphere; ++z)
			{
				ST_SPHERE s;
				s.fRadius = 0.8f;
				s.vCenter = D3DXVECTOR3(-numSphere * 0.5f + x + 0.5f, -numSphere * 0.5f + y + 0.5f, -numSphere * 0.5f + z + 0.5f);
				m_vecSphere.push_back(s);
			}
		}
	}
	m_pSkinnedMesh = new cSkinnedMesh;
	m_pSkinnedMesh->Setup("Zealot", "zealot.x");
}

void cMainGame::Update()
{
	//if (m_pCubePC)
	//	m_pCubePC->Update(); 

	if (m_pCubeMan)
		m_pCubeMan->Update(m_pMap); 

	if (m_pCamera)
		m_pCamera->Update(); 
	g_pTimeManager->Update();
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();
	
	//if (m_pRootFrame)
	//	m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), NULL); 
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112) , 
		1.0F, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render(); 

	//PickingObj_Render(); 
	//Mesh_Render();

	//if (m_pCubePC)
	//	m_pCubePC->Render(); 
//	Obj_Render(); 

	if (m_pCubeMan)
		m_pCubeMan->Render();

	if (m_pSkinnedMesh)
		SkinnedMesh_Render();

	/*g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMtlSphere);
	g_pD3DDevice->SetTexture(0, NULL);
	for (auto m_vec_sphere : m_vecSphere)
	{
		if (m_vec_sphere.isPicked == false)
		{
			D3DXMATRIXA16 matScale, matWorld;
			D3DXMatrixTranslation(&matScale, m_vec_sphere.vCenter.x, m_vec_sphere.vCenter.y, m_vec_sphere.vCenter.z);
			D3DXMatrixScaling(&matWorld, m_vec_sphere.fRadius, m_vec_sphere.fRadius, m_vec_sphere.fRadius);
			matWorld *= matScale;
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
			m_pMeshSphere->DrawSubset(0);
		}
	}*/
	if (m_pMap)
		m_pMap->Render();
	//Draw_Texture(); 
	/*{
		if (m_pRootFrame)
			m_pRootFrame->Render(); 
	}
*/
	if (m_pBigShip)
	{
		m_pBigShip->Render(0.01);
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static thread t1;
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam); 

	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			/*cRay r = cRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam)); 
			for (int i = 0; i < m_vecSphere.size(); i++)
			{
				m_vecSphere[i].isPicked = r.IsPicked(&m_vecSphere[i]); 
			}*/
		}
		break;
	case WM_RBUTTONDOWN:
		{
			static int n = 0;
			//m_pSkinnedMesh->SetAnimationIndex(++n);
			m_pSkinnedMesh->SetAnimationIndexBlend(rand() % 3);
			/*cRay r = cRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
			for (int i = 0; i < m_vecPlaneVertex.size(); i+= 3)
			{
				D3DXVECTOR3 v(0, 0, 0); 
				if (r.IntersectTri(
					m_vecPlaneVertex[i + 0].p,
					m_vecPlaneVertex[i + 1].p,
					m_vecPlaneVertex[i + 2].p,
					v
				))
				{
					m_vPickedPosition = v; 
				}
			}*/
			vector<D3DXVECTOR3> vecFrustum;

			D3DXVECTOR3 vecUnProjFrustrum[8];
			D3DXMATRIXA16 matProj, matView, matWorld;
			D3DVIEWPORT9 viewPort;
			g_pD3DDevice->GetViewport(&viewPort);
			g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
			g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
			vecFrustum.push_back(D3DXVECTOR3(0, viewPort.Height, 1.f));
			vecFrustum.push_back(D3DXVECTOR3(viewPort.Width, viewPort.Height, 1.f));
			vecFrustum.push_back(D3DXVECTOR3(viewPort.Width, 0, 1.f));
			vecFrustum.push_back(D3DXVECTOR3(0, 0, 1.f));

			vecFrustum.push_back(D3DXVECTOR3(0, viewPort.Height, 0));
			vecFrustum.push_back(D3DXVECTOR3(viewPort.Width, viewPort.Height, 0));
			vecFrustum.push_back(D3DXVECTOR3(viewPort.Width, 0, 0));
			vecFrustum.push_back(D3DXVECTOR3(0, 0, 0));
			D3DXMatrixIdentity(&matWorld);
			for (int i = 0; i < 8; ++i)
			{
				D3DXVec3Unproject(&vecUnProjFrustrum[i], &vecFrustum[i], &viewPort, &matProj, &matView, &matWorld);
			}

			D3DXPLANE frustrumPlane[6];
			D3DXPlaneFromPoints(&frustrumPlane[0], &vecUnProjFrustrum[0], &vecUnProjFrustrum[3], &vecUnProjFrustrum[7]); //��
			D3DXPlaneFromPoints(&frustrumPlane[1], &vecUnProjFrustrum[3], &vecUnProjFrustrum[0], &vecUnProjFrustrum[1]); //��
			D3DXPlaneFromPoints(&frustrumPlane[2], &vecUnProjFrustrum[6], &vecUnProjFrustrum[2], &vecUnProjFrustrum[1]); //��
			D3DXPlaneFromPoints(&frustrumPlane[3], &vecUnProjFrustrum[7], &vecUnProjFrustrum[6], &vecUnProjFrustrum[4]); //��
			D3DXPlaneFromPoints(&frustrumPlane[4], &vecUnProjFrustrum[7], &vecUnProjFrustrum[3], &vecUnProjFrustrum[2]); //
			D3DXPlaneFromPoints(&frustrumPlane[5], &vecUnProjFrustrum[4], &vecUnProjFrustrum[5], &vecUnProjFrustrum[0]);
			cHeightMap* height_map = (cHeightMap*)m_pMap;
			
			//height_map->BuildThreadCall(frustrumPlane);
			t1 = thread(&cHeightMap::BuildMesh, (cHeightMap*)m_pMap, frustrumPlane);
			t1.join();
		}
		break;
		case WM_CHAR :
		{
			if (wParam == 'k')
			{
				cHeightMap* height_map = (cHeightMap*)m_pMap;
				height_map->m_setNotDrawIdx.clear();
				//height_map->BuildMesh();
				for (int i = 0; i < m_vecSphere.size(); ++i)
				{
					m_vecSphere[i].isPicked = false;
				}
			}
		}
		break;
	}
}

void cMainGame::Set_Light()
{
	D3DLIGHT9	stLight; 
	ZeroMemory(&stLight, sizeof(D3DLIGHT9)); 
	stLight.Type = D3DLIGHT_DIRECTIONAL; 
	stLight.Ambient = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F); 
	stLight.Diffuse = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);
	stLight.Specular = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);

	D3DXVECTOR3  vDir(1.0f, -1.0f, 1.0f); 
	D3DXVec3Normalize(&vDir, &vDir); 
	stLight.Direction = vDir; 
	g_pD3DDevice->SetLight(0, &stLight); 
	g_pD3DDevice->LightEnable(0, true); 
}

void cMainGame::Setup_Texture()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, _T("../image/����.png"), &m_pTexture);
	ST_PT_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);


	// : ���ʿ� ������ ���
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(v);
}

void cMainGame::Draw_Texture()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false); 

	D3DXMATRIXA16 matWorld; 
	D3DXMatrixIdentity(&matWorld); 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	g_pD3DDevice->SetTexture(0, m_pTexture); 
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF); 
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX)); 
	g_pD3DDevice->SetTexture(0, NULL); 
}

void cMainGame::Setup_Obj()
{
	cObjLoader l; 
	l.Load(m_vecGroup, "obj", "map.obj"); 

	Load_Surface();
}

void cMainGame::Obj_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR; 
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f); 
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F); 

	matWorld = matS * matR; 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	for each(auto p in m_vecGroup)
	{
		p->Render(); 
	}
}

void cMainGame::Load_Surface()
{
	D3DXMATRIXA16 matWorld, matS, matR; 
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	matWorld = matS * matR;
	//m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);
}

void cMainGame::Setup_MeshObject()
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMeshTeapot, NULL); 
	D3DXCreateSphere(g_pD3DDevice, 0.5f , 10,10 , &m_pMeshSphere, NULL); 

	ZeroMemory(&m_stMtlTeapot, sizeof(D3DMATERIAL9)); 
	m_stMtlTeapot.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f); 
	m_stMtlTeapot.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	cObjLoader l; 
	m_pObjMesh = l.LoadMesh(m_vecObjMtlTex, "obj", "map.obj"); 
}										

void cMainGame::Mesh_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTexture(0, NULL); 

	D3DXMATRIXA16 matWorld, matS, matR; 
	{
		D3DXMatrixIdentity(&matS); 
		D3DXMatrixIdentity(&matR);
		matWorld = matS * matR; 
		D3DXMatrixTranslation(&matWorld, 0, 0, 10); 
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlTeapot); 
		m_pMeshTeapot->DrawSubset(0); 
	}
	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS * matR;
		//D3DXMatrixTranslation(&matWorld, 0, 0, 10);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlSphere);
		m_pMeshSphere->DrawSubset(0);
	}

	{
		D3DXMatrixIdentity(&matWorld); 
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);

		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
		matWorld = matS * matR;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		for( size_t i = 0 ; i < m_vecObjMtlTex.size() ; ++i)
		{
			g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial()); 
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture()); 
			m_pObjMesh->DrawSubset(i); 
		}
	}
}

void cMainGame::Setup_PickingObj()
{
	for (int i = 0; i <= 10; i++)
	{
		ST_SPHERE s; 
		s.fRadius = 0.5f; 
		s.vCenter = D3DXVECTOR3(0, 0, -10 + 2 * i); 
		m_vecSphere.push_back(s); 
	}

	ZeroMemory(&m_stMtlNone, sizeof(D3DMATERIAL9)); 
	m_stMtlNone.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f); 
	m_stMtlNone.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
	m_stMtlPicked.Ambient = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Diffuse = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Specular = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);

	ZeroMemory(&m_stMtlPlane, sizeof(D3DMATERIAL9));
	m_stMtlPlane.Ambient  = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Diffuse  = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	ST_PN_VERTEX v; 
	v.n = D3DXVECTOR3(0, 1, 0); 
	v.p = D3DXVECTOR3(-10, 0, -10); m_vecPlaneVertex.push_back(v); 
	v.p = D3DXVECTOR3(-10, 0,  10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3( 10, 0,  10); m_vecPlaneVertex.push_back(v);
	
	v.p = D3DXVECTOR3(-10, 0, -10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3( 10, 0,  10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3( 10, 0, -10); m_vecPlaneVertex.push_back(v);
}

void cMainGame::PickingObj_Render()
{
	D3DXMATRIXA16 matWorld; 

	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF); 
	g_pD3DDevice->SetMaterial(&m_stMtlPlane); 
	D3DXMatrixIdentity(&matWorld); 

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	g_pD3DDevice->SetTexture(0, 0); 
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2,
		&m_vecPlaneVertex[0], sizeof(ST_PN_VERTEX)); 

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		D3DXMatrixIdentity(&matWorld); 
		matWorld._41 = m_vecSphere[i].vCenter.x; 
		matWorld._42 = m_vecSphere[i].vCenter.y;
		matWorld._43 = m_vecSphere[i].vCenter.z;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
		g_pD3DDevice->SetMaterial(m_vecSphere[i].isPicked ?
			&m_stMtlPicked : &m_stMtlNone); 
		m_pMeshSphere->DrawSubset(0); 
	}

	g_pD3DDevice->SetMaterial(&m_stMtlNone); 
	D3DXMatrixTranslation(&matWorld,
		m_vPickedPosition.x,
		m_vPickedPosition.y,
		m_vPickedPosition.z); 

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	m_pMeshSphere->DrawSubset(0); 
}

void cMainGame::SkinnedMesh_Render()
{
	D3DXMATRIXA16 matS,matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, 100, 100, 100);
	matWorld *= matS;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	if(m_pSkinnedMesh)
	{
		m_pSkinnedMesh->Render(NULL);
	}
}

void cMainGame::Setup_HeightMap()
{
	cHeightMap * pMap = new cHeightMap;
	pMap->Setup("HeightMapData/", "HeightMap.raw", "terrain.jpg");
	m_pMap = pMap;
}


