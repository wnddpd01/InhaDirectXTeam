#include "stdafx.h"
#include "TextureManager.h"


TextureManager::~TextureManager()
{
	Destroy();
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(char * szFullPath)
{
	if (mTextureMap.find(szFullPath) == mTextureMap.end())
	{
		D3DXCreateTextureFromFileA(gD3Device, szFullPath, &mTextureMap[szFullPath]);
	}
	return mTextureMap[szFullPath];
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(std::string & sFullPath)
{
	return GetTexture((char*)sFullPath.c_str()); 
}

void TextureManager::Destroy()
{
	for each(auto it in mTextureMap)
	{
		SafeRelease(it.second); 
	}
	mTextureMap.clear();
}
