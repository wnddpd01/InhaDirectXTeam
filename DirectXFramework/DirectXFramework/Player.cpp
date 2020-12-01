#include "stdafx.h"
#include "Player.h"
#include "CameraManager.h"
#include "SkinnedMesh.h"
#include "KeyboardInputManager.h"
#include "IdleCharacterState.h"
#include "WalkCharacterState.h"
#include "FontManager.h"
#include "UIImage.h"
#include "Camera.h"
#include "ColliderCube.h"
#include "ColliderChecker.h"

Player::Player()
	: m_pSkinnedMesh(nullptr)
	, mCurState(nullptr)
	, mMoveVelocity(0, 0, 0)
	, mInteractingObject(nullptr)
{
	D3DXVECTOR3 yAxis = { 0, 1, 0 };
	float yAngle = D3DX_PI * 1.75f;
	D3DXQuaternionRotationAxis(&mRot, &yAxis, yAngle);

	mPos = { 8.f, 0.f, 8.f };
	
	D3DVIEWPORT9 viewPort;
	gD3Device->GetViewport(&viewPort);

	mDrawFontArea.left = viewPort.Width / 2;
	mDrawFontArea.top = viewPort.Height / 2;
	mDrawFontArea.right = mDrawFontArea.left + viewPort.Width * 0.3f;
	mDrawFontArea.right = mDrawFontArea.left + viewPort.Height * 0.1f;

	mInteractingObjectMark = new UIImage(string("Resources/UI/InteractMark.png"));
	mInteractingObjectMark->SetPos(D3DXVECTOR3(0, 10, 0));
	mInteractingObjectMark->SetVisible(true);
}


Player::~Player()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(mInteractingObjectMark);
}

void Player::HandleInteractableObjectSphereCollideEvent(Base3DObject* interactableObject)
{
	mInteractingObject = interactableObject;
}

void Player::ChangeState(CharacterState* nextState)
{
	SAFE_DELETE(mCurState);
	mCurState = nextState;
	mCurState->Enter(*this);
}

void Player::DrawMark()
{
	D3DXMATRIXA16 matProj;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matWorld;
	D3DVIEWPORT9 viewPort;
	gD3Device->GetTransform(D3DTS_PROJECTION, &matProj);
	gD3Device->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixIdentity(&matWorld);
	gD3Device->GetViewport(&viewPort);
	D3DXVECTOR3 markPos = mInteractingObject->GetPos();
	D3DXVec3Project(&markPos, &markPos, &viewPort, &matProj, &matView, &matWorld);
	markPos.z = 0;
	markPos.y -= mInteractingObjectMark->GetWidth() * 0.5f + viewPort.Height * 0.2f;
	markPos.x -= mInteractingObjectMark->GetWidth() * 0.5f;
	mInteractingObjectMark->SetPos(markPos);
	mInteractingObjectMark->Render();
}

void Player::MoveBack()
{
	mPos = mPrevPos;
}



