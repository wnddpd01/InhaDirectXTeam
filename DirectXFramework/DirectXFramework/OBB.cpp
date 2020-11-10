#include "stdafx.h"
#include "OBB.h"
#include "cSkinnedMesh.h"

OBB::OBB()
{
}

OBB::~OBB()
{
}

void OBB::Setup(cSkinnedMesh* pSkinnedMesh)
{
	D3DXVECTOR3 vMin = pSkinnedMesh->GetMin();
	D3DXVECTOR3 vMax = pSkinnedMesh->GetMax();

	m_vOriCenterPos = (vMin + vMax) / 2.0f;

	m_vOriAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;

	vector<D3DXVECTOR3> m_BoxVertex;

	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], 0, -m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], m_fAxisLen[1], -m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], m_fAxisLen[1], -m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], 0, -m_fAxisHalfLen[2]));

	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], 0, m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], m_fAxisLen[1], m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], m_fAxisLen[1], m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], 0, m_fAxisHalfLen[2]));

	vector<DWORD> BoxIndex;

	// �ո�
	BoxIndex.push_back(0);
	BoxIndex.push_back(1);
	BoxIndex.push_back(1);
	BoxIndex.push_back(2);
	BoxIndex.push_back(2);
	BoxIndex.push_back(3);
	BoxIndex.push_back(3);
	BoxIndex.push_back(0);

	// �޸�
	BoxIndex.push_back(4);
	BoxIndex.push_back(5);
	BoxIndex.push_back(5);
	BoxIndex.push_back(6);
	BoxIndex.push_back(6);
	BoxIndex.push_back(7);
	BoxIndex.push_back(7);
	BoxIndex.push_back(4);

	// ����
	BoxIndex.push_back(0);
	BoxIndex.push_back(4);
	BoxIndex.push_back(1);
	BoxIndex.push_back(5);
	// �ظ�
	BoxIndex.push_back(2);
	BoxIndex.push_back(6);
	BoxIndex.push_back(3);
	BoxIndex.push_back(7);

	m_BoxDrawVertex.resize(BoxIndex.size());

	for (unsigned int i = 0; i < BoxIndex.size(); ++i)
	{
		m_BoxDrawVertex[i].p = m_BoxVertex[BoxIndex[i]];
	}

	D3DXMatrixIdentity(&m_matWorldTM);
}

void OBB::Setup(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax)
{
	m_vOriCenterPos = (vMin + vMax) / 2.0f;

	m_vOriAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;

	vector<D3DXVECTOR3> m_BoxVertex;

	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], 0, -m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], m_fAxisLen[1], -m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], m_fAxisLen[1], -m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], 0, -m_fAxisHalfLen[2]));

	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], 0, m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], m_fAxisLen[1], m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], m_fAxisLen[1], m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], 0, m_fAxisHalfLen[2]));

	vector<DWORD> BoxIndex;

	// �ո�
	BoxIndex.push_back(0);
	BoxIndex.push_back(1);
	BoxIndex.push_back(1);
	BoxIndex.push_back(2);
	BoxIndex.push_back(2);
	BoxIndex.push_back(3);
	BoxIndex.push_back(3);
	BoxIndex.push_back(0);

	// �޸�
	BoxIndex.push_back(4);
	BoxIndex.push_back(5);
	BoxIndex.push_back(5);
	BoxIndex.push_back(6);
	BoxIndex.push_back(6);
	BoxIndex.push_back(7);
	BoxIndex.push_back(7);
	BoxIndex.push_back(4);

	// ����
	BoxIndex.push_back(0);
	BoxIndex.push_back(4);
	BoxIndex.push_back(1);
	BoxIndex.push_back(5);
	// �ظ�
	BoxIndex.push_back(2);
	BoxIndex.push_back(6);
	BoxIndex.push_back(3);
	BoxIndex.push_back(7);

	m_BoxDrawVertex.resize(BoxIndex.size());

	for (unsigned int i = 0; i < BoxIndex.size(); ++i)
	{
		m_BoxDrawVertex[i].p = m_BoxVertex[BoxIndex[i]];
	}

	D3DXMatrixIdentity(&m_matWorldTM);
}

void OBB::Update(D3DXMATRIXA16* pmatWorld)
{
	if (pmatWorld)
		m_matWorldTM = *pmatWorld;

	for (int i = 0; i < 3; ++i)
	{
		D3DXVec3TransformNormal(
			&m_vAxisDir[i],
			&m_vOriAxisDir[i],
			&m_matWorldTM
		);
	}

	D3DXVec3TransformCoord(
		&m_vCenterPos,
		&m_vOriCenterPos,
		&m_matWorldTM);
}

