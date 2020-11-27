#include "stdafx.h"
#include "ColliderCube.h"


ColliderCube::ColliderCube()
	: mCubeWidth(1.0f)
	, mCubeHeight(1.0f)
	, mCubeDepth(1.0f)
{
	
}

ColliderCube::~ColliderCube()
{
}

void ColliderCube::Setup()
{
	D3DXVECTOR3 mMax = D3DXVECTOR3 (mCubeWidth / 2, mCubeHeight / 2, mCubeDepth / 2);
	D3DXVECTOR3 mMin = D3DXVECTOR3(-mCubeWidth / 2, -mCubeHeight / 2, -mCubeDepth / 2);

	m_vOriCenterPos = (mMin + mMax) / 2.0f;

	m_vOriAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(mMax.x - mMin.x);
	m_fAxisLen[1] = fabs(mMax.y - mMin.y);
	m_fAxisLen[2] = fabs(mMax.z - mMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;

	vector<D3DXVECTOR3> m_BoxVertex;

	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], -m_fAxisHalfLen[1], -m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], m_fAxisHalfLen[1], -m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], m_fAxisHalfLen[1], -m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], -m_fAxisHalfLen[1], -m_fAxisHalfLen[2]));

	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], -m_fAxisHalfLen[1], m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], m_fAxisHalfLen[1], m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], m_fAxisHalfLen[1], m_fAxisHalfLen[2]));
	m_BoxVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], -m_fAxisHalfLen[1], m_fAxisHalfLen[2]));

	vector<DWORD> BoxIndex;

	// ¾Õ¸é
	BoxIndex.push_back(0);
	BoxIndex.push_back(1);
	BoxIndex.push_back(1);
	BoxIndex.push_back(2);
	BoxIndex.push_back(2);
	BoxIndex.push_back(3);
	BoxIndex.push_back(3);
	BoxIndex.push_back(0);

	// µÞ¸é
	BoxIndex.push_back(4);
	BoxIndex.push_back(5);
	BoxIndex.push_back(5);
	BoxIndex.push_back(6);
	BoxIndex.push_back(6);
	BoxIndex.push_back(7);
	BoxIndex.push_back(7);
	BoxIndex.push_back(4);

	// À­¸é
	BoxIndex.push_back(0);
	BoxIndex.push_back(4);
	BoxIndex.push_back(1);
	BoxIndex.push_back(5);
	// ¹Ø¸é
	BoxIndex.push_back(2);
	BoxIndex.push_back(6);
	BoxIndex.push_back(3);
	BoxIndex.push_back(7);

	m_BoxDrawVertex.resize(BoxIndex.size());

	for (unsigned int i = 0; i < BoxIndex.size(); ++i)
	{
		m_BoxDrawVertex[i] = m_BoxVertex[BoxIndex[i]];
	}

}

