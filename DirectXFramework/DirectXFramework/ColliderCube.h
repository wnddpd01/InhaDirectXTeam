#pragma once
#include "ColliderPolygon.h"

class ColliderCube : public ColliderPolygon
{
public:
	ColliderCube();
	virtual ~ColliderCube();
	void Setup() override;
	void Update() override;
	void SetCubeCollider(float height, float width, float depth);

private:
	float mCubeHeight;
	float mCubeWidth;
	float mCubeDepth;

};

