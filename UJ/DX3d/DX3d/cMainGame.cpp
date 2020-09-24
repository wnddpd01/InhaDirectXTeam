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
	m_isLButtonDown = false;
	m_vPosition = {0, 0, 0};
	m_vBoxDirection = { 0, 0, 1 };
	m_fBoxRotY = 0;
	m_vCamRotAngle = { 0, 0, 0 };
	m_fCameraDist = 15;
	Setup_Line();
	Setup_Box();
	Setup_Gzimo();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);	//조명 끄기
}

void cMainGame::Update()
{
	Update_Move();
	Update_Rotation();
}

void cMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXVECTOR3 vEye = D3DXVECTOR3(0, m_fCameraDist, -m_fCameraDist);
	D3DXVECTOR3 vLookAt = m_vPosition;
	D3DXVECTOR3 vUp = { 0, 1, 0 };

	D3DXMATRIX camRotX;
	D3DXMatrixRotationX(&camRotX, m_vCamRotAngle.x);
	D3DXMATRIX camRotY;
	D3DXMatrixRotationY(&camRotY, m_vCamRotAngle.y);
	D3DXMATRIX camRotZ;
	
	D3DXMatrixRotationY(&camRotZ, m_vCamRotAngle.z += 0.005f);
	D3DXVec3TransformCoord(&vEye, &vEye, &(camRotX * camRotY * camRotZ));

	vEye = vEye + m_vPosition;
	
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	if(g_pD3DDevice)
	{
		g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(47, 121, 112), 1.0f, 0);
		//g_pD3DDevice->Present(0, 0, 0, 0);
	}

	//D3DXMatrixRotationY()
	//D3DXVec3TransformNormal()
	
	g_pD3DDevice->BeginScene();
	
	Draw_Line();
	Draw_Triangle();
	Draw_Gzimo();
	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
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
			m_vCamRotAngle.y += (fDeltaX / 100.0f);
			m_vCamRotAngle.x += (fDeltaY / 100.0f);
			Render();
			if (m_vCamRotAngle.x < -D3DX_PI / 2.0f + 0.0001f)
				m_vCamRotAngle.x = -D3DX_PI / 2.0f + 0.0001f;
			if (m_vCamRotAngle.x > D3DX_PI / 2.0f - 0.0001f)
				m_vCamRotAngle.x = D3DX_PI / 2.0f - 0.0001f;
			m_ptPrevMouse = ptCurMouse;
		}
		break;
	case WM_MOUSEWHEEL:
	{
		//카메라 축소 확대
		m_fCameraDist -= GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f;
		if (m_fCameraDist < 0.00001f)
			m_fCameraDist = 0.00001f;
	}
	break;
	default:
		break;
	}
}

