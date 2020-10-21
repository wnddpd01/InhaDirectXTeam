#include "stdafx.h"
#include "cMainGame.h"

#include <iostream>

#include "cDeviceManager.h"
#include "cCamera.h"
#include "cCubePC.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cObjMap.h"	// << :
#include "cAseLoader.h"
#include "cFrame.h"
#include "cRay.h"
#include "cTerrain.h"

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL) 
	, m_pTexture(NULL)
	, m_pMap(NULL)
	, m_pRootFrame(NULL)
	, m_pMeshTeapot(NULL)
	, m_pMeshSphere(NULL)
	, m_pObjMesh(NULL)
	, m_pVecTargetPos(NULL)
	, m_pTerrain(NULL)
{
	m_vecPos = { 0, 0, 0 };
	m_vecDir = { 0, 0, 1 };
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 45;
	fd.Width = 28;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	//strcpy_s(fd.FaceName, "궁서체");   //글꼴 스타일
	AddFontResource(L"umberto.ttf");
	wcscpy(fd.FaceName, L"umberto");
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_font);
	ZeroMemory(&m_stMtlSelectedSphere, sizeof(D3DMATERIAL9));
	m_stMtlSelectedSphere.Ambient  = D3DXCOLOR(210.0f / 255.0f, 20.0f / 255.0f, 20.0f / 255.0f, 1.0f);
	m_stMtlSelectedSphere.Diffuse  = D3DXCOLOR(210.0f / 255.0f, 20.0f / 255.0f, 20.0f / 255.0f, 1.0f);
	m_stMtlSelectedSphere.Specular = D3DXCOLOR(210.0f / 255.0f, 20.0f / 255.0f, 20.0f / 255.0f, 1.0f);
	
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient  = D3DXCOLOR(13.0f / 255.0f, 130.0f / 255.0f, 217.0f / 255.0f, 1.0f);
	m_stMtlSphere.Diffuse  = D3DXCOLOR(13.0f / 255.0f, 130.0f / 255.0f, 217.0f / 255.0f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(13.0f / 255.0f, 130.0f / 255.0f, 217.0f / 255.0f, 1.0f);
}


cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC); 
	SafeDelete(m_pCamera); 
	SafeDelete(m_pGrid); 
	SafeDelete(m_pCubeMan); 
	SafeDelete(m_pMap); 
	SafeRelease(m_pTexture);
	SafeRelease(m_pMeshSphere);
	SafeRelease(m_pMeshTeapot);
	SafeRelease(m_pObjMesh);
	for (auto it : m_vecObjMtlTex)
	{
		SafeRelease(it);
	}
	m_pRootFrame->Destroy();
	for each(auto p in m_vecGroup)
	{
		SafeRelease(p); 
	}
	m_vecGroup.clear(); 
	g_pObjectManager->Destroy(); 
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCubePC = new cCubePC; 
	m_pCubePC->Setup(); 

	m_pCubeMan = new cCubeMan; 
	m_pCubeMan->Setup(); 

	//&m_pCubePC->GetPosition());

	m_pGrid = new cGrid; 
	m_pGrid->Setup(); 

	{
		cAseLoader l;
		m_pRootFrame = l.Load("woman/woman_01_all.ASE");
		/*for (int i = 0; i < 10; ++i)
		{
			m_vecPFrame.push_back(l.Load("woman/woman_01_all.ASE"));
		}*/
	}

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_vecPos);
	Setup_Texture(); 
	//Setup_Obj(); 
	Set_Light();
	Setup_MeshObject();
	Setup_PickingObj();

	m_pTerrain = cTerrain::LoadFromRawFile("HeightMapData/HeightMap.raw");
	m_pTerrain->SetTextureFromFile("HeightMapData/terrain.jpg");
}

