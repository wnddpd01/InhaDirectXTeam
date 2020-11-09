#include "stdafx.h"
#include "cSkinnedMeshManager.h"
#include "cSkinnedMesh.h"


cSkinnedMesh* cSkinnedMeshManager::GetSkinnedMesh(char* szFoler, char* szFilename)
{
	string sFullPath(szFoler);
	sFullPath += string("/") + string(szFilename);

	if(m_mapSkinnedMesh.find(sFullPath) == m_mapSkinnedMesh.end())
	{
		cSkinnedMesh *p = new cSkinnedMesh();
		p->Load(szFoler, szFilename);
		m_mapSkinnedMesh[sFullPath] = p;
	}
	return m_mapSkinnedMesh[sFullPath];
}

void cSkinnedMeshManager::Destroy()
{
	for (auto it : m_mapSkinnedMesh)
	{
		it.second->Destroy();
		SAFE_DELETE(it.second);
	}
}
