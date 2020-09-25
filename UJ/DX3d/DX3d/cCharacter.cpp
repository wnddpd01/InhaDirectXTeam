#include "stdafx.h"
#include "cCharacter.h"
#include "cCubePC.h"

cCharacter::cCharacter()
{
	this->m_fRotX = 0;
	this->m_fRotY = 0;
	m_vPosition = {0,0,0};
	isMoved = false;
}


cCharacter::~cCharacter()
{

}

void cCharacter::KeyInput()
{
	isMoved = false;
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
		isMoved = true;
		m_vPosition += (m_vDirection * 0.1f);
	}
	if (GetKeyState('S') & 0x8000)
	{
		isMoved = true;
		m_vPosition -= (m_vDirection * 0.1f);
	}
}

void cCharacter::Setup()
{
	D3DXVECTOR3 bodySize = { 0.5f,0.5f,0.125f };
	D3DXVECTOR3 headSize = { 0.3f,0.3f,0.3f };
	D3DXVECTOR3 armSize = { bodySize.x * 0.2f ,bodySize.y * 1.5f,bodySize.z };
	D3DXVECTOR3 legSize = { bodySize.x * 0.25f,bodySize.y * 0.8f,bodySize.z };

	
	cCubePC* body = new cCubePC;
	D3DXVECTOR3 bodyPos = { 0,0,0 };
	bodyPos.y = bodySize.y * 0.5 + legSize.y;
	body->SetPosition(bodyPos);
	body->Setup(bodySize);
	character_body_vector_.push_back(body);

	
	cCubePC* head = new cCubePC;
	D3DXVECTOR3 headPos = body->GetPosition();
	headPos.y += bodySize.y * 0.5 + headSize.y * 0.5;
	head->SetPosition(headPos);
	head->Setup(headSize);
	character_body_vector_.push_back(head);

	cCubePC* leftArm = new cCubePC;
	D3DXVECTOR3 leftArmPos = body->GetPosition();
	leftArmPos.x += -bodySize.x * 0.5 - armSize.x * 0.5;
	leftArmPos.y += bodySize.y * 0.5 - armSize.y *0.5;
	leftArm->SetPosition(leftArmPos);
	leftArm->Setup(armSize);
	animation_dir.push_back(-0.01f);
	character_body_vector_.push_back(leftArm);

	cCubePC* rightArm = new cCubePC;
	D3DXVECTOR3 rightArmPos = body->GetPosition();
	rightArmPos.x += bodySize.x * 0.5 + armSize.x * 0.5;
	rightArmPos.y += bodySize.y * 0.5 - armSize.y *0.5;
	rightArm->SetPosition(rightArmPos);
	rightArm->Setup(armSize);
	animation_dir.push_back(0.01f);
	character_body_vector_.push_back(rightArm);

	cCubePC* leftLeg = new cCubePC;
	D3DXVECTOR3 leftLegPos = body->GetPosition();
	leftLegPos.x += -bodySize.x * 0.1 - legSize.x * 0.5;
	leftLegPos.y += -bodySize.y * 0.5 - legSize.y *0.5;
	leftLeg->SetPosition(leftLegPos);
	leftLeg->Setup(legSize);
	animation_dir.push_back(-0.01f);
	character_body_vector_.push_back(leftLeg);

	cCubePC* rightLeg = new cCubePC;
	D3DXVECTOR3 rightLegPos = body->GetPosition();
	rightLegPos.x += +bodySize.x * 0.1 + legSize.x * 0.5;
	rightLegPos.y += -bodySize.y * 0.5 - legSize.y *0.5;
	rightLeg->SetPosition(rightLegPos);
	rightLeg->Setup(legSize);
	animation_dir.push_back(0.01f);
	character_body_vector_.push_back(rightLeg);
}

void cCharacter::Update()
{
	if (isMoved == false)
		UpdateIdle();
	else
		UpdateSwing();
	
}

void cCharacter::UpdateIdle()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;

	for (auto element : character_body_vector_)
	{
		
		if(fabsf(element->GetRotX() > 0.0001f))
		{
			element->SetRotX(element->GetRotX() * 0.08f);
		}
		else
		{
			element->SetRotX(0);
		}
		element->Update(m_matWorld);
	}
}

void cCharacter::UpdateSwing()
{
	static vector<float> dir;
	if (dir.empty() == true)
	{
		for (size_t i = 0; i < 4; i++)
		{
			dir.push_back(-0.01f * pow(-1, i));
		}
	}
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;

	for (int i = 0; i < 2; ++i)
	{
		character_body_vector_[i]->Update(m_matWorld);
	}
	for (size_t i = 2; i < character_body_vector_.size(); i++)
	{
		float rotX = character_body_vector_[i]->GetRotX();
		if(fabs(rotX) > 0.5f)
		{
			dir[i - 2] *= -1;
		}
		character_body_vector_[i]->SetRotX(character_body_vector_[i]->GetRotX() + dir[i - 2] * 5);
		character_body_vector_[i]->Update(m_matWorld);
	}
}

void cCharacter::Render()
{
	for (vector<cCubePC*>::value_type character_body_vector : character_body_vector_)
	{
		character_body_vector->Render();
	}
}

D3DXVECTOR3& cCharacter::GetPosition()
{
	return m_vPosition;
}
