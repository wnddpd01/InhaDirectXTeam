#include "stdafx.h"
#include "Chaser.h"
#include "SkinnedMesh.h"

Chaser::Chaser()
{
	SetScale(D3DXVECTOR3(0.003f, 0.003f, 0.003f));
	mSkinnedMesh = new SkinnedMesh("Resources/XFile/Chaser", "Chaser.X");
	mSkinnedMesh->SetAnimationIndex(8);
	mSkinnedMesh->PrintAnimationList();
}

Chaser::~Chaser()
{
}

void Chaser::Update()
{
	mSkinnedMesh->Update();
	Base3DObject::Update();
}

void Chaser::Render()
{
	Base3DObject::Render();
	mSkinnedMesh->Render(nullptr);
}
