#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cLight.h"
#include "cBPath.h"

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	,m_pCamera(NULL)
	,m_pGrid(NULL)
	,m_pCubeMan(NULL)
	,m_pLight(NULL)
	,m_pBPath(NULL)
{
}

cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	SafeDelete(m_pLight);
	SafeDelete(m_pBPath);
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCubePC = new cCubePC;
	m_pCubePC->Setup();

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();
	
	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pLight = new cLight;
	m_pLight->Setup();

	m_pBPath = new cBPath;
	m_pBPath->Setup();
		
}

void cMainGame::Update()
{

	if (m_pCubeMan)
		m_pCubeMan->Update();
	
	if (m_pCamera)
		m_pCamera->Update();

	//if (m_pLight)
	//	m_pLight->Update();

	
}

void cMainGame::Render()
{
	
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(65, 65, 65), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();

	if (m_pCubeMan)
		m_pCubeMan->Render();

	if (m_pLight)
		m_pLight->Render();


	if (m_pBPath)
		m_pBPath->Render();

	Draw_Texture();
	

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


	
}

void cMainGame::Draw_Texture()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
//	g_pD3DDevice->SetTexture(0, m_pTexture); //texture¾²±â
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
//	g_pD3DDevice->SetTexture(0, NULL); //texture »©±â
}
