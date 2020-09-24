#include "stdafx.h"
#include "cMainGame.h"

#define GRID_ROW 30
#define GRID_COL 30

cMainGame::cMainGame() : m_hBitmap(NULL), m_vEye(0, 0, -5, 1), m_vLookat(0, 0, 0, 1), m_vUp(0, 1, 0, 1),
						m_vPosition(0, 0, 0, 1), m_fCameraDist(5.0f), m_isLButtonDown(false), m_vCamRotAngle(0, 0, 0, 1),
						m_fBoxRotY(0.0f), m_vBoxDirection(0, 0, 1, 1)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}

cMainGame::~cMainGame()
{
	SelectObject(m_MemDc, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_MemDc);
}

void cMainGame::SetUp()
{
	HDC hdc = GetDC(g_hWnd);
	m_MemDc = CreateCompatibleDC(hdc);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	m_hOldBitmap = (HBITMAP)SelectObject(m_MemDc, m_hBitmap);
	ReleaseDC(g_hWnd, hdc);

	m_vecVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f, 1));
	m_vecVertex.push_back(cVector3(-1.0f, 1.0f, -1.0f, 1));
	m_vecVertex.push_back(cVector3(1.0f, 1.0f, -1.0f, 1));
	m_vecVertex.push_back(cVector3(1.0f, -1.0f, -1.0f, 1));
	
	m_vecVertex.push_back(cVector3(-1.0f, -1.0f, 1.0f, 1));
	m_vecVertex.push_back(cVector3(-1.0f, 1.0f, 1.0f, 1));
	m_vecVertex.push_back(cVector3(1.0f, 1.0f, 1.0f, 1));
	m_vecVertex.push_back(cVector3(1.0f, -1.0f, 1.0f, 1));

	//front
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(2);

	m_vecIndex.push_back(0);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);

	//back
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(5);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(6);

	//left
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(1);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(0);

	//right
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(3);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(7);

	//top
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(1);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(2);

	//buttom
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(3);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(7);

	m_matWorld = cMatrix::Identity((4));
	m_matView = cMatrix::Identity((4));
	m_matProj = cMatrix::Identity((4));
	m_matViewport = cMatrix::Identity((4));

	m_vLookat = cVector3(0, 0, 0, 1);
	m_vEye = cVector3(0, 5.0f, -20.0f, 1);
	m_vecFront = cVector3(0, 0, 1, 1);

	for (int i = -(GRID_COL / 2); i <= GRID_COL / 2; i++)
	{
		m_gridVertex.emplace_back(i, 0, -(GRID_COL / 2), 1);
		m_gridVertex.emplace_back(i, 0, GRID_COL / 2, 1);
	}

	for (int i = -(GRID_ROW / 2); i <= GRID_ROW / 2; i++)
	{
		m_gridVertex.emplace_back(-(GRID_ROW / 2), 0, i, 1);
		m_gridVertex.emplace_back(GRID_ROW / 2, 0, i, 1);
	}

	SetGrid();
}

void cMainGame::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	
	Update_Rotation();
	Update_Move();

	cMatrix matRX = cMatrix::RotationX(m_vCamRotAngle.x, true);
	cMatrix matRY = cMatrix::RotationY(m_vCamRotAngle.y, true);
	cMatrix matR = matRX * matRY;

	m_vEye = cVector3(0, m_fCameraDist, -m_fCameraDist, 1);
	m_vEye = cVector3::TransformCoord(m_vEye, matR);

	m_vLookat = m_vPosition;
	m_vEye = m_vEye + m_vPosition;

	matR = cMatrix::RotationY(m_fBoxRotY);
	m_vBoxDirection = cVector3(0, 0, 1, 1);
	m_vBoxDirection = cVector3::TransformNormal(m_vBoxDirection, matR);

	m_matWorld = matR * cMatrix::Translation((m_vPosition));
	//m_matWorld = cMatrix::RotationY(0) * cMatrix::Translation(0, 0, 0);
	m_matView = cMatrix::View(m_vEye, m_vLookat, m_vUp);
	m_matProj = cMatrix::Projection(45, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	m_matViewport = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
}

