#include "stdafx.h"
#include "cMainGame.h"

#include "cCamera.h"
#include "cCube.h"
#include "cGrid.h"
#include "cCharactor.h"

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCharactor(NULL)
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


	m_pCharactor = new cCharactor;
	m_pCharactor->Setup();

	
	// 基内靛
	//m_pCubePC = new cCube;
	//m_pCubePC->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCharactor->GetPosition());

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	
}

void cMainGame::Update()
{
	//UpdateMove();

	// 基
	if (m_pCubePC)
		m_pCubePC->Update();

	if (m_pCharactor)
		m_pCharactor->Update();

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

	//if (m_pCubePC)
	//	m_pCubePC->Render();
	
	if (m_pCharactor)
		m_pCharactor->Render();


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
