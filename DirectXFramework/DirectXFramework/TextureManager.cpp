#include "stdafx.h"
#include "TextureManager.h"


LPDIRECT3DTEXTURE9 TextureManager::GetTexture(char * szFullPath)
{
	if (mTextureContainer.find(szFullPath) == mTextureContainer.end())
	{
		D3DXCreateTextureFromFileA(gD3Device, szFullPath, &mTextureContainer[szFullPath]);
	}
	return mTextureContainer[szFullPath];
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(std::string & sFullPath)
{
	return GetTexture((char*)sFullPath.c_str());
}

void TextureManager::Destroy()
{
	for each(auto it in mTextureContainer)
	{
		SafeRelease(it.second);
	}
	mTextureContainer.clear();
}
