#include "stdafx.h"
#include "AttackingChaserState.h"
#include "IdleChaserState.h"
#include "MovingChaserState.h"

AttackingChaserState::AttackingChaserState()
	: mLastFindedPlayerPos(0, 0, 0)
	, mbMakePath(false)
	, mSpeed(0.f)
{
}

AttackingChaserState::~AttackingChaserState()
{
}

void AttackingChaserState::FollowingPath()
{
	D3DXVECTOR3 chaserPos = mChaser->GetPos();
	D3DXVECTOR3 moveDir = mPath.back() - chaserPos;
	const float distance = D3DXVec3Length(&moveDir);
	const float accelSpeed = 1.f;
	if (distance < 0.3f)
	{
		mChaser->SetPos(mPath.back());
		mPath.pop_back();
	}
	else
	{
		D3DXVec3Normalize(&moveDir, &moveDir);
		mChaser->SetPos(chaserPos + moveDir * gTimeManager->GetDeltaTime() * (mSpeed+=accelSpeed));
	}
}

void AttackingChaserState::Enter(Chaser* chaser)
{
	ChaserState::Enter(chaser);
	chaser->GetSkinnedMesh()->SetAnimationIndexBlend(2);
	chaser->GetSkinnedMesh()->SetCurrentAnimationSpeed(2.f);
	mLastUpdateTime = GetTickCount();
	mLastFindedPlayerPos = chaser->GetTarget();
}

ChaserState* AttackingChaserState::Update(Chaser* chaser)
{
	if(mPath.empty() == false)
	{
		FollowingPath();
	}
	DWORD deltaTimeFromLastUpdate = GetTickCount() - mLastUpdateTime;
	chaser->MatchTargetToPlayer();
	if (deltaTimeFromLastUpdate > Chaser::attackCycleTime)
	{
		if(mPath.empty() == false)
		{
			mChaser->SetPos(mPath.front());
		}
		return new MovingChaserState;
	}
	else if(deltaTimeFromLastUpdate > Chaser::attackCycleTime * 0.3f)
	{
		float distanceToTarget = 0;
		chaser->MatchTargetToPlayer();
		D3DXVECTOR3 toTargetVec = chaser->GetPos() - chaser->GetTarget();
		distanceToTarget = D3DXVec3Length(&toTargetVec);
		bool isPlayerInAttackRange = distanceToTarget < Chaser::attackRange ? true : false;
		if (isPlayerInAttackRange == false && mbMakePath == false)
		{
			D3DXVECTOR3 dir = mLastFindedPlayerPos - mChaser->GetPos();
			mPath.push_back(mChaser->GetPos() + dir * 1.1f);
			mPath.push_back(mChaser->GetPos() + dir * 0.3f + D3DXVECTOR3(0, 1, 0));
			mbMakePath = true;
		}
	}
	else
	{
		if (deltaTimeFromLastUpdate < Chaser::attackCycleTime * 0.3f)
		{
			chaser->IsPlayerInSight(&mLastFindedPlayerPos);
			chaser->RotateToTarget();
		}
	}
	return nullptr;
}
