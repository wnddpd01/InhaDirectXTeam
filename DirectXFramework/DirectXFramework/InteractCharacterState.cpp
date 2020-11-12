#include "stdafx.h"
#include "InteractCharacterState.h"
#include "cZealot.h"
#include "cSkinnedMesh.h"
#include "IdleCharacterState.h"


InteractCharacterState::InteractCharacterState()
	: interactStartTime(0)
	, AnimationPeriod(0)
{
}


InteractCharacterState::~InteractCharacterState()
{
}

void InteractCharacterState::Enter(cZealot& zealot)
{
	interactStartTime = GetTickCount();
	zealot.GetSkinnedMesh()->SetAnimationIndexBlend(rand() % 3);
	LPD3DXANIMATIONSET curAnimSet;
	zealot.GetSkinnedMesh()->m_pAnimController->GetTrackAnimationSet(0, &curAnimSet);
	AnimationPeriod = curAnimSet->GetPeriod();
}

CharacterState* InteractCharacterState::Update(cZealot& zealot)
{
	if(GetTickCount() - interactStartTime > (AnimationPeriod -  zealot.GetSkinnedMesh()->GetBlendTime() - 0.1f) * 1000 )
	{
		return new IdleCharacterState;
	}
	return nullptr;
}
