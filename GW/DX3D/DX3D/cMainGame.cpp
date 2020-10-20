#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cObjMap.h"

#include "cLight.h"
#include "cBPath.h"

#include "cFrame.h"
#include "cAseLoader.h"

#include "cRay.h"

#include <sysinfoapi.h>



cMainGame::cMainGame()
	: m_pCubePC(NULL)
	,m_pCamera(NULL)
	,m_pGrid(NULL)
	,m_pCubeMan(NULL)
	,m_pLight(NULL)
	,m_pBPath(NULL)
	,m_pMap(NULL)
	,m_pRootFrame(NULL)
	,m_pMeshSphere(NULL)
	,m_pMeshTeapot(NULL)
	,m_pObjMesh(NULL)
	,m_pRay(NULL)
	
{
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 45;
	fd.Width = 28;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	wcscpy(fd.FaceName, L"�ü�ü");   //�۲� ��Ÿ��
	AddFontResource(L"umberto.ttf");
	wcscpy(fd.FaceName, L"umberto");
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
}

cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	SafeDelete(m_pLight);
	SafeDelete(m_pBPath);
	SafeDelete(m_pMap);

	SafeDelete(m_pRay);
//<<<<<<<<<<<<<<<<<<<<<<<<<mesh
	SafeRelease(m_pMeshSphere);
	SafeRelease(m_pMeshTeapot);
	SafeRelease(m_pObjMesh);

	for each (auto p in m_vecObjMtlTex)
	{
		SafeRelease(p);
	}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<
	
	for each(auto p in m_vecGroup)
	{
		SafeRelease(p);
	}

	m_vecGroup.clear();

	m_pRootFrame->Destroy();
	
	g_pDeviceManager->Destroy();
	
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


	Setup_Obj();

	{
		cAseLoader l;
		
		m_pRootFrame = l.Load("woman/woman_01_all.ASE");
	}

	m_pLight = new cLight;
	m_pLight->Setup();

	m_pBPath = new cBPath;
	m_pBPath->Setup();




	//<<<<<<<<<<<<<<<<<<<mesh
	Setup_MeshObject();
	//<<<<<<<<<<<<<<<<<<<
		
}

void cMainGame::Update()
{

	if (m_pCubeMan)
		m_pCubeMan->Update(m_pMap);
	
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pLight)
		m_pLight->Update();

	/*if (m_pRootFrame)
		m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), NULL);*/

	
}

void cMainGame::Render()
{
	static DWORD framecount = 0;
	static DWORD frameStart = 0;
	static DWORD frame = 0;
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(65, 65, 65), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	
	
	if (m_pGrid)
		m_pGrid->Render();

	/*if (m_pCubeMan)
		m_pCubeMan->Render();*/

	//Obj_Render();

	//if (m_pLight)
	//	m_pLight->Render();


	//if (m_pBPath)
	//	m_pBPath->Render();

	//Draw_Texture();

	

	


	/*if (m_pRootFrame)
	{
		m_pRootFrame->Render();	
	}*/
	


	Mesh_Render();
	
	
	/*if (m_pFont)
	{
		RECT rc;
		SetRect(&rc, 50, 50, 100, 100);
		char szTemp[1024];
		sprintf(szTemp, "FPS = %d",frame);
		m_pFont->DrawTextA(nullptr,
			szTemp,
			strlen(szTemp),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 0, 0));
	}*/
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);


	/*framecount++;
	DWORD frameEnd = GetTickCount();
	if (frameEnd - frameStart > 999)
	{
		frameStart = frameEnd;
		frame = framecount;
		framecount = 0;
	}*/


}
	


void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);


	
	/*if (m_pRay)
		m_pRay->WndProc(hWnd, message, wParam, lParam, );*/


	switch (message)
	{
	case WM_LBUTTONDOWN:

		Ray ray = CalcPickingRay(LOWORD(lParam), HIWORD(lParam));

		D3DXMATRIX view;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &view);

		D3DXMATRIX viewInverse;
		D3DXMatrixInverse(&viewInverse, 0, &view);

		TransformRay(&ray, &viewInverse);

		for (int i = 0; i < 5; i++)
		{
			if (raySphereIntersectionTest(&ray, &bs[i]))
			{
				bs[i]._check = true;
			
			}
			else
			{
				bs[i]._check = false;
			}
		}

		break;
	}
	
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
//	g_pD3DDevice->SetTexture(0, m_pTexture); //texture����
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
//	g_pD3DDevice->SetTexture(0, NULL); //texture ����
}

