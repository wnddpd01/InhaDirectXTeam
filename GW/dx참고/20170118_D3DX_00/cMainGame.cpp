#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cHSMyCharacter.h"
#include "cGrid.h"
#include "cCharacterController.h"
#include "cWall.h"
#include "cObjMap.h"
#include "cObjLoader.h"
#include "cGeometry.h"
#include "cAseLoader.h"


cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCharacterController(NULL)
	, m_pMapSerface(NULL)
{
}


cMainGame::~cMainGame()
{
	SAFE_RELEASE(m_pFont);
	g_pTextureManager->Destroy();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destory();
}

void cMainGame::Setup()
{
	/////////////////////////////////

	D3DXMATRIXA16 mat, matS, matR;
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2);
	mat = matS * matR;
	cObjLoader* load = new cObjLoader;
	g_pAutoReleasePool->AddObject(load);
	load->Load("obj/Map.obj", &mat, m_vecMap);

	cObjMap* pObjMap = new cObjMap;
	g_pAutoReleasePool->AddObject(pObjMap);
	pObjMap->Load("obj/map_surface.obj", &mat);
	m_pMapSerface = pObjMap;

	////////////////////////////////


	srand(time(NULL));
	rand();

	m_pCharacterController = new cCharacterController;
	g_pAutoReleasePool->AddObject(m_pCharacterController);
	m_pCharacterController->Setup("ase/woman_01_all.ASE");
	m_pCharacterController->SetMap(m_pMapSerface);

	m_pCamera = new cCamera;
	g_pAutoReleasePool->AddObject(m_pCamera);
	m_pCamera->Setup();

	//m_pGrid = new cGrid;
	//g_pAutoReleasePool->AddObject(m_pGrid);
	//m_pGrid->Setup();

	AddFontResource("umberto.ttf");

	D3DXCreateFont(g_pD3DDevice, 96, 48, FW_NORMAL, NULL, true, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, NULL, FF_DONTCARE, "umberto", &m_pFont);

	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	//g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	D3DLIGHT9 light;

	light = InitDirectionalLight(&D3DXVECTOR3(1.0f, -1.0f, 0.0f), &WHITE);
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

}

void cMainGame::Update()
{
	/////////////////////////////
	//m_pMap->Update();
	////////////////////////////

	g_pTimeManager->Update();

	if (GetKeyState('4') & 0x8000)
	{
		BOOL b;
		g_pD3DDevice->GetLightEnable(0, &b);
		g_pD3DDevice->LightEnable(0, !b);
	}


	if (m_pCharacterController)
		m_pCharacterController->Update();

	if (m_pCamera)
		m_pCamera->Update(m_pCharacterController->GetPosition());
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	//pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	if (m_pCharacterController)
		m_pCharacterController->Render();

	for each (auto p in m_vecMap)
	{
		p->Render();
	}

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	//if (m_pGrid)
	//	m_pGrid->Render();

	/*RECT rc;
	SetRect(&rc, 10, 10, 1000, 1000);

	m_pFont->DrawText(NULL, "SeriousMode", strlen("SeriousMode"), &rc,
		DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));*/

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(0, 0, 0, 0);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