void cMainGame::Setup_Line()
{
	ST_PC_VERTEX v;

	/*float start_x = -GRID_COL / 2 * GRID_SIZE;
	float start_z = GRID_ROW / 2 * GRID_SIZE;
	

	v.p = D3DXVECTOR3(start_x, 0, start_z);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(start_x, 0, start_z - GRID_SIZE);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(-5, 0, -GRID_COUNT / 2);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(5, 0, -GRID_COUNT / 2);
	m_vecLineVertex.push_back(v);*/

	v.c = D3DCOLOR_XRGB(195, 195, 195);
	v.p = D3DXVECTOR3((GRID_COL / 2) * -GRID_SIZE, 0, -(GRID_COL / 2) * GRID_SIZE);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3((GRID_COL / 2) * GRID_SIZE, 0, -(GRID_COL / 2) * GRID_SIZE);
	m_vecLineVertex.push_back(v);
	
	for (int i = 0; i < GRID_ROW; i++)
	{
		int z = i * GRID_SIZE - (GRID_ROW / 2 - 1) * GRID_SIZE;
		v.c = D3DCOLOR_XRGB(195, 195, 195);
		v.p = D3DXVECTOR3((GRID_COL / 2) * GRID_SIZE, 0, z);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3((GRID_COL / 2) * GRID_SIZE, 0, z - GRID_SIZE);
		m_vecLineVertex.push_back(v);
		for (int j = 0; j < GRID_COL; j++)
		{
			int x = j * GRID_SIZE - (GRID_COL / 2) * GRID_SIZE;
			v.c = D3DCOLOR_XRGB(195, 195, 195);
			v.p = D3DXVECTOR3(x, 0, z);
			m_vecLineVertex.push_back(v);
			v.p = D3DXVECTOR3(x, 0, z - GRID_SIZE);
			m_vecLineVertex.push_back(v);
			v.p = D3DXVECTOR3(x, 0, z);
			m_vecLineVertex.push_back(v);
			v.p = D3DXVECTOR3(x + GRID_SIZE, 0, z);
			m_vecLineVertex.push_back(v);
			v.c = D3DCOLOR_XRGB(128, 128, 128);
			for (int k = 1; k < GRID_SIZE; k++)
			{
				v.p = D3DXVECTOR3(x + k, 0, z);
				m_vecLineVertex.push_back(v);
				v.p = D3DXVECTOR3(x + k, 0, z - GRID_SIZE);
				m_vecLineVertex.push_back(v);
				v.p = D3DXVECTOR3(x, 0, z - k);
				m_vecLineVertex.push_back(v);
				v.p = D3DXVECTOR3(x + GRID_SIZE, 0, z - k);
				m_vecLineVertex.push_back(v);
			}
		}
	}

	v.c = D3DCOLOR_XRGB(234, 17, 17);
	v.p = D3DXVECTOR3((GRID_COL / 2) * -GRID_SIZE, 0, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3((GRID_COL / 2) * GRID_SIZE, 0, 0);
	m_vecLineVertex.push_back(v);


	v.c = D3DCOLOR_XRGB(17, 234, 17);
	v.p = D3DXVECTOR3(0, (GRID_COL / 2) * -GRID_SIZE, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, (GRID_COL / 2) * GRID_SIZE, 0);
	m_vecLineVertex.push_back(v);


	v.c = D3DCOLOR_XRGB(17, 17, 234);
	v.p = D3DXVECTOR3(0, 0, (GRID_COL / 2) * GRID_SIZE);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, (GRID_COL / 2) * -GRID_SIZE);
	m_vecLineVertex.push_back(v);
	//v.c = D3DCOLOR_XRGB(128, 128, 128);
	//v.p = D3DXVECTOR3(-GRID_COUNT / 2, 0, -5);
	//m_vecLineVertex.push_back(v);
	//v.p = D3DXVECTOR3(-GRID_COUNT / 2, 0, 5);
	//m_vecLineVertex.push_back(v);
	//v.p = D3DXVECTOR3(-5, 0, -GRID_COUNT / 2);
	//m_vecLineVertex.push_back(v);
	//v.p = D3DXVECTOR3(5, 0, -GRID_COUNT / 2);
	//m_vecLineVertex.push_back(v);
	//for (int i = 1; i < GRID_COUNT; i++)
	//{
	//	v.c = D3DCOLOR_XRGB(195, 195, 195);
	//	v.p = D3DXVECTOR3(-GRID_COUNT / 2 + i, 0, -5);
	//	m_vecLineVertex.push_back(v);
	//	v.p = D3DXVECTOR3(-GRID_COUNT / 2 + i, 0, 5);
	//	m_vecLineVertex.push_back(v);
	//	v.p = D3DXVECTOR3(-5, 0, -GRID_COUNT / 2 + i);
	//	m_vecLineVertex.push_back(v);
	//	v.p = D3DXVECTOR3(5, 0, -GRID_COUNT / 2 + i);
	//	m_vecLineVertex.push_back(v);
	//}
	//v.c = D3DCOLOR_XRGB(128, 128, 128);
	//v.p = D3DXVECTOR3(GRID_COUNT / 2, 0, -5);
	//m_vecLineVertex.push_back(v);
	//v.p = D3DXVECTOR3(GRID_COUNT / 2, 0, 5);
	//m_vecLineVertex.push_back(v);
	//v.p = D3DXVECTOR3(-5, 0, GRID_COUNT / 2);
	//m_vecLineVertex.push_back(v);
	//v.p = D3DXVECTOR3(5, 0, GRID_COUNT / 2);
	//m_vecLineVertex.push_back(v);
	/*ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(240, 100, 100);
	v.p = D3DXVECTOR3(0, 2, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, -2, 0);
	m_vecLineVertex.push_back(v);*/
}

void cMainGame::Draw_Line()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	// 나중에 찾기
	/*for (size_t i = 0; i < m_vecLineVertex.size(); i += 2)
	{
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &m_vecLineVertex[i],
			sizeof(ST_PC_VERTEX));
	}*/
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecLineVertex.size() /2 , &m_vecLineVertex[0],
		sizeof(ST_PC_VERTEX));
}

void cMainGame::Setup_Triangle()
{
	srand((unsigned int)time(0));
	ST_PC_VERTEX	v;
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 0);
	m_vecTriangleVertex.push_back(v);
	
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 0);
	m_vecTriangleVertex.push_back(v);
	
	v.p = D3DXVECTOR3(1.0f, 1.0f, 0);
	m_vecTriangleVertex.push_back(v);
}

