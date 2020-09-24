#include "stdafx.h"
#include "Object.h"


void Object::SetGizmo()
{
	ST_PC_VERTEX ver;
	ver.c = D3DCOLOR_XRGB(255, 0, 0);

	ver.p = D3DXVECTOR3(0, 0, 0);
	m_vecGizmoVertex.push_back(ver);
	
	ver.p = D3DXVECTOR3(1.f, 0.1f, 0.1f);
	m_vecGizmoVertex.push_back(ver);
	ver.p = D3DXVECTOR3(1.f, 0.1f, -0.1f);
	m_vecGizmoVertex.push_back(ver);
	ver.p = D3DXVECTOR3(1.f, -0.1f, -0.1f);
	m_vecGizmoVertex.push_back(ver);
	ver.p = D3DXVECTOR3(1.f, -0.1f, 0.1f);
	m_vecGizmoVertex.push_back(ver);

	ver.p = D3DXVECTOR3(0.1f, 1.f, 0.1f);
	m_vecGizmoVertex.push_back(ver);
	ver.p = D3DXVECTOR3(0.1f, 1.f, -0.1f);
	m_vecGizmoVertex.push_back(ver);
	ver.p = D3DXVECTOR3(-0.1f, 1.f, -0.1f);
	m_vecGizmoVertex.push_back(ver);
	ver.p = D3DXVECTOR3(-0.1f, 1.f, 0.1f);
	m_vecGizmoVertex.push_back(ver);

	ver.p = D3DXVECTOR3(0.1f, 0.1f, 1.f);
	m_vecGizmoVertex.push_back(ver);
	ver.p = D3DXVECTOR3(0.1f, -0.1f, 1.f);
	m_vecGizmoVertex.push_back(ver);
	ver.p = D3DXVECTOR3(-0.1f, -0.1f, 1.f);
	m_vecGizmoVertex.push_back(ver);
	ver.p = D3DXVECTOR3(-0.1f, 0.1f, 1.f);
	m_vecGizmoVertex.push_back(ver);

	ST_TRIANGLE v;
	//앞
	v.index[0] = 0;
	v.index[1] = 5;
	v.index[2] = 6;
	m_vecGizmoTriangle.push_back(v);
	v.index[0] = 0;
	v.index[1] = 6;
	v.index[2] = 7;
	m_vecGizmoTriangle.push_back(v);
	v.index[0] = 0;
	v.index[1] = 7;
	v.index[2] = 8;
	m_vecGizmoTriangle.push_back(v);
	v.index[0] = 0;
	v.index[1] = 8;
	v.index[2] = 5;
	m_vecGizmoTriangle.push_back(v);

	//뒤
	v.index[0] = 0;
	v.index[1] = 1;
	v.index[2] = 2;
	m_vecGizmoTriangle.push_back(v);
	v.index[0] = 0;
	v.index[1] = 2;
	v.index[2] = 3;
	m_vecGizmoTriangle.push_back(v);
	v.index[0] = 0;
	v.index[1] = 3;
	v.index[2] = 4;
	m_vecGizmoTriangle.push_back(v);
	v.index[0] = 0;
	v.index[1] = 3;
	v.index[2] = 1;
	m_vecGizmoTriangle.push_back(v);

	v.index[0] = 0;
	v.index[1] = 9;
	v.index[2] = 10;
	m_vecGizmoTriangle.push_back(v);
	v.index[0] = 0;
	v.index[1] = 10;
	v.index[2] = 11;
	m_vecGizmoTriangle.push_back(v);
	v.index[0] = 0;
	v.index[1] = 11;
	v.index[2] = 12;
	m_vecGizmoTriangle.push_back(v);
	v.index[0] = 0;
	v.index[1] = 12;
	v.index[2] = 9;
	m_vecGizmoTriangle.push_back(v);
}

void Object::DrawGizmo()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	for (auto i : m_vecGizmoTriangle)
	{
		ST_PC_VERTEX tempTri[3] = {
			m_vecGizmoVertex[i.index[0]] ,
			m_vecGizmoVertex[i.index[1]] ,
			m_vecGizmoVertex[i.index[2]] };

			tempTri[2].c = tempTri[1].c = tempTri[0].c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			1,
			&tempTri[0],
			sizeof(ST_PC_VERTEX));
	}
}

Object::Object(int shape)
{

	vPosition = D3DXVECTOR3(0, 0, 0);
	vRotation = D3DXVECTOR3(0, 0, 0);
	vScale = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_dir = D3DXVECTOR3(0, 0, 1.f);
	m_shape = shape;


	color[0] = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	color[1] = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	color[2] = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	color[3] = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	color[4] = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	color[5] = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
		
	
	SetUp();
}

Object::~Object()
{
}