void cMainGame::InputProcess()
{
	if(GetKeyState('W') & 0x8000)
	{
		m_vecPos += m_vecDir * 0.1f;
		if (m_vecPos.x < 0)
			m_vecPos.x = 0;
		if (m_vecPos.z < 0)
			m_vecPos.z = 0;
		int col = floorf(m_vecPos.x);
		int row = floorf(m_vecPos.z);
		float A = m_pTerrain->m_arrMapVertex[row][col];
		float B = m_pTerrain->m_arrMapVertex[row + 1][col];
		float C = m_pTerrain->m_arrMapVertex[row + 1][col + 1];
		float D = m_pTerrain->m_arrMapVertex[row][col + 1];

		float dx = m_vecPos.x - col;
		float dz = m_vecPos.z - row;
		float height = 0;
		if(dz > dx)
		{
			float uy = C - B;
			float vy = A - B;
			height = B + Lerp(0, uy,  dx) + Lerp(0, vy, 1.0f - dz);
		}
		else
		{
			float uy = A - D;
			float vy = C - D;
			height = D + Lerp(0, uy, 1.0f - dx) + Lerp(0, vy, dz);
		}
		m_vecPos.y = height - m_pTerrain->m_arrMapVertex[0][0];
	}
	if (GetKeyState('A') & 0x8000)
	{
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationY(&matR, -0.01f);
		D3DXVec3TransformNormal(&m_vecDir, &m_vecDir, &matR);
	}
	if (GetKeyState('D') & 0x8000)
	{
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationY(&matR, 0.01f);
		D3DXVec3TransformNormal(&m_vecDir, &m_vecDir, &matR);
	}
}

void cMainGame::Update()
{
	
	if (m_pCubePC)
		m_pCubePC->Update(); 

	if (m_pCubeMan)
		m_pCubeMan->Update(m_pMap); 

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pRootFrame)
	{
		D3DXMATRIXA16 matS, matR, matLookAt,matT, matWorld;
		D3DXVECTOR3 vecLookAt;
		if (m_pVecTargetPos == NULL)
		{
			 vecLookAt = m_vecPos + m_vecDir - m_vecPos;
		}
		else
		{
			vecLookAt = *m_pVecTargetPos - m_vecPos;
		}
		D3DXMatrixLookAtLH(&matLookAt, &D3DXVECTOR3(0, 0, 0), &vecLookAt, &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixTranspose(&matLookAt, &matLookAt);
		D3DXVec3TransformNormal(&m_vecDir, &D3DXVECTOR3(0, 0, 1), &matLookAt);

		if(m_pVecTargetPos != NULL)
		{
			m_vecPos += m_vecDir * 0.01f;
			if(D3DXVec3Length(&(m_vecPos - *m_pVecTargetPos)) < 0.01f)
			{
				m_vecPos = *m_pVecTargetPos;
				SafeDelete(m_pVecTargetPos);
			}
		}
		
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixRotationY(&matR, D3DX_PI);
		matR *= matLookAt;
		D3DXMatrixTranslation(&matT, m_vecPos.x, m_vecPos.y, m_vecPos.z);
		matWorld = matS * matR * matT;
		m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), &matWorld);
	}
	for (auto frame : m_vecPFrame)
	{
		frame->Update(frame->GetKeyFrame(), NULL);
	}
}

