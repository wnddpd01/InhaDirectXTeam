#include "stdafx.h"
#include "cZealot.h"
#include "cSkinnedMesh.h"

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
	if(eventName == eEventName::MOUSE_R_UP)
	{
		m_pSkinnedMesh->SetAnimationIndexBlend(rand() % 3);
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
