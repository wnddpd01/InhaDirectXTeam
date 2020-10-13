#pragma once

#define g_pMaterialManager		cMaterialManager::GetInstance()

struct ST_MATERIAL
{
	D3DMATERIAL9	mtrl;
	string			stexkey;
};

class cMaterialManager
{
	SINGLETON(cMaterialManager)

private:
	map<string, ST_MATERIAL> m_mapMaterial;
public:


private:
public:
	void AddMaterial(string _key, ST_MATERIAL _Mtrl);
	void AddMaterial(string _key, string _tex, D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s);
	D3DMATERIAL9&	GetMaterial(string _key) { return m_mapMaterial[_key].mtrl; }
	string&			GetTexture(string _key) { return m_mapMaterial[_key].stexkey; }
};

