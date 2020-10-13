#include "stdafx.h"
#include "cMainGame.h"

#include <iostream>


#include "cCamera.h"
#include "cCube.h"
#include "cGrid.h"
#include "cCharactor.h"
#include "cCubeMan.h"
#include "CasteljouMove.h"
#include "ObjParser.h"
#include "tObjLoader.h"
#include "tGroup.h"
#include "cSeoLoader.h"
#include "cGeomObject.h"


cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCharactor(NULL)
	, m_pCubeMan(NULL)
	, m_pBox(NULL)
{
	Fov = D3DX_PI / 4.f;
	vEye = D3DXVECTOR3(5, 5, -5.f);
	vLookAt = D3DXVECTOR3(0, 0, 0);
	vUp = D3DXVECTOR3(0, 1, 0);
	CameraDist = 5.f;
}


cMainGame::~cMainGame()
{
	//基
	
	SafeDelete(m_pCubePC);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	//SafeDelete(m_pTexture);
	SafeDelete(m_pBox);

	for each(auto p in m_vecGroup)
	{
		SafeRelease(p);
	}

	m_vecGroup.clear();
	g_pObjectManager->Destroy();
	
	g_pDeviceManager->Destroy();
	//ddd



	/*
	for(auto i : m_vecObject)
		delete i;
	g_pDeviceManager->Destroy();
	*/
}

void cMainGame::Setup()
{

		 
	/*
	m_vecObject.push_back(new Object(CUBE));
	m_vecObject[0]->SetUp();

	m_vecObject.push_back(new Object(GRID));
	m_vecObject[1]->SetUp();

	
	*/
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	Setup_Obj();

	
	//郴 某腐磐
	//m_pCharactor = new cCharactor;
	//m_pCharactor->Setup();

	
	
	// 基内靛
	//m_pCubePC = new cCube;
	//m_pCubePC->Setup();

	//菩胶 备己
	{
		m_vecHex.resize(6);
		m_vecHex[0].p = D3DXVECTOR3(10.f, 0.f, 0.f);
		m_vecHex[1].p = D3DXVECTOR3(4.f, 0.f, -8.f);
		m_vecHex[2].p = D3DXVECTOR3(-4.f, 0.f, -8.f);
		m_vecHex[3].p = D3DXVECTOR3(-10.f, 0.f, 0.f);
		m_vecHex[4].p = D3DXVECTOR3(-4.f, 0.f, 8.f);
		m_vecHex[5].p = D3DXVECTOR3(4.f, 0.f, 8.f);
		
		CheckPoint cPoint;
		cPoint.SplinePoint.push_back(D3DXVECTOR3(10.f, 0.f, 0.f));
		cPoint.SplinePoint.push_back(D3DXVECTOR3(4.f, 0.f, -8.f));
		cPoint.SplinePoint.push_back(D3DXVECTOR3(-4.f, 0.f, -8.f));
		catelMove.AddCheckPoint(cPoint);
		cPoint.SplinePoint.clear();

		cPoint.SplinePoint.push_back(D3DXVECTOR3(-4.f, 0.f, -8.f));
		cPoint.SplinePoint.push_back(D3DXVECTOR3(-10.f, 0.f, 0.f));
		cPoint.SplinePoint.push_back(D3DXVECTOR3(-4.f, 0.f, 8.f));
		catelMove.AddCheckPoint(cPoint);
		cPoint.SplinePoint.clear();

		cPoint.SplinePoint.push_back(D3DXVECTOR3(-4.f, 0.f, 8.f));
		cPoint.SplinePoint.push_back(D3DXVECTOR3(4.f, 0.f, 8.f));
		cPoint.SplinePoint.push_back(D3DXVECTOR3(10.f, 0.f, 0.f));
		catelMove.AddCheckPoint(cPoint);
		cPoint.SplinePoint.clear();

		catelMove.CalculPath();
	}
	
		
	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	//m_pBox = new ObjParser;
	//m_pBox->Setup("box.obj");

	
	//for texture
	/*
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"texture\\brick_05.png", &m_pTexture);
		
		ST_PT_VERTEX v;
		v.p = D3DXVECTOR3(0, 0, 0);
		v.t = D3DXVECTOR2(0, 1);
		m_vecVertex.push_back(v);
		
		v.p = D3DXVECTOR3(0, 1, 0);
		v.t = D3DXVECTOR2(0, 0);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(1, 1, 0);
		v.t = D3DXVECTOR2(1, 0);
		m_vecVertex.push_back(v);
	}
	*/
	Set_Light();
	
}

void cMainGame::Update()
{
	//UpdateMove();

	//if (m_pCharactor)
	//	m_pCharactor->Update();
	
	// 基
	//if (m_pCubePC)
	//	m_pCubePC->Update();
	
	if (m_pCubeMan)
		m_pCubeMan->objUpdate(m_vecSurfGroup);
	/*
	if (m_pCubeMan)
	{
		static int ind = 0;
		if(m_pCubeMan->MoveToUpdate(catelMove.m_vecMovePoints[ind]))
		{
			ind++;
			if (ind == catelMove.m_vecMovePoints.size())
				ind = 0;
		}
	}
	*/
	if (m_pCamera)
		m_pCamera->Update();
}

void cMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hwnd, &rc);

	/*
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, Fov, rc.right / (float)rc.bottom,
		1.f, 1000.f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	*/
	
	if (g_pD3DDevice)
		g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(47, 121, 112), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	//DrawLine();
	//DrawTriangle();
	/*
	m_vecObject[0]->Render();
	m_vecObject[1]->Render();
	*/
	// 基内靛
 	if (m_pGrid)
		m_pGrid->Render();

	Obj_Render();
	
	//if (m_pCubePC)
	//	m_pCubePC->Render();
	
	//if (m_pCharactor)
	//	m_pCharactor->Render();

	if (m_pCubeMan)
		m_pCubeMan->Render();
	//Draw_Textrue();

	catelMove.Render();

	
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, m_vecHex.size() -1, &m_vecHex[0],
		sizeof(ST_PC_VERTEX));

	
	if (m_pBox)
		m_pBox->Render();

	
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(0, 0, 0, 0);



}

void cMainGame::SetupLine()
{
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(255, 0,0);
	v.p = D3DXVECTOR3(0, 2, 0);
	m_vecLineVertex.push_back(v);

	v.p = D3DXVECTOR3(0, -2, 0);
	m_vecLineVertex.push_back(v);
	
}

void cMainGame::DrawLine()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecLineVertex.size() / 2, &m_vecLineVertex[0],
		sizeof(ST_PC_VERTEX));
}

void cMainGame::SetupTriangle()
{
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(rand() % 256 , rand() % 256, rand() % 256);
	
	v.p = D3DXVECTOR3(-1.f , -1.f ,0.f);
	m_vecTriangleVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, 1.f, 0.f);
	m_vecTriangleVertex.push_back(v);
	
	v.p = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_vecTriangleVertex.push_back(v);
}

void cMainGame::DrawTriangle()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	
	D3DXVECTOR3 vPosition = D3DXVECTOR3(0, 0, 5);
	D3DXMatrixTranslation(&matWorld, vPosition.x, vPosition.y, vPosition.z);
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecTriangleVertex.size() / 3,
		&m_vecTriangleVertex[0],
		sizeof(ST_PC_VERTEX));
	
}


void cMainGame::UpdateMove()
{
	if (GetKeyState('W') & 0x8000)
	{
		m_vecObject[0]->MovePositon(0.001f);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_vecObject[0]->MovePositon(-0.001f);
	}

	if (GetKeyState('A') & 0x8000)
	{
		m_vecObject[0]->Rotate(-0.0001f);
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_vecObject[0]->Rotate(0.0001f);
	}
}


void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT lastMousePos;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		switch (wParam)
		{
			case MK_LBUTTON:
			D3DXMATRIXA16 matRo;
			D3DXMatrixRotationY(&matRo, (LOWORD(lParam) - lastMousePos.x)*0.002f);
			D3DXVec3TransformNormal(&vEye, &vEye, &matRo);
			break;
		}
		lastMousePos = { LOWORD(lParam), HIWORD(lParam) };
		break;
		
	case WM_MOUSEWHEEL:
		if ((Fov >= 0.1f) && (Fov <= (D3DX_PI / 2.f)))
			Fov += (GET_WHEEL_DELTA_WPARAM(wParam) * 0.001f);
		else if (Fov < 0.1f)
			Fov = 0.1f;
		else if (Fov > (D3DX_PI / 2.f))
			Fov = (D3DX_PI / 2.f);

		break;
	}
}

void cMainGame::WndProcTeacher(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::Set_Light()
{
	D3DLIGHT9	stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.f);

	D3DXVECTOR3		vDir(1.f, -1.f, 1.f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	
}

void cMainGame::Draw_Textrue()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3,
		&m_vecVertex[0], sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetTexture(0, NULL);
}

void cMainGame::Setup_Obj()
{
	tObjLoader l;
	l.Load(m_vecGroup, "obj", "map.obj");
	l.Load(m_vecSurfGroup, "obj", "map_surface.obj");

	cSeoLoader sl;
	sl.Load(m_vecGeomObject, "woman", "woman_01_all.ASE");

	for (auto name : m_vecGeomObject)
		std::cout << name->m_nodeName << std::endl;
}

void cMainGame::Obj_Render()
{

	D3DXMATRIXA16 matWorld, matS, matR;
	/*
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.f);

	matWorld = matS * matR;
	*/
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	/*
	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
	*/
	for each(auto p in m_vecGeomObject)
	{
		p->Render();
	}
	
	//D3DXIntersectTri(v1, v2, v3, rayPos, rayDir, u, v, f);
}

