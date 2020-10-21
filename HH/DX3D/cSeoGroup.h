#pragma once
#include "tObject.h"

class cGeomObject;

class cSeoGroup :
	public tObject
{
public:
	int							MAX_ASCIIXPORT;
	std::string					Comment;
	Scene						m_scene;
	std::vector<cGeomObject*>	m_vecGeomObject;
	std::vector<Material*>		m_vecMtlObject;
	std::vector<D3DMATERIAL9>	m_vecMtl;
	std::vector<LPDIRECT3DTEXTURE9>	m_vecPTexture;
public:
	
	cSeoGroup();
	~cSeoGroup();
	void Setup();
	void Render();
};

