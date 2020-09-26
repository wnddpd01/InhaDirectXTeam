#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"

cMainGame::cMainGame()
	:vPosition(0,0,0) , vDirection(0,0,1), vEye(0, 5, -11.0f), vLookAt(0,0,0)
	, m_fCameraDistance(5.0f), m_isLButtonDown(false), m_vCamRotAngle(0, 0, 0)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}


cMainGame::~cMainGame()
{
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	Setup_Line();
	Setup_Triangle();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Update()
{
	Update_Rotation();
	Update_Move();
}

void cMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	
	D3DXVECTOR3 vUp = D3DXVECTOR3(0, 1, 0);
	D3DXMATRIXA16 matRX;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMATRIXA16 matRY;
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);
	D3DXMATRIXA16 matR = matRX * matRY;
	
	vEye = D3DXVECTOR3(0.0f, m_fCameraDistance, -m_fCameraDistance);
	D3DXVec3TransformCoord(&vEye,&vEye, &matR);
	vLookAt = vPosition;
	vEye = vEye + vPosition;
	
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);


	if (NULL == g_pD3DDevice)
		return;
	
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET| D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(45,45,48), 1.0f, 0);
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		Draw_Line();
		Draw_Triangle();
		g_pD3DDevice->EndScene();
	}
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::Cleanup()
{
	if (g_pD3DDevice != NULL)
		g_pD3DDevice->Release();
	if (g_pD3DDevice != NULL)
		g_pD3DDevice->Release();
}

void cMainGame::Setup_Line()
{
	int nNumHalfTile = 5;
	float fInterval = 1.0f;
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;
	
	for (int i = 1; i <= nNumHalfTile; ++i)
	{
		ST_PC_VERTEX v;
		ST_PC_VERTEX v2;
		ST_PC_VERTEX v3;
		ST_PC_VERTEX v4;
		ST_PC_VERTEX v5;
		ST_PC_VERTEX v6;
		ST_PC_VERTEX v7;
		ST_PC_VERTEX v8;
		
		v.p = D3DXVECTOR3(fMin, 0, i*fInterval);
		v2.p = D3DXVECTOR3(fMax, 0, i*fInterval);
		v3.p = D3DXVECTOR3(fMin, 0, -i*fInterval);
		v4.p = D3DXVECTOR3(fMax, 0, -i*fInterval);
		v5.p = D3DXVECTOR3(i*fInterval, 0, fMin);
		v6.p = D3DXVECTOR3(i*fInterval, 0, fMax);
		v7.p = D3DXVECTOR3(-i*fInterval, 0, fMin);
		v8.p = D3DXVECTOR3(-i*fInterval, 0, fMax);
		
		m_vecLineVertex.push_back(v);
		m_vecLineVertex.push_back(v2); 

		m_vecLineVertex.push_back(v3);
		m_vecLineVertex.push_back(v4);

		m_vecLineVertex.push_back(v5);
		m_vecLineVertex.push_back(v6);

		m_vecLineVertex.push_back(v7);
		m_vecLineVertex.push_back(v8);
		
	}
	
	ST_PC_VERTEX v;
	ST_PC_VERTEX v2;
	ST_PC_VERTEX v3;
	ST_PC_VERTEX v4;
	
	v.p = D3DXVECTOR3(0, 0, fMin);
	v.c = D3DCOLOR_XRGB(100, 240, 100);
	v2.p = D3DXVECTOR3(0, 0, fMax);
	v2.c = D3DCOLOR_XRGB(100, 240, 100);
	v3.p = D3DXVECTOR3(fMin, 0, 0);
	v3.c = D3DCOLOR_XRGB(100, 240, 100);
	v4.p = D3DXVECTOR3(fMax, 0, 0);
	v4.c = D3DCOLOR_XRGB(100, 240, 100);
	
	m_vecLineVertex.push_back(v);
	m_vecLineVertex.push_back(v2);
	m_vecLineVertex.push_back(v3);
	m_vecLineVertex.push_back(v4);
}

void cMainGame::Draw_Line()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	for (size_t i = 0; i < m_vecLineVertex.size(); i += 2)
	{
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			2, &m_vecLineVertex[i], sizeof(ST_PC_VERTEX));  // 우리가 정의한 면 선 점 
	}
	
}

