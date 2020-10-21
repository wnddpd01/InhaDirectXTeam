#include "stdafx.h"
#include "cBody.h"


cBody::cBody()
{
}


cBody::~cBody()
{
}

void cBody::Setup()
{
	cCubeNode::Setup();
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	mat = matS * matT;

	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}

	float bodyStartY = 1.0f;
	float bodyStartX = 4.0f / 16.0f;
	m_vecVertex[0].t = { bodyStartX, bodyStartY };
	m_vecVertex[1].t = { bodyStartX, bodyStartY - 3.0f / 8.0f,  };
	m_vecVertex[2].t = { bodyStartX + 1.0f / 16.0f, bodyStartY - 3.0f / 8.0f};
	m_vecVertex[3].t = { bodyStartX, bodyStartY };
	m_vecVertex[4].t = m_vecVertex[2].t;
	m_vecVertex[5].t = { bodyStartX + 1.0f / 16.0f, bodyStartY};
	bodyStartX += 1.0f / 16.0f;

	m_vecVertex[6].t = { bodyStartX, bodyStartY };
	m_vecVertex[8].t = { bodyStartX, bodyStartY - 3.0f / 8.0f, };
	m_vecVertex[7].t = { bodyStartX + 2.0f / 16.0f, bodyStartY - 3.0f / 8.0f };
	m_vecVertex[9].t = { bodyStartX, bodyStartY };
	m_vecVertex[11].t = m_vecVertex[7].t;
	m_vecVertex[10].t = { bodyStartX + 2.0f / 16.0f, bodyStartY };
	bodyStartX += 2.0f / 16.0f;

	m_vecVertex[12].t = { bodyStartX, bodyStartY };
	m_vecVertex[13].t = { bodyStartX, bodyStartY - 3.0f / 8.0f, };
	m_vecVertex[14].t = { bodyStartX + 1.0f / 16.0f, bodyStartY - 3.0f / 8.0f };
	m_vecVertex[15].t = { bodyStartX, bodyStartY };
	m_vecVertex[16].t = m_vecVertex[14].t;
	m_vecVertex[17].t = { bodyStartX + 1.0f / 16.0f, bodyStartY };
	bodyStartX += 1.0f / 16.0f;

	m_vecVertex[18].t = { bodyStartX, bodyStartY };
	m_vecVertex[19].t = { bodyStartX, bodyStartY - 3.0f / 8.0f, };
	m_vecVertex[20].t = { bodyStartX + 2.0f / 16.0f, bodyStartY - 3.0f / 8.0f };
	m_vecVertex[21].t = { bodyStartX, bodyStartY };
	m_vecVertex[22].t = m_vecVertex[20].t;
	m_vecVertex[23].t = { bodyStartX + 2.0f / 16.0f, bodyStartY };

	bodyStartX = 5.0f / 16.0f;
	bodyStartY -= 3.0f / 8.0f;
	for (int i = 24; i < m_vecVertex.size(); i += 6)
	{
		m_vecVertex[i + 0].t = { bodyStartX, bodyStartY };
		m_vecVertex[i + 1].t = { bodyStartX, bodyStartY - 1.0f / 8.0f };
		m_vecVertex[i + 2].t = { bodyStartX + 1.0f / 8.0f, bodyStartY - 1.0f / 8.0f };
		m_vecVertex[i + 3].t = { bodyStartX, bodyStartY };
		m_vecVertex[i + 4].t = m_vecVertex[i + 2].t;
		m_vecVertex[i + 5].t = { bodyStartX + 1.0f / 8.0f, bodyStartY };
		bodyStartX += 1.0f / 8.0f;
	}

	this->m_vLocalPos.y = 0.9f;
}
