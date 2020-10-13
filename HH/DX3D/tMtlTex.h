#pragma once
#include "tObject.h"
class tMtlTex :
	public tObject
{
public:
	tMtlTex();
	~tMtlTex();

private:
	Synthesize_pass_by_Ref(D3DMATERIAL9, m_stMtl, Material);
	Synthesize_Add_Ref(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	
};