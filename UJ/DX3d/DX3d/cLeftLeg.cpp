#include "stdafx.h"
#include "cLeftLeg.h"


void cLeftLeg::Setup()
{
	cCubeNode::Setup();
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.2f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, -0.1f, -0.3f, 0.0f);
	mat = matS * matT;

	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}

	m_vLocalPos.y = -0.3f;

	float legStartY = 1.0f;
	float legStartX = 0.0f;
	m_vecVertex[12].t = { legStartX, legStartY };
	m_vecVertex[13].t = { legStartX, legStartY - 3.0f / 8.0f, };
	m_vecVertex[14].t = { legStartX + 1.0f / 16.0f, legStartY - 3.0f / 8.0f };
	m_vecVertex[15].t = { legStartX, legStartY };
	m_vecVertex[16].t = m_vecVertex[14].t;
	m_vecVertex[17].t = { legStartX + 1.0f / 16.0f, legStartY };
	legStartX += 1.0f / 16.0f;

	m_vecVertex[6].t = { legStartX, legStartY };
	m_vecVertex[8].t = { legStartX, legStartY - 3.0f / 8.0f, };
	m_vecVertex[7].t = { legStartX + 1.0f / 16.0f, legStartY - 3.0f / 8.0f };
	m_vecVertex[9].t = { legStartX, legStartY };
	m_vecVertex[11].t = m_vecVertex[7].t;
	m_vecVertex[10].t = { legStartX + 1.0f / 16.0f, legStartY };
	legStartX += 1.0f / 16.0f;

	m_vecVertex[0].t = { legStartX, legStartY };
	m_vecVertex[1].t = { legStartX, legStartY - 3.0f / 8.0f, };
	m_vecVertex[2].t = { legStartX + 1.0f / 16.0f, legStartY - 3.0f / 8.0f };
	m_vecVertex[3].t = { legStartX, legStartY };
	m_vecVertex[4].t = m_vecVertex[2].t;
	m_vecVertex[5].t = { legStartX + 1.0f / 16.0f, legStartY };
	legStartX += 1.0f / 16.0f;

	m_vecVertex[18].t = { legStartX + 1.0f / 16.0f, legStartY };
	m_vecVertex[20].t = { legStartX , legStartY - 3.0f / 8.0f };
	m_vecVertex[19].t = { legStartX + 1.0f / 16.0f , legStartY - 3.0f / 8.0f };
	m_vecVertex[23].t = { legStartX, legStartY };
	m_vecVertex[22].t = { legStartX , legStartY - 3.0f / 8.0f };
	m_vecVertex[21].t = { legStartX + 1.0f / 16.0f , legStartY };

	legStartX = 1.0f / 16.0f;
	legStartY -= 3.0f / 8.0f;
	for (int i = 24; i < m_vecVertex.size(); i += 6)
	{
		m_vecVertex[i + 0].t = { legStartX, legStartY };
		m_vecVertex[i + 1].t = { legStartX, legStartY - 1.0f / 8.0f };
		m_vecVertex[i + 2].t = { legStartX + 1.0f / 16.0f, legStartY - 1.0f / 8.0f };
		m_vecVertex[i + 3].t = { legStartX, legStartY };
		m_vecVertex[i + 4].t = m_vecVertex[i + 2].t;
		m_vecVertex[i + 5].t = { legStartX + 1.0f / 16.0f, legStartY };
		legStartX += 1.0f / 16.0f;
	}
}

cLeftLeg::cLeftLeg()
{
}


cLeftLeg::~cLeftLeg()
{
}
