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
#include "cObjMap.h"
#include "cAseLoader.h"
#include "Sphere.h"
#include "MapObjectCenter.h"
#include "Ray.h"
#include "HeightMap.h"
#include "cFrame.h"         // << : 

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL)
	, m_pTexture(NULL)
	, m_pMap(NULL)
	, m_pRootFrame(NULL)
	, m_pRootFrame2(NULL)
	, m_pMeshTeapot(NULL)
	, m_pMeshSphere(NULL)
	, m_pObjMesh(NULL)
	, m_pGirlMesh(NULL)
	, m_MapObjCenter(NULL)
	, m_pRay(NULL)
	, m_pHeightMap(NULL)
{
}


cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC); 
	SafeDelete(m_pCamera); 
	SafeDelete(m_pGrid); 
	SafeDelete(m_pCubeMan); 
	SafeDelete(m_pMap); 
	SafeRelease(m_pTexture);
	SafeRelease(m_pMeshTeapot);
	SafeRelease(m_pMeshSphere);
	SafeRelease(m_pObjMesh);
	SafeRelease(m_pGirlMesh);
	SafeDelete(m_MapObjCenter);
	SafeDelete(m_pRay);
	SafeDelete(m_pHeightMap);
	for each(auto p in m_vecGirlMtlTex)
	{
		SafeRelease(p);
	}
	
	for each(auto p in m_vecObjMtlTex)
	{
		SafeRelease(p);
	}
	
	for each(auto p in m_vecGroup)
	{
		SafeRelease(p); 
	}
	m_vecGroup.clear();

	m_pRootFrame->Destroy();
	m_pRootFrame2->Destroy();
	g_pObjectManager->Destroy(); 

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	
	m_pCubePC = new cCubePC; 
	m_pCubePC->Setup(); 

	m_pHeightMap = new HeightMap;
	m_pHeightMap->Setup(L"../HeightMapData/HeightMap.raw");
	
	m_pCubeMan = new cCubeMan; 
	m_pCubeMan->Setup(m_pHeightMap); 

	m_pCamera = new cCamera; 
	m_pCamera->Setup(&m_pCubeMan->GetPosition()); 
	// &m_pCubePC->GetPosition());

	m_pGrid = new cGrid; 
	m_pGrid->Setup(); 

	
	//m_pRay = new Ray;
	
	{
		cAseLoader l;
		m_pRootFrame = l.Load("woman/woman_01_all.ASE");
		//m_pRootFrame2 = l.Load("woman/woman_01_all.ASE");
		//m_pRootFrame2->BuildIB();
	}

	/*
	m_MapObjCenter = new MapObjectCenter;

	for(int i = -8; i <= 8 ; i += 2)
	{
		new Sphere(m_MapObjCenter, D3DXVECTOR3(0,0, i));
	}

	m_MapObjCenter->Setup();

	//Setup_Texture(); 
	//Setup_Obj(); 
	

	m_PickingMap.SetupBoard();

	//Setup_MeshObject();
	*/
	
	Set_Light();


	//��Ʈ ����
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 45;
	fd.Width = 28;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	//strcpy_s(fd.FaceName, "�ü�ü");   //�۲� ��Ÿ��
	AddFontResource(L"umberto.ttf");
	strcpy((char*)fd.FaceName, "umberto");

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
	
}

void cMainGame::Update()
{
	//if (m_pCubePC)
	//	m_pCubePC->Update(); 

	if (m_pCubeMan)
		m_pCubeMan->Update(); 

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pRootFrame)
		m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), NULL);

	//if (m_pRootFrame2)
	//	m_pRootFrame2->Update(m_pRootFrame2->GetKeyFrame(), NULL);
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112) , 
		1.0F, 0);

	g_pD3DDevice->BeginScene();
	static chrono::system_clock::time_point lastTime;
	lastTime = std::chrono::system_clock::now();
	
//	m_PickingMap.RenderBoard();
	m_pHeightMap->Render();
	
	if (m_pGrid)
		m_pGrid->Render();

	//m_MapObjCenter->Render();
	
	//if (m_pCubePC)
	//	m_pCubePC->Render(); 
	//

	if (m_pCubeMan)
		m_pCubeMan->Render(); 

	//Draw_Texture(); 

	{
		for(int i = 0; i < 1; i++)
		{
			//Mesh_Render();
			
			//Obj_Render();
			
			//if (m_pRootFrame)
			//	m_pRootFrame->Render();
			
			//if (m_pRootFrame2)
			//	m_pRootFrame2->RenderIndex();
		}
		
		
	}

	chrono::duration<double> time = chrono::system_clock::now() - lastTime;
	
	if (m_pFont)
	{
		RECT rc;
		SetRect(&rc, 100, 100, 103, 103);
		char szTemp[1024];
		sprintf(szTemp, "FPS = %f", (1 / time.count()));
		m_pFont->DrawTextA(nullptr,
			szTemp,
			strlen(szTemp),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 0, 0));
	}

	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	/*
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		if(!(wParam & MK_SHIFT))
		{
			m_pRay->SetStart(m_pCamera->GetvEye());
			m_pRay->SetDir(LParam2Vec3(lParam));

			for (auto i : m_MapObjCenter->GetVecMapObj())
			{
				if (m_pRay->CheckCollisionMesh(*i))
				{
					i->ToggleMtl();
					break;
				}
			}
		}
	}
	break;
		
	case WM_RBUTTONDOWN:
	{
		if (!(wParam & MK_SHIFT))
		{
			m_pRay->SetStart(m_pCamera->GetvEye());
			m_pRay->SetDir(LParam2Vec3(lParam));
			m_pRay->CheckCollisionBoard(m_PickingMap);
			m_pRootFrame->SetDir(m_PickingMap.GetWayPoint());
			m_pCubeMan->SetLookat(m_PickingMap.GetWayPoint());
		}
	}
	break;
	}
	*/
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
	m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);
}

D3DXVECTOR3 cMainGame::LParam2Vec3(LPARAM lParam)
{
	D3DXVECTOR3 temp(LOWORD(lParam), HIWORD(lParam),1.f);
	D3DXVECTOR3 result;
	D3DVIEWPORT9 viewport;
	g_pD3DDevice->GetViewport(&viewport);
	D3DXMATRIXA16 matProj, matView, matWorld;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixIdentity(&matWorld);
	
	D3DXVec3Unproject(&result, &temp, &viewport, &matProj,
		&matView, &matWorld);

	result = result - m_pCamera->GetvEye();
	
	return result;
}

void cMainGame::Setup_MeshObject()
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMeshTeapot, NULL);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10,10, &m_pMeshSphere, NULL);
	ZeroMemory(&m_stMtlTeapot, sizeof(D3DMATERIAL9));
	m_stMtlTeapot.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.f);
	m_stMtlTeapot.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.f);
	m_stMtlTeapot.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.f);
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.f);

	cObjLoader l;
	m_pObjMesh = l.LoadMesh(m_vecObjMtlTex, "obj", "map.obj");

	
}

void cMainGame::Mesh_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTexture(0, NULL);
	
	D3DXMATRIXA16 matWorld, matS, matR;
	/*
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
	*/
	{

		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		
		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);

		matWorld = matS * matR;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		for (size_t i = 0; i < m_vecObjMtlTex.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
			m_pObjMesh->DrawSubset(i);
		}
	}
}


