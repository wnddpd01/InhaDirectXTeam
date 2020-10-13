#include "stdafx.h"
#include "cCharacterController.h"
#include "cObjMap.h"
#include "cHSMyCharacter.h"


cCharacterController::cCharacterController()
	: m_vPosition(0, 0, 0)
	, m_fRotY(0)
	, m_fSpeed(1.0f)
	, m_fJumpAcc(Max_JumpAcc)
	, m_bJump(false)
	, m_bInAir(false)
	, m_pMap(NULL)
	, m_pCharacter(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacterController::~cCharacterController()
{
}

void cCharacterController::Setup(char * _szFilePath)
{
	if (_szFilePath == NULL)
		return;

	m_pCharacter = new cHSMyCharacter;
	g_pAutoReleasePool->AddObject(m_pCharacter);
	m_pCharacter->Setup(_szFilePath, D3DXVECTOR3(10.f, 10.f, 10.f));
}

void cCharacterController::Update()
{
	if (GetKeyState(' ') & 0x8000)
	{
		m_bJump = true;
	}

	if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.1f;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.1f;
	}

	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_fRotY);

	D3DXVECTOR3 vDir(0.0f, 0.0f, -1.0f);
	D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);

	D3DXVECTOR3 pos;
	if (GetKeyState('W') & 0x8000)
	{
		pos = m_vPosition + vDir * m_fSpeed;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		pos = m_vPosition - vDir * m_fSpeed;
	}
	if (GetKeyState('W') & 0x8000 || GetKeyState('S') & 0x8000)
	{
		m_pCharacter->SetAnimation(true);
	}
	else
	{
		m_pCharacter->SetAnimation(false);
	}


	if (m_pMap)
	{
		if (m_pMap->GetHeight(pos.x, pos.y, pos.z))
			m_vPosition = pos;
	}

	Jump();
	InAir();

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matRotY * matT;

	D3DXVECTOR3 v = m_vPosition;
	v.y += 5.0f;

	D3DLIGHT9 light = InitSpotLight(&v, &vDir, &YELLOW);
	g_pD3DDevice->SetLight(2, &light);
	g_pD3DDevice->LightEnable(2, true);

	if(m_pCharacter)
		m_pCharacter->Update(&m_matWorld);
}

void cCharacterController::Render()
{
	if (m_pCharacter)
		m_pCharacter->Render();
}


void cCharacterController::Jump()
{
	if (m_bJump == false || m_fJumpAcc < EPSILON)
		return;
	
	m_vPosition.y += m_fJumpAcc;
	m_fJumpAcc -= 0.1f;

}

void cCharacterController::InAir()
{
	D3DXVECTOR3 pos = m_vPosition;
	m_pMap->GetHeight(m_vPosition.x, m_vPosition.y, m_vPosition.z);
	float fDis = m_pMap->GetDistance();

	if (abs(fDis - MAX_CLIME_SIZE) < EPSILON)
	{
		m_bJump = false;
		m_fJumpAcc = Max_JumpAcc;
		return;
	}

	else if (fDis < MAX_CLIME_SIZE)
		m_vPosition.y += MAX_CLIME_SIZE - fDis;

	else
		m_vPosition.y += GRAVITY;
}