#include "stdafx.h"
#include "cCubeNode.h"


cCubeNode::cCubeNode()
	: m_fRotDeltaX(0.f)
	, m_pParentWorldTM(NULL)
	, m_vLocalPos(0, 0, 0)
	, m_fRotX(0.f)
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}


cCubeNode::~cCubeNode()
{
}

void cCubeNode::AddChild(cCubeNode* pChild)
{
	pChild->m_pParentWorldTM = &m_matWorldTM;
	m_vecChild.push_back(pChild);
}

void cCubeNode::Destroy()
{
	for each(auto p in m_vecChild)
	{
		p->Destroy();
	}
	delete this;
}

void cCubeNode::SetMineCraftTexture(float left, float top, float width, float depth ,float hight )
{
	//float left, top;
	//left = 0.f / TEXTURESIZE;
	//top = 16.f / TEXTURESIZE;

	//float width = 4.f / TEXTURESIZE;
	//float deep = 4.f / TEXTURESIZE;
	//float high = 12.f / TEXTURESIZE;

	//앞
	m_vecVertex[0].t.x = left + depth;			m_vecVertex[0].t.y = top + depth + hight;
	m_vecVertex[1].t.x = left + depth;			m_vecVertex[1].t.y = top + depth;
	m_vecVertex[2].t.x = left + depth + width;	m_vecVertex[2].t.y = top + depth;

	m_vecVertex[3].t.x = left + depth;		   m_vecVertex[3].t.y = top + depth + hight;
	m_vecVertex[4].t.x = left + depth + width;  m_vecVertex[4].t.y = top + depth;
	m_vecVertex[5].t.x = left + depth + width;  m_vecVertex[5].t.y = top + depth + hight;
	//뒤
	m_vecVertex[6].t.x = left + 2 * depth + 2 * width;	m_vecVertex[6].t.y = top + depth + hight;
	m_vecVertex[7].t.x = left + 2 * depth + width;		m_vecVertex[7].t.y = top + depth;
	m_vecVertex[8].t.x = left + 2 * depth + 2 * width;	m_vecVertex[8].t.y = top + depth;

	m_vecVertex[9].t.x = left + 2 * depth + 2 * width;   m_vecVertex[9].t.y = top + depth + hight;
	m_vecVertex[10].t.x = left + 2 * depth + width;		m_vecVertex[10].t.y = top + depth + hight;
	m_vecVertex[11].t.x = left + 2 * depth + width;		m_vecVertex[11].t.y = top + depth;
	//왼
	m_vecVertex[12].t.x = left;   m_vecVertex[12].t.y = top + depth + hight;
	m_vecVertex[13].t.x = left;  m_vecVertex[13].t.y = top + depth;
	m_vecVertex[14].t.x = left + depth;  m_vecVertex[14].t.y = top + depth;

	m_vecVertex[15].t.x = left;   m_vecVertex[15].t.y = top + depth + hight;
	m_vecVertex[16].t.x = left + depth;  m_vecVertex[16].t.y = top + depth;
	m_vecVertex[17].t.x = left + depth;  m_vecVertex[17].t.y = top + depth + hight;
	//오
	m_vecVertex[18].t.x = left + depth + width;  m_vecVertex[18].t.y = top + depth + hight;
	m_vecVertex[19].t.x = left + depth + width;  m_vecVertex[19].t.y = top + depth;
	m_vecVertex[20].t.x = left + 2 * depth + width;  m_vecVertex[20].t.y = top + depth;

	m_vecVertex[21].t.x = left + depth + width;  m_vecVertex[21].t.y = top + depth + hight;
	m_vecVertex[22].t.x = left + 2 * depth + width;  m_vecVertex[22].t.y = top + depth;
	m_vecVertex[23].t.x = left + 2 * depth + width;  m_vecVertex[23].t.y = top + depth + hight;

	//위
	m_vecVertex[24].t.x = left + depth;  m_vecVertex[24].t.y = top + depth;
	m_vecVertex[25].t.x = left + depth;  m_vecVertex[25].t.y = top;
	m_vecVertex[26].t.x = left + depth + width;  m_vecVertex[26].t.y = top;

	m_vecVertex[27].t.x = left + depth;  m_vecVertex[27].t.y = top + depth;
	m_vecVertex[28].t.x = left + depth + width;  m_vecVertex[28].t.y = top;
	m_vecVertex[29].t.x = left + depth + width;  m_vecVertex[29].t.y = top + depth;
	//아래
	m_vecVertex[30].t.x = left + depth + width;  m_vecVertex[30].t.y = top;
	m_vecVertex[31].t.x = left + depth + width;  m_vecVertex[31].t.y = top + depth;
	m_vecVertex[32].t.x = left + 2 * depth + width;  m_vecVertex[32].t.y = top + depth;

	m_vecVertex[33].t.x = left + depth + width;  m_vecVertex[33].t.y = top;
	m_vecVertex[34].t.x = left + 2 * depth + width;  m_vecVertex[34].t.y = top + depth;
	m_vecVertex[35].t.x = left + 2 * depth + width;  m_vecVertex[35].t.y = top;
}

void cCubeNode::Setup()
{
	cCubePNT::Setup();
	
}

void cCubeNode::Update()
{
	cCubePNT::Update();

	m_fRotX += m_fRotDeltaX;
	if(m_fRotX > D3DX_PI / 6.f)
	{
		m_fRotX = D3DX_PI / 6.f;
		m_fRotDeltaX *= -1;
	}
	if (m_fRotX < -D3DX_PI / 6.f)
	{
		m_fRotX = -D3DX_PI / 6.f;
		m_fRotDeltaX *= -1;
	}

	
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixRotationX(&matR, m_fRotX);
	D3DXMatrixTranslation(&matT, m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);
	m_matLocalTM = matR * matT;

	m_matWorldTM = m_matLocalTM;
	if( m_pParentWorldTM)
	{
		m_matWorldTM *= *m_pParentWorldTM;
	}

	for each(auto p in m_vecChild)
	{
		p->Update();
	}
}

void cCubeNode::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	cCubePNT::Render();
	for each(auto p in m_vecChild)
	{
		p->Render();
	}
}
