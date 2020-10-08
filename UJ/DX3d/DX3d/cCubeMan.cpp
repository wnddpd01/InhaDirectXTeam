#include "stdafx.h"
#include "cCubeMan.h"
#include "cBody.h"
#include "cHead.h"
#include "cLeftArm.h"
#include "cRightArm.h"
#include "cLeftLeg.h"
#include "cRightLeg.h"


cCubeMan::cCubeMan()
	: m_pRoot(NULL)
{
}


cCubeMan::~cCubeMan()
{
	if(m_pRoot)
	{
		m_pRoot->Destroy();
	}
	SafeRelease(m_pTextrue);
}

void cCubeMan::Setup()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, L"sb.png", &m_pTextrue);
	
	cCharacterSam::Setup();
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	cBody* p_body = new cBody;
	p_body->Setup();
	p_body->SetParentWorldTM(&m_matWorld);
	m_pRoot = p_body;

	cHead * p_head = new cHead;
	p_head->Setup();
	m_pRoot->AddChild(p_head);

	cLeftArm * p_left_arm = new cLeftArm;
	p_left_arm->Setup();
	p_left_arm->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(p_left_arm);

	cRightArm * p_right_arm = new cRightArm;
	p_right_arm->Setup();
	p_right_arm->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(p_right_arm);
	
	cLeftLeg * p_left_leg = new cLeftLeg;
	p_left_leg->Setup();
	p_left_leg->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(p_left_leg);
	
	cRightLeg * p_right_leg = new cRightLeg;
	p_right_leg->Setup();
	p_right_leg->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(p_right_leg);
}

void cCubeMan::Update()
{
	cCharacterSam::Update();
	if (m_pRoot)
		m_pRoot->Update();
}

void cCubeMan::Render()
{
	if(g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		//g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
		g_pD3DDevice->SetMaterial(&m_stMtl);
		g_pD3DDevice->SetTexture(0, m_pTextrue);
		cCharacterSam::Render();
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		if (m_pRoot)
			m_pRoot->Render();
		g_pD3DDevice->SetTexture(0, NULL);
	}
}

void cCubeMan::Command(WPARAM key)
{
	if (key == 'A')
	{
		m_fRotY -= 0.1f;
		D3DXMatrixRotationY(&m_matR, m_fRotY);
	}
	else if (key == 'D')
	{
		m_fRotY += 0.1f;
		D3DXMatrixRotationY(&m_matR, m_fRotY);
	}
	else if (key == 'W')
		m_vPosition += (m_vDirection * 0.1f);
	else if (key == 'S')
		m_vPosition -= (m_vDirection * 0.1f);
}
