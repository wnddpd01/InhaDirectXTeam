#include "stdafx.h"
#include "WalkCharacterState.h"
#include "cZealot.h"
#include "cSkinnedMesh.h"
#include "KeyboardInputManager.h"
#include "IdleCharacterState.h"

WalkCharacterState::WalkCharacterState()
{
}


WalkCharacterState::~WalkCharacterState()
{
}

void WalkCharacterState::Enter(cZealot& zealot)
{
	zealot.GetSkinnedMesh()->SetAnimationIndexBlend(3);
	mPrevMoveVelocity = D3DXVECTOR3(0, 0, 0);
	mMoveVelocity = D3DXVECTOR3(0, 0, 0);
}

CharacterState* WalkCharacterState::HandleInput(cZealot& zealot, eEventName eventName, eKeyName &key)
{
	if(eventName == eEventName::KEY_DOWN)
	{
		switch (key)
		{
			case eKeyName::KEY_FRONT:
				{
					mMoveVelocity.z += 1;
				}
				break;
			case eKeyName::KEY_BACK:
				{
					mMoveVelocity.z -= 1;
				}
				break;
			case eKeyName::KEY_LEFT:
				{
					mMoveVelocity.x -= 1;
				}
				break;
			case eKeyName::KEY_RIGHT:
				{
					mMoveVelocity.x += 1;
				}
				break;
		}
	}
	/*else if(eventName == eEventName::KEY_UP)
	{
		switch (key)
		{
			case eKeyName::KEY_FRONT:
			case eKeyName::KEY_BACK :
			case eKeyName::KEY_LEFT :
			case eKeyName::KEY_RIGHT:
				return new IdleCharacterState;
				break;
		}
	}*/
	return nullptr;
}

CharacterState* WalkCharacterState::Update(cZealot& zealot)
{
	if (D3DXVec3Length(&mMoveVelocity) == 0.f)
	{
		zealot.SetMoveVelocity(mMoveVelocity);
		return new IdleCharacterState;
	}
	if(mMoveVelocity != mPrevMoveVelocity)
	{
		D3DXQUATERNION & zealotRot = zealot.GetRotRef();
		
		D3DXMATRIXA16 matLook;
		D3DXMatrixLookAtLH(&matLook, &D3DXVECTOR3(0, 0, 0), &mMoveVelocity, &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixInverse(&matLook, nullptr, &matLook);

		
		D3DXQUATERNION moveRot;
		D3DXQuaternionRotationMatrix(&moveRot, &matLook);


		D3DXVECTOR3 yAxis = { 0, 1, 0 };
		float yAngle = D3DX_PI;
		D3DXQuaternionRotationAxis(&zealotRot, &yAxis, yAngle);
		zealotRot *= moveRot;
		mPrevMoveVelocity = mMoveVelocity;
	}
	D3DXVec3Normalize(&mMoveVelocity, &mMoveVelocity);
	zealot.SetMoveVelocity(mMoveVelocity * gTimeManager->GetDeltaTime() * walkSpeed);
	mMoveVelocity = D3DXVECTOR3(0,0,0);
	return nullptr;
}

