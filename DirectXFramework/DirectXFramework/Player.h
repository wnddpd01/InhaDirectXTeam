#pragma once
#include "Base3DObject.h"

class SkinnedMesh;
class CharacterState;
class UIImage;

class Player : public Base3DObject, public BaseObserver
{
	RECT mDrawFontArea;
	CharacterState* mCurState;
	D3DXVECTOR3 mMoveVelocity;
	Base3DObject * mInteractingObject;
	UIImage * mInteractingObjectMark;
	void StateChange(CharacterState * nextState);
	void DrawMark();
public:
	SkinnedMesh* m_pSkinnedMesh;
#pragma region GetterAndSetter
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
	Base3DObject * GetInteractingObject() { return mInteractingObject; }
	
#pragma endregion

	void Setup() override;
	void Update() override;
	void Render() override;

	bool Update(eEventName eventName, void* parameter) override;

	SkinnedMesh * GetSkinnedMesh()
	{
		return m_pSkinnedMesh;
	}

	void SetAnimationSpeed(FLOAT spd);
	
	Player();
	virtual ~Player();

	void PlayerCollideHandle(Base3DObject* player, string& myColliderTag, Base3DObject * otherCollider, string& otherColliderTag);
};

