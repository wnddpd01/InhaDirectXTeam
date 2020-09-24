#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"

cMainGame::cMainGame()
{
	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_vBoxDirection = D3DXVECTOR3(0, 0, 1);
	m_fBoxRotY = 0.0f;
	m_vCamRotAngle = D3DXVECTOR3(0, 0, 0);
	m_fCameraDistance = 10;
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
	m_isLButtonDown = false;
}

cMainGame::~cMainGame()
{
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	Setup_Line();
	Setup_Gizmos();
	Setup_Cube();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false); //조명 끄기
}

void cMainGame::Update()
{
	
	Update_Rotation();
	Update_Move();
	
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	
	D3DXMATRIXA16 matRX;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMATRIXA16 matRY;
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);
	matR = matRX*matRY;
	
	D3DXVECTOR3 vEye = D3DXVECTOR3(0.0f, m_fCameraDistance, -m_fCameraDistance);
	D3DXVec3TransformCoord(&vEye, &vEye, &matR);
	D3DXVECTOR3 vLookAt = m_vPosition;
	vEye = vEye + m_vPosition;
	D3DXVECTOR3 vUp = D3DXVECTOR3(0, 1, 0);

	D3DXMatrixRotationY(&matR, m_fBoxRotY);
	m_vBoxDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vBoxDirection, &m_vBoxDirection, &matR);
	
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	
	/*D3DXMatrixRotationX();
	D3DXVec3TransformNormal();*/

}

void cMainGame::Render()
{	
	g_pD3DDevice->Clear(NULL, NULL, 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
		D3DCOLOR_XRGB(47,121,112), 1.0F, 0);

	g_pD3DDevice->BeginScene();

	Draw_Line();
	Draw_Gizmos();
	Draw_Cube();
	
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::Setup_Line()
{
	ST_PC_VERTEX v;


	int nNumHalfTile2 = 25;
	float fInterval2 = 1.0f;
	float fMax2 = nNumHalfTile2 * fInterval2;
	float fMin2 = -nNumHalfTile2 * fInterval2;

	v.c = D3DCOLOR_XRGB(130, 130, 130);
	for (int i = 1; i <= nNumHalfTile2; i++)
	{
		v.p = D3DXVECTOR3(fMin2, 0, i*fInterval2);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax2, 0, i*fInterval2);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(fMin2, 0, -i*fInterval2);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax2, 0, -i*fInterval2);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval2, 0, fMin2);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval2, 0, fMax2);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval2, 0, fMin2);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval2, 0, fMax2);
		m_vecLineVertex.push_back(v);
	}
	v.p = D3DXVECTOR3(0, 0, fMin2);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax2);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(fMin2, 0, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax2, 0, 0);
	m_vecLineVertex.push_back(v);

	
	
	int nNumHalfTile = 5;
	float fInterval = 5.0f;
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;
	
	v.c = D3DCOLOR_XRGB(250,250,250);
	for (int i = 1; i <= nNumHalfTile; i++)
	{
		v.p = D3DXVECTOR3(fMin, 0, i*fInterval);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i*fInterval);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(fMin, 0, -i*fInterval);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i*fInterval);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval, 0, fMin);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval, 0, fMax);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval, 0, fMin);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval, 0, fMax);
		m_vecLineVertex.push_back(v);
	}
	v.p = D3DXVECTOR3(0, 0, fMin);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(fMin, 0, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0);
	m_vecLineVertex.push_back(v);


}

void cMainGame::Draw_Line()
{

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 
		m_vecLineVertex.size()/2,
		&m_vecLineVertex[0], 
		sizeof(ST_PC_VERTEX));//정의한 점선면
	
}

