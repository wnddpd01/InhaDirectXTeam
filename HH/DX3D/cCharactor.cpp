#include "stdafx.h"
#include "cCharactor.h"


cCharactor::cCharactor()
	: m_vBody(0, 4, 0)
	, m_vDirection(0, 0, 1)
	, m_fRotY(0.f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharactor::~cCharactor()
{
	for (auto part : parts)
	{
		SafeDelete(part);
	}
}

void cCharactor::Update()
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.001f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.001f;
	}

	if (GetKeyState('W') & 0x8000)
	{
		//MoveOnOff(true);
		m_vBody += (m_vDirection*0.001f);
		m_Move = true;
	}
	

	
	if (GetKeyState('S') & 0x8000)
	{
		//MoveOnOff(true);
		m_vBody -= (m_vDirection*0.001f);
		m_Move = true;
	}
	

	
	RECT rc;
	GetClientRect(g_hwnd, &rc);

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vBody.x, m_vBody.y, m_vBody.z);
	m_matWorld = matR * matT;

	if(m_Move)
	{
		for (auto part : parts)
		{
			part->Update();
		}
	}
}

void cCharactor::Setup()
{
	cBodyCube* Body = new cBodyCube(&m_matWorld, D3DXVECTOR3(0, 0, 0) ,
		D3DXVECTOR3(1.f, 1.5f, 0.6f));
	
	cBodyCube* Head = new cBodyCube(&m_matWorld, D3DXVECTOR3(0, 2.6f, 0) ,
		D3DXVECTOR3(1.1f, 1.1f, 1.1f));
	
	cBodyCube* rightArm = new cBodyCube(&m_matWorld, D3DXVECTOR3(1.5f,0.f,0),
		D3DXVECTOR3(0.5f, 1.5f, 0.6f),
		D3DXVECTOR3(0.f, -1.f, 0.f),
	true);
	rightArm->OnMove(true);
	
	cBodyCube* leftArm = new cBodyCube(&m_matWorld, D3DXVECTOR3(-1.5f, 0.f, 0),
		D3DXVECTOR3(0.5f, 1.5f, 0.6f),
		D3DXVECTOR3(0.f, 1.f, 0.f));
	leftArm->OnMove(true);
	
	cBodyCube* rightLeg = new cBodyCube(&m_matWorld, D3DXVECTOR3(0.5, -3, 0),
		D3DXVECTOR3(0.5f, 1.5f, 0.6f),
		D3DXVECTOR3(0.f, -1.5f, 0.f));
	rightLeg->OnMove(true);
	
	cBodyCube* leftLeg = new cBodyCube(&m_matWorld, D3DXVECTOR3(-0.5, -3, 0), 
		D3DXVECTOR3(0.5f, 1.5f, 0.6f),
		D3DXVECTOR3(0.f, -1.5f, 0.f),
	true);
	leftLeg->OnMove(true);

	
	parts.push_back(Body);
	parts.push_back(Head);
	parts.push_back(rightArm);
	parts.push_back(leftArm);
	parts.push_back(rightLeg);
	parts.push_back(leftLeg);

	//delete  Head;
	//delete  rightArm;
	//delete  leftArm;
	//delete  rightLeg;
	//delete  leftLeg;
	for (auto part : parts)
	{
		part->Setup();
	}
}

void cCharactor::Render()
{
	for(auto part : parts)
	{
		part->Render();
	}
}

D3DXVECTOR3& cCharactor::GetPosition()
{
	return this->m_vBody;
	
}

void cCharactor::MoveOnOff(bool triger)
{
	for (auto part : parts)
	{
		part->OnMove(triger);
	}
}
