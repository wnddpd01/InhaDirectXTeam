#include "stdafx.h"
#include "cAseLoader.h"
#include "cMtlTex.h"


using namespace std;

cAseLoader::cAseLoader()
{
}


cAseLoader::~cAseLoader()
{

	
}

void cAseLoader::LoadMtlLib(char* szFolder, char* szFile)
{
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE *fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;

	while (true)
	{
		if (feof(fp))break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);
		
		if(strstr(szTemp,"SCENE"))
		{
			while(true)
			{
				fgets(szTemp, 1024, fp);

				/*
				 *ªÁ¿Ã 
				 * 
				 */
				if (szTemp[0] == '}')
					break;
				
			}
		}
		
		
	}
	fclose(fp);
	
}