void Player::Setup()
{
	Base3DObject::Setup();
	m_pSkinnedMesh = new SkinnedMesh("Resources/XFile/Zealot", "zealot.X");
	m_pSkinnedMesh->SetRandomTrackPosition();
	
	mCurState = new IdleCharacterState;
	mCurState->Enter(*this);

	CollideHandle = bind(&Player::HandlePlayerCubeCollideEvent, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
}

void Player::Update()
{	


	CharacterState * retState = mCurState->Update(*this);
	if (retState != nullptr)
	{
		ChangeState(retState);
	}

	if (D3DXVec3Length(&mMoveVelocity) > 0.01f)
	{
		
		mPrevPos = mPos;
		mPos += mMoveVelocity;
		
	}
	m_pSkinnedMesh->Update();

	if (mInteractingObject != nullptr)
	{
		mInteractingObject = nullptr;
	}

	Base3DObject::Update();

	mInventory.Update();

	//ProcessCollisionEventQueue();
	
}

void Player::Render()
 {
	Base3DObject::Render();
	D3DXMATRIXA16 matWorld;
	
	gD3Device->GetTransform(D3DTS_WORLD, &matWorld);
	
	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	m_pSkinnedMesh->SetTransform(&matWorld);
	m_pSkinnedMesh->Render(nullptr);
	
	if(mInteractingObject != nullptr)
	{
		DrawMark();
	}

	mInventory.Render();
}

bool Player::Update(eEventName eventName, void* parameter)
{
	switch (eventName)
	{
		case eEventName::KEY_DOWN:
		case eEventName::KEY_UP:
			{
				eKeyName key = *(eKeyName*)parameter;
				
				CharacterState * retState =  mCurState->HandleInput(*this, eventName,key);
				if(retState != nullptr)
				{
					ChangeState(retState);
				}
			}
			break;
		case eEventName::MOUSE_MOVE :
			{
				if (mCurState->GetStateName() != eCharacterStateName::INTERACTION_STATE)
				{
					POINT& mousePt = *(POINT*)parameter;
					D3DXVECTOR3 mouseWorldPos = gCurrentCamera->GetPickingPosition(mousePt) - mPos;
					
					D3DXMATRIXA16 matRot;
					D3DXMatrixLookAtLH(&matRot, &D3DXVECTOR3(0, 0, 0), &mouseWorldPos, &D3DXVECTOR3(0, 1, 0));

					D3DXQUATERNION quatRot;
					D3DXQuaternionRotationMatrix(&quatRot, &matRot);

					mRot = quatRot;
				}

			}
			break;
		default:
			break;
	}

	return true;
}

void Player::SetAnimationSpeed(FLOAT spd)
{
	m_pSkinnedMesh->m_pAnimController->SetTrackSpeed(0, spd);
}


void Player::HandlePlayerCubeCollideEvent(Base3DObject* player, string& myColliderTag, Base3DObject * otherCollider, string& otherColliderTag)
{
	if(otherColliderTag == "basicColliderCube")
	{
		mCollisionEventQueue.push({ player , myColliderTag ,otherCollider, otherColliderTag });
	}

	/*
	if(otherColliderTag == "basicColliderCube")
	{
		MoveBack();
		//otherCollider->GetColliderCube()[otherColliderTag]->GetAxisDir()[0];

		Base3DObject::Update();

		D3DXMATRIXA16 rot45;
		D3DXMatrixRotationY(&rot45, D3DX_PI * 0.25);

		float XAxisVelocity, ZAxisVelocity;

		XAxisVelocity = D3DXVec3Dot(
			&(otherCollider->GetColliderCube()[otherColliderTag]->GetAxisDir()[0]),
			&(mMoveVelocity));
		
		ZAxisVelocity = D3DXVec3Dot(
			&(otherCollider->GetColliderCube()[otherColliderTag]->GetAxisDir()[2]),
			&(mMoveVelocity));
		

		if (abs(XAxisVelocity) > 0.01f)
		{
			mPos += (XAxisVelocity * (otherCollider->GetColliderCube()[otherColliderTag]->GetAxisDir()[0]));
			Base3DObject::Update();

			if (ColliderCube::IsCollision(player->GetColliderCube()[myColliderTag], otherCollider->GetColliderCube()[otherColliderTag]))
			{
				mPos = mPrevPos;
				if (abs(ZAxisVelocity) > 0.01f)
				{
					mPos += (ZAxisVelocity * (otherCollider->GetColliderCube()[otherColliderTag]->GetAxisDir()[2]));
					Base3DObject::Update();
					if (ColliderCube::IsCollision(player->GetColliderCube()[myColliderTag], otherCollider->GetColliderCube()[otherColliderTag]))
					{
						mPos = mPrevPos;
					}
				}
			}
		}
	}
	*/
	/*
		//콜라이더 체크이용 슬라이딩 벡터
		Base3DObject::Update();

		D3DXMATRIXA16 rot45;
		D3DXMatrixRotationY(&rot45, D3DX_PI * 0.25);

		D3DXVECTOR3 rot45Velocity;
		D3DXVec3TransformNormal(&rot45Velocity, &mMoveVelocity, &rot45);

		if (D3DXVec3Length(&rot45Velocity) > 0.01f)
		{
			mPos += rot45Velocity;
			Base3DObject::Update();

			if (ColliderCube::IsCollision(player->GetColliderCube()[myColliderTag], otherCollider->GetColliderCube()[otherColliderTag]))
			{
				mPos = mPrevPos;
				D3DXVECTOR3 rot45RevVelocity;
				D3DXMATRIXA16 rotRev45;
				D3DXMatrixRotationY(&rotRev45, D3DX_PI * -0.25);
				D3DXVec3TransformNormal(&rot45RevVelocity, &mMoveVelocity, &rotRev45);
				if (D3DXVec3Length(&rot45Velocity) > 0.01f)
				{
					mPos += rot45RevVelocity;
					Base3DObject::Update();
					if (ColliderCube::IsCollision(player->GetColliderCube()[myColliderTag], otherCollider->GetColliderCube()[otherColliderTag]))
					{
						mPos = mPrevPos;
					}
				}
			}
		}
		*/

	
}

void Player::ProcessCollisionEventQueue()
{
	vector<D3DXVECTOR3> vecNextMoveVelocity;

	while (!mCollisionEventQueue.empty())
	{
		MoveBack();
		Base3DObject::Update();

		float XAxisVelocity, ZAxisVelocity;

		XAxisVelocity = D3DXVec3Dot(
			&(mCollisionEventQueue.front().obj2->GetColliderCube()[mCollisionEventQueue.front().obj2ColliderTag]->GetAxisDir()[0]),
			&(mMoveVelocity));

		ZAxisVelocity = D3DXVec3Dot(
			&(mCollisionEventQueue.front().obj2->GetColliderCube()[mCollisionEventQueue.front().obj2ColliderTag]->GetAxisDir()[2]),
			&(mMoveVelocity));

		cout << "xAxis : " << XAxisVelocity << endl;
		cout << "zAxis : " << ZAxisVelocity << endl;

		if (abs(XAxisVelocity) > 0.01f)
		{
			mPos += (XAxisVelocity * (mCollisionEventQueue.front().obj2->GetColliderCube()[mCollisionEventQueue.front().obj2ColliderTag]->GetAxisDir()[0]));
			Base3DObject::Update();
			if (ColliderCube::IsCollision(
				mCollisionEventQueue.front().obj1->GetColliderCube()[mCollisionEventQueue.front().obj1ColliderTag],
				mCollisionEventQueue.front().obj2->GetColliderCube()[mCollisionEventQueue.front().obj2ColliderTag]))
			{
				MoveBack();
				if (abs(ZAxisVelocity) > 0.01f)
				{
					mPos += (ZAxisVelocity * (mCollisionEventQueue.front().obj2->GetColliderCube()[mCollisionEventQueue.front().obj2ColliderTag]->GetAxisDir()[2]));
					Base3DObject::Update();
					if (ColliderCube::IsCollision(
						mCollisionEventQueue.front().obj1->GetColliderCube()[mCollisionEventQueue.front().obj1ColliderTag],
						mCollisionEventQueue.front().obj2->GetColliderCube()[mCollisionEventQueue.front().obj2ColliderTag]))
					{
						MoveBack();
					}
					else
					{
						MoveBack();
						vecNextMoveVelocity.push_back((ZAxisVelocity * (mCollisionEventQueue.front().obj2->GetColliderCube()[mCollisionEventQueue.front().obj2ColliderTag]->GetAxisDir()[2])));
					}
				}
			}
			else
			{
				MoveBack();
				vecNextMoveVelocity.push_back((XAxisVelocity * (mCollisionEventQueue.front().obj2->GetColliderCube()[mCollisionEventQueue.front().obj2ColliderTag]->GetAxisDir()[0])));
			}
		}
		mCollisionEventQueue.pop();
	}

	bool bMovable = true;
	for (auto& i : vecNextMoveVelocity)
	{
		if (vecNextMoveVelocity[0] != i)
		{
			bMovable = false;
		}
	}
	if(!vecNextMoveVelocity.empty())
	{
		if (bMovable)
		{
			mPos += vecNextMoveVelocity[0];
			Base3DObject::Update();
		}
	}
	
}

