#pragma once
#include "MapObject.h"

class MapObjectCenter;

class Sphere :
	public MapObject
{
public:
	Sphere(MapObjectCenter* p, D3DXVECTOR3 pos);
	~Sphere();

	void Setup() override;
	void Update() override;
	void Render() override;
};

