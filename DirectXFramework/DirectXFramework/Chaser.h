#pragma once
#include "Base3DObject.h"

class SkinnedMesh;
class Chaser :
	public Base3DObject
{
private :
	constexpr static float basicSpeed = 0.05f;
	constexpr static float angrySpeed = 0.05f;
	SkinnedMesh* mSkinnedMesh;
	vector<D3DXVECTOR3> mPath;
	float mSpeed;

	void FollowingPath();
	void RotateToNextNode();
public :
	Chaser();
	~Chaser();

	void SetPath(vector<D3DXVECTOR3>& pathNodes);
	
	void Update() override;
	void Render() override;
};

