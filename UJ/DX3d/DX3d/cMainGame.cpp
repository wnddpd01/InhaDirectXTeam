#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cPyramid.h"
#include "cGrid.h"
#include "cCharacter.h"
#include "cCubeMan.h"

cMainGame::cMainGame()
	:m_pCubePc(NULL),
	m_pCamera(NULL),
	m_pGrid(NULL),
	m_pCharacter(NULL),
	m_pCubeMan(NULL)

{
}

cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePc);
	SafeDelete(m_pCharacter);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	//m_pCubePc = new cCubePC;
	//m_pCubePc->Setup();
	m_pCharacter = new cCharacter;
	m_pCharacter->Setup();

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();
	
	m_pCamera = new cCamera;
	m_pCamera->Setup(&(m_pCubeMan->GetPosition()));

	m_pGrid = new cGrid;
	m_pGrid->Setup();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	/*{
		
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

		v.p = D3DXVECTOR3(0, 0, 0);
		v.t = D3DXVECTOR2(0, 0);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(1, 1, 0);
		v.t = D3DXVECTOR2(1, 0);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(1, 0, 0);
		v.t = D3DXVECTOR2(1, 1);
		m_vecVertex.push_back(v);
	}*/
	Set_Light();
}

void cMainGame::Update()
{
	//if (m_pCharacter != NULL)
	//{
	//	m_pCharacter->KeyInput();
	//	m_pCharacter->Update();
	//}
	if (m_pCubeMan != NULL)
		m_pCubeMan->Update();
	if (m_pCamera)
		m_pCamera->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(47, 121, 112), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	if (m_pCubeMan != NULL)
		m_pCubeMan->Render();
	
	if(m_pGrid != NULL)
		m_pGrid->Render();
	//if (m_pCharacter != NULL)
	//	m_pCharacter->Render();
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::Set_Light()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3 vDir = { 1.0f, -1.0f, 1.0f };
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, TRUE);
}

