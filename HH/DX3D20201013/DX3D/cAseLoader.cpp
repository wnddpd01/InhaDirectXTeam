#include "stdafx.h"
#include "cAseLoader.h"
#include "Asciitok.h"
#include "cMtlTex.h"
#include "cFrame.h"

cAseLoader::cAseLoader()
	: m_fp(NULL)
{
}


cAseLoader::~cAseLoader()
{
}

cFrame* cAseLoader::Load(char* szFullPath)
{
	cFrame* pRoot = NULL;

	fopen_s(&m_fp, szFullPath, "r");
	while (char* szToken = GetToken())
	{
		if (IsEqual(szToken, ID_SCENE))
		{
			ProcessScene();
		}
		else if(IsEqual(szToken, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if (IsEqual(szToken, ID_GEOMETRY))
		{
			cFrame* pFrame = ProcessGEOMOBJECT();
			if(pRoot == NULL)
			{
				pRoot = pFrame;
				SetSceneFrame(pRoot);
			}
		}
	}
	fclose(m_fp);

	for each(auto p in m_vecMtlTex)
	{
		SafeRelease(p);
	}

	pRoot->CalsOriginLocalTM(NULL);
	
	return pRoot;


	// 메시
	
}

cFrame* cAseLoader::LoadMesh(char* szFullPath)
{
	cFrame* pRoot = NULL;

	fopen_s(&m_fp, szFullPath, "r");
	while (char* szToken = GetToken())
	{
		if (IsEqual(szToken, ID_SCENE))
		{
			ProcessScene();
		}
		else if (IsEqual(szToken, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if (IsEqual(szToken, ID_GEOMETRY))
		{
			cFrame* pFrame = ProcessGEOMOBJECT();
			if (pRoot == NULL)
			{
				pRoot = pFrame;
				SetSceneFrame(pRoot);
			}
		}
	}
	fclose(m_fp);

	for each(auto p in m_vecMtlTex)
	{
		SafeRelease(p);
	}

	pRoot->CalsOriginLocalTM(NULL);

	return pRoot;

}

char* cAseLoader::GetToken()
{
	int nReadCnt = 0;
	bool isQuote = false;
	while(true)
	{
		char c = fgetc(m_fp);
		if (feof(m_fp)) break;

		if(c == '\"')
		{
			if (isQuote) break;
			isQuote = true;
			continue;
		}

		if(!isQuote && IsWhite(c))
		{
			if(nReadCnt == 0)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		m_szToken[nReadCnt++] = c;
	}

	if (nReadCnt == 0)
	{
		return NULL;
		
	}

	m_szToken[nReadCnt] = '\0';

	return m_szToken;
}

int cAseLoader::GetIneger()
{
	return atoi(GetToken());
}

float cAseLoader::GetFloat()
{
	return (float)atof(GetToken());
}

bool cAseLoader::IsWhite(char c)
{
	return c < 33;
}

bool cAseLoader::IsEqual(char* str1, char* str2)
{
	return strcmp(str1, str2) == 0;
}

void cAseLoader::SkipBlock()
{
	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMATERIAL_LIST()
{
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MATERIAL_COUNT))
		{
			for each(auto p in m_vecMtlTex)
			{
				SafeRelease(p);
			}
			m_vecMtlTex.resize(GetIneger());
		}
		else if (IsEqual(szToken, ID_MATERIAL))
		{
			int nIndex = GetIneger();
			m_vecMtlTex[nIndex] = new cMtlTex;
			ProcessMATERIAL(m_vecMtlTex[nIndex]);
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMATERIAL(cMtlTex* pMtlTex)
{
	D3DMATERIAL9	stMtl;
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
	
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_AMBIENT))
		{
			stMtl.Ambient.r = GetFloat();
			stMtl.Ambient.g = GetFloat();
			stMtl.Ambient.b = GetFloat();
			stMtl.Ambient.a = 1.f;
		}
		else if (IsEqual(szToken, ID_DIFFUSE))
		{
			stMtl.Diffuse.r = GetFloat();
			stMtl.Diffuse.g = GetFloat();
			stMtl.Diffuse.b = GetFloat();
			stMtl.Diffuse.a = 1.f;
		}
		else if (IsEqual(szToken, ID_SPECULAR))
		{
			stMtl.Specular.r = GetFloat();
			stMtl.Specular.g = GetFloat();
			stMtl.Specular.b = GetFloat();
			stMtl.Specular.a = 1.f;
		}
		else if( IsEqual(szToken, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(pMtlTex);
		}
	} while (nLevel > 0);

	pMtlTex->SetMaterial(stMtl);
}

void cAseLoader::ProcessMAP_DIFFUSE(cMtlTex* pMtlTex)
{
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_BITMAP))
		{
			szToken = GetToken();
			pMtlTex->SetTexture(g_pTextureManager->GetTexture(szToken));
		}
	} while (nLevel > 0);
}

cFrame* cAseLoader::ProcessGEOMOBJECT()
{
	cFrame*		pFrame = new cFrame;
	
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_NODE_NAME))
		{
			m_mapFrame[GetToken()] = pFrame;
		}
		else if (IsEqual(szToken, ID_NODE_PARENT))
		{
			m_mapFrame[GetToken()]->AddChild(pFrame);
		}
		else if (IsEqual(szToken, ID_NODE_TM))
		{
			ProcessNODE_TM(pFrame);
		}
		else if (IsEqual(szToken, ID_MESH))
		{
			ProcessMESH(pFrame);
			
		}
		else if (IsEqual(szToken, ID_TM_ANIMATION))
		{
			ProcessTM_ANIMATION(pFrame);
		}
		else if (IsEqual(szToken, ID_MATERIAL_REF))
		{
			int nMtlIndex = GetIneger();
			pFrame->SetMtlTex(m_vecMtlTex[nMtlIndex]);
		}
	} while (nLevel > 0);
	return pFrame;
}

