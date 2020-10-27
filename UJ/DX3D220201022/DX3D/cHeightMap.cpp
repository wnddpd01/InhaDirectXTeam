#include "stdafx.h"
#include "cHeightMap.h"


#include <iostream>
#include <thread>


cHeightMap::cHeightMap()
	: m_pTexture(NULL)
	, m_pMesh(NULL)
{	
}


cHeightMap::~cHeightMap()
{
	Destroy();
}

void cHeightMap::BuildThreadCall(D3DXPLANE * planes)
{
	//m_thread = 
}

void cHeightMap::BuildMesh(D3DXPLANE * planes)
{
	cout << "thread Start\n";
	if (planes)
	{
		for (int p = 0; p < 6; ++p)
		{
			/*for (int i = 0; i < m_vecSphere.size(); ++i)
			{
			if (D3DXPlaneDotCoord(&frustrumPlane[p], &m_vecSphere[i].vCenter) > 0.5f)
			{
			m_vecSphere[i].isPicked = true;
			}
			}*/
			for (int i = 0; i < m_vecVertex.size(); ++i)
			{
				if (D3DXPlaneDotCoord(&planes[p], &m_vecVertex[i]) > 0.5f)
				{
					if (m_setNotDrawIdx.find(i) == m_setNotDrawIdx.end())
					{
						m_setNotDrawIdx.insert(i);
					}
				}
			}

		}
	}
	size_t nNumVertex = 257 * 257;
	size_t nCol = 257;
	size_t nTimeN = 256;
	//vector<ST_PNT_VERTEX> vecVertex(nNumVertex);
	vector<DWORD> vecIndex;
	vecIndex.reserve(nTimeN * nTimeN * 2 * 3);
	LPD3DXMESH tempMesh;
	for (int x = 0; x < nTimeN; ++x)
	{
		for (int z = 0; z < nTimeN; ++z)
		{
			size_t _0 = (z + 0) * nCol + x + 0;
			size_t _1 = (z + 1) * nCol + x + 0;
			size_t _2 = (z + 1) * nCol + x + 1;
			size_t _3 = (z + 0) * nCol + x + 1;

			if (m_setNotDrawIdx.find(_0) == m_setNotDrawIdx.end() && m_setNotDrawIdx.find(_1) == m_setNotDrawIdx.end() && m_setNotDrawIdx.find(_2) == m_setNotDrawIdx.end())
			{
				vecIndex.push_back(_0);
				vecIndex.push_back(_1);
				vecIndex.push_back(_3);
			}
			if (m_setNotDrawIdx.find(_2) == m_setNotDrawIdx.end() && m_setNotDrawIdx.find(_3) == m_setNotDrawIdx.end() && m_setNotDrawIdx.find(_1) == m_setNotDrawIdx.end())
			{
				vecIndex.push_back(_2);
				vecIndex.push_back(_3);
				vecIndex.push_back(_1);
			}
		}
	}
	
	D3DXCreateMeshFVF(vecIndex.size() / 3, m_vecPNTVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDevice, &tempMesh);
	
	ST_PNT_VERTEX * pV = NULL;
	tempMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &m_vecPNTVertex[0], m_vecPNTVertex.size() * sizeof(ST_PNT_VERTEX));
	tempMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	tempMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	tempMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	tempMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, (vecIndex.size() / 3) * sizeof(DWORD));
	tempMesh->UnlockAttributeBuffer();
	vector<DWORD> vecAdj(vecIndex.size());
	tempMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	tempMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0);
	if (m_pMesh)
	{
		SafeRelease(m_pMesh);
	}
	m_pMesh = tempMesh;
	cout << "thread End\n";
}

