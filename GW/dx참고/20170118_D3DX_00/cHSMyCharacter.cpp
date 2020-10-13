#include "stdafx.h"
#include "cHSMyCharacter.h"
#include "cAseLoader.h"


cHSMyCharacter::cHSMyCharacter()
	:	m_pModel(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cHSMyCharacter::~cHSMyCharacter()
{
}

void cHSMyCharacter::Setup(char* _szFilePath, D3DXVECTOR3 _vScale)
{
	// 로드..도 이렇게 하지말고 파일명을 인자로 받자.
	cAseLoader* pAse = new cAseLoader;
	g_pAutoReleasePool->AddObject(pAse);
	pAse->Load(_szFilePath, m_pModel, m_stScene);

		
	//스케일이라던지.. 이런것도 다 인자로 받자.
	m_vScale = _vScale;

	//여기서 m_pModel의 버텍스들을 로컬로 바꿔주자. 근데 지금은 귀찮으니까 업뎃에서 로컬로 바꾸고 애니하고 월드로 해주지.
}

void cHSMyCharacter::Update(D3DXMATRIXA16* _matParent)
{
	if (_matParent == NULL)
		return;
	
	cGameObject::Update(_matParent);
	
	
	int nKeyFrame = ( GetTickCount() * 3) % ((m_stScene.nLastFrame - m_stScene.nFirstFrame) * m_stScene.nTicksPerFrame) + m_stScene.nFirstFrame* m_stScene.nTicksPerFrame;
	
	m_pModel->Update(nKeyFrame, &m_matWorld);
	
	//키프레임 계산하기
}

void cHSMyCharacter::Render()
{
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	if (m_pModel != NULL)
	{
		m_pModel->Render();
	}
}
