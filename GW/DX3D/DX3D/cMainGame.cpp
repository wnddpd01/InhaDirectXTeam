#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cKids.h"
#include "cCubeMan.h"
#include "cLight.h"

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	,m_pCamera(NULL)
	,m_pGrid(NULL)
	,m_pCubeMan(NULL)
, m_pLight(NULL)
{
}

cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	SafeDelete(m_pLight);
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

	//>>:for texture
	{
		//D3DXCreateTextureFromFile(g_pD3DDevice, L"monkey.png", &m_pTexture);

		
		ST_PT_VERTEX v;


		v.p = D3DXVECTOR3(1, 1, 0);
		v.t = D3DXVECTOR2(0.26f, 0.13f);
		m_vecVertx.push_back(v);

	
		v.p = D3DXVECTOR3(1, 0, 0);
		v.t = D3DXVECTOR2(0.26f, 0.25f);
		m_vecVertx.push_back(v);

	
		
		
	}

	

}

void cMainGame::Update()
{

	if (m_pCubeMan)
		m_pCubeMan->Update();
	
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pLight)
		m_pLight->Update();
	
	
}

void cMainGame::Render()
{
	
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(65, 65, 65), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();

	if (m_pCubeMan)
		m_pCubeMan->Render();


	Draw_Texture();


	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
	


void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	if (m_pLight)
		m_pLight->WndProc(hWnd, message, wParam, lParam);

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
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertx.size() / 3, &m_vecVertx[0], sizeof(ST_PT_VERTEX));
//	g_pD3DDevice->SetTexture(0, NULL); //texture »©±â
}
