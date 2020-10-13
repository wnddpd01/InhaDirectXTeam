#include "stdafx.h"
#include "cAseLoader.h"
#include "Asciitok.h"
#include "cMtrlTex.h"


cAseLoader::cAseLoader()
{
}


cAseLoader::~cAseLoader()
{
}


void cAseLoader::Load(IN const char* szFilePath, OUT cGeometry*& vecGeometry, OUT ST_ASE_SCENE& _stScene)
{
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<D3DXVECTOR3> vecVN;
	vector<ST_PNT_VERTEX> vecVertex;

	int nIndex;
	cGeometry* pNewGeometry = NULL;

	FILE* fp = NULL;
	fopen_s(&fp, szFilePath, "r");

	while (true)
	{
		if (feof(fp))
			break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		char szBuff[1024];
		sscanf(szTemp, "%s", szBuff);

		///////////////////////////////////////////////// Set Animation
		if (!strcmp(szBuff, ID_FIRSTFRAME))
		{
			int nFirstFrame;
			sscanf(szTemp, "%*s %d", &nFirstFrame);
			_stScene.nFirstFrame = nFirstFrame;
		}
		else if (!strcmp(szBuff, ID_LASTFRAME))
		{
			int nLastFrame;
			sscanf(szTemp, "%*s %d", &nLastFrame);
			_stScene.nLastFrame = nLastFrame;
		}
		else if (!strcmp(szBuff, ID_FRAMESPEED))
		{
			int nFrameSpeed;
			sscanf(szTemp, "%*s %d", &nFrameSpeed);
			_stScene.nFrameSpeed = nFrameSpeed;
		}
		else if (!strcmp(szBuff, ID_TICKSPERFRAME))
		{
			int nTicksPerFrame;
			sscanf(szTemp, "%*s %d", &nTicksPerFrame);
			_stScene.nTicksPerFrame = nTicksPerFrame;
		}
		else if (!strcmp(szBuff, ID_POS_TRACK))
		{
			
		}
		else if (!strcmp(szBuff, ID_ROT_TRACK))
		{
			
		}
		else if (!strcmp(szBuff, ID_ROT_SAMPLE))
		{
			ST_ROT_SAMPLE stRot;
			sscanf(szTemp, "%*s %d %f %f %f %f", &stRot.n, &stRot.q.x, &stRot.q.z, &stRot.q.y, &stRot.q.w);
			stRot.q.x *= sinf(stRot.q.w / 2.f);
			stRot.q.y *= sinf(stRot.q.w / 2.f);
			stRot.q.z *= sinf(stRot.q.w / 2.f);
			stRot.q.w =  cosf(stRot.q.w / 2.f);

			if (!pNewGeometry->GetRotTrack().empty())
				stRot.q = pNewGeometry->GetRotTrack().back().q * stRot.q;

			pNewGeometry->GetRotTrack().push_back(stRot);
		}
		else if (!strcmp(szBuff, ID_POS_SAMPLE))
		{
			ST_POS_SAMPLE stPos;
			sscanf(szTemp, "%*s %d %f %f %f", &stPos.n, &stPos.v.x, &stPos.v.z, &stPos.v.y);
			pNewGeometry->GetPosTrack().push_back(stPos);
		}
		
		///////////////////////////////////////////////// Set Material
		else if (!strcmp(szBuff, ID_MATERIAL_COUNT))
		{
			int nSize;
			sscanf(szTemp, "%*s %d", &nSize);
			
			m_vecMtrlTex.resize(nSize);
		}
		else if (!strcmp(szBuff, ID_MATERIAL))
		{
			sscanf(szTemp, "%*s %d", &nIndex);

			SAFE_RELEASE(m_vecMtrlTex[nIndex]);
			m_vecMtrlTex[nIndex] = new cMtrlTex;
		}
		else if (!strcmp(szBuff, ID_AMBIENT))
		{
			D3DMATERIAL9& stMtrl = m_vecMtrlTex[nIndex]->GetMtrl();
			float r, g, b;
			sscanf(szTemp, "%*s %f %f %f", &r, &g, &b);

			stMtrl.Ambient.r = r;
			stMtrl.Ambient.g = g;
			stMtrl.Ambient.b = b;
			stMtrl.Ambient.a = 1.0;
		}
		else if (!strcmp(szBuff, ID_DIFFUSE))
		{
			D3DMATERIAL9& stMtrl = m_vecMtrlTex[nIndex]->GetMtrl();
			float r, g, b;
			sscanf(szTemp, "%*s %f %f %f", &r, &g, &b);

			stMtrl.Diffuse.r = r;
			stMtrl.Diffuse.g = g;
			stMtrl.Diffuse.b = b;
			stMtrl.Diffuse.a = 1.0;
		}
		else if (!strcmp(szBuff, ID_SPECULAR))
		{
			D3DMATERIAL9& stMtrl = m_vecMtrlTex[nIndex]->GetMtrl();
			float r, g, b;
			sscanf(szTemp, "%*s %f %f %f", &r, &g, &b);

			stMtrl.Specular.r = r;
			stMtrl.Specular.g = g;
			stMtrl.Specular.b = b;
			stMtrl.Specular.a = 1.0;
		}
		else if (!strcmp(szBuff, ID_BITMAP))
		{
			char szTexturePath[1024];
			char szFullPath[1024];
			sscanf(szTemp, "%*s \"C:\\3dsealonline\\character\\%[^\"]s", szTexturePath);
			sprintf(szFullPath, "ase/%s", szTexturePath);

			g_pTextureManager->AddTexture(szTexturePath, szFullPath);
			m_vecMtrlTex[nIndex]->SetTexture(g_pTextureManager->GetTexture(szTexturePath));
		}

		////////////////////////////////////////////////////////// Set GeoMetry
		else if (!strcmp(szBuff, ID_GEOMETRY))
		{
			if (pNewGeometry == NULL)
			{
				////만약 안지워졌다면 여기서 지워줘야함
				pNewGeometry = new cGeometry;
				g_pAutoReleasePool->AddObject(pNewGeometry);
				vecGeometry = pNewGeometry;
			}
			else
			{
				if (!vecVertex.empty())
				{
					D3DXMATRIXA16 matInverse; 
					matInverse = pNewGeometry->GetMatWorld();
					D3DXMatrixInverse(&matInverse, 0, &matInverse);
					for (int i = 0; i < vecVertex.size(); i++)
					{
						D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInverse);
						D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInverse);
					}
					pNewGeometry->SetVertex(vecVertex);
					pNewGeometry->SetMatLocal(pNewGeometry->GetMatWorld());
					vecVertex.clear();
				}
				pNewGeometry = new cGeometry;
				g_pAutoReleasePool->AddObject(pNewGeometry);
				
			}
			
			//ZeroMemory(pNewGeometry, sizeof(cGeometry));
			

		}
		else if (!strcmp(szBuff, ID_NODE_NAME))
		{
			char szNodeName[1024];
			sscanf(szTemp, "%*s \"%[^\"]s", szNodeName);
			pNewGeometry->SetMyName(szNodeName);
		}
		else if (!strcmp(szBuff, ID_NODE_PARENT))
		{
			char szParentsName[1024];
			sscanf(szTemp, "%*s \"%[^\"]s", szParentsName);
			cGeometry* pParents = NULL;
			pParents = vecGeometry->GetMyParents(szParentsName);
			if (pParents)
				pParents->AddMyChild(pNewGeometry);
		}
		else if (!strcmp(szBuff, ID_TM_ROW0))
		{
			float x, y, z;
			sscanf(szTemp, "%*s %f %f %f", &x, &z, &y);
			D3DXMATRIXA16 TM = pNewGeometry->GetMatWorld();
			TM._11 = x;
			TM._12 = y;
			TM._13 = z;
			TM._14 = 0.0f;
			pNewGeometry->SetMatWorld(TM);
		}
		else if (!strcmp(szBuff, ID_TM_ROW1))
		{
			float x, y, z;
			sscanf(szTemp, "%*s %f %f %f", &x, &z, &y);
			D3DXMATRIXA16 TM = pNewGeometry->GetMatWorld();
			TM._31 = x;
			TM._32 = y;
			TM._33 = z;
			TM._34 = 0.0f;
			pNewGeometry->SetMatWorld(TM);
		}
		else if (!strcmp(szBuff, ID_TM_ROW2))
		{
			float x, y, z;
			sscanf(szTemp, "%*s %f %f %f", &x, &z, &y);
			D3DXMATRIXA16 TM = pNewGeometry->GetMatWorld();
			TM._21 = x;
			TM._22 = y;
			TM._23 = z;
			TM._24 = 0.0f;
			pNewGeometry->SetMatWorld(TM);
		}
		else if (!strcmp(szBuff, ID_TM_ROW3))
		{
			float x, y, z;
			sscanf(szTemp, "%*s %f %f %f", &x, &z, &y);
			D3DXMATRIXA16 TM = pNewGeometry->GetMatWorld();
			TM._41 = x;
			TM._42 = y;
			TM._43 = z;
			TM._44 = 1.0f;
			pNewGeometry->SetMatWorld(TM);
		}
		else if (!strcmp(szBuff, ID_MESH_NUMVERTEX))
		{
			int nSize;
			sscanf(szTemp, "%*s %d", &nSize);

			vecV.clear();
			vecV.resize(nSize);
		}
		else if (!strcmp(szBuff, ID_MESH_VERTEX))
		{
			int nVerIndex;
			D3DXVECTOR3 v;
			sscanf(szTemp, "%*s %d %f %f %f", &nVerIndex, &v.x, &v.z, &v.y);
			vecV[nVerIndex] = v;
		}
		else if (!strcmp(szBuff, ID_MESH_NUMFACES))
		{
			int nSize;
			sscanf(szTemp, "%*s %d", &nSize);
			
			vecVertex.clear();
			vecVertex.resize(nSize * 3);
		}
		else if (!strcmp(szBuff, ID_MESH_FACE))
		{
			int nFaceIndex;
			int a, b, c;
			sscanf(szTemp, "%*s %d: A: %d B: %d C: %d", &nFaceIndex, &a, &c, &b);
			vecVertex[nFaceIndex * 3].p = vecV[a];
			vecVertex[nFaceIndex * 3 + 1].p = vecV[b];
			vecVertex[nFaceIndex * 3 + 2].p = vecV[c];
		}
		else if (!strcmp(szBuff, ID_MESH_NUMTVERTEX))
		{
			int nSize;
			sscanf(szTemp, "%*s %d", &nSize);

			vecVT.clear();
			vecVT.resize(nSize);
		}
		else if (!strcmp(szBuff, ID_MESH_TVERT))
		{
			int nVTIndex;
			D3DXVECTOR2 v;
			sscanf(szTemp, "%*s %d %f %f %*f", &nVTIndex, &v.x, &v.y);
			v.y = 1.0f - v.y;
			vecVT[nVTIndex] = v;
		}
		else if (!strcmp(szBuff, ID_MESH_TFACE))
		{
			int nFaceIndex;
			int a, b, c;
			sscanf(szTemp, "%*s %d %d %d %d", &nFaceIndex, &a, &c, &b);
			vecVertex[nFaceIndex * 3].t		= vecVT[a];
			vecVertex[nFaceIndex * 3 + 1].t = vecVT[b];
			vecVertex[nFaceIndex * 3 + 2].t = vecVT[c];
		}
		else if (!strcmp(szBuff, ID_MESH_FACENORMAL))
		{
			int nFaceIndex;
			D3DXVECTOR3 a, b, c;
			sscanf(szTemp, "%*s %d", &nFaceIndex);

			fgets(szTemp, 1024, fp);
			sscanf(szTemp, "%*s %*d %f %f %f", &a.x, &a.z, &a.y);
			fgets(szTemp, 1024, fp);
			sscanf(szTemp, "%*s %*d %f %f %f", &c.x, &c.z, &c.y);
			fgets(szTemp, 1024, fp);
			sscanf(szTemp, "%*s %*d %f %f %f", &b.x, &b.z, &b.y);

			vecVertex[nFaceIndex * 3].n		= a;
			vecVertex[nFaceIndex * 3 + 1].n = b;
			vecVertex[nFaceIndex * 3 + 2].n = c;
		}
		else if (!strcmp(szBuff, ID_MATERIAL_REF))
		{
			int nMtrlIndex;
			sscanf(szTemp, "%*s %d", &nMtrlIndex);
			pNewGeometry->SetMtrlTex((m_vecMtrlTex[nMtrlIndex]));
		}


	}

	if (!vecVertex.empty())
	{
		D3DXMATRIXA16 matInverse;
		matInverse = pNewGeometry->GetMatWorld();
		D3DXMatrixInverse(&matInverse, 0, &matInverse);
		for (int i = 0; i < vecVertex.size(); i++)
		{
			D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInverse);
			D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInverse);
		}
		pNewGeometry->SetVertex(vecVertex);
		pNewGeometry->SetMatLocal(pNewGeometry->GetMatWorld());
	}

	for (int i = 0; i < m_vecMtrlTex.size(); i++)
	{
		SAFE_RELEASE(m_vecMtrlTex[i]);
	}

	m_vecMtrlTex.clear();

	fclose(fp);

	vecGeometry->CalcLocalTM(NULL);
}

