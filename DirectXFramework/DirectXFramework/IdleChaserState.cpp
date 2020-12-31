#include "stdafx.h"
#include "IdleChaserState.h"

#include "MovingChaserState.h"

IdleChaserState::IdleChaserState()
	: mIdleEnterTime(0)
{
	mChaserStateName = eChaserStateName::IDLE;
}

IdleChaserState::~IdleChaserState()
{
}

void IdleChaserState::Enter(Chaser* chaser)
{
	mIdleEnterTime = GetTickCount();
	ChaserState::Enter(chaser);
	chaser->GetSkinnedMesh()->SetAnimationIndex(8);
	chaser->SetSightFrustum(&Chaser::baseSightFrustum);
}

ChaserState* IdleChaserState::Update(Chaser* chaser)
{
	if(D3DXVec3Length(&(chaser->GetPos() - chaser->GetBasePos())) > 1.f && GetTickCount() - mIdleEnterTime > 1000)
	{
		D3DXVECTOR3 basePos = chaser->GetBasePos();
		chaser->SetTarget(basePos);
		return new MovingChaserState;
	}
	else if(GetTickCount() - mLastUpdateTime > Chaser::findCycleTime)
	{
		mLastUpdateTime = GetTickCount();
		chaser->MatchTargetToPlayer();
		if(chaser->IsTargetInSight())
		{
			D3DXVECTOR3 targetPos = chaser->GetTarget();
			chaser->SetTarget(targetPos);
			return new MovingChaserState;
		}
	}
	return nullptr;
}
