#pragma once
#include "Base3DObject.h"

class SkinnedMesh;
class CharacterState;

class Player : public Base3DObject, public BaseObserver
{
	CharacterState* mCurState;

	D3DXVECTOR3 mMoveVelocity;


	void StateChange(CharacterState * nextState);
public:
	SkinnedMesh* m_pSkinnedMesh;
	D3DXQUATERNION& GetRotRef()
	{
		return mRot;
	}
	
	D3DXVECTOR3 GetPos() const
	{
		return mPos;
	}

	D3DXVECTOR3 * GetPosRef()
	{
		return &mPos;
	}
	
	void SetPos(const D3DXVECTOR3& pos)
	{
		mPos = pos;
	}

	void SetMoveVelocity(const D3DXVECTOR3& moveVelocity)
	{
		mMoveVelocity = moveVelocity;
	}
	void Setup();
	void Update();
	void Render();

	bool Update(eEventName eventName, void* parameter) override;

	SkinnedMesh * GetSkinnedMesh()
	{
		return m_pSkinnedMesh;
	}

	void SetAnimationSpeed(FLOAT spd);
	
	Player();
	virtual ~Player();
};