void cMainGame::Render()
{
	static DWORD framecount = 0;
	static DWORD frameStart = 0;
	static DWORD frame = 0;
	g_pD3DDevice->Clear(NULL, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112) , 
		1.0F, 0);

	g_pD3DDevice->BeginScene();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	/*if (m_pGrid)
		m_pGrid->Render();*/
	//if (m_pCubePC)
	//	m_pCubePC->Render(); 
	//Obj_Render(); 

	//if (m_pCubeMan)
		//m_pCubeMan->Render(); 
	
	//PickingObj_Render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	if (m_pRootFrame)
	{
		m_pRootFrame->Render();
	}
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	for (auto frame : m_vecPFrame)
	{
		frame->Render();
	}
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pTerrain->Render();
	/*g_pD3DDevice->SetTexture(0, NULL);
	for (auto object : m_vecObject)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &object->m_matWorld);
		g_pD3DDevice->SetMaterial(&object->m_mtl);
		object->m_pMesh->DrawSubset(0);
	}*/
	//Mesh_Render();
	//Draw_Texture(); 
	if (m_font)
	{
		RECT rc;
		SetRect(&rc, 0, 0, 103, 103);
		char szTemp[1024];
		sprintf(szTemp, "FPS = %d", frame);
		m_font->DrawTextA(nullptr,
			szTemp,
			strlen(szTemp),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 0, 0));
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	
	framecount++;
	DWORD frameEnd = GetTickCount();
	if(frameEnd - frameStart > 999)
	{
		frameStart = frameEnd;
		frame = framecount;
		framecount = 0;
	}
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	switch (message)
	{
	case WM_LBUTTONUP:
	{
		/*POINT ptMouse;
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);
		D3DXMATRIXA16 matProj, matView;
		RECT rectWindow;
		GetClientRect(hWnd, &rectWindow);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixInverse(&matView, NULL, &matView);
		D3DXVECTOR3 vecRayDir;
		vecRayDir.x = ((2.0f * ptMouse.x / rectWindow.right) - 1) / matProj.m[0][0];
		vecRayDir.y = ((-2.0f * ptMouse.y / rectWindow.bottom) + 1) / matProj.m[1][1];
		vecRayDir.z = 1.0f;
		D3DXVECTOR3 vecRayOrigin = { 0, 0, 0 };
		D3DXVec3TransformCoord(&vecRayOrigin, &vecRayOrigin, &matView);
		D3DXVec3TransformNormal(&vecRayDir, &vecRayDir, &matView);
		D3DXVec3Normalize(&vecRayDir, &vecRayDir);


		for (auto m_vec_object : m_vecObject)
		{
			D3DXVECTOR3 v = vecRayOrigin - m_vec_object->m_pos;

			float b = 2.0f * D3DXVec3Dot(&vecRayDir, &v);
			float c = D3DXVec3Dot(&v, &v) - ((m_vec_object->m_fScale * 0.5f) * (m_vec_object->m_fScale * 0.5f));

			float discriminant = (b * b) - (4.0f) * c;

			if (discriminant < 0.0f)
			{
				m_vec_object->m_mtl = m_stMtlSphere;
				break;
			}

			discriminant = sqrtf(discriminant);

			float s0 = (-b + discriminant) / 2.0f;
			float s1 = (-b - discriminant) / 2.0f;

			if (s0 >= 0.0f || s1 >= 0.0f)
			{
				m_vec_object->m_mtl = m_stMtlSelectedSphere;
			}
			else
			{
				m_vec_object->m_mtl = m_stMtlSphere;
			}
		}*/
		cRay r = cRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
		for (int i = 0; i < m_vecSphere.size(); ++i)
		{
			m_vecSphere[i].isPicked = r.IsPicked(&m_vecSphere[i]);
		}
	}
	break;
	case WM_RBUTTONDOWN:
	{
		/*for (int i = 0; i < m_pGrid->m_vecVertex.size(); i += 6)
		{
			POINT ptMouse;
			ptMouse.x = LOWORD(lParam);
			ptMouse.y = HIWORD(lParam);
			D3DXMATRIXA16 matProj, matView;
			RECT rectWindow;
			GetClientRect(hWnd, &rectWindow);
			g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
			g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
			D3DXMatrixInverse(&matView, NULL, &matView);
			D3DXVECTOR3 vecRayDir;
			vecRayDir.x = ((2.0f * ptMouse.x / rectWindow.right) - 1) / matProj.m[0][0];
			vecRayDir.y = ((-2.0f * ptMouse.y / rectWindow.bottom) + 1) / matProj.m[1][1];
			vecRayDir.z = 1.0f;
			D3DXVECTOR3 vecRayOrigin = { 0, 0, 0 };
			D3DXVec3TransformCoord(&vecRayOrigin, &vecRayOrigin, &matView);
			D3DXVec3TransformNormal(&vecRayDir, &vecRayDir, &matView);
			D3DXVec3Normalize(&vecRayDir, &vecRayDir);

			float u, v, dist;
			if (D3DXIntersectTri(&m_pGrid->m_vecVertex[i + 0].p, &m_pGrid->m_vecVertex[i + 1].p, &m_pGrid->m_vecVertex[i + 2].p,
				&vecRayOrigin, &vecRayDir, &u, &v, &dist)
				||
				D3DXIntersectTri(&m_pGrid->m_vecVertex[i + 3].p, &m_pGrid->m_vecVertex[i + 4].p, &m_pGrid->m_vecVertex[i + 5].p,
					&vecRayOrigin, &vecRayDir, &u, &v, &dist))
			{
				m_pGrid->m_vecVertex[i + 0].c = D3DXCOLOR(13.0f / 255.0f, 130.0f / 255.0f, 217.0f / 255.0f, 1.0f);
				m_pGrid->m_vecVertex[i + 1].c = D3DXCOLOR(13.0f / 255.0f, 130.0f / 255.0f, 217.0f / 255.0f, 1.0f);
				m_pGrid->m_vecVertex[i + 2].c = D3DXCOLOR(13.0f / 255.0f, 130.0f / 255.0f, 217.0f / 255.0f, 1.0f);
				m_pGrid->m_vecVertex[i + 3].c = D3DXCOLOR(13.0f / 255.0f, 130.0f / 255.0f, 217.0f / 255.0f, 1.0f);
				m_pGrid->m_vecVertex[i + 4].c = D3DXCOLOR(13.0f / 255.0f, 130.0f / 255.0f, 217.0f / 255.0f, 1.0f);
				m_pGrid->m_vecVertex[i + 5].c = D3DXCOLOR(13.0f / 255.0f, 130.0f / 255.0f, 217.0f / 255.0f, 1.0f);

				m_pVecTargetPos = new D3DXVECTOR3((m_pGrid->m_vecVertex[i + 0].p.x + m_pGrid->m_vecVertex[i + 5].p.x) / 2.0f, 0, (m_pGrid->m_vecVertex[i + 0].p.z + m_pGrid->m_vecVertex[i + 5].p.z) / 2.0f);
				break;
			}
		}*/
		cRay r = cRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
		for (int i = 0; i < m_vecPlaneVertex.size(); i+=3)
		{
			D3DXVECTOR3 v(0, 0, 0);
			if (r.IntersectTri(m_vecPlaneVertex[i + 0].p, m_vecPlaneVertex[i + 1].p, m_vecPlaneVertex[i + 2].p, v))
			{
				m_vPickedPosition = v;
			}
		}
	}
	break;
	}
}