void cMainGame::Setup_Triangle()
{
	m_vecVertex.push_back(D3DXVECTOR3(-1.0f, -1.0f, -1.0f));
	m_vecVertex.push_back(D3DXVECTOR3(-1.0f, 1.0f, -1.0f));
	m_vecVertex.push_back(D3DXVECTOR3(1.0f, 1.0f, -1.0f));
	m_vecVertex.push_back(D3DXVECTOR3(1.0f, -1.0f, -1.0f));

	m_vecVertex.push_back(D3DXVECTOR3(-1.0f, -1.0f, 1.0f));
	m_vecVertex.push_back(D3DXVECTOR3(-1.0f, 1.0f, 1.0f));
	m_vecVertex.push_back(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_vecVertex.push_back(D3DXVECTOR3(1.0f, -1.0f, 1.0f));
	
	// front

	m_vecIndex.push_back((0));
	m_vecIndex.push_back((1));
	m_vecIndex.push_back((2));

	m_vecIndex.push_back((0));
	m_vecIndex.push_back((2));
	m_vecIndex.push_back((3));

	// back
	m_vecIndex.push_back((4));
	m_vecIndex.push_back((6));
	m_vecIndex.push_back((5));

	m_vecIndex.push_back((4));
	m_vecIndex.push_back((7));
	m_vecIndex.push_back((6));

	//left
	m_vecIndex.push_back((4));
	m_vecIndex.push_back((5));
	m_vecIndex.push_back((1));

	m_vecIndex.push_back((4));
	m_vecIndex.push_back((1));
	m_vecIndex.push_back((0));
	//right
	m_vecIndex.push_back((3));
	m_vecIndex.push_back((2));
	m_vecIndex.push_back((6));

	m_vecIndex.push_back((3));
	m_vecIndex.push_back((6));
	m_vecIndex.push_back((7));

	//up
	m_vecIndex.push_back((1));
	m_vecIndex.push_back((5));
	m_vecIndex.push_back((6));

	m_vecIndex.push_back((1));
	m_vecIndex.push_back((6));
	m_vecIndex.push_back((2));

	//down
	m_vecIndex.push_back((4));
	m_vecIndex.push_back((0));
	m_vecIndex.push_back((3));

	m_vecIndex.push_back((4));
	m_vecIndex.push_back((3));
	m_vecIndex.push_back((7));

	m_vecGizmoP.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_vecGizmoP.push_back(D3DXVECTOR3(-0.25f, 1.5f, 0.25f));
	m_vecGizmoP.push_back(D3DXVECTOR3(-0.25f, 1.5f, -0.25f));
	m_vecGizmoP.push_back(D3DXVECTOR3(0.25f, 1.5f, 0.25f));
	m_vecGizmoP.push_back(D3DXVECTOR3(0.25f, 1.5f, -0.25f));

	//front
	m_GizmoIndex.push_back((0));
	m_GizmoIndex.push_back((2));
	m_GizmoIndex.push_back((4));
	
	//back
	m_GizmoIndex.push_back((0));
	m_GizmoIndex.push_back((3));
	m_GizmoIndex.push_back((1));
	
	//left
	m_GizmoIndex.push_back((0));
	m_GizmoIndex.push_back((1));
	m_GizmoIndex.push_back((2));
	
	//right
	m_GizmoIndex.push_back((0));
	m_GizmoIndex.push_back((4));
	m_GizmoIndex.push_back((3));
	
	//up down
	m_GizmoIndex.push_back((2));
	m_GizmoIndex.push_back((1));
	m_GizmoIndex.push_back((4));
	
	//up up
	m_GizmoIndex.push_back((4));
	m_GizmoIndex.push_back((1));
	m_GizmoIndex.push_back((3));

	for (size_t i = 0; i < m_vecIndex.size(); i += 6)
	{
		ST_PC_VERTEX v;
		ST_PC_VERTEX v2;
		ST_PC_VERTEX v3;
		
		int randColor = rand() % 256;
		int randColor2 = rand() % 256;
		int randColor3 = rand() % 256;

		v.c = D3DCOLOR_XRGB(randColor, randColor2, randColor3);
		v.p = m_vecVertex[m_vecIndex[i + 0]];
		v2.c = D3DCOLOR_XRGB(randColor, randColor2, randColor3);
		v2.p = m_vecVertex[m_vecIndex[i + 1]];
		v3.c = D3DCOLOR_XRGB(randColor, randColor2, randColor3);
		v3.p = m_vecVertex[m_vecIndex[i + 2]];

		m_vecTriangleVertex.push_back(v);
		m_vecTriangleVertex.push_back(v2);
		m_vecTriangleVertex.push_back(v3);
		
		v.c = D3DCOLOR_XRGB(randColor, randColor2, randColor3);
		v.p = m_vecVertex[m_vecIndex[i + 3]];
		v2.c = D3DCOLOR_XRGB(randColor, randColor2, randColor3);
		v2.p = m_vecVertex[m_vecIndex[i + 4]];
		v3.c = D3DCOLOR_XRGB(randColor, randColor2, randColor3);
		v3.p = m_vecVertex[m_vecIndex[i + 5]];
		
		m_vecTriangleVertex.push_back(v);
		m_vecTriangleVertex.push_back(v2);
		m_vecTriangleVertex.push_back(v3);
		
	}
	
	for (size_t i = 0; i < m_GizmoIndex.size(); i += 3)
	{
		ST_PC_VERTEX v;
		ST_PC_VERTEX v2;
		ST_PC_VERTEX v3;
		
		v.p = m_vecGizmoP[m_GizmoIndex[i + 0]];
		v2.p = m_vecGizmoP[m_GizmoIndex[i + 1]];
		v3.p = m_vecGizmoP[m_GizmoIndex[i + 2]];

		m_vecGizmo.push_back(v);
		m_vecGizmo.push_back(v2);
		m_vecGizmo.push_back(v3);

	}
	
}

void cMainGame::Draw_Triangle()
{
	D3DXMATRIXA16 matWorld;
	
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixRotationY(&matRot, Angle);
	vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformCoord(&vDirection, &vDirection, &matRot);
	
	D3DXMatrixTranslation(&matTrans, vPosition.x, vPosition.y, vPosition.z);

	matWorld = matRot * matTrans;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	
	for (int i = 0; i < m_vecTriangleVertex.size(); i+= 3)
	{	
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			3, &m_vecTriangleVertex[i], sizeof(ST_PC_VERTEX));  // 우리가 정의한 면 선 점 
	}

	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	
	for (int i = 0; i < m_vecGizmo.size(); i += 3)
	{
		m_vecGizmo[i].c = D3DCOLOR_XRGB(0, 255, 0);
		m_vecGizmo[i + 1].c = D3DCOLOR_XRGB(0, 255, 0);
		m_vecGizmo[i + 2].c = D3DCOLOR_XRGB(0, 255, 0);

		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			3, &m_vecGizmo[i], sizeof(ST_PC_VERTEX));  // 우리가 정의한 면 선 점 
	}

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationZ(&matWorld, 90*(D3DX_PI/180));
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	
	for (int i = 0; i < m_vecGizmo.size(); i += 3)
	{
		m_vecGizmo[i].c = D3DCOLOR_XRGB(255, 0, 0);
		m_vecGizmo[i+1].c = D3DCOLOR_XRGB(255, 0, 0);
		m_vecGizmo[i+2].c = D3DCOLOR_XRGB(255, 0, 0);
		
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			3, &m_vecGizmo[i], sizeof(ST_PC_VERTEX));  // 우리가 정의한 면 선 점 
	}

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationX(&matWorld, 90 * (D3DX_PI / 180));

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	
	for (int i = 0; i < m_vecGizmo.size(); i += 3)
	{
		m_vecGizmo[i].c = D3DCOLOR_XRGB(0, 0, 255);
		m_vecGizmo[i + 1].c = D3DCOLOR_XRGB(0, 0, 255);
		m_vecGizmo[i + 2].c = D3DCOLOR_XRGB(0, 0, 255);

		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			3, &m_vecGizmo[i], sizeof(ST_PC_VERTEX));  // 우리가 정의한 면 선 점 
	}
}

