#include "stdafx.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cGroup.h"


cObjLoader::cObjLoader()
{
}


cObjLoader::~cObjLoader()
{
}

void cObjLoader::Load(std::vector<cGroup*>& vecGroup, char* szFolder, char* szFile)
{
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<D3DXVECTOR3> vecN;
	vector<ST_PNT_VERTEX> vecVertex;

	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE *fp;
	fopen_s(&fp, sFullPath.c_str(), "r");
	string sMtlName;

	D3DXMATRIXA16 matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2);
	while(true)
	{
		if(feof(fp)) break;
		char szTemp[1024];

		fgets(szTemp, 1024, fp);

		if(szTemp[0] == '#')
			continue;
		else if(szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if(szTemp[0] == 'g')
		{
			if(!vecVertex.empty())
			{
				cGroup* p_group = new cGroup;
				p_group->SetVerTex(vecVertex);
				p_group->SetMtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(p_group);
				vecVertex.clear();
			}
		}
		else if(szTemp[0] == 'v')
		{
			if(szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if(szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if(szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if(szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf(szTemp, "%*s %s", szMtlName);
			sMtlName = string(szMtlName);
		}
		else if(szTemp[0] == 'f')
		{
			int nIndex[3][3];
			sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2], &nIndex[2][0], &nIndex[2][1], &nIndex[2][2]);
			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecN[nIndex[i][2] - 1];
				D3DXVec3TransformNormal(&v.p, &v.p, &matS);
				D3DXVec3TransformNormal(&v.p, &v.p, &matR);
				D3DXVec3TransformNormal(&v.n, &v.n, &matS);
				D3DXVec3TransformNormal(&v.n, &v.n, &matR);
				vecVertex.push_back(v);
			}
		}
	}

	fclose(fp);

	for (auto it : m_mapMtlTex)
	{
		SafeRelease(it.second);
	}
	m_mapMtlTex.clear();
}

void cObjLoader::LoadMtlLib(char* szFolder, char* szFile)
{
	string sFullPath(szFolder);
	sFullPath += string("/") + string(szFile);

	FILE *fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;


	while(true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if(szTemp[0] == '#')
			continue;
		else if(szTemp[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);
			if(m_mapMtlTex.find(sMtlName) == m_mapMtlTex.end())
			{
				m_mapMtlTex[sMtlName] = new cMtlTex;
			}
		}
		else if (szTemp[0] == 'K')
		{
			if(szTemp[1] == 'a')
			{
				float r, g, b;
				sscanf(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.a = 1.0f;
			}
			else if(szTemp[1] == 'd')
			{
				float r, g, b;
				sscanf(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.a = 1.0f;
			}
			else if(szTemp[1] == 's')
			{
				float r, g, b;
				sscanf(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.a = 1.0f;
			}
		}
		else if (szTemp[0] == 'd')
		{
			float d;
			sscanf(szTemp, "%*s %f", &d);
			m_mapMtlTex[sMtlName]->GetMaterial().Power = d;
		}
		else if (szTemp[0] == 'm')
		{
			char szTexFile[1024];
			sscanf_s(szTemp, "%*s %s", szTexFile, 1024);
			sFullPath = string(szFolder);
			sFullPath += string("/") + string(szTexFile);
			LPDIRECT3DTEXTURE9 p_texture9 = g_pTextureManger->GetTexture(sFullPath);
			m_mapMtlTex[sMtlName]->SetTexture(p_texture9);

		}
	}
}