void cMainGame::Setup_Gizmos()
{
	ST_PC_VERTEX v;
	int nNumHalfTile = 5;
	float fInterval = 5.0f;
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;
	
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0);
	m_vecLineVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0);
	m_vecLineVertex.push_back(v);


	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax);
	m_vecLineVertex.push_back(v);



	ST_PC_VERTEX v2;

	v2.p = D3DXVECTOR3(-0.5f,2.5f,-0.5f);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(-0.5f, 2.5f, 0.5f);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(0.5f, 2.5f, 0.5f);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(-0.5f, 2.5f, -0.5f);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(0.5f, 2.5f, 0.5f);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(0.5f, 2.5f, -0.5f);
	m_vecGizmosVertex.push_back(v2);

	v2.p = D3DXVECTOR3(0, 1.0f, 0);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(-0.5, 2.5f, 0.5f);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(0.5f, 2.5f, 0.5f);
	m_vecGizmosVertex.push_back(v2);

	v2.p = D3DXVECTOR3(0, 1.0f, 0);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(-0.5, 2.5f, -0.5f);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(0.5f, 2.5f, -0.5f);
	m_vecGizmosVertex.push_back(v2);


	v2.p = D3DXVECTOR3(0, 1.0f, 0);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(-0.5f, 2.5f, -0.5f);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(0.5, 2.5f, 0.5f);
	m_vecGizmosVertex.push_back(v2);


	v2.p = D3DXVECTOR3(0, 1.0f, 0);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(-0.5f, 2.5f, 0.5f);
	m_vecGizmosVertex.push_back(v2);
	v2.p = D3DXVECTOR3(-0.5, 2.5f, -0.5f);
	m_vecGizmosVertex.push_back(v2);


	
	
}

void cMainGame::Draw_Gizmos()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecLineVertex.size() / 2,
		&m_vecLineVertex[0],
		sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecGizmosVertex.size() / 3,
		&m_vecGizmosVertex[0],
		sizeof(ST_PC_VERTEX));

	
}

