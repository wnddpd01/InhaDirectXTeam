#include "stdafx.h"
#include "PlayerCharacter.h"
#include "cSkinnedMesh.h"
#include "KeyboardInputManager.h"
#include "OBB.h"
#include "QuarterMap.h"

PlayerCharacter::PlayerCharacter()
	: m_pSkinnedMesh(NULL)
	, m_pOBB(NULL)
	, m_vPosition(5, 0, 2)
	, m_vDirection(0, 0, -1)
	, mQuarterMap(nullptr)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	D3DXMatrixIdentity(&matR);
}

PlayerCharacter::~PlayerCharacter()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_pOBB);
}

void PlayerCharacter::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("Zealot", "zealot.X");
	m_pSkinnedMesh->SetRandomTrackPosition();

	mQuarterMap = new QuarterMap;
	mQuarterMap->Setup("HeightMapData/", "QuarterHeightMap.raw", "StoneTiles.jpg");
	
	m_pOBB = new OBB;
	m_pOBB->Setup(m_pSkinnedMesh);
}

void PlayerCharacter::Update()
{
	m_pSkinnedMesh->Update();

	if (m_pOBB)
		m_pOBB->Update(&m_matWorld);
}

void PlayerCharacter::Render()
{
	m_pSkinnedMesh->SetTransform(&m_matWorld);
	
	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	m_pSkinnedMesh->Render(nullptr);
	
	
	if (m_pOBB)
		m_pOBB->OBBBOX_Render(D3DCOLOR_XRGB(255,255,255));
}

bool PlayerCharacter::Update(eEventName eventName, void* parameter)
{
	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);
	static D3DXVECTOR3 prevPosition = m_vPosition;
	
	switch (eventName)
	{
		case eEventName::MOUSE_MOVE:
			{
				D3DXVECTOR3 pickPosition = *(D3DXVECTOR3*)parameter;

				D3DXMatrixLookAtRH(&matR, &m_vPosition, &pickPosition, &D3DXVECTOR3(0, 1, 0));

				matR._41 = matR._42 = matR._43 = 0.0f;
				D3DXMatrixInverse(&matR, NULL, &matR);
				m_vDirection =  pickPosition - m_vPosition;
				D3DXVec3Normalize(&m_vDirection, &m_vDirection);
			}
			break;
		case eEventName::KEY_DOWN:
			{
				eKeyName key = *(eKeyName*)parameter;
				switch (key)
				{
					case eKeyName::KEY_FRONT_DOWN :
						{
							m_vPosition += (m_vDirection * 4.f) * gTimeManager->GetDeltaTime();
							
						}
						break;
					case eKeyName::KEY_BACK_DOWN :
						{
							m_vPosition -= (m_vDirection * 4.f) * gTimeManager->GetDeltaTime();
						}
						break;
					case eKeyName::KEY_LEFT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, -(90 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 4.f) * gTimeManager->GetDeltaTime();
							D3DXMatrixRotationY(&matR, +(90 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
						}
						break;
					case eKeyName::KEY_RIGHT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, +(90*(D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 4.f) * gTimeManager->GetDeltaTime();
							D3DXMatrixRotationY(&matR, -(90 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
						}
						break;
					case eKeyName::KEY_FRONT_RIGHT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, +(45 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 4.f) * gTimeManager->GetDeltaTime();
							D3DXMatrixRotationY(&matR, -(45 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
						}
						break;
					case eKeyName::KEY_FRONT_LEFT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, -(45 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 4.f) * gTimeManager->GetDeltaTime();
							D3DXMatrixRotationY(&matR, +(45 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
						}
						break;
					case eKeyName::KEY_BACK_RIGHT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, +(135 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 4.f) * gTimeManager->GetDeltaTime();
							D3DXMatrixRotationY(&matR, -(135 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
						}
						break;
					case eKeyName::KEY_BACK_LEFT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, -(135 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 4.f) * gTimeManager->GetDeltaTime();
							D3DXMatrixRotationY(&matR, +(135 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
						}
						break;
					case eKeyName::KEY_INTERACTION_DOWN:
						{
							
						}
						break;
					case eKeyName::KEY_RUN_DOWN:
						{

						}
						break;
					case eKeyName::KEY_EQUIP_CHAGE_LFFT_DOWN:
						{

						}
						break;
					case eKeyName::KEY_EQUIP_CHAGE_RIGHT_DOWN:
						{

						}
						break;
					default:
						break;
				}
			}
			break;
		default:
			break;
	}
	
	cout << mQuarterMap->GetHeight(m_vPosition.x, m_vPosition.z) << endl;
	
	if(mQuarterMap->GetHeight(m_vPosition.x, m_vPosition.z) > 19.0f || isCollision)
	{
		m_vPosition = prevPosition;
	}
	else
	{
		prevPosition = m_vPosition;
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		m_matWorld = matR * matT;
	}

	
	
	return true;
}

OBB * PlayerCharacter::GetOBB()
{
	return m_pOBB;
}

D3DXVECTOR3& PlayerCharacter::GetPosition()
{
	return m_vPosition;
}

void PlayerCharacter::SetCollsion(bool Collision)
{
	isCollision = Collision;
}