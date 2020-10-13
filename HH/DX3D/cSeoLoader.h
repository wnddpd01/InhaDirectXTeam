#pragma once
class cGeomObject;

class cSeoLoader
{
private:

public:
	cSeoLoader();
	~cSeoLoader();

	void Load(OUT std::vector<cGeomObject*> & vecGeomObject, IN char* szFolder, IN char* szFile);
	void LoadMtlLib(char* szFolder, char* szFile);
};

