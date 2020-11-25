#include "stdafx.h"
#include "InteractCharacterState.h"
#include "Player.h"
#include "SkinnedMesh.h"
#include "IdleCharacterState.h"

InteractCharacterState::InteractCharacterState()
	: interactStartTime(0)
	, AnimationPeriod(0)
{
	mStateName = eCharacterStateName::INTERACTION_STATE;
}

InteractCharacterState::~InteractCharacterState()
{
}

void InteractCharacterState::Enter(Player& player)
{
	interactStartTime = GetTickCount();
	player.GetSkinnedMesh()->SetAnimationIndexBlend(rand() % 3);
	LPD3DXANIMATIONSET curAnimSet;
	player.GetSkinnedMesh()->m_pAnimController->GetTrackAnimationSet(0, &curAnimSet);
	AnimationPeriod = curAnimSet->GetPeriod();
}

CharacterState* InteractCharacterState::Update(Player& player)
{
	if(GetTickCount() - interactStartTime > (AnimationPeriod -  player.GetSkinnedMesh()->GetBlendTime() - 0.1f) * 1000 )
	{
		//player.GetInteractingObject()->DeleteInRoom(player.GetInteractingObject()->GetObjectName());
		
		player.mInventory.UseItem(*player.GetInteractingObject());	
		player.mInventory.SetInItem(true, player.GetInteractingObject()->GetObjectName());	
		return new IdleCharacterState;
	}
	return nullptr;
}
