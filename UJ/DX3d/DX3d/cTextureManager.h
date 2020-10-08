#pragma once
class cTextureManager
{
private:
	Singleton(cTextureManager);
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;
public :
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(string & sFullpath);
	void Destroy();
};

#define g_pTextureManger cTextureManager::GetInstance()