void cMainGame::Draw_Triangle()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXVECTOR3 vPosition = m_vPosition;
	D3DXMATRIXA16 matRot,matTran;
	D3DXMatrixRotationY(&matRot, m_fBoxRotY);
	D3DXMatrixTranslation(&matTran, vPosition.x, vPosition.y, vPosition.z);

	matWorld = matWorld * matRot * matTran;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecTriangleVertex.size() / 3, &m_vecTriangleVertex[0],
		sizeof(ST_PC_VERTEX));
	LPD3DXMESH m_mesh;
	//D3DXCreateSphere(g_pD3DDevice, 3.0f, 50, 100, &m_SphereMesh, NULL);
	D3DXCreateTeapot(g_pD3DDevice, &m_mesh, NULL);
	m_mesh->DrawSubset(0);

}

void cMainGame::Setup_Box()
{
	m_vecBoxVertex.push_back(D3DXVECTOR3(-1.0f, -1.0f, -1.0f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(-1.0f, 1.0f, -1.0f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(1.0f, 1.0f, -1.0f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(1.0f, -1.0f, -1.0f));

	m_vecBoxVertex.push_back(D3DXVECTOR3(-1.0f, -1.0f, 1.0f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(-1.0f, 1.0f, 1.0f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(1.0f, -1.0f, 1.0f));

	ST_PC_VERTEX v;
	//front = BLUE
	v.c = D3DCOLOR_XRGB(0, 77, 255);
	
	v.p = m_vecBoxVertex[0];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[1];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[2];
	m_vecTriangleVertex.push_back(v);
	
	v.p = m_vecBoxVertex[0];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[2];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[3];
	m_vecTriangleVertex.push_back(v);
	//m_vecTriangleVertex.push_back(v);
	//m_vecBoxIndex.push_back(0);
	//m_vecBoxIndex.push_back(1);
	//m_vecBoxIndex.push_back(2);

	//m_vecBoxIndex.push_back(0);
	//m_vecBoxIndex.push_back(2);
	//m_vecBoxIndex.push_back(3);

	//back == red
	v.c = D3DCOLOR_XRGB(242, 41, 31);
	v.p = m_vecBoxVertex[4];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[5];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[4];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[7];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecTriangleVertex.push_back(v);
	//m_vecBoxIndex.push_back(4);
	//m_vecBoxIndex.push_back(6);
	//m_vecBoxIndex.push_back(5);

	//m_vecBoxIndex.push_back(4);
	//m_vecBoxIndex.push_back(7);
	//m_vecBoxIndex.push_back(6);

	//left == green
	v.c = D3DCOLOR_XRGB(49, 225, 30);
	v.p = m_vecBoxVertex[4];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[5];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[1];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[4];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[1];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[0];
	m_vecTriangleVertex.push_back(v);
	//m_vecBoxIndex.push_back(4);
	//m_vecBoxIndex.push_back(5);
	//m_vecBoxIndex.push_back(1);

	//m_vecBoxIndex.push_back(4);
	//m_vecBoxIndex.push_back(1);
	//m_vecBoxIndex.push_back(0);

	//right == purple
	v.c = D3DCOLOR_XRGB(221, 34, 207);
	v.p = m_vecBoxVertex[3];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[2];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[3];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[7];
	m_vecTriangleVertex.push_back(v);
	//m_vecBoxIndex.push_back(3);
	//m_vecBoxIndex.push_back(2);
	//m_vecBoxIndex.push_back(6);

	//m_vecBoxIndex.push_back(3);
	//m_vecBoxIndex.push_back(6);
	//m_vecBoxIndex.push_back(7);

	//top == yellow
	v.c = D3DCOLOR_XRGB(219, 209, 36);
	v.p = m_vecBoxVertex[1];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[5];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[1];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[2];
	m_vecTriangleVertex.push_back(v);
	//m_vecBoxIndex.push_back(1);
	//m_vecBoxIndex.push_back(5);
	//m_vecBoxIndex.push_back(6);

	//m_vecBoxIndex.push_back(1);
	//m_vecBoxIndex.push_back(6);
	//m_vecBoxIndex.push_back(2);

	//bottom
	v.c = D3DCOLOR_XRGB(205, 50, 123);
	v.p = m_vecBoxVertex[4];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[0];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[3];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[4];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[3];
	m_vecTriangleVertex.push_back(v);
	v.p = m_vecBoxVertex[7];
	m_vecTriangleVertex.push_back(v);
	//m_vecBoxIndex.push_back(4);
	//m_vecBoxIndex.push_back(0);
	//m_vecBoxIndex.push_back(3);

	//m_vecBoxIndex.push_back(4);
	//m_vecBoxIndex.push_back(3);
	//m_vecBoxIndex.push_back(7);
}

void cMainGame::Setup_Grid()
{
	ST_PC_VERTEX v;
	int nNumHalfTile = 5;
	float fInterval = 1.0f;
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;

	//for (int i = 1; i <= nNumHalfTile; i++)
	//{
	//	v.p = D3DXVECTOR3(fMin, 0, i*fInterval);
	//	m_vecLineVertex.push_back(v);
	//	v.p = D3DXVECTOR3(fMax, 0, i*fInterval);
	//	m_vecLineVertex.push_back(v);

	//	m_vecLineVertex.push_back(D3DXVECTOR3(fMin, 0, -i*fInterval, 1));
	//	m_vecLineVertex.push_back(D3DXVECTOR3(fMax, 0, -i*fInterval, 1));

	//	m_vecLineVertex.push_back(D3DXVECTOR3(i*fInterval, 0, fMin, 1));
	//	m_vecLineVertex.push_back(D3DXVECTOR3(i*fInterval, 0, fMax, 1));

	//	m_vecLineVertex.push_back(D3DXVECTOR3(-i*fInterval, 0, fMin, 1));
	//	m_vecLineVertex.push_back(D3DXVECTOR3(-i*fInterval, 0, fMax, 1));
	//}
	////가운데 선
	//m_vecLineVertex.push_back(D3DXVECTOR3(0, 0, fMin));
	//m_vecLineVertex.push_back(D3DXVECTOR3(0, 0, fMax));

	//m_vecLineVertex.push_back(D3DXVECTOR3(fMin, 0, 0));
	//m_vecLineVertex.push_back(D3DXVECTOR3(fMax, 0, 0));
}

void cMainGame::Setup_Gzimo()
{
	D3DXVECTOR3 originPoint = { 0, 0, 0 };
	vector<D3DXVECTOR3> gzimoVertex;
	D3DXVECTOR3 temp;
	temp = D3DXVECTOR3(3, 0.2, -0.2);
	gzimoVertex.push_back(temp);
	temp = D3DXVECTOR3( 3, 0.2, 0.2 );
	gzimoVertex.push_back(temp);
	temp = D3DXVECTOR3( 3, -0.2, 0.2 );
	gzimoVertex.push_back(temp);
	temp = D3DXVECTOR3(3, -0.2, -0.2);
	gzimoVertex.push_back(temp);

	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(234, 17, 17);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);

	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[3];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[3];
	m_vecGizmo.push_back(v);


	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[3];
	m_vecGizmo.push_back(v);
	gzimoVertex.clear();
	temp = D3DXVECTOR3(-0.2, 3, -0.2);
	gzimoVertex.push_back(temp);
	temp = D3DXVECTOR3(-0.2, 3, 0.2);
	gzimoVertex.push_back(temp);
	temp = D3DXVECTOR3(0.2, 3, 0.2);
	gzimoVertex.push_back(temp);
	temp = D3DXVECTOR3(0.2, 3, -0.2);
	gzimoVertex.push_back(temp);

	v.c = D3DCOLOR_XRGB(17, 234, 17);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);

	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[3];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[3];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);


	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[3];
	m_vecGizmo.push_back(v);

	gzimoVertex.clear();
	temp = D3DXVECTOR3(0.2, 0.2, 3);
	gzimoVertex.push_back(temp);
	temp = D3DXVECTOR3(-0.2, 0.2, 3);
	gzimoVertex.push_back(temp);
	temp = D3DXVECTOR3(-0.2, -0.2, 3);
	gzimoVertex.push_back(temp);
	temp = D3DXVECTOR3(0.2, -0.2, 3);
	gzimoVertex.push_back(temp);

	v.c = D3DCOLOR_XRGB(17, 17, 234);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);

	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[3];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[1];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);

	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[2];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[3];
	m_vecGizmo.push_back(v);


	v.p = originPoint;
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[0];
	m_vecGizmo.push_back(v);
	v.p = gzimoVertex[3];
	m_vecGizmo.push_back(v);
}

void cMainGame::Draw_Gzimo()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	// 나중에 찾기
	/*for (size_t i = 0; i < m_vecLineVertex.size(); i += 2)
	{
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &m_vecLineVertex[i],
	sizeof(ST_PC_VERTEX));
	}*/
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecGizmo.size() / 3, &m_vecGizmo[0],
		sizeof(ST_PC_VERTEX));
}

void cMainGame::Draw_Grid()
{
}

void cMainGame::Update_Move()
{
	D3DXMATRIX matRot;
	D3DXMatrixRotationY(&matRot, m_fBoxRotY);

	D3DXVECTOR3 movedir;
	D3DXVec3TransformNormal(&movedir, &m_vBoxDirection, &matRot);
	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + (movedir * 0.1f);
	}
	else if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - (movedir * 0.1f);
	}
}

void cMainGame::Update_Rotation()
{
	if (GetKeyState('A') & 0x8000)
		m_fBoxRotY -= 0.1;
	else if (GetKeyState('D') & 0x8000)
		m_fBoxRotY += 0.1;
}
