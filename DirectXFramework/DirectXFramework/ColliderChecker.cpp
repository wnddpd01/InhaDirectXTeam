#include "stdafx.h"
#include "ColliderChecker.h"
#include "ColliderCube.h"
#include "ColliderSphere.h"


ColliderChecker::ColliderChecker()
{
}


ColliderChecker::~ColliderChecker()
{
}

void ColliderChecker::CheckCollider(map<string, Base3DObject*>& objects)
{
	for (map<string, Base3DObject*>::iterator iter = objects.begin(); iter != prev(objects.end(),1) ; ++iter)
	{
		for (map<string, Base3DObject*>::iterator iter2 = next(iter,1); iter2 != objects.end(); ++iter2)
		{
			if(CheckSphere((*iter).second, (*iter2).second))
			{
				string obj1Tag;
				string obj2Tag;
				
				if(CheckCube((*iter).second,(*iter2).second, obj1Tag, obj2Tag))
				{
					
				}
				else
				{
					
				}
			}
		}
	}
}

bool ColliderChecker::CheckCube(IN Base3DObject * object1, IN Base3DObject * object2, OUT string& obj1Tag, OUT string& obj2Tag)
{
	for (map<string, ColliderCube*>::iterator iter = object1->GetColliderCube().begin(); iter != object1->GetColliderCube().end(); ++iter)
	{
		for (map<string, ColliderCube*>::iterator iter2 = object2->GetColliderCube().begin(); iter2 != object2->GetColliderCube().end(); ++iter2)
		{
			CheckCubeByOBB((*iter).second,(*iter2).second);
		}
	}

	return true;
}

bool ColliderChecker::CheckSphere(Base3DObject* object1, Base3DObject* object2)
{
	float distance;
	D3DXVECTOR3 diff;

	object1->GetColliderSphere()->GetPosition() - object2->GetColliderSphere()->GetPosition();
	distance = D3DXVec3Length(&diff);

	if (distance <= object1->GetColliderSphere()->GetRadius() + object2->GetColliderSphere()->GetRadius())
	{
		return true;
	}
	return false;
}

bool ColliderChecker::CheckCubeByOBB(ColliderCube* obj1Cube, ColliderCube* obj2Cube)
{
	D3DXVECTOR3 vMax = obj1Cube->GetMax();
	D3DXVECTOR3 vMin = obj1Cube->GetMin();

	/*m_vOriCenterPos = (vMin + vMax) / 2.0f;

	D3DXVECTOR3 m_vOriAxisDir[3];
	
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

	 ¾Õ¸é
	BoxIndex.push_back(0);
	BoxIndex.push_back(1);
	BoxIndex.push_back(1);
	BoxIndex.push_back(2);
	BoxIndex.push_back(2);
	BoxIndex.push_back(3);
	BoxIndex.push_back(3);
	BoxIndex.push_back(0);

	 µÞ¸é
	BoxIndex.push_back(4);
	BoxIndex.push_back(5);
	BoxIndex.push_back(5);
	BoxIndex.push_back(6);
	BoxIndex.push_back(6);
	BoxIndex.push_back(7);
	BoxIndex.push_back(7);
	BoxIndex.push_back(4);

	 À­¸é
	BoxIndex.push_back(0);
	BoxIndex.push_back(4);
	BoxIndex.push_back(1);
	BoxIndex.push_back(5);
	 ¹Ø¸é
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
		&m_matWorldTM);*/
	
	float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r;
	const float cutOff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 D = obj1Cube->GetPosition() - obj2Cube->GetPosition();

	//for (int a = 0; a < 3; a++)
	//{
	//	for (int b = 0; b < 3; ++b)
	//	{
	//		cos[a][b] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &pOBB2->m_vAxisDir[b]);
	//		absCos[a][b] = abs(cos[a][b]);

	//		if (absCos[a][b] > cutOff)
	//			existsParallelPair = true;
	//	}
	//	dist[a] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &D);
	//	r = abs(dist[a]);

	//	r0 = pOBB1->m_fAxisHalfLen[a];
	//	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[a][0] +
	//		pOBB2->m_fAxisHalfLen[1] * absCos[a][1] +
	//		pOBB2->m_fAxisHalfLen[2] * absCos[a][2];

	//	if (r > r0 + r1)
	//		return false;

	//} // << : for a

	//for (int b = 0; b < 3; ++b)
	//{
	//	r = abs(D3DXVec3Dot(&pOBB2->m_vAxisDir[b], &D));
	//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[0][b] +
	//		pOBB1->m_fAxisHalfLen[1] * absCos[1][b] +
	//		pOBB1->m_fAxisHalfLen[2] * absCos[2][b];
	//	r1 = pOBB2->m_fAxisHalfLen[b];

	//	if (r > r0 + r1)
	//	{
	//		return false;
	//	}
	//}

	//if (existsParallelPair) return true;

	//{
	//	// : 0
	//	r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
	//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][0] + pOBB1->m_fAxisHalfLen[2] * absCos[0][0];
	//	r1 = pOBB1->m_fAxisHalfLen[1] * absCos[1][2] + pOBB1->m_fAxisHalfLen[2] * absCos[1][1];
	//	if (r > r0 + r1) return false;

	//	r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
	//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][1] + pOBB1->m_fAxisHalfLen[2] * absCos[0][1];
	//	r1 = pOBB1->m_fAxisHalfLen[0] * absCos[1][2] + pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
	//	if (r > r0 + r1) return false;

	//	r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
	//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[0][2];
	//	r1 = pOBB1->m_fAxisHalfLen[1] * absCos[1][1] + pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
	//	if (r > r0 + r1) return false;

	//	// : 1
	//	r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
	//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][0] + pOBB1->m_fAxisHalfLen[1] * absCos[0][0];
	//	r1 = pOBB1->m_fAxisHalfLen[1] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[2][1];
	//	if (r > r0 + r1) return false;

	//	r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
	//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][1] + pOBB1->m_fAxisHalfLen[1] * absCos[0][1];
	//	r1 = pOBB1->m_fAxisHalfLen[0] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[2][0];
	//	if (r > r0 + r1) return false;

	//	r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
	//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][2] + pOBB1->m_fAxisHalfLen[1] * absCos[0][2];
	//	r1 = pOBB1->m_fAxisHalfLen[1] * absCos[2][1] + pOBB1->m_fAxisHalfLen[1] * absCos[2][0];
	//	if (r > r0 + r1) return false;

	//	// : 2
	//	r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
	//	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][0] + pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
	//	r1 = pOBB1->m_fAxisHalfLen[1] * absCos[0][2] + pOBB1->m_fAxisHalfLen[2] * absCos[0][1];
	//	if (r > r0 + r1) return false;

	//	r = abs(dist[2] * cos[1][1] - dist[1] * cos[1][1]);
	//	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][1] + pOBB1->m_fAxisHalfLen[2] * absCos[1][1];
	//	r1 = pOBB1->m_fAxisHalfLen[0] * absCos[0][2] + pOBB1->m_fAxisHalfLen[2] * absCos[0][0];
	//	if (r > r0 + r1) return false;

	//	r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
	//	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[1][2];
	//	r1 = pOBB1->m_fAxisHalfLen[0] * absCos[0][1] + pOBB1->m_fAxisHalfLen[1] * absCos[0][0];
	//	if (r > r0 + r1) return false;
	//}
	return true;
}