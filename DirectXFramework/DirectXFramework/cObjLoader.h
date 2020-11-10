#pragma once

class cMtlTex;
class Group;

class cObjLoader : public BaseObject
{
public:
	cObjLoader();
	~cObjLoader();

private :
	std::map<std::string, cMtlTex* > m_mapMtlTex; 
public :
	void Load(OUT std::vector<Group*> & vecGroup, IN char* szFolder, IN char* szFile); 
	void LoadMtlLib(char* szFolder, char* szFile); 
	void LoadSurface(OUT vector<D3DXVECTOR3>& vecSurface, IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pmat = NULL); 
	LPD3DXMESH	LoadMesh(OUT vector<cMtlTex*>& vecMtlTex, IN char* szFolder, IN char* szFile);
	void Obj_Render(std::vector<Group*>& vecGroup);
};