void cAseLoader::ProcessMESH(cFrame* pFrame)
{
	vector<D3DXVECTOR3>		vecV;
	vector<D3DXVECTOR2>		vecVT;
	vector<ST_PNT_VERTEX>	vecVertex;
	vector<ST_ABC_INDEX>	vecIndex;

	

	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_NUMVERTEX))
		{
			vecV.resize(GetIneger());
		}
		else if (IsEqual(szToken, ID_MESH_NUMFACES))
		{
			vecVertex.resize(GetIneger() * 3);
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX_LIST))
		{
			ProcessMESH_VERTEX_LIST(vecV);
		}
		else if (IsEqual(szToken, ID_MESH_FACE_LIST))
		{
			ProcessMESH_FACE_LIST(vecVertex, vecV, vecIndex);
		}
		else if (IsEqual(szToken, ID_MESH_NUMTVERTEX))
		{
			vecVT.resize(GetIneger());
		}
		else if (IsEqual(szToken, ID_MESH_TVERTLIST))
		{
			ProcessMESH_TVERTLIST(vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_TFACELIST))
		{
			ProcessMEsh_TFACELIST(vecVertex, vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_NORMALS))
		{
			ProcessMESH_NORMALS(vecVertex);
		}
	} while (nLevel > 0);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, 0, &pFrame->GetWorldTM());
	for (size_t i = 0; i < vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInvWorld);
		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInvWorld);
	}
	
	//pFrame->SetVertex(vecVertex);
	//버텍스버퍼를 위해 제거
	//인덱스 버퍼
	
	for (auto ver : vecV)
	{
		ST_PNT_VERTEX temp;
		temp.p = ver;
		pFrame->GetVertex4Index().push_back(temp);
	}
	D3DXMATRIXA16 inTemp;
	D3DXMatrixInverse(&inTemp, NULL, &pFrame->GetWorldTM());

	/*
	for (auto ver : pFrame->GetVertex4Index())
		D3DXVec3TransformCoord(&ver.p, &ver.p, &inTemp);
	*/
	
	for (auto ver : vecIndex)
	{
		pFrame->GetIndex().push_back(ver);
	}
	
	pFrame->BuildVB(pFrame->GetVertex4Index());
	pFrame->BuildIB();
	//pFrame->BuildVB(vecVertex);
	
}

void cAseLoader::ProcessMESH_VERTEX_LIST(vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nIndex = GetIneger();
			vecV[nIndex].x = GetFloat();
			vecV[nIndex].z = GetFloat();
			vecV[nIndex].y = GetFloat();
		}
	} while (nLevel > 0);

	
}

void cAseLoader::ProcessMESH_FACE_LIST(vector<ST_PNT_VERTEX>& vecVertex, vector<D3DXVECTOR3>& vecV, vector<ST_ABC_INDEX>& vecIndex)
{
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_FACE))
		{
			ST_ABC_INDEX abc;
			int nFaceIndex = GetIneger();
			GetToken(); abc.a = GetIneger();
			vecVertex[nFaceIndex * 3 + 0].p = vecV[abc.a];
			
			GetToken(); abc.b = GetIneger();
			vecVertex[nFaceIndex * 3 + 2].p = vecV[abc.b];
			
			GetToken(); abc.c = GetIneger();
			vecVertex[nFaceIndex * 3 + 1].p = vecV[abc.c];
			
			vecIndex.push_back(abc);
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMESH_TVERTLIST(vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TVERT))
		{
			int nIndex = GetIneger();
			vecVT[nIndex].x = GetFloat();
			vecVT[nIndex].y = 1.f - GetFloat();

		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMEsh_TFACELIST(vector<ST_PNT_VERTEX>& vecVertex, vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TFACE))
		{
			int nFaceIndex = GetIneger();
			vecVertex[nFaceIndex * 3 + 0].t = vecVT[GetIneger()];
			vecVertex[nFaceIndex * 3 + 2].t = vecVT[GetIneger()];
			vecVertex[nFaceIndex * 3 + 1].t = vecVT[GetIneger()];
		}
	} while (nLevel > 0);
}


