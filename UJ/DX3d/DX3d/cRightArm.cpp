#include "stdafx.h"
#include "cRightArm.h"


void cRightArm::Setup()
{
	cCubeNode::Setup();
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.2f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, 0.3f, -0.3f, 0);
	mat = matS * matT;

	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}

	m_vLocalPos.y = 0.3f;

	float armStartY = 1.0f;
	float armStartX = 10.0f / 16.0f;
	m_vecVertex[0].t = { armStartX, armStartY };
	m_vecVertex[1].t = { armStartX, armStartY - 3.0f / 8.0f, };
	m_vecVertex[2].t = { armStartX + 1.0f / 16.0f, armStartY - 3.0f / 8.0f };
	m_vecVertex[3].t = { armStartX, armStartY };
	m_vecVertex[4].t = m_vecVertex[2].t;
	m_vecVertex[5].t = { armStartX + 1.0f / 16.0f, armStartY };
	armStartX += 1.0f / 16.0f;


	m_vecVertex[6].t = { armStartX + 1.0f / 16.0f,  armStartY };
	m_vecVertex[7].t = { armStartX , armStartY - 3.0f / 8.0f };
	m_vecVertex[8].t = { armStartX + 1.0f / 16.0f, armStartY - 3.0f / 8.0f };
	m_vecVertex[9].t = { armStartX + 1.0f / 16.0f, armStartY };
	m_vecVertex[10].t = { armStartX, armStartY };
	m_vecVertex[11].t = { armStartX, armStartY - 3.0f / 8.0f, };
	armStartX += 1.0f / 16.0f;

	m_vecVertex[12].t = { armStartX, armStartY };
	m_vecVertex[13].t = { armStartX, armStartY - 3.0f / 8.0f, };
	m_vecVertex[14].t = { armStartX + 1.0f / 16.0f, armStartY - 3.0f / 8.0f };
	m_vecVertex[15].t = { armStartX, armStartY };
	m_vecVertex[16].t = m_vecVertex[14].t;
	m_vecVertex[17].t = { armStartX + 1.0f / 16.0f, armStartY };
	armStartX += 1.0f / 16.0f;

	m_vecVertex[18].t = { armStartX, armStartY };
	m_vecVertex[19].t = { armStartX, armStartY - 3.0f / 8.0f, };
	m_vecVertex[20].t = { armStartX + 1.0f / 16.0f, armStartY - 3.0f / 8.0f };
	m_vecVertex[21].t = { armStartX, armStartY };
	m_vecVertex[22].t = m_vecVertex[20].t;
	m_vecVertex[23].t = { armStartX + 1.0f / 16.0f, armStartY };

	armStartX = 11.0f / 16.0f;
	armStartY -= 3.0f / 8.0f;
	for (int i = 24; i < m_vecVertex.size(); i += 6)
	{
		m_vecVertex[i + 0].t = { armStartX, armStartY };
		m_vecVertex[i + 1].t = { armStartX, armStartY - 1.0f / 8.0f };
		m_vecVertex[i + 2].t = { armStartX + 1.0f / 16.0f, armStartY - 1.0f / 8.0f };
		m_vecVertex[i + 3].t = { armStartX, armStartY };
		m_vecVertex[i + 4].t = m_vecVertex[i + 2].t;
		m_vecVertex[i + 5].t = { armStartX + 1.0f / 16.0f, armStartY };
		armStartX += 1.0f / 16.0f;
	}
}

cRightArm::cRightArm()
{
}


cRightArm::~cRightArm()
{
}
