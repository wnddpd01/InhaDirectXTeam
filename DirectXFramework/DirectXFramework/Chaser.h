#pragma once
#include "Base3DObject.h"

class ChaserState;
class SkinnedMesh;

class Chaser :
	public Base3DObject
{
private :
	static D3DXVECTOR3 baseSightDir;
	static float baseSightLength;
	static float baseSightAngle;
	static float angrySightAngle;
	
	RoomCenter* mRoomCenter;
	ChaserState* mChaserState;
	SkinnedMesh* mSkinnedMesh;
	D3DXVECTOR3 mBasePos;
	D3DXVECTOR3 mTargetPos;
	vector<D3DXPLANE>* mSightFrustum;
	DWORD mCycleTime;
	DWORD mLastUpdateTime;
	float mSpeed;

	bool ObjectInSightFrustum(D3DXVECTOR3& objectPos, vector<D3DXPLANE>& sightFrustum);
	void MakeSightFrustum(OUT vector<D3DXPLANE>& sightPlane);
	void FollowingPath();
	void ReturnToBasePos();
	void Attack(Player* player);
public :
	constexpr static DWORD findCycleTime = 300;
	constexpr static DWORD attackCycleTime = 1500;
	constexpr static float attackRange = 1.f;
	constexpr static float findRange = 10.f;
	static vector<D3DXPLANE> baseSightFrustum;
	static vector<D3DXPLANE> angrySightFrustum;
	
	Chaser(D3DXVECTOR3 basePos, RoomCenter* roomCenter);
	virtual ~Chaser();

	D3DXVECTOR3 GetBasePos() const { return mBasePos; }
	SkinnedMesh* GetSkinnedMesh() const { return mSkinnedMesh; }

	void MatchTargetToPlayer();
	void SetTarget(D3DXVECTOR3& targetPos) { mTargetPos = targetPos; }
	D3DXVECTOR3 GetTarget() const { return mTargetPos; }

	void SetSightFrustum(vector<D3DXPLANE>* sightFrustum) { mSightFrustum = sightFrustum; }

	ChaserState* GetChaserState() const { return mChaserState; }
	
	bool IsTargetInSight();
	void RotateToTarget();

	void ChangeState(ChaserState* newState);
	
	void Update() override;
	void Render() override;
};

