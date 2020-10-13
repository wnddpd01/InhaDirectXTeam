#pragma once
class cMtlTex;
class cGroup;
class cCubeNode;

class cAseLoader
{
protected:
	void LoadMaterial(FILE* fp);
	void LoadGeomObject(FILE* fp);
	std::map< std::string, cMtlTex* > m_mapMtlTex;
	std::map< std::string, cCubeNode* > m_mapCubeNode;
public :
	void Load(OUT std::vector<cGroup*>& vecGroup, IN char* szFolder, IN char* szFile);
};

