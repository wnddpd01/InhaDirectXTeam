#pragma once
class cTerrain
{
public:
	cTerrain();
	~cTerrain();
private:
	float m_aMapVertex[257][257];
public:
	bool readRawFile(char* filename);
};

