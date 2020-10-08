#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char* szFullPath)
{
	if(m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileA(g_pD3DDevice, szFullPath, &m_mapTexture[szFullPath]);
	}
	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(string& sFullpath)
{
	return GetTexture((char *)sFullpath.c_str());
}

void cTextureManager::Destroy()
{
	for (auto m_map_texture : m_mapTexture)
	{
		SafeRelease(m_map_texture.second);
	}
	m_mapTexture.clear();
}
