#include "stdafx.h"
#include "tTextureManager.h"


tTextureManager::tTextureManager()
{
}


tTextureManager::~tTextureManager()
{
}

LPDIRECT3DTEXTURE9 tTextureManager::GetTexture(char* szFullPath)
{
	if(m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileA(g_pD3DDevice, szFullPath, &m_mapTexture[szFullPath]);
	}

	return m_mapTexture[szFullPath];
}


LPDIRECT3DTEXTURE9 tTextureManager::GetTexture(std::string& sFullPath)
{
	return GetTexture((char*)sFullPath.c_str());
}


void tTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SafeRelease(it.second);
	}
	m_mapTexture.clear();
}