void cMainGame::Setup_Obj()
{
	cObjLoader l;
	l.Load(m_vecGroup, "obj", "map.obj");
	//l.LoadAse(m_vecGroup, "ase", "woman_01_all.ASE");
	Load_Surface();
}

void cMainGame::Obj_Render()
{
	g_pD3DDevice->SetTexture(0, NULL);

	D3DXMATRIXA16 matWorld, matS, matR;
	//D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);

	matWorld = matS * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for each(auto p in m_vecGroup)
	{
		p->Render();
	}


	//D3DXIntersectTri(v1,v2,v3,rayPos,rayDir, u, v, f)
	
}

void cMainGame::Load_Surface()
{
	/*D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;
	m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);*/

	
}

void cMainGame::Setup_MeshObject()
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMeshTeapot, NULL);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 30, 10, &m_pMeshSphere, NULL);
		
	ZeroMemory(&m_stMtlTeapot, sizeof(D3DMATERIAL9));
	m_stMtlTeapot.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);


	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);


	cObjLoader l;
	m_pObjMesh = l.LoadMesh(m_vecObjMtlTex, "obj", "map.obj");

	
}

void cMainGame::Mesh_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	{
	/*	D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS * matR;	
		D3DXMatrixTranslation(&matWorld, 0, 0, 10);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlTeapot);
		m_pMeshTeapot->DrawSubset(0);*/
	}

	

		int i = 0;
		for (int j = 0 ; j<5; j++)
		{
			
			D3DXMatrixIdentity(&matS);
			D3DXMatrixIdentity(&matR);
			D3DXMatrixTranslation(&matT, 0.0f+i, 0.0f, 0.0f);
			matWorld = matS * matR * matT;
			bs[j]._center = D3DXVECTOR3(0.0f+i,0,0);
			bs[j]._radius = 0.5f;
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
			g_pD3DDevice->SetMaterial(&m_stMtlSphere);
			m_pMeshSphere->DrawSubset(0);


			if(bs[j]._check)
			{
				m_stMtlSphere.Ambient = D3DXCOLOR(5.7f, 0.7f, 0.0f, 1.0f);
				m_stMtlSphere.Diffuse = D3DXCOLOR(5.7f, 0.7f, 0.0f, 1.0f);
				m_stMtlSphere.Specular = D3DXCOLOR(5.7f, 0.7f, 0.0f, 1.0f);
			}
			else
			{
				m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
				m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
				m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
			}		
			i+=2;
		}



	

	
	

	{
		/*D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);

		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
		matWorld = matS * matR;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		for(size_t i = 0; i<m_vecObjMtlTex.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
			m_pObjMesh->DrawSubset(i);
		}*/
	}
	
}

cMainGame::Ray cMainGame::CalcPickingRay(int x, int y)
{
	float px = 0.0f;
	float py = 0.0f;

	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXMATRIX proj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &proj);

	px = (((2.0f*x) / vp.Width) - 1.0f) / proj(0, 0);
	py = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);

	Ray ray;
	ray._origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ray._direction = D3DXVECTOR3(px, py, 1.0f);

	return ray;
}

void cMainGame::TransformRay(Ray* ray, D3DXMATRIX* T)
{
	D3DXVec3TransformCoord(&ray->_origin, &ray->_origin, T);
	D3DXVec3TransformNormal(&ray->_direction, &ray->_direction, T);

	D3DXVec3Normalize(&ray->_direction, &ray->_direction);
}

bool cMainGame::raySphereIntersectionTest(Ray* ray, BoundingSphere* sphere)
{
	D3DXVECTOR3 v = ray->_origin - sphere->_center;

	float b = 2.0f * D3DXVec3Dot(&ray->_direction, &v);
	float c = D3DXVec3Dot(&v, &v) - (sphere->_radius * sphere->_radius);

	float discirminant = (b*b) - (4.0f *c);

	if (discirminant < 0.0f)
		return false;

	discirminant = sqrtf(discirminant);

	float s0 = (-b + discirminant) / 2.0f;
	float s1 = (-b - discirminant) / 2.0f;

	if (s0 >= 0.0f || s1 >= 0.0f)
		return true;

	return false;

}


