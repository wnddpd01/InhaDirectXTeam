#pragma once
class cMtlTex;
class cGroup;
class cCubeNode;

class cAseLoader
{
protected:
	void LoadMaterial(FILE* fp);
	void LoadGeomObject(FILE* fp);
	std::map< int, cMtlTex* > m_mapMtlTex;
	std::map< std::string, cCubeNode* > m_mapCubeNode;
	string rootNodeName;
public :
	void Load(OUT cCubeNode ** root_node, IN char* szFolder, IN char* szFile);
};