void cAseLoader::ProcessMESH_NORMALS(vector<ST_PNT_VERTEX>& vecVertex)
{
	int nFaceIndex = 0;
	int aModIndex[3] = { 0, 2 ,1 };
	int nModCount = 0;
	
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_FACENORMAL))
		{
			nFaceIndex = GetIneger();
			nModCount = 0;
			
		}
		else if (IsEqual(szToken, ID_MESH_VERTEXNORMAL))
		{
			GetToken();
			D3DXVECTOR3 n;
			n.x = GetFloat();
			n.z = GetFloat();
			n.y = GetFloat();
			vecVertex[nFaceIndex * 3 + aModIndex[nModCount++]].n = n;
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessNODE_TM(cFrame* pFrame)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_TM_ROW0))
		{
			matWorld._11 = GetFloat();
			matWorld._13 = GetFloat();
			matWorld._12 = GetFloat();
			matWorld._14 = 0.f;
		}
		else if (IsEqual(szToken, ID_TM_ROW1))
		{
			matWorld._31 = GetFloat();
			matWorld._33 = GetFloat();
			matWorld._32 = GetFloat();
			matWorld._34 = 0.f;
		}
		else if (IsEqual(szToken, ID_TM_ROW2))
		{
			matWorld._21 = GetFloat();
			matWorld._23 = GetFloat();
			matWorld._22 = GetFloat();
			matWorld._24 = 0.f;
		}
		else if (IsEqual(szToken, ID_TM_ROW3))
		{
			matWorld._41 = GetFloat();
			matWorld._43 = GetFloat();
			matWorld._42 = GetFloat();
			matWorld._44 = 1.f;
		}
	} while (nLevel > 0);

	pFrame->SetWorldTM(matWorld);
}


void cAseLoader::ProcessTM_ANIMATION(cFrame* pFrame)
{
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_POS_TRACK))
		{
			ProcessCONTROL_POS_TRACK(pFrame);
		}
		else if (IsEqual(szToken, ID_ROT_TRACK))
		{
			ProcessCONTROL_ROT_TRACK(pFrame);
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessCONTROL_POS_TRACK(cFrame* pFrame)
{
	vector<ST_POS_SAMPLE> vecPosTrack;
	
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_POS_SAMPLE))
		{
			ST_POS_SAMPLE s;
			s.n = GetIneger();
			s.v.x = GetFloat();
			s.v.z = GetFloat();
			s.v.y = GetFloat();
			vecPosTrack.push_back(s);
		}
	} while (nLevel > 0);

	pFrame->SetPosTrack(vecPosTrack);
}

void cAseLoader::ProcessCONTROL_ROT_TRACK(cFrame* pFrame)
{
	vector<ST_ROT_SAMPLE> vecRotTrack;
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_ROT_SAMPLE ))
		{
			ST_ROT_SAMPLE s;
			s.n = GetIneger();
			s.q.x = GetFloat();
			s.q.z = GetFloat();
			s.q.y = GetFloat();
			s.q.w = GetFloat();

			s.q.x *= sinf(s.q.w / 2.f);
			s.q.y *= sinf(s.q.w / 2.f);
			s.q.z *= sinf(s.q.w / 2.f);
			s.q.w = cosf(s.q.w / 2.f);

			if(!vecRotTrack.empty())
			{
				s.q = vecRotTrack.back().q * s.q;
			}
			vecRotTrack.push_back(s);
		}
	} while (nLevel > 0);

	pFrame->SetRotTrack(vecRotTrack);
}



void cAseLoader::ProcessScene()
{
	int nLevel = 0;
	do {
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_FIRSTFRAME))
		{
			m_dwFirstFrame = GetIneger();
		}
		else if (IsEqual(szToken, ID_LASTFRAME))
		{
			m_dwLastFrame = GetIneger();
		}
		else if (IsEqual(szToken, ID_FRAMESPEED))
		{
			m_dwFrameSpeed = GetIneger();
		}
		else if (IsEqual(szToken, ID_TICKSPERFRAME))
		{
			m_dwTicksPerFrame = GetIneger();
		}
	} while (nLevel > 0);
}

void cAseLoader::SetSceneFrame(cFrame* pRoot)
{
	pRoot->m_dwFirstFrame = m_dwFirstFrame;
	pRoot->m_dwLastFrame = m_dwLastFrame;
	pRoot->m_dwFrameSpeed = m_dwFrameSpeed;
	pRoot->m_dwTicksPerFrame = m_dwTicksPerFrame;
}
