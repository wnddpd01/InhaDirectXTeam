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
	// �ε�..�� �̷��� �������� ���ϸ��� ���ڷ� ����.
	cAseLoader* pAse = new cAseLoader;
	g_pAutoReleasePool->AddObject(pAse);
	pAse->Load(_szFilePath, m_pModel, m_stScene);

		
	//�������̶����.. �̷��͵� �� ���ڷ� ����.
	m_vScale = _vScale;

	//���⼭ m_pModel�� ���ؽ����� ���÷� �ٲ�����. �ٵ� ������ �������ϱ� �������� ���÷� �ٲٰ� �ִ��ϰ� ����� ������.
}

void cHSMyCharacter::Update(D3DXMATRIXA16* _matParent)
{
	if (_matParent == NULL)
		return;
	
	cGameObject::Update(_matParent);
	
	
	int nKeyFrame = ( GetTickCount() * 3) % ((m_stScene.nLastFrame - m_stScene.nFirstFrame) * m_stScene.nTicksPerFrame) + m_stScene.nFirstFrame* m_stScene.nTicksPerFrame;
	
	m_pModel->Update(nKeyFrame, &m_matWorld);
	
	//Ű������ ����ϱ�
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
