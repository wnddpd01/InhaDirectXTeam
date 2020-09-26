#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cPyramid.h"
#include "cGrid.h"
#include "cCharacter.h"

cMainGame::cMainGame()
	:m_pCubePc(NULL),
	m_pCamera(NULL),
	m_pGrid(NULL),
	m_pCharacter(NULL)
{
}

cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePc);
	SafeDelete(m_pCharacter);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	//m_pCubePc = new cCubePC;
	//m_pCubePc->Setup();
	m_pCharacter = new cCharacter;
	m_pCharacter->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&(m_pCharacter->GetPosition()));

	m_pGrid = new cGrid;
	m_pGrid->Setup();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Update()
{
	if (m_pCharacter != NULL)
	{
		m_pCharacter->KeyInput();
		m_pCharacter->Update();
	}
	if (m_pCamera)
		m_pCamera->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(47, 121, 112), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	if(m_pGrid != NULL)
		m_pGrid->Render();
	if (m_pCharacter != NULL)
		m_pCharacter->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
