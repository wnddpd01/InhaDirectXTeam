#include "stdafx.h"
#include "MovingChaserState.h"


#include "AttackingChaserState.h"
#include "IdleChaserState.h"

void MovingChaserState::FindPath(Chaser * chaser)
{
	mPath.clear();
	mPath = gAstarManager->FindPath(gAstarManager->SearchToChaserNode(chaser->GetPos()), gAstarManager->SearchToPlayerNode(chaser->GetTarget()));
	RotateToNextNode();
}


void MovingChaserState::FollowingPath()
{
	D3DXVECTOR3 chaserPos = mChaser->GetPos();
	D3DXVECTOR3 moveDir = mPath.back() - chaserPos;
	const float distance = D3DXVec3Length(&moveDir);
	if (distance < 0.1f)
	{
		mChaser->SetPos(mPath.back());
		mPath.pop_back();
		if (mPath.empty() == false)
		{
			RotateToNextNode();
		}
	}
	else
	{
		D3DXVec3Normalize(&moveDir, &moveDir);
		mChaser->SetPos(chaserPos + moveDir * mSpeed * gTimeManager->GetDeltaTime());
	}
}

void MovingChaserState::RotateToNextNode()
{
	if(mPath.empty() == true)
	{
		return;
	}
	D3DXQUATERNION quatRot;
	D3DXMATRIXA16 matRot;
	D3DXVECTOR3 dir = mPath.back() - mChaser->GetPos();
	D3DXVec3Normalize(&dir, &dir);
	D3DXMatrixLookAtLH(&matRot, &D3DXVECTOR3(0, 0, 0), &dir, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixInverse(&matRot, nullptr, &matRot);
	D3DXQuaternionRotationMatrix(&quatRot, &matRot);

	static D3DXQUATERNION idleRot = *D3DXQuaternionRotationYawPitchRoll(&idleRot, D3DX_PI, 0, 0);
	mChaser->SetRot(idleRot * quatRot);
}

MovingChaserState::MovingChaserState()
	: mSpeed(angrySpeed)
{
	mChaserStateName = eChaserStateName::MOVING;
}

MovingChaserState::~MovingChaserState()
{
}

void MovingChaserState::Enter(Chaser* chaser)
{
	ChaserState::Enter(chaser);
	chaser->GetSkinnedMesh()->SetAnimationIndex(6);
	chaser->SetSightFrustum(&Chaser::angrySightFrustum);
	if(chaser->IsTargetInSight())
	{
		mPath.clear();
		mPath.push_back(chaser->GetTarget());
		RotateToNextNode();
	}
	else
	{
		FindPath(chaser);
	}
	if (!gSoundManager->Playing("Chaser"))
	{
		gSoundManager->Play("Chaser", 0.3f);
	}
}

ChaserState* MovingChaserState::Update(Chaser* chaser)
{
	if (mPath.empty() == false)
	{
		FollowingPath();
	}
	float distanceToTarget = 0;
	chaser->MatchTargetToPlayer();
	D3DXVECTOR3 toTargetVec = chaser->GetPos() - chaser->GetTarget();
	distanceToTarget = D3DXVec3Length(&toTargetVec);
	bool isPlayerInAttackRange = distanceToTarget < Chaser::attackRange ? true : false;
	if(isPlayerInAttackRange)
	{
		return new AttackingChaserState;
	}
	if (GetTickCount() - mLastUpdateTime > Chaser::findCycleTime)
	{
		if(chaser->IsTargetInSight())
		{
			mPath.clear();
			mPath.push_back(chaser->GetTarget());
			RotateToNextNode();
		}
		mLastUpdateTime = GetTickCount();
	}
	if(mPath.empty() == true)
	{
		return new IdleChaserState;
	}
	return nullptr;
}
