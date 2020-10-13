#pragma once

#define g_pTextureManager tTextureManager::GetInstance()

class tTextureManager
{
	Singletone(tTextureManager);
private:
	
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;

public:
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string &sFullPath);
	void Destroy();
};

