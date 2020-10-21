#include "stdafx.h"
#include "cHead.h"


cHead::cHead()
{
}


cHead::~cHead()
{
}

void cHead::Setup()
{
	cCubeNode::Setup();
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, 0, 0 , 0.0f);
	mat = matS * matT;

	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}

	m_vLocalPos.y = 0.5f;

	float headStartX = 0;
	float headStartY = 4.0f / 8.0f;

	for (int i = 0; i < 6; i+=6)
	{
		m_vecVertex[i].t = { headStartX, headStartY };
		m_vecVertex[i + 1].t = { headStartX, headStartY - 2.0f / 8.0f };
		m_vecVertex[i + 2].t = { headStartX + 1.0f / 8.0f, headStartY - 2.0f / 8.0f };

		m_vecVertex[i + 3].t = { headStartX, headStartY };
		m_vecVertex[i + 4].t = { headStartX + 1.0f / 8.0f, headStartY - 2.0f / 8.0f };
		m_vecVertex[i + 5].t = { headStartX + 1.0f / 8.0f, headStartY };

		headStartX += 0.125f;
	}
	m_vecVertex[6].t = { headStartX, headStartY };
	m_vecVertex[7].t = { headStartX + 1.0f / 8.0f, headStartY - 2.0f / 8.0f };
	m_vecVertex[8].t = { headStartX, headStartY - 2.0f / 8.0f };
	m_vecVertex[9].t = { headStartX, headStartY };
	m_vecVertex[10].t = { headStartX + 1.0f / 8.0f, headStartY };
	m_vecVertex[11].t = m_vecVertex[7].t;
	headStartX += 0.125f;
	for (int i = 12; i < 24; i += 6)
	{
		m_vecVertex[i].t = { headStartX, headStartY };
		m_vecVertex[i + 1].t = { headStartX, headStartY - 2.0f / 8.0f };
		m_vecVertex[i + 2].t = { headStartX + 1.0f / 8.0f, headStartY - 2.0f / 8.0f };

		m_vecVertex[i + 3].t = { headStartX, headStartY };
		m_vecVertex[i + 4].t = { headStartX + 1.0f / 8.0f, headStartY - 2.0f / 8.0f };
		m_vecVertex[i + 5].t = { headStartX + 1.0f / 8.0f, headStartY };

		headStartX += 0.125f;
	}
	headStartX = 1.0f / 8.0f;
	headStartY -= 2.0f / 8.0f;
	for (int i = 24; i < m_vecVertex.size(); i+=6)
	{
		m_vecVertex[i + 0].t = { headStartX, headStartY };
		m_vecVertex[i + 1].t = { headStartX, headStartY - 2.0f / 8.0f };
		m_vecVertex[i + 2].t = { headStartX + 1.0f / 8.0f, headStartY - 2.0f / 8.0f };
		m_vecVertex[i + 3].t = { headStartX, headStartY };
		m_vecVertex[i + 4].t = m_vecVertex[i + 2].t;
		m_vecVertex[i + 5].t = { headStartX + 1.0f / 8.0f, headStartY };
		headStartX += 1.0f / 8.0f;
	}
	
}
