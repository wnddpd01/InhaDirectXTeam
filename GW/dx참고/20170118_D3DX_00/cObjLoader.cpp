#include "stdafx.h"
#include "cObjLoader.h"
#include "cGeometry.h"
#include "cMtrlTex.h"


cObjLoader::cObjLoader()
{
}


cObjLoader::~cObjLoader()
{
}

void cObjLoader::Load(IN char* szFilePath, IN D3DXMATRIXA16* pMat, OUT vector<cGeometry*>& vecGeometry)
{
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<D3DXVECTOR3> vecVN;
	vector<ST_PNT_VERTEX> vecVertex;

	string sMtlName;

	FILE* fp = NULL;
	fopen_s(&fp, szFilePath, "r");

	while (true)
	{
		if (feof(fp))
			break;

		char szTemp[1024];

		fgets(szTemp, 1024, fp);

		if (szTemp[0] == 'm')
		{
			char szMtlPath[1024];
			char szFullPath[1024];

			sscanf(szTemp, "%*s ./%s", szMtlPath);
			sprintf(szFullPath, "obj/%s", szMtlPath);
			LoadMtlLib(szFullPath);
		}
		else if (szTemp[0] == 'g')
		{
			if (vecVertex.empty())
				continue;

			cGeometry* pGeo = new cGeometry;
			g_pAutoReleasePool->AddObject(pGeo);
			pGeo->SetVertex(vecVertex);
			pGeo->SetMtrlTex(m_mapMtrlTex[sMtlName]);
			vecGeometry.push_back(pGeo);
			vecVertex.clear();
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == 't')
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f", &x, &y);
				vecVT.push_back(D3DXVECTOR2(x, y));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
			else // v
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf(szTemp, "%*s %s", szMtlName);
			sMtlName = szMtlName;
		}
		else if (szTemp[0] == 'f')
		{
			int aIndex[3][3];
			sscanf(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX pnt;
				pnt.p = vecV[aIndex[i][0] - 1];
				pnt.t = vecVT[aIndex[i][1] - 1];
				pnt.n = vecVN[aIndex[i][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
				}
				vecVertex.push_back(pnt);
			}
		}
	}

	for each (auto p in m_mapMtrlTex)
	{
		SAFE_RELEASE(p.second);
	}

	m_mapMtrlTex.clear();

	fclose(fp);
}

LPD3DXMESH cObjLoader::Load(IN char * szFilePath, IN D3DXMATRIXA16 * pMat)
{
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<D3DXVECTOR3> vecVN;
	vector<ST_PNT_VERTEX> vecVertex;
	vector<cGeometry*> vecGeometry;

	string sMtlName;

	FILE* fp = NULL;
	fopen_s(&fp, szFilePath, "r");

	while (true)
	{
		if (feof(fp))
			break;

		char szTemp[1024];

		fgets(szTemp, 1024, fp);

		if (szTemp[0] == 'm')
		{
			char szMtlPath[1024];
			char szFullPath[1024];

			sscanf(szTemp, "%*s ./%s", szMtlPath);
			sprintf(szFullPath, "obj/%s", szMtlPath);
			LoadMtlLib(szFullPath);
		}
		else if (szTemp[0] == 'g')
		{
			if (vecVertex.empty())
				continue;

			cGeometry* pGeo = new cGeometry;
			g_pAutoReleasePool->AddObject(pGeo);
			pGeo->SetVertex(vecVertex);
			pGeo->SetMtrlTex(m_mapMtrlTex[sMtlName]);
			vecGeometry.push_back(pGeo);
			vecVertex.clear();
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == 't')
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f", &x, &y);
				vecVT.push_back(D3DXVECTOR2(x, y));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
			else // v
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf(szTemp, "%*s %s", szMtlName);
			sMtlName = szMtlName;
		}
		else if (szTemp[0] == 'f')
		{
			int aIndex[3][3];
			sscanf(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX pnt;
				pnt.p = vecV[aIndex[i][0] - 1];
				pnt.t = vecVT[aIndex[i][1] - 1];
				pnt.n = vecVN[aIndex[i][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
				}
				vecVertex.push_back(pnt);
			}
		}
	}

	for each (auto p in m_mapMtrlTex)
	{
		SAFE_RELEASE(p.second);
	}

	m_mapMtrlTex.clear();

	fclose(fp);



}

void cObjLoader::LoadMtlLib(char* szFilePath)
{
	FILE* fp = NULL;
	fopen_s(&fp, szFilePath, "r");

	string sMtrlName;

	while (true)
	{
		if (feof(fp))
			break;

		char szTemp[1024];

		fgets(szTemp, 1024, fp);

		if (szTemp[0] == 'n')
		{
			char szMtrlName[1024];
			sscanf(szTemp, "%*s %s", szMtrlName);
			sMtrlName = szMtrlName;

			SAFE_RELEASE(m_mapMtrlTex[sMtrlName]);
			m_mapMtrlTex[sMtrlName] = new cMtrlTex;
		}
		else if (szTemp[0] == 'K')
		{
			float r, g, b;
			sscanf(szTemp, "%*s %f %f %f", &r, &g, &b);
			D3DMATERIAL9& stMtrl = m_mapMtrlTex[sMtrlName]->GetMtrl();

			if (szTemp[1] == 'a')
			{
				stMtrl.Ambient.r = r;
				stMtrl.Ambient.g = g;
				stMtrl.Ambient.b = b;
				stMtrl.Ambient.a = 1.0;
			}
			else if (szTemp[1] == 'd')
			{
				stMtrl.Diffuse.r = r;
				stMtrl.Diffuse.g = g;
				stMtrl.Diffuse.b = b;
				stMtrl.Diffuse.a = 1.0;
			}
			else if (szTemp[1] == 's')
			{
				stMtrl.Specular.r = r;
				stMtrl.Specular.g = g;
				stMtrl.Specular.b = b;
				stMtrl.Specular.a = 1.0;
			}
		}
		else if (szTemp[0] == 'm')
		{
			char szTexturePath[1024];
			char szFullPath[1024];
			sscanf(szTemp, "%*s %s", szTexturePath);
			sprintf(szFullPath, "obj/%s", szTexturePath);

			g_pTextureManager->AddTexture(szTexturePath, szFullPath);
			m_mapMtrlTex[sMtrlName]->SetTexture(g_pTextureManager->GetTexture(szTexturePath));
		}
	}

	fclose(fp);
}