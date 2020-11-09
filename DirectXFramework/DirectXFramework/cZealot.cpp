#include "stdafx.h"
#include "cZealot.h"
#include "cSkinnedMesh.h"
#include "KeyboardInputManager.h"

void cZealot::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("Zealot", "zealot.X");
	m_pSkinnedMesh->SetRandomTrackPosition();
}

void cZealot::Update()
{
	m_pSkinnedMesh->Update();
}

void cZealot::Render()
{
	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	m_pSkinnedMesh->Render(nullptr);
}

bool cZealot::Update(eEventName eventName, void* parameter)
{
	switch (eventName)
	{
		case eEventName::KEY_DOWN:
			{
				eKeyName key = *(eKeyName*)parameter;
				switch (key)
				{
					case eKeyName::KEY_FRONT_DOWN :
						{
							D3DXMATRIXA16 matT;
							D3DXMatrixTranslation(&matT, 0, 0, -1 * gTimeManager->GetDeltaTime());
							m_pSkinnedMesh->m_matWorldTM = m_pSkinnedMesh->m_matWorldTM * matT;
						}
						break;
					case eKeyName::KEY_BACK_DOWN :
						{
							D3DXMATRIXA16 matT;
							D3DXMatrixTranslation(&matT, 0, 0, 1 * gTimeManager->GetDeltaTime());
							m_pSkinnedMesh->m_matWorldTM = m_pSkinnedMesh->m_matWorldTM * matT;
						}
						break;
					case eKeyName::KEY_LEFT_DOWN:
						{
							D3DXMATRIXA16 matT;
							D3DXMatrixTranslation(&matT, -1 * gTimeManager->GetDeltaTime(), 0, 0);
							m_pSkinnedMesh->m_matWorldTM = m_pSkinnedMesh->m_matWorldTM * matT;
						}
						break;
					case eKeyName::KEY_RIGHT_DOWN:
						{
							D3DXMATRIXA16 matT;
							D3DXMatrixTranslation(&matT, 1 * gTimeManager->GetDeltaTime(), 0, 0);
							m_pSkinnedMesh->m_matWorldTM = m_pSkinnedMesh->m_matWorldTM * matT;
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

	return true;
}


cZealot::cZealot() : m_pSkinnedMesh(NULL)
{
}


cZealot::~cZealot()
{
	SAFE_DELETE(m_pSkinnedMesh);
}