void cMainGame::Render(HDC hdc)
{
	Update();
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	PatBlt(m_MemDc, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);
	
	cMatrix matWVP = m_matWorld * m_matView * m_matProj;
	cVector3 eyeToLook =  m_vLookat - m_vEye;
	for(int i = 0; i < m_vecIndex.size(); i += 3)
	{
		cVector3 v1 = m_vecVertex[m_vecIndex[i + 0]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecIndex[i + 2]];

		v1 = cVector3::TransformCoord(v1, matWVP);
		v2 = cVector3::TransformCoord(v2, matWVP);
		v3 = cVector3::TransformCoord(v3, matWVP);

		v1 = cVector3::TransformCoord(v1, m_matViewport);
		v2 = cVector3::TransformCoord(v2, m_matViewport);
		v3 = cVector3::TransformCoord(v3, m_matViewport);

		cout << m_vCamRotAngle.y << endl;

		/*if (m_vCamRotAngle.y > 1.58 && m_vCamRotAngle.y < 4.7)
		{
			if (cVector3::Dot(cVector3::Cross(v2 - v1, v3 - v2), eyeToLook) > 0)
				continue;
		}
		else
		{
			if (cVector3::Dot(, eyeToLook) < 0)
				continue;
		}*/
		if(cVector3::Cross(v2 - v1, v3 - v2).z <= 0)
			continue;
		CreatePolygonRgn();
		MoveToEx(m_MemDc, v1.x, v1.y, NULL);
		LineTo(m_MemDc, v2.x, v2.y);
		LineTo(m_MemDc, v3.x, v3.y);
		LineTo(m_MemDc, v1.x, v1.y);
	}
	/*m_gridIndex.clear();
		for (cVector3 c_vector3 : m_gridVertex)
			m_gridIndex.push_back(cVector3::TransformCoord(c_vector3, matWVP * m_matViewport));
	
	for (int i = 0; i < (GRID_COL + GRID_ROW) * 2 - 1; i += 2)
	{
		MoveToEx(m_MemDc, m_gridIndex[i].x, m_gridIndex[i].y, NULL);
		LineTo(m_MemDc, m_gridIndex[i + 1].x, m_gridIndex[i + 1].y);
	}*/

	DrawGrid();
	
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDc, 0, 0, SRCCOPY);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*if (GetKeyState(VK_LEFT) & 0x8000)
	{
		for(int i = 0; i < m_vecVertex.size(); i++)
			m_vecVertex[i].x -= 0.2f;
		m_vEye.x -= 0.2f;
		m_vLookat.x -= 0.2f;
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		for (int i = 0; i < m_vecVertex.size(); i++)
			m_vecVertex[i].x += 0.2f;
		m_vEye.x += 0.2f;
		m_vLookat.x += 0.2f;
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		for (int i = 0; i < m_vecVertex.size(); i++)
			m_vecVertex[i] = m_vecVertex[i] + m_vecFront;
		m_vEye = m_vEye + m_vecFront;
		m_vLookat = m_vLookat + m_vecFront;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		for (int i = 0; i < m_vecVertex.size(); i++)
			m_vecVertex[i] = m_vecVertex[i] - m_vecFront;
		m_vEye = m_vEye - m_vecFront;
		m_vLookat = m_vLookat - m_vecFront;
	}

	if (GetKeyState('A') & 0x8000)
	{
		for (int i = 0; i < m_vecVertex.size(); i++)
		{
			m_vecVertex[i] = m_vecVertex[i] - m_vLookat;
			m_vecVertex[i]= cVector3::TransformCoord(m_vecVertex[i] ,cMatrix::RotationY(-1)) + m_vLookat;
		}
		m_vecFront = cVector3::TransformNormal(m_vecFront, cMatrix::RotationY(-1)).Normalize() * 0.1f;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		for (int i = 0; i < m_vecVertex.size(); i++)
		{
			m_vecVertex[i] = m_vecVertex[i] - m_vLookat;
			m_vecVertex[i] = cVector3::TransformCoord(m_vecVertex[i], cMatrix::RotationY(1)) + m_vLookat;
		}
		m_vecFront = cVector3::TransformNormal(m_vecFront, cMatrix::RotationY(1)).Normalize()* 0.1f;
	}*/
	
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
		if(m_isLButtonDown)
		{
			POINT ptCurMouse;
			ptCurMouse.x = LOWORD(lParam);
			ptCurMouse.y = HIWORD(lParam);
			float fDeltaX = (float)ptCurMouse.x - m_ptPrevMouse.x;
			float fDeltaY = (float)ptCurMouse.y - m_ptPrevMouse.y;
			m_vCamRotAngle.y += (fDeltaX / 100.f);
			m_vCamRotAngle.x += (fDeltaY / 100.f);

			if (m_vCamRotAngle.x < -M_PI / 2.0f + 0.0001f)
				m_vCamRotAngle.x = -M_PI / 2.0f + 0.0001f;
			if (m_vCamRotAngle.x > M_PI / 2.0f - 0.0001f)
				m_vCamRotAngle.x = M_PI / 2.0f - 0.0001f;
			if(m_vCamRotAngle.y > 2 * M_PI)
			{
				m_vCamRotAngle.y -= 2 * M_PI;
			}
			m_ptPrevMouse = ptCurMouse;
		}
		switch (message)
		{
		case WM_RBUTTONDOWN:

			break;
		default:
			break;
		}
		//카메라 시점 변경
		break;
	case WM_MOUSEWHEEL:
	{
		//카메라 축소 확대
		m_fCameraDist -= GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f;
		if (m_fCameraDist < 1)
			m_fCameraDist = 1;
		
	}
	break;
	default:
		break;
	}
}

