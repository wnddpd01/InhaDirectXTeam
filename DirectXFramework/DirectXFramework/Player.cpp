#include "stdafx.h"
#include "Player.h"
#include "SkinnedMesh.h"
#include "KeyboardInputManager.h"
#include "IdleCharacterState.h"
#include "WalkCharacterState.h"
#include "FontManager.h";
#include "Camera.h"

Player::Player()
	: m_pSkinnedMesh(nullptr)
	, mCurState(nullptr)
	, mMoveVelocity(0, 0, 0)
	, interactingObject(nullptr)
{
	D3DXVECTOR3 yAxis = { 0, 1, 0 };
	float yAngle = D3DX_PI * 1.75f;
	D3DXQuaternionRotationAxis(&mRot, &yAxis, yAngle);

	mPos = { 8.f, 0.f, 8.f };
	
	D3DVIEWPORT9 viewPort;
	gD3Device->GetViewport(&viewPort);

	mDrawFontArea.left = viewPort.Width / 2;
	mDrawFontArea.top = viewPort.Height / 2;
	mDrawFontArea.right = mDrawFontArea.left + viewPort.Width * 0.3f;
	mDrawFontArea.right = mDrawFontArea.left + viewPort.Height * 0.1f;

}


Player::~Player()
{
		SAFE_DELETE(m_pSkinnedMesh);
}

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

	if (interactingObject != nullptr)
	{
		interactingObject = nullptr;
	}
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
		case eEventName::MOUSE_MOVE :
			{
				POINT& mousePt = *(POINT*)parameter;
				D3DXVECTOR3 mouseWorldPos = gCurrentCamera->GetPickingPosition(mousePt);
				
				cout << to_string(mouseWorldPos) << endl;
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


void Player::PlayerCollideHandle(Base3DObject* player, string& myColliderTag, Base3DObject * otherCollider, string& otherColliderTag)
{
	if(otherColliderTag == "keyCubeCollider")
	{
		interactingObject = otherCollider;
	}
}
