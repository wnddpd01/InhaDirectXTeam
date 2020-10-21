#pragma once
#include "cCubePNT.h"
class cBox :
	public cCubePNT
{
public:
	LPDIRECT3DTEXTURE9 m_pTextrue;
	D3DMATERIAL9 m_stMtl;
	cBox();
	~cBox();

	void Render() override;
};