void cMainGame::Update_Move()
{
	if (GetKeyState('W') & 0x8000)
	{
		vPosition = vPosition + (vDirection * 0.1f);
		vEye = vEye + (vDirection * 0.1f);;
	}
	if (GetKeyState('S') & 0x8000)
	{
		vPosition = vPosition - (vDirection * 0.1f);
		vEye = vEye - (vDirection * 0.1f);;
	}
}

void cMainGame::Update_Rotation()
{
	if (GetKeyState('A') & 0x8000)
	{
		Angle += 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		Angle -= 0.1f;
	}
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isLButtonDown = true;
		break;
	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		break;
	case WM_MOUSEWHEEL:
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f);
		if (m_fCameraDistance < 0.0001f)
			m_fCameraDistance = 0.0001f;
		break;
	case WM_MOUSEMOVE:
		if (m_isLButtonDown)
		{
			POINT ptCurMouse;
			ptCurMouse.x = LOWORD(lParam);
			ptCurMouse.y = HIWORD(lParam);
			float fDeltaX = (float)ptCurMouse.x - m_ptPrevMouse.x;
			float fDeltaY = (float)ptCurMouse.y - m_ptPrevMouse.y;
			m_vCamRotAngle.y += (fDeltaX / 100.f);
			m_vCamRotAngle.x += (fDeltaY / 100.f);

			if (m_vCamRotAngle.x < -D3DX_PI / 2.0f + 0.0001f)
				m_vCamRotAngle.x = -D3DX_PI / 2.0f + 0.0001f;
			if (m_vCamRotAngle.x > D3DX_PI / 2.0f - 0.0001f)
				m_vCamRotAngle.x = D3DX_PI / 2.0f - 0.0001f;

			m_ptPrevMouse = ptCurMouse;

		}
	}
}

