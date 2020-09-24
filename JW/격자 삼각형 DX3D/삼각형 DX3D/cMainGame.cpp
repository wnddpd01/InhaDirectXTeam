#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"

cMainGame::cMainGame()
{
	
}


cMainGame::~cMainGame()
{
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	Setup_Line();
	Setup_Triangle();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false); // 선생님 추가

}



void cMainGame::Update()
{
}

void cMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, -5.0f);
	D3DXVECTOR3 vLookAt = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0,1, 0);

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f,
		rc.right / (float)rc.bottom,
		1.0f,
		1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	
	// D3DXVec3TransformNormal();

	
	if (NULL == g_pD3DDevice)
		return;
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET| D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(47,121,112), 1.0f, 0);
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		Draw_Line();
		/*Draw_Triangle();*/
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
	float length = 10;
	float num = 1;
	float z = length *  num;
	float x = -length * num;
	float y = -num;
	for (int i = 0; i <= length; ++i)
	{
		ST_PC_VERTEX v;
		ST_PC_VERTEX v2;
		ST_PC_VERTEX v3;
		ST_PC_VERTEX v4;
		ST_PC_VERTEX v5;
		ST_PC_VERTEX v6;
		ST_PC_VERTEX v7;
		ST_PC_VERTEX v8;

		/////가로
		v.p = D3DXVECTOR3(z, y, i);
		v2.p = D3DXVECTOR3(x, y, i);
		v3.p = D3DXVECTOR3(z, y, -i);
		v4.p = D3DXVECTOR3(x, y, -i);
		m_vecLineVertex.push_back(v);
		m_vecLineVertex.push_back(v2);
		m_vecLineVertex.push_back(v3);
		m_vecLineVertex.push_back(v4);


		////////세로
		v5.p = D3DXVECTOR3(i, y, x);
		v6.p = D3DXVECTOR3(i, y, z);
		v7.p = D3DXVECTOR3(-i, y, x);
		v8.p = D3DXVECTOR3(-i, y, z);

		m_vecLineVertex.push_back(v5);
		m_vecLineVertex.push_back(v6);
		m_vecLineVertex.push_back(v7);
		m_vecLineVertex.push_back(v8);
	}


	//중간 선
	ST_PC_VERTEX v;
	ST_PC_VERTEX v2;
	ST_PC_VERTEX v3;
	ST_PC_VERTEX v4;

	v.p = D3DXVECTOR3(0, y, length);
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v2.p = D3DXVECTOR3(0, y, -length);
	v2.c = D3DCOLOR_XRGB(255, 0, 0);
	v3.p = D3DXVECTOR3(length, y, 0);
	v3.c = D3DCOLOR_XRGB(255, 0, 0);
	v4.p = D3DXVECTOR3(-length, y, 0);
	v4.c = D3DCOLOR_XRGB(255, 0, 0);
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
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecLineVertex.size() / 2, &m_vecLineVertex[0],
		sizeof(ST_PC_VERTEX)); // 매개변수 점을 그릴래 선을 그릴래 뭘 그릴래
}


void cMainGame::Setup_Triangle()
{
	ST_PC_VERTEX v;
	
	//v.c = D3DCOLOR_XRGB(255,0,0);
	
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);  // 삼각형 색 바꾸고 싶으면 v.c 주석처리를 한다.
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	m_vecTriangleVertex.push_back(v);

	//v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_vecTriangleVertex.push_back(v);

	//v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_vecTriangleVertex.push_back(v);
}

void cMainGame::Draw_Triangle()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	/*g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);*/

	D3DXVECTOR3 vPosition = D3DXVECTOR3(1, 0, 5);
	D3DXMatrixTranslation(&matWorld, vPosition.x, vPosition.y, vPosition.z);

	
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecTriangleVertex.size()/3,
		&m_vecTriangleVertex[0],
		sizeof(ST_PC_VERTEX));
}