void Object::SetUp()
{
	ST_PC_VERTEX ver;
	ST_PC_VERTEX gridver;
	
	switch (m_shape)
	{
	case CUBE:
	
		ver.c = D3DCOLOR_XRGB(255,0,255);
		ver.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
		m_vecVertex.push_back(ver);
		ver.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
		m_vecVertex.push_back(ver);
		ver.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
		m_vecVertex.push_back(ver);
		ver.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
		m_vecVertex.push_back(ver);

		ver.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
		m_vecVertex.push_back(ver);
		ver.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
		m_vecVertex.push_back(ver);
		ver.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_vecVertex.push_back(ver);
		ver.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
		m_vecVertex.push_back(ver);
		
		
		ST_TRIANGLE v;
		//앞
		v.index[0] = 0;
		v.index[1] = 1;
		v.index[2] = 2;
		m_vecTriangle.push_back(v);
		v.index[0] = 0;
		v.index[1] = 2;
		v.index[2] = 3;
		m_vecTriangle.push_back(v);
		
		//뒤
		v.index[0] = 4;
		v.index[1] = 6;
		v.index[2] = 5;
		m_vecTriangle.push_back(v);
		v.index[0] = 4;
		v.index[1] = 7;
		v.index[2] = 6;
		m_vecTriangle.push_back(v);

		//왼
		v.index[0] = 4;
		v.index[1] = 5;
		v.index[2] = 1;
		m_vecTriangle.push_back(v);
		v.index[0] = 4;
		v.index[1] = 1;
		v.index[2] = 0;
		m_vecTriangle.push_back(v);

		//오른
		v.index[0] = 3;
		v.index[1] = 2;
		v.index[2] = 6;
		m_vecTriangle.push_back(v);
		v.index[0] = 3;
		v.index[1] = 6;
		v.index[2] = 7;
		m_vecTriangle.push_back(v);
		
		//위
		v.index[0] = 1;
		v.index[1] = 5;
		v.index[2] = 6;
		m_vecTriangle.push_back(v);
		v.index[0] = 1;
		v.index[1] = 6;
		v.index[2] = 2;
		m_vecTriangle.push_back(v);

		//아래
		v.index[0] = 4;
		v.index[1] = 0;
		v.index[2] = 3;
		m_vecTriangle.push_back(v);
		v.index[0] = 4;
		v.index[1] = 3;
		v.index[2] = 7;
		m_vecTriangle.push_back(v);
		break;

	case GRID:
		SetGizmo();
		
		for (float i = -5.f; i < 6.f; i += 1.f)
		{
			if((i == -5.f) || (i == 5.f))
				gridver.c = D3DCOLOR_XRGB(0, 0, 0);
			else
				gridver.c = D3DCOLOR_XRGB(100, 100, 100);
			
			gridver.p = D3DXVECTOR3(i, 0, -5);
			m_vecVertex.push_back(gridver);

			gridver.p = D3DXVECTOR3(i, 0, 5);
			m_vecVertex.push_back(gridver);
			
			gridver.p = D3DXVECTOR3(-5, 0, i);
			m_vecVertex.push_back(gridver);
			
			gridver.p = D3DXVECTOR3(5, 0, i);
			m_vecVertex.push_back(gridver);
		}

		break;
	}
}

void Object::UpDate()
{
	
}

void Object::Render()
{
	D3DXMATRIXA16 matObject;

	D3DXMATRIXA16 matRo;
	D3DXMATRIXA16 matPo;

	D3DXMatrixIdentity(&matObject);
	
	switch (m_shape)
	{
	case CUBE :
	
		//D3DXMatrixScaling(&matObject, vScale.x, vScale.y, vScale.z);
		D3DXMatrixRotationY(&matRo, vRotation.y);
		D3DXMatrixTranslation(&matPo, vPosition.x, vPosition.y, vPosition.z);

		matObject = matRo * matPo;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matObject);
		g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
		

		for(auto i : m_vecTriangle)
		{
			ST_PC_VERTEX tempTri[3] = {
				m_vecVertex[i.index[0]] ,
				m_vecVertex[i.index[1]] ,
				m_vecVertex[i.index[2]] };

			tempTri[0].c = tempTri[1].c = tempTri[2].c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
		
			D3DXVec3TransformNormal(&tempTri[0].p, &tempTri[0].p, &matObject);
			D3DXVec3TransformNormal(&tempTri[1].p, &tempTri[1].p, &matObject);
			D3DXVec3TransformNormal(&tempTri[2].p, &tempTri[2].p, &matObject);
		
			
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
				1,
				&tempTri[0],
				sizeof(ST_PC_VERTEX));
		}


		break;
	case GRID:

		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
		
		for (int i = 0; i < 11; i++)
		{
			ST_PC_VERTEX tempCol[2] = { m_vecVertex[4 * i + 0], m_vecVertex[4 * i + 1] };
			ST_PC_VERTEX tempRow[2] = { m_vecVertex[4 * i + 2], m_vecVertex[4 * i + 3] };

			g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
				1, &tempCol[0],
				sizeof(ST_PC_VERTEX));
			
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
				1, &tempRow[0],
				sizeof(ST_PC_VERTEX));
		}
		
		for (auto i : m_vecGizmoTriangle)
		{
			ST_PC_VERTEX tempTri[3] = {
				m_vecGizmoVertex[i.index[0]] ,
				m_vecGizmoVertex[i.index[1]] ,
				m_vecGizmoVertex[i.index[2]] };

			tempTri[2].c = tempTri[1].c = tempTri[0].c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);

			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
				1,
				&tempTri[0],
				sizeof(ST_PC_VERTEX));
		}
		
		break;
	}
}

void Object::MovePositon(float plusDistance)
{
	D3DXVECTOR3 vecGo;
	D3DXMATRIXA16 matRo;
	D3DXMatrixRotationY(&matRo, vRotation.y*2);
	D3DXVec3TransformNormal(&vecGo, &m_dir, &matRo);
	D3DXVec3Normalize(&vecGo, &vecGo);
	
	vPosition += (vecGo * plusDistance);
}

void Object::Rotate(float plusAngle)
{
	vRotation.y += plusAngle;
}