void cMainGame::SetGrid()
{
	int nNumHalfTile = 5;
	float fInterval = 1.0f;
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;

	for(int i = 1; i <= nNumHalfTile; i++)
	{
		m_vecLineVertex.push_back(cVector3(fMin, 0, i*fInterval, 1));
		m_vecLineVertex.push_back(cVector3(fMax, 0, i*fInterval, 1));

		m_vecLineVertex.push_back(cVector3(fMin, 0, -i*fInterval, 1));
		m_vecLineVertex.push_back(cVector3(fMax, 0, -i*fInterval, 1));

		m_vecLineVertex.push_back(cVector3(i*fInterval, 0, fMin, 1));
		m_vecLineVertex.push_back(cVector3(i*fInterval, 0, fMax, 1));

		m_vecLineVertex.push_back(cVector3(-i*fInterval, 0, fMin, 1));
		m_vecLineVertex.push_back(cVector3(-i*fInterval, 0, fMax, 1));
	}
	//가운데 선
	m_vecLineVertex.push_back(cVector3(0, 0, fMin, 1));
	m_vecLineVertex.push_back(cVector3(0, 0, fMax, 1));

	m_vecLineVertex.push_back(cVector3(fMin, 0, 0, 1));
	m_vecLineVertex.push_back(cVector3(fMax, 0, 0, 1));

	m_vAxisXTextPosition = cVector3(fMax, 0, 0, 1);
	m_vAxisZTextPosition = cVector3(0, 0, fMax, 1);
}

void cMainGame::DrawGrid()
{
	cMatrix mat = m_matView * m_matProj * m_matViewport;

	for(int i = 0; i < m_vecLineVertex.size(); i += 2)
	{
		cVector3 v1 = m_vecLineVertex[i + 0];
		cVector3 v2 = m_vecLineVertex[i + 1];

		v1 = cVector3::TransformCoord(v1, mat);
		v2 = cVector3::TransformCoord(v2, mat);
	
		MoveToEx(m_MemDc, v1.x, v1.y, NULL);
		if(v2.y < 0)
			LineTo(m_MemDc, v2.x, 0);
		else
			LineTo(m_MemDc, v2.x, v2.y);
	}

	cVector3 v = m_vAxisXTextPosition;
	v = cVector3::TransformCoord(v, mat);
	TextOut(m_MemDc, v.x, v.y, (LPCWSTR)"X", 1);

	v = m_vAxisZTextPosition;
	v = cVector3::TransformCoord(v, mat);
	TextOut(m_MemDc, v.x, v.y, (LPCWSTR)"Z", 1);
}

void cMainGame::Update_Move()
{
	if(GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + (m_vBoxDirection * 0.1f);
	}
	else if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - (m_vBoxDirection * 0.1f);
	}
}

void cMainGame::Update_Rotation()
{
	if(GetKeyState('A') & 0x8000)
	{
		m_fBoxRotY -= 0.5f;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		m_fBoxRotY += 0.5f;
	}
}
