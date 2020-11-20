#pragma once
#include "Base3DObject.h"
class Portal :
	public Base3DObject
{
	D3DXVECTOR3 mExitPos;
public:
	Portal();
	~Portal();

	void SetExitPos(D3DXVECTOR3 exitPos) { mExitPos = exitPos; }
	D3DXVECTOR3 GetExitPos() const { return mExitPos; }
};

