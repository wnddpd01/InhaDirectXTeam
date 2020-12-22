#include "stdafx.h"
#include "CCTV.h"

#include "ColliderSphere.h"
#include "SkinnedMesh.h"

CCTV::CCTV(const LPD3DXMESH& floorMesh, D3DXVECTOR3 eyeDir, D3DXVECTOR3 pos)
{
	SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	mSkinnedMesh = new SkinnedMesh("Resources/XFile/CCTV", "CCTV.X");
	mSkinnedMesh->SetAnimationIndexBlend(0);
	D3DXVec3Normalize(&mEyeDir, &eyeDir);
	mPos = pos;
	BOOL isHit;
	float hitDist = 0;
	static D3DXVECTOR3 floorPos = D3DXVECTOR3(75, 0, 75);
	D3DXIntersect(floorMesh, &(mPos - floorPos), &mEyeDir, &isHit, nullptr, nullptr, nullptr, &hitDist, nullptr, nullptr);
	mDetectSpherePos = mPos + mEyeDir * hitDist;
	mDetectSphere = new ColliderSphere;
	mDetectSphere->SetPosition(&mDetectSpherePos);
}

CCTV::~CCTV()
{
	SAFE_DELETE(mSkinnedMesh);
}

void CCTV::Update()
{
	mSkinnedMesh->Update();
	Base3DObject::Update();
}

void CCTV::Render()
{
	Base3DObject::Render();
	mSkinnedMesh->Render(nullptr);
	mDetectSphere->Render();
}
