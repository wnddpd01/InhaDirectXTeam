#pragma once

#define g_pSkinnedMeshManger cSkinnedMeshManager::GetInstance()
class cSkinnedMesh;

class cSkinnedMeshManager : public Singleton<cSkinnedMeshManager>
{
private:
	map<string, cSkinnedMesh*> m_mapSkinnedMesh;
public:

	cSkinnedMesh* GetSkinnedMesh(char* szFoler, char* szFilename);
	void Destroy();
	
};

