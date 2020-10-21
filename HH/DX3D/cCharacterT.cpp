#include "stdafx.h"
#include "cCharacterT.h"


cCharacterT::cCharacterT()
	: m_fRotY(0.f)
	, m_vDirection(0,0,1)
	, m_vPosition(0,0.8f,0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacterT::~cCharacterT()
{
}

void cCharacterT::Setup()
{
}

void cCharacterT::Update()
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.1f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.1f;
	}

	if (GetKeyState('W') & 0x8000)
	{
		//MoveOnOff(true);
		m_vPosition -= (m_vDirection*0.1f);
	}

	if (GetKeyState('S') & 0x8000)
	{
		//MoveOnOff(true);
		m_vPosition += (m_vDirection*0.1f);
	}


	RECT rc;
	GetClientRect(g_hwnd, &rc);

	D3DXMATRIXA16 matR, matT;

	D3DXMatrixRotationY(&matR, m_fRotY);
	/*
	{
		D3DXVECTOR3 vUp(0, 1, 0);
		D3DXVECTOR3 vAt(1, 0, 1);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixLookAtLH(&matR, &m_vPosition, &vAt, &vUp);
	}
	*/
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	
	m_matWorld = matR * matT;
}


void cCharacterT::Render()
{
}

D3DXVECTOR3& cCharacterT::GetPosition()
{
	return m_vPosition;
}
