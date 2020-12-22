#include "stdafx.h"
#include "CCTV.h"
#include "SkinnedMesh.h"

CCTV::CCTV()
{
	mSkinnedMesh = new SkinnedMesh("Resources/XFile/CCTV", "CCTV.X");
	mSkinnedMesh->PrintAnimationList();
}

CCTV::~CCTV()
{
	SAFE_DELETE(mSkinnedMesh);
}
