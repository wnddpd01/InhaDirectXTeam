#pragma once
#include "Singleton.h"
#define gTextureManager TextureManager::GetInstance()


class TextureManager : public Singleton<TextureManager>
{
private:
	std::map<std::string, LPDIRECT3DTEXTURE9> mTextureContainer;

public:
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string & sFullPath);
	void Destroy();
	
	
};

