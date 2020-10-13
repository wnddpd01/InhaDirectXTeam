#pragma once

class tMtlTex;
class tGroup;

class tObjLoader
{
public:
	tObjLoader();
	~tObjLoader();

private:
	std::map<std::string, tMtlTex*> m_mapMtlTex;
public:
	void Load(OUT std::vector<tGroup*> & vecGroup, IN char* szFolder, IN char* szFile);
	void LoadMtlLib(char* szFolder, char* szFile);
};

