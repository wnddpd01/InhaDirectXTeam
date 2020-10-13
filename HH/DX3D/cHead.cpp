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
	D3DXMATRIXA16	matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, 0.f, 0.f, 0.f);
	mat = matS * matT;
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}
	/*
	//앞
	m_vecVertex[0].t.x = 8.f / TEXTURESIZE; m_vecVertex[0].t.y = 16.f / TEXTURESIZE;
	m_vecVertex[1].t.x = 8.f / TEXTURESIZE; m_vecVertex[1].t.y = 8.f / TEXTURESIZE;
	m_vecVertex[2].t.x = 16.f / TEXTURESIZE;  m_vecVertex[2].t.y = 8.f / TEXTURESIZE;

	m_vecVertex[3].t.x = 8.f / TEXTURESIZE;   m_vecVertex[3].t.y = 16.f / TEXTURESIZE;
	m_vecVertex[4].t.x = 16.f / TEXTURESIZE;  m_vecVertex[4].t.y = 8.f / TEXTURESIZE;
	m_vecVertex[5].t.x = 16.f / TEXTURESIZE;  m_vecVertex[5].t.y = 16.f / TEXTURESIZE;
	//뒤
	m_vecVertex[6].t.x = 32.f / TEXTURESIZE;   m_vecVertex[6].t.y = 16.f / TEXTURESIZE;
	m_vecVertex[7].t.x = 24.f / TEXTURESIZE;  m_vecVertex[7].t.y = 8.f / TEXTURESIZE;
	m_vecVertex[8].t.x = 32.f / TEXTURESIZE;  m_vecVertex[8].t.y = 16.f / TEXTURESIZE;

	m_vecVertex[9].t.x = 32.f / TEXTURESIZE;   m_vecVertex[9].t.y = 16.f / TEXTURESIZE;
	m_vecVertex[10].t.x = 24.f / TEXTURESIZE;  m_vecVertex[10].t.y = 16.f / TEXTURESIZE;
	m_vecVertex[11].t.x = 24.f / TEXTURESIZE;  m_vecVertex[11].t.y = 8.f / TEXTURESIZE;
	//왼
	m_vecVertex[12].t.x = 0.f / TEXTURESIZE;   m_vecVertex[12].t.y = 16.f / TEXTURESIZE;
	m_vecVertex[13].t.x = 0.f / TEXTURESIZE;  m_vecVertex[13].t.y = 8.f / TEXTURESIZE;
	m_vecVertex[14].t.x = 8.f / TEXTURESIZE;  m_vecVertex[14].t.y = 8.f / TEXTURESIZE;

	m_vecVertex[15].t.x = 0.f / TEXTURESIZE;   m_vecVertex[15].t.y = 16.f / TEXTURESIZE;
	m_vecVertex[16].t.x = 8.f / TEXTURESIZE;  m_vecVertex[16].t.y = 8.f / TEXTURESIZE;
	m_vecVertex[17].t.x = 8.f / TEXTURESIZE;  m_vecVertex[17].t.y = 16.f / TEXTURESIZE;
	//오
	m_vecVertex[18].t.x = 16.f / TEXTURESIZE;  m_vecVertex[18].t.y = 16.f / TEXTURESIZE;
	m_vecVertex[19].t.x = 16.f / TEXTURESIZE;  m_vecVertex[19].t.y = 8.f / TEXTURESIZE;
	m_vecVertex[20].t.x = 24.f / TEXTURESIZE;  m_vecVertex[20].t.y = 8.f / TEXTURESIZE;

	m_vecVertex[21].t.x = 16.f / TEXTURESIZE;  m_vecVertex[21].t.y = 16.f / TEXTURESIZE;
	m_vecVertex[22].t.x = 24.f / TEXTURESIZE;  m_vecVertex[22].t.y = 8.f / TEXTURESIZE;
	m_vecVertex[23].t.x = 24.f / TEXTURESIZE;  m_vecVertex[23].t.y = 16.f / TEXTURESIZE;

	//위
	m_vecVertex[24].t.x = 8.f / TEXTURESIZE;  m_vecVertex[24].t.y = 8.f / TEXTURESIZE;
	m_vecVertex[25].t.x = 8.f / TEXTURESIZE;  m_vecVertex[25].t.y = 0.f / TEXTURESIZE;
	m_vecVertex[26].t.x = 16.f / TEXTURESIZE;  m_vecVertex[26].t.y = 0.f / TEXTURESIZE;

	m_vecVertex[27].t.x = 8.f / TEXTURESIZE;  m_vecVertex[27].t.y = 8.f / TEXTURESIZE;
	m_vecVertex[28].t.x = 16.f / TEXTURESIZE;  m_vecVertex[28].t.y = 0.f / TEXTURESIZE;
	m_vecVertex[29].t.x = 16.f / TEXTURESIZE;  m_vecVertex[29].t.y = 8.f / TEXTURESIZE;
	//아래
	m_vecVertex[30].t.x = 16.f / TEXTURESIZE;  m_vecVertex[30].t.y = 0.f / TEXTURESIZE;
	m_vecVertex[31].t.x = 16.f / TEXTURESIZE;  m_vecVertex[31].t.y = 8.f / TEXTURESIZE;
	m_vecVertex[32].t.x = 24.f / TEXTURESIZE;  m_vecVertex[32].t.y = 8.f / TEXTURESIZE;

	m_vecVertex[33].t.x = 16.f / TEXTURESIZE;  m_vecVertex[33].t.y = 0.f / TEXTURESIZE;
	m_vecVertex[34].t.x = 24.f / TEXTURESIZE;  m_vecVertex[34].t.y = 8.f / TEXTURESIZE;
	m_vecVertex[35].t.x = 24.f / TEXTURESIZE;  m_vecVertex[35].t.y = 0.f / TEXTURESIZE;


	
	*/
	m_vLocalPos.y = 0.5f;

	SetMineCraftTexture(
		0.f / TEXTURESIZE,
		0.f / TEXTURESIZE,
		8.f / TEXTURESIZE,
		8.f / TEXTURESIZE,
		8.f / TEXTURESIZE
	);
	
}
