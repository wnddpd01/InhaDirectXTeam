#pragma once
#include "ColliderPolygon.h"

class ColliderSphere : public ColliderPolygon
{
public:
	ColliderSphere();
	virtual ~ColliderSphere();
	void Setup() override;
	void SetSphereCollider(float radius);
	float& GetRadius() { return mRadius; }
	
private:
	float mRadius;
};

