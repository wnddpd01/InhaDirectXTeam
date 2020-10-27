#include "stdafx.h"
#include "cTerrain.h"


cTerrain::cTerrain()
{
}


cTerrain::~cTerrain()
{
}

bool cTerrain::readRawFile(char* filename)
{
	FILE* pFile = fopen(filename, "rb");
	char c;
	if (pFile == NULL)
	{
		return false;
	}

	while ((c = fgetc(pFile))!= EOF)
	{
		for (int i = 0; i < 257; i++)
		{
			for (int j = 0; j < 257; j++)
			{
				m_aMapVertex[i][j] = (BYTE)c;
			}
		}
	}

	fclose(pFile);

	return true;

}


