#include "stdafx.h"
#include "cCharacterSam.h"


cCharacterSam::cCharacterSam()
	: m_fRotY(0.0f)
	, m_vDirection(0.0f, 0.0f, 0.0f)
	, m_vPosition(0.0f, 0.0f, 0.0f )
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacterSam::~cCharacterSam()
{
}

void cCharacterSam::Setup()
{
}

void cCharacterSam::Update()
{
	if (GetKeyState('A') & 0x8000)
		m_fRotY -= 0.1f;
	else if (GetKeyState('D') & 0x8000)
		m_fRotY += 0.1f;

	if (GetKeyState('W') & 0x8000)
		m_vPosition += (m_vDirection * 0.1f);
	else if (GetKeyState('S') & 0x8000)
		m_vPosition -= (m_vDirection * 0.1f);

	D3DXMATRIXA16   matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);   //Y축으로 회전된 행렬 제작

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);   //벡터 라디안 회전
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);   //이동된 행렬 제작

	m_matWorld = matR * matT;
}

void cCharacterSam::Render()
{
}

D3DXVECTOR3& cCharacterSam::GetPosition()
{
	return m_vPosition;
}
