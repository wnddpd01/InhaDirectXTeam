#include "stdafx.h"
#include "PlayerCharacter.h"
#include "cSkinnedMesh.h"
#include "KeyboardInputManager.h"
#include "OBB.h"

PlayerCharacter::PlayerCharacter()
	: m_pSkinnedMesh(NULL)
	, m_pOBB(NULL)
	, m_vPosition(3, 0, 0)
	, m_vDirection(0, 0, -1)
{
	D3DXMatrixIdentity(&m_matWorld);
	
	D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);

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
	D3DXMATRIXA16 matR;
	
	switch (eventName)
	{
		case eEventName::MOUSE_MOVE:
			{
				POINT mousePosition = *(POINT*)parameter;
				D3DXVECTOR3 mousePositionVector(0,0,0);

				mousePositionVector.x = mousePosition.x;
				mousePositionVector.y = mousePosition.y;
				
				D3DVIEWPORT9 vp;
				gD3Device->GetViewport(&vp);
				D3DXMATRIXA16 matProj;
				gD3Device->GetTransform(D3DTS_PROJECTION, &matProj);
				D3DXMATRIXA16 matView;
				gD3Device->GetTransform(D3DTS_VIEW, &matView);
				
				D3DXVec3Unproject(&mousePositionVector, &mousePositionVector, &vp, &matProj, &matView, nullptr);
				
				/*m_vDirection = m_vPosition - mousePositionVector;
				m_vDirection.y = 0;
				D3DXVec3Normalize(&m_vDirection, &m_vDirection);*/
				
				D3DXMatrixLookAtLH(&matR, &m_vPosition, &mousePositionVector, &D3DXVECTOR3(0, 1, 0));
				matR._41 = matR._42 = matR._43 = 0.0f;
				D3DXMatrixInverse(&matR, NULL, &matR);
			}
			break;
		case eEventName::KEY_DOWN:
			{
				eKeyName key = *(eKeyName*)parameter;
				switch (key)
				{
					case eKeyName::KEY_FRONT_DOWN :
						{
							m_vPosition += (m_vDirection * 1.5f) * gTimeManager->GetDeltaTime();
						}
						break;
					case eKeyName::KEY_BACK_DOWN :
						{
							m_vPosition -= (m_vDirection * 1.5f) * gTimeManager->GetDeltaTime();
						}
						break;
					case eKeyName::KEY_LEFT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, -(90 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 1.5f) * gTimeManager->GetDeltaTime();
							D3DXMatrixRotationY(&matR, +(90 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
						}
						break;
					case eKeyName::KEY_RIGHT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, +(90*(D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 1.5f) * gTimeManager->GetDeltaTime();
							D3DXMatrixRotationY(&matR, -(90 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
						}
						break;
					case eKeyName::KEY_FRONTRIGHT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, +(45 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 1.5f) * gTimeManager->GetDeltaTime();
							D3DXMatrixRotationY(&matR, -(45 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
						}
						break;
					case eKeyName::KEY_FRONTLEFT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, -(45 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 1.5f) * gTimeManager->GetDeltaTime();
							D3DXMatrixRotationY(&matR, +(45 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
						}
						break;
					case eKeyName::KEY_BACKRIGHT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, +(135 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 1.5f) * gTimeManager->GetDeltaTime();
							D3DXMatrixRotationY(&matR, -(135 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
						}
						break;
					case eKeyName::KEY_BACKLEFT_DOWN:
						{
							D3DXMATRIXA16 matR;
							D3DXMatrixRotationY(&matR, -(135 * (D3DX_PI / 180)));
							D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
							m_vPosition += (m_vDirection * 1.5f) * gTimeManager->GetDeltaTime();
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
					case eKeyName::KEY_EQUIPCHAGELFFT_DOWN:
						{

						}
						break;
					case eKeyName::KEY_EQUIPCHAGERIGHT_DOWN:
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

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
	
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