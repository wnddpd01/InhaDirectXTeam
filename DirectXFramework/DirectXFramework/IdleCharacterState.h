#pragma once
#include "CharacterState.h"
class IdleCharacterState :
	public CharacterState
{
	D3DXVECTOR3 mMoveVelocity;
	DWORD idleStartTime;
	bool mbAnimationChanged;
public:
	IdleCharacterState();
	~IdleCharacterState();

	void Enter(cZealot& zealot) override;
	CharacterState* HandleInput(cZealot& zealot, eEventName eventName, eKeyName &key) override;
	CharacterState* Update(cZealot& zealot) override;
};

