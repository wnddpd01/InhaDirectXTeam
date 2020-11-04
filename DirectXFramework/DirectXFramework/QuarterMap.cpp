#include "stdafx.h"
#include "QuarterMap.h"


QuarterMap::QuarterMap()
{
}


QuarterMap::~QuarterMap()
{

	
}

void QuarterMap::Setup(char* szFolder, char* szRaw, char* szTex, DWORD dwBytesPerPixel)
{
	
	//todo ���� ���� ��������� ����
	int mapHeight = 400;
	int mapWidth = 800;
	
	string sFolder(szFolder);
	string sRaw = sFolder + string(szRaw);
	string sTex = sFolder + string(szTex);

	//m_pTextrue = g_pTextureManager->GetTexture(sTex);

	FILE* fp = NULL;
	fopen_s(&fp, sRaw.c_str(), "rb");
	fseek(fp, 0, SEEK_END);
	int nFileSize = ftell(fp);
	int nNumVertex = nFileSize / dwBytesPerPixel;

	fseek(fp, 0, SEEK_SET);
	vector<Vertex> vecVertex(mapHeight*mapWidth);
	mVertexContainer.resize(mapHeight*mapWidth);

	vector<DWORD> vecIndex;
	vecIndex.reserve(mapHeight*mapWidth * 2 * 3);

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			int tempY;
			if ((tempY = fgetc(fp)) == EOF)
				tempY = 255;

			Vertex v;
			v.Pos = D3DXVECTOR3(((i * mapHeight) + j) % mapWidth, tempY / 5.f - 15.f, ((i * mapHeight) + j) / mapWidth);
			v.Normal = D3DXVECTOR3(0, 1, 0);
			v.TexUV = D3DXVECTOR2((((i * mapHeight) + j) % mapWidth) / (float)mapWidth, (((i * mapHeight) + j) / mapWidth) / (float)mapWidth);

			vecVertex[((i * mapHeight) + j)] = v;
			mVertexContainer[((i * mapHeight) + j)] = v.Pos;

			if (dwBytesPerPixel == 3)
			{
				fgetc(fp), fgetc(fp);
			}
		}
	}
	fclose(fp);

	for (int x = 0; x < mapHeight; ++x)
	{
		for (int z = 0; z < mapWidth; ++z)
		{
			int _0 = (z + 0)* mapHeight + x + 0;
			int _1 = (z + 1)* mapHeight + x + 0;
			int _2 = (z + 1)* mapHeight + x + 1;
			int _3 = (z + 0)* mapHeight + x + 1;

			vecIndex.push_back(_0);
			vecIndex.push_back(_1);
			vecIndex.push_back(_3);

			vecIndex.push_back(_2);
			vecIndex.push_back(_3);
			vecIndex.push_back(_1);
		}
	}
	
	D3DXCreateMeshFVF(vecIndex.size() / 3, vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		Vertex::FVF, gD3Device, &mMesh);

	Vertex * pV = NULL;
	mMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(Vertex));
	mMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	mMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	mMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	mMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, (vecIndex.size() / 3) * sizeof(DWORD));
	mMesh->UnlockAttributeBuffer();

	vector<DWORD> vecAdj(vecIndex.size());
	mMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	mMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		0, 0, 0);

	ZeroMemory(&mMaterial, sizeof(D3DMATERIAL9));
	mMaterial.Ambient = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.f);
	mMaterial.Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.f);
	mMaterial.Specular = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.f);
}

void QuarterMap::Update()
{
}

void QuarterMap::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	gD3Device->SetTransform(D3DTS_WORLD, &matWorld);
	gD3Device->SetMaterial(&mMaterial);
	gD3Device->SetRenderState(D3DRS_LIGHTING, true);
	gD3Device->SetTexture(0, mTextrue);
	mMesh->DrawSubset(0);
	gD3Device->SetRenderState(D3DRS_LIGHTING, false);
}

void QuarterMap::Destroy()
{
}
