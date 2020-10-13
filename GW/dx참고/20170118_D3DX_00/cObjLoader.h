#pragma once


class cMtrlTex;
class cGeometry;

class cObjLoader : public cObject
{
private:
	map<string, cMtrlTex*> m_mapMtrlTex;
public:


private:
	void LoadMtlLib(char* szFilePath);

public:
	cObjLoader();
	~cObjLoader();

	void Load(IN char* szFilePath, IN D3DXMATRIXA16* pMat,
		OUT vector<cGeometry*>& vecGeometry);
	LPD3DXMESH Load(IN char* szFilePath, IN D3DXMATRIXA16* pMat);
};

