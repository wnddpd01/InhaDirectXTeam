#pragma once

class cSkinnedMesh;
class CharacterState;

class cZealot : public BaseObject, public BaseObserver
{
	CharacterState* mCurState;

	D3DXVECTOR3 mMoveVelocity;

	D3DXQUATERNION mRot;

	D3DXVECTOR3 mPos;

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