void cMainGame::Setup_Cube()
{
	ST_PC_VERTEX point;
	
	point.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	m_vecVertex.push_back(point);
	point.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	m_vecVertex.push_back(point);
	point.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	m_vecVertex.push_back(point);
	point.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	m_vecVertex.push_back(point);
	point.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	m_vecVertex.push_back(point);
	point.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	m_vecVertex.push_back(point);
	point.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vecVertex.push_back(point);
	point.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	m_vecVertex.push_back(point);

	
	ST_PC_VERTEX v;

	m_vecVertex[0].c = D3DCOLOR_XRGB(255, 255, 0);
	m_vecVertex[1].c = D3DCOLOR_XRGB(255, 255, 0);
	m_vecVertex[2].c = D3DCOLOR_XRGB(255, 255, 0);
	m_vecVertex[3].c = D3DCOLOR_XRGB(255, 255, 0);
	m_vecTriangleVertex.push_back(m_vecVertex[0]);
	m_vecTriangleVertex.push_back(m_vecVertex[1]);
	m_vecTriangleVertex.push_back(m_vecVertex[2]);


	m_vecTriangleVertex.push_back(m_vecVertex[0]);
	m_vecTriangleVertex.push_back(m_vecVertex[2]);
	m_vecTriangleVertex.push_back(m_vecVertex[3]);


	m_vecVertex[4].c = D3DCOLOR_XRGB(255, 255, 200);
	m_vecVertex[5].c = D3DCOLOR_XRGB(255, 255, 200);
	m_vecVertex[6].c = D3DCOLOR_XRGB(255, 255, 200);
	m_vecVertex[7].c = D3DCOLOR_XRGB(255, 255, 200);
	m_vecTriangleVertex.push_back(m_vecVertex[4]);
	m_vecTriangleVertex.push_back(m_vecVertex[6]);
	m_vecTriangleVertex.push_back(m_vecVertex[5]);

	m_vecTriangleVertex.push_back(m_vecVertex[4]);
	m_vecTriangleVertex.push_back(m_vecVertex[7]);
	m_vecTriangleVertex.push_back(m_vecVertex[6]);


	m_vecVertex[4].c = D3DCOLOR_XRGB(255, 0, 200);
	m_vecVertex[5].c = D3DCOLOR_XRGB(255, 0, 200);
	m_vecVertex[1].c = D3DCOLOR_XRGB(255, 0, 200);
	m_vecVertex[0].c = D3DCOLOR_XRGB(255, 0, 200);
	m_vecTriangleVertex.push_back(m_vecVertex[4]);
	m_vecTriangleVertex.push_back(m_vecVertex[5]);
	m_vecTriangleVertex.push_back(m_vecVertex[1]);

	m_vecTriangleVertex.push_back(m_vecVertex[4]);
	m_vecTriangleVertex.push_back(m_vecVertex[1]);
	m_vecTriangleVertex.push_back(m_vecVertex[0]);



	m_vecVertex[2].c = D3DCOLOR_XRGB(100, 50, 200);
	m_vecVertex[3].c = D3DCOLOR_XRGB(100, 50, 200);
	m_vecVertex[6].c = D3DCOLOR_XRGB(100, 50, 200);
	m_vecVertex[7].c = D3DCOLOR_XRGB(100, 50, 200);
	m_vecTriangleVertex.push_back(m_vecVertex[3]);
	m_vecTriangleVertex.push_back(m_vecVertex[2]);
	m_vecTriangleVertex.push_back(m_vecVertex[6]);

	m_vecTriangleVertex.push_back(m_vecVertex[3]);
	m_vecTriangleVertex.push_back(m_vecVertex[6]);
	m_vecTriangleVertex.push_back(m_vecVertex[7]);


	m_vecVertex[1].c = D3DCOLOR_XRGB(100, 220, 200);
	m_vecVertex[2].c = D3DCOLOR_XRGB(100, 220, 200);
	m_vecVertex[5].c = D3DCOLOR_XRGB(100, 220, 200);
	m_vecVertex[6].c = D3DCOLOR_XRGB(100, 220, 200);
	m_vecTriangleVertex.push_back(m_vecVertex[1]);
	m_vecTriangleVertex.push_back(m_vecVertex[5]);
	m_vecTriangleVertex.push_back(m_vecVertex[6]);

	m_vecTriangleVertex.push_back(m_vecVertex[1]);
	m_vecTriangleVertex.push_back(m_vecVertex[6]);
	m_vecTriangleVertex.push_back(m_vecVertex[2]);



	m_vecVertex[0].c = D3DCOLOR_XRGB(100, 0, 150);
	m_vecVertex[3].c = D3DCOLOR_XRGB(100, 0, 150);
	m_vecVertex[4].c = D3DCOLOR_XRGB(100, 0, 150);
	m_vecVertex[7].c = D3DCOLOR_XRGB(100, 0, 150);
	m_vecTriangleVertex.push_back(m_vecVertex[4]);
	m_vecTriangleVertex.push_back(m_vecVertex[0]);
	m_vecTriangleVertex.push_back(m_vecVertex[3]);

	m_vecTriangleVertex.push_back(m_vecVertex[4]);
	m_vecTriangleVertex.push_back(m_vecVertex[3]);
	m_vecTriangleVertex.push_back(m_vecVertex[7]);




	
}

void cMainGame::Draw_Cube()
{
	D3DXMATRIXA16 matWorld , R , T;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&T, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	matWorld = matWorld * matR * T;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecTriangleVertex.size()/3,
		&m_vecTriangleVertex[0],
		sizeof(ST_PC_VERTEX));
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

			m_ptPrevMouse = ptCurMouse;
		}
		break;
	case WM_MOUSEWHEEL:
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f);
		if (m_fCameraDistance < 0.0001f)
			m_fCameraDistance = 0.0001f;
		break;
	default:
		break;
	}
}

void cMainGame::Update_Rotation()
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fBoxRotY -= 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_fBoxRotY += 0.1f;
	}
	
}

void cMainGame::Update_Move()
{
	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + (m_vBoxDirection*0.1f);
	}
	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - (m_vBoxDirection*0.1f);
	}
	
}
