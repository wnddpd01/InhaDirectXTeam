#include "stdafx.h"
#include "Player.h"
#include "SkinnedMesh.h"
#include "KeyboardInputManager.h"
#include "IdleCharacterState.h"
#include "WalkCharacterState.h"

void Player::StateChange(CharacterState* nextState)
{
	SAFE_DELETE(mCurState);
	mCurState = nextState;
	mCurState->Enter(*this);
}

void Player::Setup()
{
	Base3DObject::Setup();
	m_pSkinnedMesh = new SkinnedMesh("Resources/XFile/Zealot", "zealot.X");
	m_pSkinnedMesh->SetRandomTrackPosition();
	
	m_pSkinnedMesh->m_matWorldTM = m_pSkinnedMesh->m_matWorldTM;
	mCurState = new IdleCharacterState;
	mCurState->Enter(*this);

	CollideHandle = bind(&Player::PlayerCollideHandle, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
}

void Player::Update()
{
	D3DXMATRIXA16 matWorld, matR, matT;

	Base3DObject::Update();

	if (D3DXVec3Length(&mMoveVelocity) != 0)
	{
		mPos += mMoveVelocity;
	}
	D3DXMatrixRotationQuaternion(&matR, &mRot);
	D3DXMatrixTranslation(&matT, mPos.x, mPos.y, mPos.z);
	matWorld = matR * matT;
	m_pSkinnedMesh->SetTransform(&matWorld);

	
	CharacterState * retState = mCurState->Update(*this);
	if (retState != nullptr)
	{
		StateChange(retState);
	}
	m_pSkinnedMesh->Update();
}

void Player::Render()
{
	Base3DObject::Render();
	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	m_pSkinnedMesh->Render(nullptr);
}

bool Player::Update(eEventName eventName, void* parameter)
{
	switch (eventName)
	{
		case eEventName::KEY_DOWN:
		case eEventName::KEY_UP:
			{
				eKeyName key = *(eKeyName*)parameter;
				
				CharacterState * retState =  mCurState->HandleInput(*this, eventName,key);
				if(retState != nullptr)
				{
					StateChange(retState);
				}
			}
			break;
		default:
			break;
	}

	return true;
}

void Player::SetAnimationSpeed(FLOAT spd)
{
	m_pSkinnedMesh->m_pAnimController->SetTrackSpeed(0, spd);
}

Player::Player()
	:m_pSkinnedMesh(nullptr)
	,mCurState(nullptr)
	,mMoveVelocity(0,0,0)
{
	D3DXVECTOR3 yAxis = { 0, 1, 0 };
	float yAngle = D3DX_PI * 1.75f;
	D3DXQuaternionRotationAxis(&mRot, &yAxis, yAngle);
}


Player::~Player()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void Player::PlayerCollideHandle(Base3DObject* player, string& myColliderTag, Base3DObject * otherCollider, string& otherColliderTag)
{
	if(otherColliderTag == "keyCubeCollider")
	{
		cout << "플레이어가 열쇠와 충돌" << endl;
	}
}
