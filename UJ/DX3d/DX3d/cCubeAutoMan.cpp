#include "stdafx.h"
#include "cCubeAutoMan.h"


cCubeAutoMan::cCubeAutoMan()
{
}


cCubeAutoMan::~cCubeAutoMan()
{
}

void cCubeAutoMan::Setup(vector<ST_PC_VERTEX>& vertices)
{
	currentVertex = 0;
	vertices_ = vertices;
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVECTOR3 moveDir = vertices_[1].p - vertices_[0].p;
	m_fRotY = acosf(D3DXVec3Dot(&m_vDirection, &moveDir) / (D3DXVec3Length(&m_vDirection) * D3DXVec3Length(&moveDir)));
	//D3DXMATRIXA16 rotY;
	//D3DXMatrixRotationY(&rotY, m_fRotY);
	//D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &rotY);
	cCubeMan::Setup();
}

void cCubeAutoMan::Update()
{
	if(D3DXVec3Length(&(m_vPosition - vertices_[currentVertex].p)) < 0.01f)
	{
		size_t prevVertex = currentVertex;
		++currentVertex;
		if(currentVertex == vertices_.size())
		{
			currentVertex = 0;
		}
		m_vDirection = m_vPosition;
		D3DXMATRIXA16 rotY;

		float a = D3DXVec3Length(&vertices_[prevVertex].p);
		float b = D3DXVec3Dot(&vertices_[prevVertex].p, &vertices_[currentVertex].p) / (D3DXVec3Length(&vertices_[prevVertex].p) * D3DXVec3Length(&vertices_[currentVertex].p));
		
		m_fRotY += acosf(b);
	}
	cCubeMan::Update();
	cCubeMan::Command('W');
}