void cHeightMap::Setup(char* szFolder, char* szRaw, char* szTex, DWORD dwBytesPerPixel)
{
	string sFolder(szFolder);
	string sRaw = sFolder + string(szRaw);
	string sTex = sFolder + string(szTex);

	m_pTexture = g_pTextureManager->GetTexture(sTex);

	FILE * fp = NULL;
	fopen_s(&fp, sRaw.c_str(), "rb");

	fseek(fp, 0, SEEK_END);
	int nFileSize = ftell(fp);
	int nNumVertex = nFileSize / dwBytesPerPixel;
	int nRow = (int)(sqrt((float)nNumVertex) + 0.0001f);
	int nCol = nRow;
	int nTimeN = nRow - 1;
	m_nTileNum = nTimeN;
	fseek(fp, 0, SEEK_SET);
	m_vecVertex.resize(nNumVertex);
	m_vecPNTVertex.resize(nNumVertex);
	vector<ST_PNT_VERTEX> vecVertex(nNumVertex);
	vector<DWORD> vecIndex;
	vecIndex.reserve(nTimeN * nTimeN * 2 * 3);

	for (int i = 0; i < nNumVertex; ++i)
	{
		ST_PNT_VERTEX v;
		v.p = D3DXVECTOR3(i % nCol, ((unsigned char)fgetc(fp)) / 10.f, i / nCol);
		v.n = D3DXVECTOR3(0, 1, 0);
		v.t = D3DXVECTOR2(i % nCol / (float)(nCol), (i / nCol) / (float)nCol);

		m_vecPNTVertex[i] = v;
		m_vecVertex[i] = v.p;

		if (dwBytesPerPixel == 3)
		{
			fgetc(fp), fgetc(fp);
		}
	}
	fclose(fp);
	for (int x = 1; x < nTimeN; ++x)
	{
		for (int z = 1; z < nTimeN; ++z)
		{
			int left = (z + 0) * nCol + x - 1;
			int right = (z + 0) * nCol + x + 1;
			int up = (z + 1) * nCol + x;
			int down = (z - 1) * nCol + x;

			D3DXVECTOR3 leftToRight = m_vecVertex[right] - m_vecVertex[left];
			D3DXVECTOR3 downToUp = m_vecVertex[up] - m_vecVertex[down];

			D3DXVECTOR3 normal;
			D3DXVec3Cross(&normal, &downToUp, &leftToRight);
			D3DXVec3Normalize(&normal, &normal);

			int nIndex = z * nCol + x;
			m_vecPNTVertex[nIndex].n = normal;
		}
	}

	BuildMesh();
	
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
}

void cHeightMap::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
}

bool cHeightMap::GetHeight(float x, float& y, float z)
{
	if( x < 0.f || z < 0.f || x >= m_nTileNum || z >= m_nTileNum)
	{
		y = 0;
		return false;
	}
	int nX = x;
	int nZ = z;

	float fDeltaX = x - nX;
	float fDeltaZ = z - nZ;

	int _0 = (nZ + 0) * (m_nTileNum + 1) + nX + 0;
	int _1 = (nZ + 1) * (m_nTileNum + 1) + nX + 0;
	int _2 = (nZ + 1) * (m_nTileNum + 1) + nX + 1;
	int _3 = (nZ + 0) * (m_nTileNum + 1) + nX + 1;

	if(fDeltaX + fDeltaZ < 1.0f)
	{
		D3DXVECTOR3 v01 = m_vecVertex[_1] - m_vecVertex[_0];
		D3DXVECTOR3 v03 = m_vecVertex[_3] - m_vecVertex[_0];

		y = m_vecVertex[_0].y + (v01 * fDeltaZ + v03 *fDeltaX).y;
	}
	else
	{
		fDeltaX = 1.0f - fDeltaX;
		fDeltaZ = 1.0f - fDeltaZ;
		D3DXVECTOR3 v21 = m_vecVertex[_1] - m_vecVertex[_2];
		D3DXVECTOR3 v23 = m_vecVertex[_3] - m_vecVertex[_2];
		y = m_vecVertex[_2].y + (v21 * fDeltaX + v23 * fDeltaZ).y;
	}
	
	return true;
}

void cHeightMap::Destroy()
{
	SafeRelease(m_pTexture);
	SafeRelease(m_pMesh);
}