void cMainGame::Set_Light()
{
	D3DLIGHT9	stLight; 
	ZeroMemory(&stLight, sizeof(D3DLIGHT9)); 
	stLight.Type = D3DLIGHT_DIRECTIONAL; 
	stLight.Ambient  = D3DXCOLOR(1.0F, 1.0F, 1.0F, 1.0F); 
	stLight.Specular = D3DXCOLOR(1.0F, 1.0F, 1.0F, 1.0F);
	stLight.Diffuse  = D3DXCOLOR(1.0F, 1.0F, 1.0F, 1.0F);

	D3DXVECTOR3  vDir(0.0f, -1.0f, 1.0f); 
	D3DXVec3Normalize(&vDir, &vDir); 
	stLight.Direction = vDir; 
	g_pD3DDevice->SetLight(0, &stLight); 
	g_pD3DDevice->LightEnable(0, true); 
}

void cMainGame::Setup_Texture()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, _T("../image/수지.png"), &m_pTexture);
	ST_PT_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);


	// : 왼쪽에 뒤집어 출력
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(v);
}

void cMainGame::Draw_Texture()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false); 

	D3DXMATRIXA16 matWorld; 
	D3DXMatrixIdentity(&matWorld); 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	g_pD3DDevice->SetTexture(0, m_pTexture); 
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF); 
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX)); 
	g_pD3DDevice->SetTexture(0, NULL);
}

void cMainGame::Setup_Obj()
{
	cObjLoader l; 
	l.Load(m_vecGroup, "obj", "map.obj"); 

	Load_Surface();
}

void cMainGame::Obj_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR; 
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f); 
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F); 

	matWorld = matS * matR; 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	for each(auto p in m_vecGroup)
	{
		p->Render(); 
	}
}

