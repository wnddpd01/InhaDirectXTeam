#include "stdafx.h"
#include "cZealot.h"
#include "cSkinnedMesh.h"
#include "KeyboardInputManager.h"
#include "IdleCharacterState.h"
#include "WalkCharacterState.h"

void cZealot::StateChange(CharacterState* nextState)
{
	SAFE_DELETE(mCurState);
	mCurState = nextState;
	mCurState->Enter(*this);
}

void cZealot::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("Zealot", "zealot.X");
	m_pSkinnedMesh->SetRandomTrackPosition();
	
	m_pSkinnedMesh->m_matWorldTM = m_pSkinnedMesh->m_matWorldTM;
	mCurState = new IdleCharacterState;
	mCurState->Enter(*this);
}

void cZealot::Update()
{
	D3DXMATRIXA16 matWorld, matR, matT;


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

void cZealot::Render()
{
	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	m_pSkinnedMesh->Render(nullptr);
}

bool cZealot::Update(eEventName eventName, void* parameter)
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
				/*switch (key)
				{
					case eKeyName::KEY_FRONT_DOWN :
						{
							D3DXMATRIXA16 matT;
							D3DXMatrixTranslation(&matT, 0, 0, -1 * gTimeManager->GetDeltaTime());
							m_pSkinnedMesh->m_matWorldTM = m_pSkinnedMesh->m_matWorldTM * matT;
						}
						break;
					case eKeyName::KEY_BACK_DOWN :
						{
							D3DXMATRIXA16 matT;
							D3DXMatrixTranslation(&matT, 0, 0, 1 * gTimeManager->GetDeltaTime());
							m_pSkinnedMesh->m_matWorldTM = m_pSkinnedMesh->m_matWorldTM * matT;
						}
						break;
					case eKeyName::KEY_LEFT_DOWN:
						{
							D3DXMATRIXA16 matT;
							D3DXMatrixTranslation(&matT, 1 * gTimeManager->GetDeltaTime(), 0, 0);
							m_pSkinnedMesh->m_matWorldTM = m_pSkinnedMesh->m_matWorldTM * matT;
						}
						break;
					case eKeyName::KEY_RIGHT_DOWN:
						{
							D3DXMATRIXA16 matT;
							D3DXMatrixTranslation(&matT, -1 * gTimeManager->GetDeltaTime(), 0, 0);
							m_pSkinnedMesh->m_matWorldTM = m_pSkinnedMesh->m_matWorldTM * matT;
						}
						break;
					default:
						break;
				}*/
			}
			break;
		default:
			break;
	}

	return true;
}

void cZealot::SetAnimationSpeed(FLOAT spd)
{
	m_pSkinnedMesh->m_pAnimController->SetTrackSpeed(0, spd);
}

cZealot::cZealot()
	:m_pSkinnedMesh(nullptr)
	,mPos(0,0,0)
	,mCurState(nullptr)
	,mMoveVelocity(0,0,0)
{
	D3DXVECTOR3 yAxis = { 0, 1, 0 };
	float yAngle = D3DX_PI;
	D3DXQuaternionRotationAxis(&mRot, &yAxis, yAngle);
}


cZealot::~cZealot()
{
	SAFE_DELETE(m_pSkinnedMesh);
}
