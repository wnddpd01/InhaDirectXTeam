#pragma once
#include "Base3DObject.h"

class SkinnedMesh;

enum class ChaserState
{
	STOP = 0, RETURNING, CHASING
};

class Chaser :
	public Base3DObject
{
private :
	constexpr static float basicSpeed = 0.04f;
	constexpr static float angrySpeed = 0.06f;
	ChaserState mChaserState;
	SkinnedMesh* mSkinnedMesh;
	vector<D3DXVECTOR3> mPath;
	D3DXVECTOR3 mBasePos;
	float mSpeed;

	void FollowingPath();
	void RotateToNextNode();
	void FindPath(D3DXVECTOR3& targetPos);
	void ReturnToBasePos();
public :
	Chaser(D3DXVECTOR3 basePos);
	~Chaser();

	D3DXVECTOR3 GetBasePos() const { return mBasePos; }
	
	void SetTarget(D3DXVECTOR3& targetPos);
	
	void Update() override;
	void Render() override;
};

