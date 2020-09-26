#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cKids.h"

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	,m_pCamera(NULL)
	,m_pGrid(NULL)
	,m_pKids(NULL)
{
}

cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pKids);
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{

	m_pCubePC = new cCubePC;
	m_pCubePC->Setup();

	m_pKids = new cKids;
	m_pKids->Setup();
	
	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubePC->GetPosition());

	m_pGrid = new cGrid;
	m_pGrid->Setup();
	
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false); //Α¶Έν ²τ±β
}

void cMainGame::Update()
{
	/*if (m_pCubePC)
		m_pCubePC->Update();*/

	if (m_pKids)
		m_pKids->Update();
	
	if (m_pCamera)
		m_pCamera->Update();
	
}

void cMainGame::Render()
{
	
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(65, 65, 65), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();

	//if (m_pCubePC)
	//	m_pCubePC->Render();

	if (m_pKids)
		m_pKids->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
	


void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
