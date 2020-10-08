#include "stdafx.h"
#include "cMainGame.h"

#include <iostream>

#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cPyramid.h"
#include "cGrid.h"
#include "cCharacter.h"
#include "cCubeMan.h"
#include "cHexagon.h"
#include "cCubeAutoMan.h"
#include <stdlib.h>
#include <stdio.h>  

#include "cBox.h"
#include "cGroup.h"
#include "cObjLoader.h"


cMainGame::cMainGame()
	:m_pCubePc(NULL),
	m_pCamera(NULL),
	m_pGrid(NULL),
	m_pCharacter(NULL),
	m_pCubeMan(NULL),
	m_pBox(NULL)
{
}

cMainGame::~cMainGame()
{
	delete[] m_pCubePc;
	SafeDelete(m_pCharacter);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	for (auto it : m_vecMap)
	{
		SafeRelease(it);
	}
	m_vecMap.clear();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	//m_pCubePc = new cCubePC;
	//m_pCubePc->Setup();
	/*m_pCharacter = new cCharacter;
	m_pCharacter->Setup();*/

	ObjectCreator();
	
	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();

	m_hexagon = new cHexagon;
	m_hexagon->Setup();
	
	m_pCubeAutoMan = new cCubeAutoMan[2];
	for (int i = 0; i < 2; ++i)
	{
		m_pCubeAutoMan[i].SetPosition(D3DXVECTOR3(10, 0, 0));
	}
	m_pCubeAutoMan[0].Setup(m_hexagon->st_pc_bezier_vertices_);
	m_pCamera = new cCamera;
	m_pCamera->Setup(&(m_pCubeMan->GetPosition()));

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	Setup_Obj();
	Set_Light();
	
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
	for (int i = 0; i < 1; ++i)
	{
		m_pCubeAutoMan[i].Update();
	}
	//D3DLIGHT9 sun;
	//g_pD3DDevice->GetLight(0, &sun);
	//D3DXMATRIXA16 rotY;
	//D3DXMatrixRotationZ(&rotY, 0.01f);
	//D3DXVECTOR3 temp = sun.Direction;

	//D3DXVec3TransformNormal(&temp, &temp, &rotY);
	//sun.Direction = temp;
	//if(temp.y < 0)
	//{
	//	g_pD3DDevice->LightEnable(0, true);
	//}
	//else
	//{
	//	g_pD3DDevice->LightEnable(0, false);
	//}
	//g_pD3DDevice->SetLight(0, &sun);
	//D3DXIntersectTri()
	
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
	for (int i = 0; i < 1; ++i)
	{
		m_pCubeAutoMan[i].Render();
	}
	if(m_pGrid != NULL)
		m_pGrid->Render();

	if (m_hexagon != NULL)
		m_hexagon->Render();

	Obj_Render();
	
	//if (m_pBox != NULL)
	//	m_pBox->Render();
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

void cMainGame::ObjectCreator(string obj_file_name)
{
	m_pBox = new cBox;
	
	FILE *fp = fopen(obj_file_name.c_str(), "r");
	if(!fp)
	{
		
	}
	char line[256];
	char materialName[32];
	vector<D3DXVECTOR3> vertices;
	vector<D3DXVECTOR2> tex_vertices;
	vector<D3DXVECTOR3> nomals;
	
	while(fgets(line, sizeof(line), fp) != NULL)
	{
		char *ptr = strtok(line, " ");
		if(line[0] == '#')
			continue;
		else if(strcmp(ptr, "mtllib") == 0)
		{
			ptr = strtok(NULL, " ");
			strcpy(materialName, ptr);
			cout << materialName << endl;
		}
		else if (strcmp(ptr, "v") == 0)
		{
			D3DXVECTOR3 vertex;
			
			ptr = strtok(NULL, " ");
			vertex.x = stof(ptr);
			
			ptr = strtok(NULL, " ");
			vertex.y = stof(ptr);
			
			ptr = strtok(NULL, " ");
			vertex.z = stof(ptr);
			
			vertices.push_back(vertex);
			cout << "ver x : " << vertex.x << " y : " << vertex.y << " z : " << vertex.z << endl;
		}
		else if(strcmp(ptr, "vt") == 0)
		{
			D3DXVECTOR2 tex_vertex;
			ptr = strtok(NULL, " ");
			tex_vertex.x = stof(ptr);
			ptr = strtok(NULL, " ");
			tex_vertex.y = stof(ptr);
			tex_vertices.push_back(tex_vertex);
			cout << "tex x : " << tex_vertex.x << " y : " << tex_vertex.y << endl;
		}
		else if (strcmp(ptr, "vn") == 0)
		{
			D3DXVECTOR3 nomal;
			ptr = strtok(NULL, " ");
			nomal.x = stof(ptr);
			ptr = strtok(NULL, " ");
			nomal.y = stof(ptr);
			ptr = strtok(NULL, " ");
			nomal.z = stof(ptr);
			D3DXVec3Normalize(&nomal, &nomal);
			nomals.push_back(nomal);
			cout << "nor x : " << nomal.x << " y : " << nomal.y << " z : " << nomal.z << endl;
		}
		else if (strcmp(ptr, "f") == 0)
		{
			ptr = strtok(NULL, " ");
			while(ptr != NULL)
			{
				ST_PNT_VERTEX vt;
				char *ptr2 = strtok(ptr, "/");
				cout << stoi(ptr2) - 1 << '/';
				vt.p = vertices[stoi(ptr2) - 1];
				ptr2 = strtok(NULL, "/");
				cout << stoi(ptr2) - 1 << '/';
				vt.t = tex_vertices[stoi(ptr2) - 1];
				ptr2 = strtok(NULL, "/");
				cout << stoi(ptr2) - 1;
				vt.n = nomals[stoi(ptr2) - 1];
				cout << endl;
				m_pBox->m_vecVertex.push_back(vt);
				ptr = strtok(ptr2 + 2, " ");
			}
		}
	}
	fclose(fp);
	char texFileName[32];


	materialName[strlen(materialName) - 1] = '\0';
	fp = fopen(materialName, "r");
	if (!fp)
	{
		PostQuitMessage(0);
	}
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		char *ptr = strtok(line, " ");
		if (line[0] == '#')
			continue;
		else if (strcmp(ptr, "Ka") == 0)
		{
			m_pBox->m_stMtl.Ambient.a = 1.0f;
			ptr = strtok(NULL, " ");
			m_pBox->m_stMtl.Ambient.r = stof(ptr);
			ptr = strtok(NULL, " ");
			m_pBox->m_stMtl.Ambient.g = stof(ptr);
			ptr = strtok(NULL, " ");
			m_pBox->m_stMtl.Ambient.b = stof(ptr);
		}
		else if (strcmp(ptr, "Kd") == 0)
		{
			m_pBox->m_stMtl.Diffuse.a = 1.0f;
			ptr = strtok(NULL, " ");
			m_pBox->m_stMtl.Diffuse.r = stof(ptr);
			ptr = strtok(NULL, " ");
			m_pBox->m_stMtl.Diffuse.g = stof(ptr);
			ptr = strtok(NULL, " ");
			m_pBox->m_stMtl.Diffuse.b = stof(ptr);
		}
		else if (strcmp(ptr, "Ks") == 0)
		{
			m_pBox->m_stMtl.Specular.a = 1.0f;
			ptr = strtok(NULL, " ");
			m_pBox->m_stMtl.Specular.r = stof(ptr);
			ptr = strtok(NULL, " ");
			m_pBox->m_stMtl.Specular.g = stof(ptr);
			ptr = strtok(NULL, " ");
			m_pBox->m_stMtl.Specular.b = stof(ptr);
		}
		else if (strcmp(ptr, "d") == 0)
		{
			ptr = strtok(NULL, " ");
			m_pBox->m_stMtl.Power = stof(ptr);
		}
		else if (strcmp(ptr, "map_Kd") == 0)
		{
			WCHAR texFile[32];
			ZeroMemory(&texFile, sizeof(texFile));
			ptr = strtok(NULL, " ");
			ptr[strlen(ptr) - 1] = '\0';
			//wsprintf(texFile, L"%s", ptr);
			mbstowcs(texFile, ptr, strlen(ptr));
			D3DXCreateTextureFromFile(g_pD3DDevice, texFile, &m_pBox->m_pTextrue);
		}
	}
	fclose(fp);
}

void cMainGame::Set_Light()
{
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

	/*
	m_pCubePc = new cCubePC[2];
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
	m_pCubePc[1].SetPosition(stSpotLight.Position);*/
}

void cMainGame::Setup_Obj()
{
	cObjLoader l;
	l.Load(m_vecMap, "obj", "map.obj");
}

void cMainGame::Obj_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);

	matWorld = matS * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	for (auto it : m_vecMap)
	{
		it->Render();
	}
}

