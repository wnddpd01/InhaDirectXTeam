#pragma once
#include "ColliderPolygon.h"

class ColliderSphere : public ColliderPolygon
{
public:
	ColliderSphere();
	~ColliderSphere();
	void Setup() override;
	void Update() override;
	void SetSphereCollider(float radius);

private:
	float mRadius;
};

