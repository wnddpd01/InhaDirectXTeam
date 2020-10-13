#pragma once


class cMtrlTex : public cObject
{

private:
	SYNTHESIZE_PASS_BY_REF(D3DMATERIAL9, m_stMtrl, Mtrl)
	SYNTHESIZE_ADD_REF(LPDIRECT3DTEXTURE9, m_pTexture, Texture)

public:
	cMtrlTex();
	~cMtrlTex();
};

