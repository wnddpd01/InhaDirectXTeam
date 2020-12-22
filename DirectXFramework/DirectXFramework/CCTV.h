#pragma once

#include "Base3DObject.h"

class SkinnedMesh;

class CCTV :
	public Base3DObject
{
private :
	SkinnedMesh* mSkinnedMesh;

public :
	CCTV();
	~CCTV();
};

