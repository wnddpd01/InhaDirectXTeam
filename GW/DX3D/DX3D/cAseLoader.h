#pragma once

class cMtlTex;


class cAseLoader
{
public:
	cAseLoader();
	~cAseLoader();


private:
	std::vector<std::string,cMtlTex*> m_mapMtlTex;

public:
	void Load();
	void LoadMtlLib(char* szFolder, char* szFile);
};

