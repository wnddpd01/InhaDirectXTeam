#pragma once

#include "Singleton.h"

#define gTextureManager TextureManager::GetInstance()

class TextureManager : public Singleton<TextureManager>
{
	~TextureManager();
private :
	map<std::string, LPDIRECT3DTEXTURE9> mTextureMap; 

public : 
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath); 
	LPDIRECT3DTEXTURE9 GetTexture(std::string & sFullPath); 
	void Destroy();
};

