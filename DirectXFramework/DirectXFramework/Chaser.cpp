#include "stdafx.h"
#include "Chaser.h"
#include "SkinnedMesh.h"
#include "RoomCenter.h"
#include "Player.h"
#include "ColliderCube.h"
#include "IdleChaserState.h"
#include "Room.h"

D3DXVECTOR3 Chaser::baseSightDir = { 0, 0, 1 };
float Chaser::baseSightLength = 20.f;
float Chaser::baseSightAngle = D3DX_PI / 12.f;
float Chaser::angrySightAngle = D3DX_PI / 2.5f;
vector<D3DXPLANE> Chaser::baseSightFrustum;
vector<D3DXPLANE> Chaser::angrySightFrustum;
vector<D3DXVECTOR3> Chaser::baseFrustumPoints;
vector<D3DXVECTOR3> Chaser::angryFrustumPoints;
ID3DXLine* line = nullptr;

//void Chaser::FollowingPath()
//{
//	D3DXVECTOR3 moveDir = mPath.back() - mPos;
//	const float distance = D3DXVec3Length(&moveDir);
//	if(distance < 0.1f)
//	{
//		mPos = mPath.back();
//		mPath.pop_back();
//		if (mPath.empty() == false)
//		{
//			RotateToNextNode();
//		}
//		else
//		{
//			if(mChaserState == ChaserState::CHASING)
//			{
//				ReturnToBasePos();
//			}
//			else
//			{
//				mChaserState = ChaserState::IDLE;
//				mSkinnedMesh->SetAnimationIndexBlend(8);
//			}
//		}
//	}
//	else
//	{
//		D3DXVec3Normalize(&moveDir, &moveDir);
//		mPos += moveDir * mSpeed;
//	}
//}

