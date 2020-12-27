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
	constexpr static DWORD findCycleTime = 300;
	static D3DXVECTOR3 baseSightDir;
	static float baseSightLength;
	static float baseSightAngle;
	static vector<D3DXPLANE> baseSightFrustum;
	
	RoomCenter* mRoomCenter;
	ChaserState mChaserState;
	SkinnedMesh* mSkinnedMesh;
	vector<D3DXVECTOR3> mPath;
	D3DXVECTOR3 mBasePos;
	DWORD mLastFindTime;
	float mSpeed;

	D3DXVECTOR3 testSightDir; // test
	
	void FollowingPath();
	void RotateToNextNode();
	bool ObjectInSightFrustum(Base3DObject* object, vector<D3DXPLANE>& sightFrustum);
	void MakeSightFrustum(OUT vector<D3DXPLANE>& sightPlane);
	void FindPath(D3DXVECTOR3& endPos);
	void ReturnToBasePos();
public :
	Chaser(D3DXVECTOR3 basePos, RoomCenter* roomCenter);
	~Chaser();

	D3DXVECTOR3 GetBasePos() const { return mBasePos; }
	
	void SetTarget(D3DXVECTOR3& targetPos);
	
	void Update() override;
	void Render() override;
};

