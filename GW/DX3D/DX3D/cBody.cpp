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
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	mat = matS * matT;

	//:front
	m_vecVertex[6].t = D3DXVECTOR2(0.30f,  0.5f);
	m_vecVertex[7].t = D3DXVECTOR2(0.44f,  0.3f);
	m_vecVertex[8].t = D3DXVECTOR2(0.30f,  0.3f);
	m_vecVertex[9].t = D3DXVECTOR2(0.30f,  0.5f);
	m_vecVertex[10].t = D3DXVECTOR2(0.44f, 0.5f);
	m_vecVertex[11].t = D3DXVECTOR2(0.44f, 0.3f);


	//:back
	m_vecVertex[0].t = D3DXVECTOR2(0.48f, 0.5f);
	m_vecVertex[1].t = D3DXVECTOR2(0.48f, 0.3f);
	m_vecVertex[2].t = D3DXVECTOR2(0.63f, 0.3f);
	m_vecVertex[3].t = D3DXVECTOR2(0.48f, 0.5f);
	m_vecVertex[4].t = D3DXVECTOR2(0.63f, 0.5f);
	m_vecVertex[5].t = D3DXVECTOR2(0.63f, 0.3f);


	//:left
	m_vecVertex[12].t = D3DXVECTOR2(0.27f, 0.5f);
	m_vecVertex[13].t = D3DXVECTOR2(0.27f, 0.3f);
	m_vecVertex[14].t = D3DXVECTOR2(0.42f, 0.3f);
	m_vecVertex[15].t = D3DXVECTOR2(0.27f, 0.5f);
	m_vecVertex[16].t = D3DXVECTOR2(0.42f, 0.5f);
	m_vecVertex[17].t = D3DXVECTOR2(0.42f, 0.3f);

	//:right

	m_vecVertex[18].t = D3DXVECTOR2(0, 0.5f);
	m_vecVertex[19].t = D3DXVECTOR2(0, 0.3f);
	m_vecVertex[20].t = D3DXVECTOR2(0.15f, 0.3f);
	m_vecVertex[21].t = D3DXVECTOR2(0.27f, 0.5f);
	m_vecVertex[22].t = D3DXVECTOR2(0.42f, 0.5f);
	m_vecVertex[23].t = D3DXVECTOR2(0.42f, 0.3f);



	//:top
	m_vecVertex[24].t = D3DXVECTOR2(0.13f, 0.5f);
	m_vecVertex[26].t = D3DXVECTOR2(0.26f, 0.3f);
	m_vecVertex[25].t = D3DXVECTOR2(0.13f, 0.3f);
	m_vecVertex[27].t = D3DXVECTOR2(0.13f, 0.5f);
	m_vecVertex[29].t = D3DXVECTOR2(0.26f, 0.5f);
	m_vecVertex[28].t = D3DXVECTOR2(0.26f, 0.3f);

	
	for(size_t i = 0 ; i<m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}
}