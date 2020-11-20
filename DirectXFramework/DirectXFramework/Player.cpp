#include "stdafx.h"
#include "Player.h"
#include "CameraManager.h"
#include "SkinnedMesh.h"
#include "KeyboardInputManager.h"
#include "IdleCharacterState.h"
#include "WalkCharacterState.h"
#include "FontManager.h"
#include "UIImage.h"
#include "Camera.h"

Player::Player()
	: m_pSkinnedMesh(nullptr)
	, mCurState(nullptr)
	, mMoveVelocity(0, 0, 0)
	, mInteractingObject(nullptr)
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

	mInteractingObjectMark = new UIImage(string("Resources/UI/InteractMark.png"));
	mInteractingObjectMark->SetPos(D3DXVECTOR3(0, 10, 0));
	mInteractingObjectMark->SetVisible(true);
}


Player::~Player()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(mInteractingObjectMark);
}

void Player::StateChange(CharacterState* nextState)
{
	SAFE_DELETE(mCurState);
	mCurState = nextState;
	mCurState->Enter(*this);
}

void Player::DrawMark()
{
	D3DXMATRIXA16 matProj;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matWorld;
	D3DVIEWPORT9 viewPort;
	gD3Device->GetTransform(D3DTS_PROJECTION, &matProj);
	gD3Device->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixIdentity(&matWorld);
	gD3Device->GetViewport(&viewPort);
	D3DXVECTOR3 markPos = mInteractingObject->GetPos();
	D3DXVec3Project(&markPos, &markPos, &viewPort, &matProj, &matView, &matWorld);
	markPos.z = 0;
	markPos.y -= mInteractingObjectMark->GetWidth() * 0.5f + viewPort.Height * 0.2f;
	markPos.x -= mInteractingObjectMark->GetWidth() * 0.5f;
	mInteractingObjectMark->SetPos(markPos);
	mInteractingObjectMark->Render();
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

	if (mInteractingObject != nullptr)
	{
		mInteractingObject = nullptr;
	}
}

void Player::Render()
{
	Base3DObject::Render();
	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	m_pSkinnedMesh->Render(nullptr);
	if(mInteractingObject != nullptr)
	{
		DrawMark();
	}

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
				cout << to_string(mPos) << endl;
			}
			break;
		case eEventName::MOUSE_MOVE :
			{
				if (mCurState->GetStateName() == eCharacterStateName::IDLE_STATE)
				{
					POINT& mousePt = *(POINT*)parameter;
					D3DXVECTOR3 mouseWorldPos = gCurrentCamera->GetPickingPosition(mousePt) - mPos;
					
					D3DXMATRIXA16 matRot;
					D3DXMatrixLookAtLH(&matRot, &D3DXVECTOR3(0, 0, 0), &mouseWorldPos, &D3DXVECTOR3(0, 1, 0));

					D3DXQUATERNION quatRot;
					D3DXQuaternionRotationMatrix(&quatRot, &matRot);

					mRot = quatRot;
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


void Player::PlayerCollideHandle(Base3DObject* player, string& myColliderTag, Base3DObject * otherCollider, string& otherColliderTag)
{
	if(otherColliderTag == "keyCubeCollider")
	{
		mInteractingObject = otherCollider;
	}
}