void Chaser::RotateToTarget()
{
	D3DXQUATERNION quatRot;
	D3DXMATRIXA16 matRot;
	D3DXVECTOR3 dir = mTargetPos - mPos;
	D3DXVec3Normalize(&dir, &dir);
	D3DXMatrixLookAtLH(&matRot, &D3DXVECTOR3(0, 0, 0), &dir, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixInverse(&matRot, nullptr, &matRot);
	D3DXQuaternionRotationMatrix(&quatRot, &matRot);

	static D3DXQUATERNION idleRot = *D3DXQuaternionRotationYawPitchRoll(&idleRot, D3DX_PI, 0, 0);
	this->SetRot(idleRot * quatRot);
}

void Chaser::ChangeState(ChaserState* newState)
{
	SAFE_DELETE(mChaserState);
	newState->Enter(this);
	mChaserState = newState;
}

bool Chaser::ObjectInSightFrustum(D3DXVECTOR3& objectPos, vector<D3DXPLANE>& sightFrustum)
{
	cout << D3DXVec3Length(&(mPos - objectPos)) << endl;
	if(D3DXVec3Length(&(mPos - objectPos)) > baseSightLength)
	{
		return false;
	}

	for (vector<D3DXPLANE>::value_type plane : sightFrustum)
	{
		if(D3DXPlaneDotCoord(&plane, &objectPos) < 0.f)
		{
			return false;
		}
	}
	
	return true;
}

void Chaser::MakeSightFrustum(vector<D3DXPLANE>& sightPlane)
{
	D3DXMATRIXA16 matR, matT, matWorld;
	D3DXMatrixRotationQuaternion(&matR, &mRot);
	D3DXMatrixTranslation(&matT, mPos.x, mPos.y, mPos.z);
	matWorld = matR * matT;
	D3DXMatrixInverse(&matWorld, nullptr, &matWorld);
	D3DXMatrixTranspose(&matWorld, &matWorld);
	D3DXPLANE transformPlane;
	for (vector<D3DXPLANE>::value_type& plane : *mSightFrustum)
	{
		D3DXPlaneNormalize(&transformPlane, &plane);
		D3DXPlaneTransform(&transformPlane, &plane, &matWorld);
		sightPlane.push_back(transformPlane);
	}
}

Chaser::Chaser(D3DXVECTOR3 basePos, RoomCenter* roomCenter)
	: mSpeed(0.05f)
	, mBasePos(basePos)
	, mRoomCenter(roomCenter)
	, mLastUpdateTime(0)
	, mCycleTime(findCycleTime)
{
	mPos = basePos;
	SetScale(D3DXVECTOR3(0.003f, 0.003f, 0.003f));
	AddColliderCube("basicColliderCube");
	mSkinnedMesh = new SkinnedMesh("Resources/XFile/Chaser", "Chaser.X");
	mSkinnedMesh->SetAnimationIndex(8);
	mChaserState = new IdleChaserState;
	mChaserState->Enter(this);
	if(baseSightFrustum.size() == 0)
	{
		GetFrustum((D3DXVECTOR3(0, 0, 0)), Chaser::baseSightDir, Chaser::baseSightLength, Chaser::baseSightAngle, D3DX_PI / 14, Chaser::baseSightFrustum, &baseFrustumPoints);
		GetFrustum((D3DXVECTOR3(0, 0, 0)), Chaser::baseSightDir, Chaser::baseSightLength, Chaser::angrySightAngle, D3DX_PI / 10, Chaser::angrySightFrustum, &angryFrustumPoints);
	}
	mSightFrustum = &baseSightFrustum;
	AddColliderCube("basicColliderCube");
	Base3DObject::Setup();
}

Chaser::~Chaser()
{
	SAFE_DELETE(mSkinnedMesh);
}

void Chaser::MatchTargetToPlayer()
{
	mTargetPos = mRoomCenter->GetPlayer()->GetPos();
}


void Chaser::FollowingPath()
{
}

void Chaser::ReturnToBasePos()
{
}

void Chaser::Attack(Player* player)
{
}

void Chaser::RenderFrustum()
{
	D3DXMATRIX matWorld, matR, matView;
	D3DXMatrixTranslation(&matWorld, mPos.x, mPos.y, mPos.z);
	static D3DXQUATERNION idleRot = *D3DXQuaternionRotationYawPitchRoll(&idleRot, D3DX_PI, 0, 0);
	D3DXMatrixRotationQuaternion(&matR, &(mRot * idleRot));
	matWorld = matR * matWorld;
	D3DXVECTOR3 linePoints[8];
	linePoints[0] = D3DXVECTOR3(0, 0, 0);
	D3DXVec3TransformCoord(&linePoints[0], &linePoints[0], &matWorld);
	linePoints[1] = (baseFrustumPoints[0]);
	linePoints[2] = (baseFrustumPoints[1]);
	linePoints[3] = (baseFrustumPoints[2]);
	linePoints[4] = (baseFrustumPoints[3]);
	/*linePoints[0] = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
	linePoints[1] = D3DXVECTOR3(5.0f, 0.0f, 0.0f);*/
	D3DCOLOR color = mChaserState->GetChaserStateName() != eChaserStateName::MOVING ? D3DCOLOR_XRGB(10, 255, 10) : D3DCOLOR_XRGB(255, 10, 10);
	for (int i = 1; i < 5; i++)
	{
		D3DXVec3TransformCoord(&linePoints[i], &linePoints[i], &matWorld);
		Draw3DLine(linePoints[0], linePoints[i], color);
		cout << to_string(linePoints[i]) << endl;
	}
	Draw3DLine(linePoints[1], linePoints[2], color);
	Draw3DLine(linePoints[1], linePoints[3], color);
	Draw3DLine(linePoints[3], linePoints[4], color);
}

//void Chaser::ReturnToBasePos()
//{
//	mChaserState = ChaserState::RETURNING;
//	mSkinnedMesh->SetAnimationIndexBlend(4);
//	mSpeed = Chaser::basicSpeed;
//	FindPath(mBasePos);
//}
//
//void Chaser::Attack(Player* player)
//{
//	mPath.clear();
//	mChaserState = ChaserState::ATTACKING;
//	mSkinnedMesh->SetAnimationIndexBlend(2);
//	mSkinnedMesh->SetCurrentAnimationSpeed(3);
//	mCycleTime = attackCycleTime;
//}
//
//void Chaser::SetTarget(D3DXVECTOR3& targetPos)
//{
//	if (mChaserState != ChaserState::CHASING)
//	{
//		mChaserState = ChaserState::CHASING;
//		mSkinnedMesh->SetAnimationIndexBlend(6);
//		mSpeed = Chaser::angrySpeed;
//		mCycleTime = findCycleTime;
//	}
//	FindPath(targetPos);
//}

bool Chaser::IsTargetInSight()
{
	vector<D3DXPLANE> sightFrustum;
	MakeSightFrustum(sightFrustum);
	if (ObjectInSightFrustum(mTargetPos, sightFrustum))
	{
		D3DXVECTOR3 sightRayDir = mTargetPos - mPos;
		float distanceToTarget = D3DXVec3Length(&sightRayDir);
		D3DXVec3Normalize(&sightRayDir, &sightRayDir);
		Room* currentRoom = mRoomCenter->FindRoomIncludePos(mPos);
		Room* targetRoom = mRoomCenter->FindRoomIncludePos(mTargetPos);
		if(currentRoom == nullptr || targetRoom == nullptr)
		{
			return false;
		}
		map<string, Base3DObject*> * objectsInRoom = &currentRoom->GetObjectsInRoomRef();
		BOOL canSeeTarget = true;
		float distanceToHitPoint = 0.f;
		for (map<string, Base3DObject*>::value_type& objectInRoom : *objectsInRoom)
		{
			if ((*objectInRoom.second->GetColliderCube().begin()).second->isIntersectRay(mPos, sightRayDir, &distanceToHitPoint))
			{
				if (distanceToHitPoint > 0 && distanceToHitPoint < distanceToTarget)
				{
					canSeeTarget = false;
					break;
				}
			}
		}
		if(targetRoom != nullptr && currentRoom != targetRoom)
		{
			objectsInRoom = &targetRoom->GetObjectsInRoomRef();
			for (map<string, Base3DObject*>::value_type& objectInRoom : *objectsInRoom)
			{
				if ((*objectInRoom.second->GetColliderCube().begin()).second->isIntersectRay(mPos, sightRayDir, &distanceToHitPoint))
				{
					if (distanceToHitPoint > 0 && distanceToHitPoint < distanceToTarget)
					{
						canSeeTarget = false;
						break;
					}
				}
			}
		}
		if (canSeeTarget == true)
		{
			return true;
		}
	}
	return false;
}

void Chaser::Update()
{
	/*if(GetTickCount() - mLastUpdateTime > mCycleTime)
	{
		mLastUpdateTime = GetTickCount();
		Player* player = mRoomCenter->GetPlayer();
		
		vector<D3DXPLANE> sightFrustum;
		MakeSightFrustum(sightFrustum);
		if(ObjectInSightFrustum(player, sightFrustum))
		{
			D3DXVECTOR3 playerPos = player->GetPos();
			D3DXVECTOR3 sightRayDir = playerPos - mPos;
			float distanceToPlayer = D3DXVec3Length(&sightRayDir);
			D3DXVec3Normalize(&sightRayDir, &sightRayDir);
			map<string, Base3DObject*>& objectsInRoom = mRoomCenter->FindRoomIncludePos(mPos)->GetObjectsInRoomRef();
			BOOL canSeePlayer = true;
			float distanceToHitPoint = 0.f;
			for (map<string, Base3DObject*>::value_type& objectInRoom : objectsInRoom)
			{
				if((*objectInRoom.second->GetColliderCube().begin()).second->isIntersectRay(mPos, sightRayDir, &distanceToHitPoint))
				{
					if(distanceToHitPoint > 0 && distanceToHitPoint < distanceToPlayer)
					{
						canSeePlayer = false;
						break;
					}
				}
			}
			if(canSeePlayer == true)
			{
				if(distanceToPlayer < attackRange)
				{
					Attack(player);
				}
				else
				{
					SetTarget(playerPos);
				}
			}
		}
		else
		{
			if(mChaserState != ChaserState::IDLE && mPath.empty() == true)
			{
				ReturnToBasePos();
			}
		}
	}

	if(mPath.empty() == false)
	{
		FollowingPath();
	}*/
	
	if(ChaserState * newChaserState =  mChaserState->Update(this))
	{
		ChangeState(newChaserState);
	}
	mSkinnedMesh->Update();
	Base3DObject::Update();
}

void Chaser::Render()
{
	Base3DObject::Render();
	mSkinnedMesh->Render(nullptr);
	RenderFrustum();
}
