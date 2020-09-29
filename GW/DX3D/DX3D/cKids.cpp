#include "stdafx.h"
#include "cKids.h"
#include "cCubePC.h"

cKids::cKids()
	:m_vDirection(0,0,1)
	,m_vPosition(0,0,0)
	,m_fRotY(0.0f)
	,m_pBody(NULL)
	,m_pHead(NULL)
	,m_prLeg(NULL)
	,m_plLeg(NULL)
	,m_prArm(NULL)
	,m_plArm(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cKids::~cKids()
{
	for each(auto p in m_vecKids)
	{
		SafeDelete(p);
	}

	m_vecKids.clear();

}

void cKids::Setup()
{
	m_pHead = new cCubePC;
	m_pHead->Setup();
	m_pHead->SetScling(0.5f, 0.5f, 0.5f);
	m_pHead->SetTrans(0, 2.1f, 0);

	m_pBody = new cCubePC;
	m_pBody->Setup();
	m_pBody->SetScling(0.5f, 0.5f, 0.3f);
	m_pBody->SetTrans(0, 1.1f, 0);

	m_prArm = new cCubePC;
	m_prArm->Setup();
	m_prArm->SetScling(0.2f, 0.5f, 0.2f);
	m_prArm->SetTrans(0.7f, 1.0f, 0);

	m_plArm = new cCubePC;
	m_plArm->Setup();
	m_plArm->SetScling(0.2f, 0.5f, 0.2f);
	m_plArm->SetTrans(-0.7f, 1.0f, 0);

	m_prLeg = new cCubePC;
	m_prLeg->Setup();
	m_prLeg->SetScling(0.2f, 0.3f, 0.2f);
	m_prLeg->SetTrans(0.2f, 0.3f, 0);

	m_plLeg = new cCubePC;
	m_plLeg->Setup();
	m_plLeg->SetScling(0.2f, 0.3f, 0.2f);
	m_plLeg->SetTrans(-0.2f, 0.3f, 0);

	m_vecKids.push_back(m_pHead);
	m_vecKids.push_back(m_pBody);
	m_vecKids.push_back(m_prArm);
	m_vecKids.push_back(m_plArm);
	m_vecKids.push_back(m_prLeg);
	m_vecKids.push_back(m_plLeg);

}

void cKids::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matR, matT;


	for each(auto p in m_vecKids)
	{
		p->Update(&m_matWorld);
	}


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
		m_vecKids[2]->SetRotation(1.0f);
	}
	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition -= (m_vDirection*0.1f);
		m_vecKids[2]->SetRotation(-1.0f);
	}


	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR*matT;


}

void cKids::Render()
{

	for each(auto p in m_vecKids)
	{
		p->Render();	
	}



}

D3DXVECTOR3 & cKids::GetPosition()
{
	return m_vPosition;
}
