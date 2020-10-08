#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
	:m_fRotY(0.0f)
, m_vDirection(0,0,1)
,m_vPosition(0,0.9f,0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
}

void cCharacter::Setup()
{

}

void cCharacter::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matR, matT;


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
		m_vPosition += (m_vDirection*0.1f);
	}
	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition -= (m_vDirection*0.1f);
	}


	D3DXMatrixRotationY(&matR, m_fRotY);

	/*
	     �����  �ٲٱ�
	D3DXVECTOR3 vUP(0,1,0);
	D3DXVECTOR3 vAt(1,0,0);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixLookAtLH(&matR, &m)vPosition, &vAt, &vUp);
	D3DXMatrixTranspose(&matR,&matR); 
	 */

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR*matT;
}

void cCharacter::Render()
{
}

D3DXVECTOR3& cCharacter::GetPosition()
{
	return m_vPosition;
}
