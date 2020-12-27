#include "stdafx.h"
#include "Chaser.h"
#include "SkinnedMesh.h"
#include "RoomCenter.h"
#include "Player.h"
#include "ColliderCube.h"
#include "Room.h"

D3DXVECTOR3 Chaser::baseSightDir = { 0, 0, 1 };
float Chaser::baseSightLength = 30.f;
float Chaser::baseSightAngle = D3DX_PI / 6.f;
vector<D3DXPLANE> Chaser::baseSightFrustum;

void Chaser::FollowingPath()
{
	D3DXVECTOR3 moveDir = mPath.back() - mPos;
	const float distance = D3DXVec3Length(&moveDir);
	if(distance < 0.1f)
	{
		mPos = mPath.back();
		mPath.pop_back();
		if (mPath.empty() == false)
		{
			RotateToNextNode();
		}
		else
		{
			if(mChaserState == ChaserState::CHASING)
			{
				ReturnToBasePos();
			}
			else
			{
				mChaserState = ChaserState::STOP;
				mSkinnedMesh->SetAnimationIndexBlend(8);
			}
		}
	}
	else
	{
		D3DXVec3Normalize(&moveDir, &moveDir);
		mPos += moveDir * mSpeed;
	}
}

void Chaser::RotateToNextNode()
{
	D3DXQUATERNION quatRot;
	D3DXMATRIXA16 matRot;
	D3DXMatrixLookAtLH(&matRot, &(GetPos()), &mPath.back(), &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixInverse(&matRot, nullptr, &matRot);
	D3DXQuaternionRotationMatrix(&quatRot, &matRot);

	static D3DXQUATERNION idleRot = *D3DXQuaternionRotationYawPitchRoll(&idleRot, D3DX_PI, 0, 0);
	SetRot(idleRot * quatRot);
}

bool Chaser::ObjectInSightFrustum(Base3DObject* object, vector<D3DXPLANE>& sightFrustum)
{
	if(D3DXVec3Length(&(mPos - object->GetPos())) > baseSightLength)
	{
		return false;
	}

	for (vector<D3DXPLANE>::value_type plane : sightFrustum)
	{
		if(D3DXPlaneDotCoord(&plane, &object->GetPos()) < 0.f)
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
	for (vector<D3DXPLANE>::value_type& plane : baseSightFrustum)
	{
		D3DXPlaneNormalize(&transformPlane, &plane);
		D3DXPlaneTransform(&transformPlane, &plane, &matWorld);
		sightPlane.push_back(transformPlane);
	}
}

Chaser::Chaser(D3DXVECTOR3 basePos, RoomCenter* roomCenter)
	: mChaserState(ChaserState::STOP)
	, mSpeed(0.05f)
	, mBasePos(basePos)
	, mRoomCenter(roomCenter)
	, mLastFindTime(0)
	, testSightDir(0, 0, 0)
{
	mPos = basePos;
	SetScale(D3DXVECTOR3(0.003f, 0.003f, 0.003f));
	mSkinnedMesh = new SkinnedMesh("Resources/XFile/Chaser", "Chaser.X");
	mSkinnedMesh->SetAnimationIndex(8);

	if(baseSightFrustum.size() == 0)
	{
		GetFrustum((D3DXVECTOR3(0, 0, 0)), Chaser::baseSightDir, Chaser::baseSightLength, Chaser::baseSightAngle, Chaser::baseSightFrustum);
	}
}

Chaser::~Chaser()
{
	mPath.clear();
	SAFE_DELETE(mSkinnedMesh);
}

void Chaser::FindPath(D3DXVECTOR3& endPos)
{
	mPath.clear();
	mPath.push_back(endPos);
	RotateToNextNode();
}

void Chaser::ReturnToBasePos()
{
	mChaserState = ChaserState::RETURNING;
	mSkinnedMesh->SetAnimationIndex(4);
	mSpeed = Chaser::basicSpeed;
	FindPath(mBasePos);
}

void Chaser::SetTarget(D3DXVECTOR3& targetPos)
{
	if (mChaserState != ChaserState::CHASING)
	{
		mChaserState = ChaserState::CHASING;
		mSkinnedMesh->SetAnimationIndexBlend(6);
		mSpeed = Chaser::angrySpeed;
	}
	FindPath(targetPos);
}

void Chaser::Update()
{
	if(GetTickCount() - mLastFindTime > findCycleTime)
	{
		mLastFindTime = GetTickCount();
		Player* player = mRoomCenter->GetPlayer();
		D3DXVECTOR3 playerPos = player->GetPos();
		vector<D3DXPLANE> sightFrustum;
		MakeSightFrustum(sightFrustum);
		if(ObjectInSightFrustum(player, sightFrustum))
		{
			D3DXVECTOR3 sightRayDir = playerPos - mPos;
			testSightDir = sightRayDir;
			float distanceToPlayer = D3DXVec3Length(&sightRayDir);
			D3DXVec3Normalize(&sightRayDir, &sightRayDir);
			map<string, Base3DObject*>& objectsInRoom = mRoomCenter->FindRoomIncludePos(mPos)->GetObjectsInRoomRef();
			BOOL canSeePlayer = true;
			float distanceToHitPoint = 0.f;
			for (map<string, Base3DObject*>::value_type& objectInRoom : objectsInRoom)
			{
				(*objectInRoom.second->GetColliderCube().begin()).second->isIntersectRay(mPos, sightRayDir, &distanceToHitPoint);
				cout << "hitPoint" << distanceToHitPoint << " pa" << distanceToPlayer << endl;
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
				SetTarget(playerPos);
			}
		}
	}

	if(mPath.empty() == false)
	{
		FollowingPath();
	}
	mSkinnedMesh->Update();
	Base3DObject::Update();
}

void Chaser::Render()
{
	Base3DObject::Render();
	mSkinnedMesh->Render(nullptr);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	gD3Device->SetTransform(D3DTS_WORLD, &matWorld);
	
	D3DXVECTOR3 lineVec[2];
	lineVec[0] = mPos;
	lineVec[1] = mPos + testSightDir * baseSightLength;
	
	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	gD3Device->SetTexture(0, nullptr);
	gD3Device->SetFVF(D3DFVF_XYZ);
	gD3Device->DrawPrimitiveUP(D3DPT_LINELIST, 1, lineVec, sizeof(D3DXVECTOR3));
}
