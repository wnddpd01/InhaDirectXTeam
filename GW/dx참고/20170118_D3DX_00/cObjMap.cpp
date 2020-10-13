#include "stdafx.h"
#include "cObjMap.h"


cObjMap::cObjMap()
{
}


cObjMap::~cObjMap()
{
}

void cObjMap::Load(char* szFilePath, D3DXMATRIXA16* pMat)
{
	vector<D3DXVECTOR3> vecV;

	FILE* fp = NULL;
	fopen_s(&fp, szFilePath, "r");

	while (true)
	{
		if (feof(fp))
			break;

		char szTemp[1024];

		fgets(szTemp, 1024, fp);

		if (szTemp[0] == 'v')
		{
			if (szTemp[1] == 't')
			{
			}
			else if (szTemp[1] == 'n')
			{
			}
			else // v
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'f')
		{
			int aIndex[3];
			sscanf(szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&aIndex[0], &aIndex[1], &aIndex[2]);

			for (int i = 0; i < 3; ++i)
			{
				D3DXVECTOR3 v;
				v = vecV[aIndex[i] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&v, &v, pMat);
				}
				m_vecVertex.push_back(v);
			}
		}
	}

	fclose(fp);
}

bool cObjMap::GetHeight(IN const float& x, OUT float& y, IN const float& z)
{
	D3DXVECTOR3 vRayOrigin(x, y+MAX_CLIME_SIZE, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);
	float u, v;

	for (int i = 0; i < m_vecVertex.size(); i += 3)
	{
		if (D3DXIntersectTri(&m_vecVertex[i], &m_vecVertex[i + 1], &m_vecVertex[i + 2],
			&vRayOrigin, &vRayDir, &u, &v, &m_fDistance))
		{
			//y =  y + MAX_CLIME_SIZE - m_fDistance;
			return true;
		}
	}

	return false;
}
