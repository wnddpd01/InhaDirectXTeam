#pragma once
class cSeoGroup;

class cSeoLoader
{
private:

public:
	cSeoLoader();
	~cSeoLoader();

	void Load(OUT std::vector<cSeoGroup*> & vecGeomObject, IN char* szFolder, IN char* szFile);
	void LoadMtlLib(char* szFolder, char* szFile);
};

