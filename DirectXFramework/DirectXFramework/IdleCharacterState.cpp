#include "stdafx.h"
#include "IdleCharacterState.h"
#include "KeyboardInputManager.h"
#include "WalkCharacterState.h"
#include "cZealot.h"
#include "cSkinnedMesh.h"
#include "InteractCharacterState.h"


IdleCharacterState::IdleCharacterState()
	: mMoveVelocity(0,0,0)
	, idleStartTime(0)
	, mbAnimationChanged(false)
{
}


IdleCharacterState::~IdleCharacterState()
{
}

void IdleCharacterState::Enter(cZealot& zealot)
{
	idleStartTime = GetTickCount();
	mbAnimationChanged = false;
	mMoveVelocity = D3DXVECTOR3(0, 0, 0);
}

CharacterState* IdleCharacterState::HandleInput(cZealot& zealot, eEventName eventName, eKeyName &key)
{
	if(key == eKeyName::KEY_INTERACTION)
	{
		return new InteractCharacterState;
	}
	else if (eventName == eEventName::KEY_DOWN)
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
	return nullptr;
}

CharacterState* IdleCharacterState::Update(cZealot& zealot)
{
	if (D3DXVec3Length(&mMoveVelocity) != 0.f)
	{
		return new WalkCharacterState;
	}
	if(mbAnimationChanged == false && GetTickCount() - idleStartTime > 50)
	{
		mbAnimationChanged = true;
		zealot.GetSkinnedMesh()->SetAnimationIndexBlend(4);
	}
	return nullptr;
}