bool OBB::IsCollision(OBB* pOBB1, OBB* pOBB2)
{
	float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r;
	const float cutOff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 D = pOBB2->m_vCenterPos - pOBB1->m_vCenterPos;

	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; ++b)
		{
			cos[a][b] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &pOBB2->m_vAxisDir[b]);
			absCos[a][b] = abs(cos[a][b]);

			if (absCos[a][b] > cutOff)
				existsParallelPair = true;
		}
		dist[a] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &D);
		r = abs(dist[a]);

		r0 = pOBB1->m_fAxisHalfLen[a];
		r1 = pOBB2->m_fAxisHalfLen[0] * absCos[a][0] +
			pOBB2->m_fAxisHalfLen[1] * absCos[a][1] +
			pOBB2->m_fAxisHalfLen[2] * absCos[a][2];

		if (r > r0 + r1)
			return false;

	} // << : for a

	for (int b = 0; b < 3; ++b)
	{
		r = abs(D3DXVec3Dot(&pOBB2->m_vAxisDir[b], &D));
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[0][b] +
			pOBB1->m_fAxisHalfLen[1] * absCos[1][b] +
			pOBB1->m_fAxisHalfLen[2] * absCos[2][b];
		r1 = pOBB2->m_fAxisHalfLen[b];

		if (r > r0 + r1)
		{
			return false;
		}
	}

	if (existsParallelPair) return true;
	
	{
		// : 0
		r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][0] + pOBB1->m_fAxisHalfLen[2] * absCos[0][0];
		r1 = pOBB1->m_fAxisHalfLen[1] * absCos[1][2] + pOBB1->m_fAxisHalfLen[2] * absCos[1][1];
		if (r > r0 + r1) return false;

		r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][1] + pOBB1->m_fAxisHalfLen[2] * absCos[0][1];
		r1 = pOBB1->m_fAxisHalfLen[0] * absCos[1][2] + pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
		if (r > r0 + r1) return false;

		r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[0][2];
		r1 = pOBB1->m_fAxisHalfLen[1] * absCos[1][1] + pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
		if (r > r0 + r1) return false;

		// : 1
		r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][0] + pOBB1->m_fAxisHalfLen[1] * absCos[0][0];
		r1 = pOBB1->m_fAxisHalfLen[1] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[2][1];
		if (r > r0 + r1) return false;

		r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][1] + pOBB1->m_fAxisHalfLen[1] * absCos[0][1];
		r1 = pOBB1->m_fAxisHalfLen[0] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[2][0];
		if (r > r0 + r1) return false;

		r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][2] + pOBB1->m_fAxisHalfLen[1] * absCos[0][2];
		r1 = pOBB1->m_fAxisHalfLen[1] * absCos[2][1] + pOBB1->m_fAxisHalfLen[1] * absCos[2][0];
		if (r > r0 + r1) return false;

		// : 2
		r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][0] + pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
		r1 = pOBB1->m_fAxisHalfLen[1] * absCos[0][2] + pOBB1->m_fAxisHalfLen[2] * absCos[0][1];
		if (r > r0 + r1) return false;

		r = abs(dist[2] * cos[1][1] - dist[1] * cos[1][1]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][1] + pOBB1->m_fAxisHalfLen[2] * absCos[1][1];
		r1 = pOBB1->m_fAxisHalfLen[0] * absCos[0][2] + pOBB1->m_fAxisHalfLen[2] * absCos[0][0];
		if (r > r0 + r1) return false;

		r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[1][2];
		r1 = pOBB1->m_fAxisHalfLen[0] * absCos[0][1] + pOBB1->m_fAxisHalfLen[1] * absCos[0][0];
		if (r > r0 + r1) return false;
	}
	return true;
}

void OBB::OBBBOX_Render(D3DCOLOR c)
{
	for (unsigned int i = 0; i < m_BoxDrawVertex.size(); ++i)
	{
		m_BoxDrawVertex[i].c = c;
	}

	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	gD3Device->SetTexture(0, nullptr);
	gD3Device->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	gD3Device->SetFVF(ST_PC_VERTEX::FVF);
	gD3Device->DrawPrimitiveUP(D3DPT_LINELIST, m_BoxDrawVertex.size() / 2, &m_BoxDrawVertex[0], sizeof(ST_PC_VERTEX));
}
