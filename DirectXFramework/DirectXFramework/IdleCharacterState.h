#pragma once
#include "CharacterState.h"
class IdleCharacterState :
	public CharacterState
{
	D3DXVECTOR3 mMoveVelocity;
public:
	IdleCharacterState();
	~IdleCharacterState();

	void Enter(cZealot& zealot) override;
	CharacterState* HandleInput(cZealot& zealot, eEventName eventName, eKeyName &key) override;
	CharacterState* Update(cZealot& zealot) override;
};