void cMainGame::Load_Surface()
{
	D3DXMATRIXA16 matWorld, matS, matR; 
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	matWorld = matS * matR;
	m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);
}

void cMainGame::Setup_MeshObject()
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMeshTeapot, NULL);
	D3DXCreateSphere(g_pD3DDevice, 0.5, 10, 10, &m_pMeshSphere, NULL);
	ZeroMemory(&m_stMtlTeapot, sizeof(D3DMATERIAL9));
	m_stMtlTeapot.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient  = D3DXCOLOR(0.7f, 0.7f, 0, 1.0f);
	m_stMtlSphere.Diffuse  = D3DXCOLOR(0.7f, 0.7f, 0, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0, 1.0f);

	BasicObject* object = new BasicObject;
	D3DXCreateSphere(g_pD3DDevice, 0.5, 10, 10, &object->m_pMesh, NULL);
	object->m_mtl = m_stMtlSphere;
	m_vecObject.push_back(object);
	
	//cObjLoader l;
	//m_pObjMesh = l.LoadMesh(m_vecObjMtlTex, "obj", "map.obj");
	/*cAseLoader l;
	m_pObjMesh = l.LoadMesh(m_vecObjMtlTex, "woman/woman_01_all.ASE");*/
}

void cMainGame::Mesh_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTexture(0, NULL);
	D3DXMATRIXA16 matWorld, matS, matR;
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS * matR;
		D3DXMatrixTranslation(&matWorld, 0, 0, 10);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlTeapot);
		m_pMeshTeapot->DrawSubset(0);
	}
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS * matR;
		//D3DXMatrixTranslation(&matWorld, 0, 0, 10);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlSphere);
		m_pMeshSphere->DrawSubset(0);
	}

	{
		D3DXMATRIXA16 matWorld, matS, matR;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
		matWorld = matS * matR;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		for (size_t i = 0; i < m_vecObjMtlTex.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[0]->GetTexture());
			m_pObjMesh->DrawSubset(i);
		}
	}
}

void cMainGame::Setup_PickingObj()
{
	for (int i = 0; i < 10; ++i)
	{
		ST_SPHERE s;
		s.fRadius = 0.5f;
		s.vCenter = D3DXVECTOR3(0, 0, -10 + 2 * i);
		m_vecSphere.push_back(s);
	}

	ZeroMemory(&m_stMtlNone, sizeof(D3DMATERIAL9));
	m_stMtlNone.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
	m_stMtlPicked.Ambient = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Diffuse = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Specular = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);


	ZeroMemory(&m_stMtlPlane, sizeof(D3DMATERIAL9));
	m_stMtlPlane.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	ST_PN_VERTEX v;
	v.n = D3DXVECTOR3(0, 1, 0);
	v.p = D3DXVECTOR3(-10, 0, -10);
	m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(-10, 0, 10);
	m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(10, 0, 10);
	m_vecPlaneVertex.push_back(v);


	v.p = D3DXVECTOR3(-10, 0, -10);
	m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(10, 0, 10);
	m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(10, 0, -10);
	m_vecPlaneVertex.push_back(v);
}

void cMainGame::PickingObj_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matWorld;

	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMtlPlane);
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecPlaneVertex[0], sizeof(ST_PN_VERTEX));

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	for (int i = 0; i < m_vecSphere.size(); ++i)
	{
		D3DXMatrixIdentity(&matWorld);
		matWorld._41 = m_vecSphere[i].vCenter.x;
		matWorld._42 = m_vecSphere[i].vCenter.y;
		matWorld._43 = m_vecSphere[i].vCenter.z;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&(m_vecSphere[i].isPicked ? m_stMtlPicked : m_stMtlNone));
		m_pMeshSphere->DrawSubset(0);
	}

	g_pD3DDevice->SetMaterial(&m_stMtlNone);
	D3DXMatrixTranslation(&matWorld, m_vPickedPosition.x, m_vPickedPosition.y, m_vPickedPosition.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pMeshSphere->DrawSubset(0);
	
}


