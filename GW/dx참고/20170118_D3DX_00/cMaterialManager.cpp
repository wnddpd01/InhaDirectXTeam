#include "stdafx.h"
#include "cMaterialManager.h"


cMaterialManager::cMaterialManager()
{
}


cMaterialManager::~cMaterialManager()
{
}

void cMaterialManager::AddMaterial(string _key, ST_MATERIAL _Mtrl)
{
	m_mapMaterial[_key] = _Mtrl;
}

void cMaterialManager::AddMaterial(string _key, string _tex, D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s)
{
	ST_MATERIAL mNewMtrl;
	mNewMtrl.mtrl = InitMtrl(a, d, s);
	mNewMtrl.stexkey = _key;

	g_pTextureManager->AddTexture(_key, _tex);

	m_mapMaterial[_key] = mNewMtrl;
}
