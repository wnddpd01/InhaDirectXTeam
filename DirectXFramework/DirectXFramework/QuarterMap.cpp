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
	//todo 추후 파일 입출력으로 변경
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
	vector<Vertex> vecVertex(nNumVertex);
	m_vecVertex.resize(nNumVertex);

	vector<DWORD> vecIndex;
	vecIndex.reserve(mapHeight*mapWidth * 2 * 3);

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			/*
			Vertex v;
			v.Pos = D3DXVECTOR3(i % nCol, ((unsigned char)fgetc(fp)) / 5.f - 15.f, i / nCol);
			v.Normal = D3DXVECTOR3(0, 1, 0);
			v.TexUV = D3DXVECTOR2((i % nCol) / (float)nCol, (i / nCol) / (float)nCol);

			vecVertex[i] = v;
			m_vecVertex[i] = v.p;

			if (dwBytesPerPixel == 3)
			{
				fgetc(fp), fgetc(fp);
			}
			*/
		}
	}
	fclose(fp);
}

void QuarterMap::Update()
{
}

void QuarterMap::Render()
{
}

void QuarterMap::Destroy()
{
}
