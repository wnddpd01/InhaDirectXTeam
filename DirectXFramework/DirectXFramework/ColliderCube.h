#pragma once
#include "ColliderPolygon.h"

class ColliderCube : public ColliderPolygon
{
public:
	ColliderCube();
	virtual ~ColliderCube();
	void Setup() override;
	void Update() override;
	void Render() override;
	
	void SetCubeCollider(float height, float width, float depth);
	
	static bool IsCollision(ColliderCube* obj1Cube, ColliderCube* obj2Cube);

	D3DXVECTOR3* GetAxisDir();
	
private:
	float mCubeHeight;
	float mCubeWidth;
	float mCubeDepth;

	D3DXVECTOR3 m_vOriCenterPos;
	D3DXVECTOR3 m_vOriAxisDir[3];
	
	vector<D3DXVECTOR3> m_BoxDrawVertex;
	
	D3DXVECTOR3 m_vCenterPos;
	D3DXVECTOR3 m_vAxisDir[3];
	
	float m_fAxisLen[3];
	float m_fAxisHalfLen[3];

	
};

