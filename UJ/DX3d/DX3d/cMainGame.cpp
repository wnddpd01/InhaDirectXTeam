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
	delete[] m_pCubePc;
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
	/*m_pCharacter = new cCharacter;
	m_pCharacter->Setup();*/

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();
	
	m_pCamera = new cCamera;
	m_pCamera->Setup(&(m_pCubeMan->GetPosition()));

	m_pGrid = new cGrid;
	m_pGrid->Setup(150, 0.1f);
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

void cMainGame::KeyInput()
{
	if (GetKeyState('A') & 0x8000)
		m_pCubeMan->Command('A');
	if (GetKeyState('D') & 0x8000)
		m_pCubeMan->Command('D');
	if (GetKeyState('W') & 0x8000)
		m_pCubeMan->Command('W');
	if (GetKeyState('S') & 0x8000)
		m_pCubeMan->Command('S');
	if(GetKeyState('Z') & 0x8000)
	{
		D3DLIGHT9 light;
		g_pD3DDevice->GetLight(1, &light);
		light.Range += 5.0f * 0.1f;
		//light.Attenuation1 -= 0.125f * 0.1f;
		g_pD3DDevice->SetLight(1, &light);
	}
	if(GetKeyState('X') & 0x8000)
	{
		D3DLIGHT9 light;
		g_pD3DDevice->GetLight(1, &light);
		light.Range -= 5.0f * 0.1f;
		//light.Attenuation1 += 0.125f * 0.1f;
		g_pD3DDevice->SetLight(1, &light);
	}
	if (GetKeyState('C') & 0x8000)
	{
		D3DLIGHT9 light;
		g_pD3DDevice->GetLight(2, &light);
		D3DXVECTOR3 dir = m_pCubeMan->GetPosition() - light.Position;
		D3DXVec3Normalize(&dir, &dir);
		light.Direction = dir;
		//light.Attenuation1 += 0.125f * 0.1f;
		g_pD3DDevice->SetLight(2, &light);
	}
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
	if(m_pCubePc != NULL)
	{
		m_pCubePc[0].Update();
		m_pCubePc[1].Update();
	}
	D3DLIGHT9 sun;
	g_pD3DDevice->GetLight(0, &sun);
	D3DXMATRIXA16 rotY;
	D3DXMatrixRotationZ(&rotY, 0.01f);
	D3DXVECTOR3 temp = sun.Direction;

	D3DXVec3TransformNormal(&temp, &temp, &rotY);
	sun.Direction = temp;
	if(temp.y < 0)
	{
		g_pD3DDevice->LightEnable(0, true);
	}
	else
	{
		g_pD3DDevice->LightEnable(0, false);
	}
	g_pD3DDevice->SetLight(0, &sun);
	
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(47, 121, 112), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	if(m_pCubePc != NULL)
	{
		m_pCubePc[0].Render();
		m_pCubePc[1].Render();
	}
	
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
	m_pCubePc = new cCubePC[2];
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Range = 5.0f;
	D3DXVECTOR3 vDir = { 1.0f, -3.0f, 1.0f };
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, TRUE);

	D3DLIGHT9 stPointLight;
	ZeroMemory(&stPointLight, sizeof(D3DLIGHT9));
	stPointLight.Type = D3DLIGHT_POINT;
	stPointLight.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	stPointLight.Diffuse = D3DXCOLOR(0.5f, 0.0f, 0.0f, 0.5f);
	stPointLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stPointLight.Range = 8.0f;
	stPointLight.Attenuation1 = 0.0625f;
	stPointLight.Position = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	g_pD3DDevice->SetLight(1, &stPointLight);
	g_pD3DDevice->LightEnable(1, TRUE);
	m_pCubePc[0].Setup();
	m_pCubePc[0].SetPosition(stPointLight.Position);
	
	D3DLIGHT9 stSpotLight;
	ZeroMemory(&stSpotLight, sizeof(D3DLIGHT9));
	stSpotLight.Type = D3DLIGHT_SPOT;
	stSpotLight.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	stSpotLight.Diffuse = D3DXCOLOR(0.0f, 0.5f, 0.0f, 0.5f);
	stSpotLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stSpotLight.Range = 10.0f;
	stSpotLight.Attenuation1 = 0.0625f;
	stSpotLight.Position = D3DXVECTOR3(-5.0f, 5.0f, -5.0f);
	stSpotLight.Direction = D3DXVECTOR3(0, -1, 0);
	stSpotLight.Falloff = 1.0f;
	stSpotLight.Theta = D3DX_PI / 4.0f;
	stSpotLight.Phi = D3DX_PI / 2.0f;
	g_pD3DDevice->SetLight(2, &stSpotLight);
	g_pD3DDevice->LightEnable(2, TRUE);
	m_pCubePc[1].Setup();
	m_pCubePc[1].SetPosition(stSpotLight.Position);
}

