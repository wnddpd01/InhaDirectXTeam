#pragma once

#define g_pSkinnedMeshManger cSkinnedMeshManager::GetInstance()
class cSkinnedMesh;

class cSkinnedMeshManager
{
private:
	map<string, cSkinnedMesh*> m_mapSkinnedMesh;
public:
	Singletone(cSkinnedMeshManager);

	cSkinnedMesh* GetSkinnedMesh(char* szFoler, char* szFilename);
	void Destroy();
	
};

