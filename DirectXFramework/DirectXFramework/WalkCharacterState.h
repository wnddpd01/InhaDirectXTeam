#pragma once
#include "CharacterState.h"
class WalkCharacterState :
	public CharacterState
{
	D3DXVECTOR3 mPrevMoveVelocity;
	D3DXVECTOR3 mMoveVelocity;

	static const UINT walkSpeed = 4;
public:
	WalkCharacterState();
	~WalkCharacterState();
	
	void Enter(cZealot& zealot) override;
	CharacterState* HandleInput(cZealot& zealot, eEventName eventName, eKeyName &key) override;
	CharacterState* Update(cZealot& zealot) override;
};

