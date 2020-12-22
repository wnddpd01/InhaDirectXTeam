#include "stdafx.h"
#include "Chaser.h"
#include "SkinnedMesh.h"

void Chaser::FollowingPath()
{
	D3DXVECTOR3 moveDir = mPath.back() - mPos;
	float distance = D3DXVec3Length(&moveDir);
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
			mSkinnedMesh->SetAnimationIndexBlend(8);
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

	static D3DXQUATERNION idleRot;
	D3DXQuaternionRotationYawPitchRoll(&idleRot, D3DX_PI, 0, 0);
	SetRot(idleRot * quatRot);
}

void Chaser::MakingAndSetTestPath()
{
	vector<D3DXVECTOR3> path;
	path.emplace_back(10, 0, 10);
	path.emplace_back(0, 0, 10);
	path.emplace_back(0, 0, -10);
	path.emplace_back(-10, 0, -10);
	SetPath(path);
}

Chaser::Chaser()
	: mSpeed(0.05f)
{
	SetScale(D3DXVECTOR3(0.003f, 0.003f, 0.003f));
	mSkinnedMesh = new SkinnedMesh("Resources/XFile/Chaser", "Chaser.X");
	mSkinnedMesh->SetAnimationIndex(8); 
}

Chaser::~Chaser()
{
	mPath.clear();
	SAFE_DELETE(mSkinnedMesh);
}

void Chaser::SetPath(vector<D3DXVECTOR3>& pathNodes)
{
	mPath.clear();
	mPath.assign(pathNodes.rbegin(), pathNodes.rend());
	RotateToNextNode();
	mSkinnedMesh->SetAnimationIndexBlend(4);
}


void Chaser::Update()
{
	mSkinnedMesh->Update();
	if(mPath.empty() == false)
	{
		FollowingPath();
	}
	Base3DObject::Update();
}

void Chaser::Render()
{
	Base3DObject::Render();
	mSkinnedMesh->Render(nullptr);
}