void ColliderCube::Update()
{
	D3DXMATRIXA16 matR;
	D3DXMATRIXA16 matT;
	
	D3DXMatrixTranslation(&matT, (*mPosition).x, (*mPosition).y, (*mPosition).z);
	D3DXMatrixRotationQuaternion(&matR, mRot);

	D3DXMATRIXA16 m_matWorldTM = matR * matT;

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


void ColliderCube::SetCubeCollider(float height, float width, float depth)
{
	mCubeWidth = width;
	mCubeHeight = height;
	mCubeDepth = depth;
	Setup();
}

bool ColliderCube::IsCollision(ColliderCube * obj1Cube, ColliderCube * obj2Cube)
{
	float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r;
	const float cutOff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 D = obj2Cube->m_vCenterPos - obj1Cube->m_vCenterPos;


	float obj1AxisHalfLen[3];
	float obj2AxisHalfLen[3];

	obj1AxisHalfLen[0] = obj1Cube->m_fAxisHalfLen[0];
	obj1AxisHalfLen[1] = obj1Cube->m_fAxisHalfLen[1];
	obj1AxisHalfLen[2] = obj1Cube->m_fAxisHalfLen[2];
	
	obj2AxisHalfLen[0] = obj2Cube->m_fAxisHalfLen[0];
	obj2AxisHalfLen[1] = obj2Cube->m_fAxisHalfLen[1];
	obj2AxisHalfLen[2] = obj2Cube->m_fAxisHalfLen[2];
	
	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; ++b)
		{
			cos[a][b] = D3DXVec3Dot(&obj1Cube->m_vAxisDir[a], &obj2Cube->m_vAxisDir[b]);
			absCos[a][b] = abs(cos[a][b]);

			if (absCos[a][b] > cutOff)
				existsParallelPair = true;
		}
		dist[a] = D3DXVec3Dot(&obj1Cube->m_vAxisDir[a], &D);
		r = abs(dist[a]);

		r0 = obj1AxisHalfLen[a];
		r1 = obj2AxisHalfLen[0] * absCos[a][0] +
			obj2AxisHalfLen[1] * absCos[a][1] +
			obj2AxisHalfLen[2] * absCos[a][2];

		if (r > r0 + r1)
			return false;

	} // << : for a

	for (int b = 0; b < 3; ++b)
	{
		r = abs(D3DXVec3Dot(&obj2Cube->m_vAxisDir[b], &D));
		r0 = obj1AxisHalfLen[0] * absCos[0][b] +
			obj1AxisHalfLen[1] * absCos[1][b] +
			obj1AxisHalfLen[2] * absCos[2][b];
		r1 = obj2AxisHalfLen[b];

		if (r > r0 + r1)
		{
			return false;
		}
	}

	if (existsParallelPair) return true;

	{
		// : 0
		r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
		r0 = obj1AxisHalfLen[0] * absCos[2][0] + obj1AxisHalfLen[2] * absCos[0][0];
		r1 = obj2AxisHalfLen[1] * absCos[1][2] + obj2AxisHalfLen[2] * absCos[1][1];
		if (r > r0 + r1) return false;

		r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
		r0 = obj1AxisHalfLen[0] * absCos[2][1] + obj1AxisHalfLen[2] * absCos[0][1];
		r1 = obj2AxisHalfLen[0] * absCos[1][2] + obj2AxisHalfLen[2] * absCos[1][0];
		if (r > r0 + r1) return false;

		r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
		r0 = obj1AxisHalfLen[0] * absCos[2][2] + obj1AxisHalfLen[2] * absCos[0][2];
		r1 = obj2AxisHalfLen[0] * absCos[1][1] + obj2AxisHalfLen[1] * absCos[1][0];
		if (r > r0 + r1) return false;

		// : 1
		r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
		r0 = obj1AxisHalfLen[0] * absCos[1][1] + obj1AxisHalfLen[1] * absCos[0][1];
		r1 = obj2AxisHalfLen[1] * absCos[2][2] + obj2AxisHalfLen[2] * absCos[2][0];
		if (r > r0 + r1) return false;

		r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
		r0 = obj1AxisHalfLen[0] * absCos[1][1] + obj1AxisHalfLen[1] * absCos[0][1];
		r1 = obj2AxisHalfLen[0] * absCos[2][2] + obj2AxisHalfLen[2] * absCos[2][0];
		if (r > r0 + r1) return false;

		r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
		r0 = obj1AxisHalfLen[0] * absCos[1][2] + obj1AxisHalfLen[1] * absCos[0][2];
		r1 = obj2AxisHalfLen[1] * absCos[2][1] + obj2AxisHalfLen[1] * absCos[2][0];
		if (r > r0 + r1) return false;

		// : 2
		r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
		r0 = obj1AxisHalfLen[1] * absCos[2][0] + obj1AxisHalfLen[2] * absCos[1][0];
		r1 = obj2AxisHalfLen[1] * absCos[0][2] + obj2AxisHalfLen[2] * absCos[0][1];
		if (r > r0 + r1) return false;

		r = abs(dist[2] * cos[1][1] - dist[1] * cos[1][1]);
		r0 = obj1AxisHalfLen[1] * absCos[2][1] + obj1AxisHalfLen[2] * absCos[1][1];
		r1 = obj2AxisHalfLen[0] * absCos[0][2] + obj2AxisHalfLen[2] * absCos[0][0];
		if (r > r0 + r1) return false;

		r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
		r0 = obj1AxisHalfLen[1] * absCos[2][2] + obj1AxisHalfLen[2] * absCos[1][2];
		r1 = obj2AxisHalfLen[0] * absCos[0][1] + obj2AxisHalfLen[1] * absCos[0][0];
		if (r > r0 + r1) return false;
	}
	return true;
}

void ColliderCube::Render()
{	
	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
	gD3Device->SetTexture(0, nullptr);
	gD3Device->SetFVF(D3DFVF_XYZ);
	gD3Device->DrawPrimitiveUP(D3DPT_LINELIST, m_BoxDrawVertex.size() / 2, &m_BoxDrawVertex[0], sizeof(D3DXVECTOR3));
}

