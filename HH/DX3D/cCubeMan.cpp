#include "stdafx.h"
#include "cCubeMan.h"

#include "cBody.h"
#include "cLeftArm.h"
#include "cRightArm.h"
#include "cRightLeg.h"
#include "cLeftLeg.h"
#include "cHead.h"


cCubeMan::cCubeMan()
	: m_pRoot(NULL)
	, m_pTexture(NULL)
{
}


cCubeMan::~cCubeMan()
{
	if (m_pRoot)
		m_pRoot->Destroy();
}

void cCubeMan::Setup()
{
	cCharacterT::Setup();

	D3DXCreateTextureFromFile(g_pD3DDevice, L"texture\\rainbow.png", &m_pTexture);
	
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.f);

	cBody*	pBody = new cBody;
	pBody->Setup();
	pBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = pBody;

	cHead* pHead = new cHead;
	pHead->Setup();
	//pHead->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(pHead);

	cLeftArm* pLArm = new cLeftArm;
	pLArm->Setup();
	pLArm->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(pLArm);

	cRightArm* pRArm = new cRightArm;
	pRArm->Setup();
	pRArm->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(pRArm);

	cLeftLeg* pLLeg = new cLeftLeg;
	pLLeg->Setup();
	pLLeg->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(pLLeg);

	cRightLeg* pRLeg = new cRightLeg;
	pRLeg->Setup();
	pRLeg->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(pRLeg);

	
	
}

void cCubeMan::Update()
{
	cCharacterT::Update();
	if (m_pRoot)
		m_pRoot->Update();
}

void cCubeMan::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetMaterial(&m_stMtl);
		g_pD3DDevice->SetTexture(0, m_pTexture);
		cCharacterT::Render();

		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		
		if (m_pRoot)
		{
			m_pRoot->Render();
		}
		g_pD3DDevice->SetTexture(0, nullptr);
	}

}

bool cCubeMan::MoveToUpdate(D3DXVECTOR3 dest)
{
	RECT rc;
	GetClientRect(g_hwnd, &rc);

	D3DXMATRIXA16 matR, matT;

	D3DXMatrixRotationY(&matR, m_fRotY);

	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0,0,0), &(dest-m_vPosition), &D3DXVECTOR3(0,1,0));
	//D3DXMatrixLookAtLH(&matR, &m_vPosition, &dest , &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matR, &matR);
	
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	//D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	D3DXVec3Normalize(&m_vDirection, &(dest - m_vPosition));
	//float charRot = D3DXVec3Dot(&m_vDirection, &D3DXVECTOR3(0.f, 0.f, 1.f));
	//m_fRotY = acos(charRot);
	
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT ;
	
	if (m_pRoot)
		m_pRoot->Update();

	D3DXVECTOR3 vTemp = (this->m_vPosition - dest);
	if (D3DXVec3Length(&vTemp) > 0.3f)
	{
		m_vPosition += (m_vDirection*0.1f);
		return false;
	}
	else
		return true;
}

void cCubeMan::objUpdate(std::vector<tGroup*>& vecSufGroup)
{
	//발판 ray
	bool onSurface = false;
	float dist;
	
	for (int i = 0; i < vecSufGroup[0]->GetVertex().size(); i += 3)
	{
		if (D3DXIntersectTri(
			&vecSufGroup[0]->GetVertex()[i].p
			, &vecSufGroup[0]->GetVertex()[i + 1].p
			, &vecSufGroup[0]->GetVertex()[i + 2].p
			, &D3DXVECTOR3(m_vPosition.x, 100.f, m_vPosition.z), &D3DXVECTOR3(0, -1, 0),
			nullptr, nullptr, &dist))
		{
			onSurface = true;
			break;
		}
	}
	
	if (onSurface)
	{
		std::cout << (100.8f - (m_vPosition.y + dist)) << std::endl;
		if((100.8f - (m_vPosition.y + dist)) < 2.f)
			m_vPosition.y = (100.8f - dist);
		else
			m_vPosition = m_prevPosition;
	}
	else
	{
		m_vPosition = m_prevPosition;
	}

	m_prevPosition = m_vPosition;

	
	//발판 ray 끝

	Update();
	
}
