#pragma once
#include "ColliderPolygon.h"

class ColliderCube : public ColliderPolygon
{
public:
	ColliderCube();
	virtual ~ColliderCube();
	void Setup() override;
	void SetCubeCollider(float height, float width, float depth);

	D3DXVECTOR3 GetMax() { return D3DXVECTOR3(mCubeWidth, mCubeHeight, mCubeDepth); }
	D3DXVECTOR3 GetMin() { return D3DXVECTOR3(0, 0, 0); }
	
private:
	float mCubeHeight;
	float mCubeWidth;
	float mCubeDepth;

};

