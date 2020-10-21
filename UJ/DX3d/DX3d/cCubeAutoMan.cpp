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
	//D3DXMATRIXA16 rotY;
	//D3DXMatrixRotationY(&rotY, m_fRotY);
	//D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &rotY);
	cCubeMan::Setup();
}

void cCubeAutoMan::Update()
{
	if(D3DXVec3Length(&(m_vPosition - vertices_[currentVertex].p)) < 0.1f)
	{
		size_t prevVertex = currentVertex;
		m_vPosition = vertices_[currentVertex].p;
		++currentVertex;
		if(currentVertex == vertices_.size())
		{
			currentVertex = 0;
		}
		m_vDirection = D3DXVECTOR3(0, 0, 1);

		D3DXVECTOR3 moveDir = vertices_[currentVertex].p - m_vPosition;
		
		/*float a = acosf(D3DXVec3Dot(&m_vDirection, &m_vPosition) / (D3DXVec3Length(&m_vDirection) * D3DXVec3Length(&m_vPosition)));
		float b = acosf(D3DXVec3Dot(&m_vPosition, &moveDir) / (D3DXVec3Length(&m_vPosition) * D3DXVec3Length(&moveDir)));
		a = m_vPosition.x > 0 ? a : 2 * D3DX_PI - a;
		m_fRotY = a + b;*/

		D3DXMatrixLookAtLH(&m_matR, &D3DXVECTOR3(0, 0, 0), &moveDir, &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixTranspose(&m_matR, &m_matR);
	}
	cCubeMan::Update();
	cCubeMan::Command('W');
}
