#pragma once
#include "CharacterState.h"
class InteractCharacterState :
	public CharacterState
{
	DWORD interactStartTime;
	float AnimationPeriod;
public:
	InteractCharacterState();
	~InteractCharacterState();

	void Enter(cZealot& zealot) override;
	CharacterState* Update(cZealot& zealot) override;
};

