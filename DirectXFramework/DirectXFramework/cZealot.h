#pragma once
#include "Base3DObject.h"

class cSkinnedMesh;
class CharacterState;

class cZealot : public Base3DObject, public BaseObserver
{
	CharacterState* mCurState;

	D3DXVECTOR3 mMoveVelocity;


	void StateChange(CharacterState * nextState);
public:
	cSkinnedMesh* m_pSkinnedMesh;
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

	cSkinnedMesh * GetSkinnedMesh()
	{
		return m_pSkinnedMesh;
	}

	void SetAnimationSpeed(FLOAT spd);
	
	cZealot();
	virtual ~cZealot();
};

