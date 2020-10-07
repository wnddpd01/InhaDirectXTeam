#include "stdafx.h"
#include "cCharacterSam.h"


cCharacterSam::cCharacterSam()
	: m_fRotY(0.0f)
	, m_vDirection(0.0f, 0.0f, 1.0f)
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

void cCharacterSam:: Update()
{

	D3DXMATRIXA16  matR ,matT;
	D3DXMatrixRotationY(&matR, m_fRotY);   //Y������ ȸ���� ��� ����

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);   //���� ���� ȸ��
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);   //�̵��� ��� ����

	m_matWorld = matR * matT;
}

void cCharacterSam::Render()
{
}

void cCharacterSam::SetPosition(D3DXVECTOR3& newPos)
{
	m_vPosition = newPos;
}

D3DXVECTOR3& cCharacterSam::GetPosition()
{
	return m_vPosition;
}
