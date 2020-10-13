#pragma once

#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
	SINGLETON(cTextureManager)

private:
	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;
public:

private:
public:
	void AddTexture(string key, string fileName);
	void Destroy();
	LPDIRECT3DTEXTURE9& GetTexture(string key) { return m_mapTexture[key]; }
};

