#include "stdafx.h"
#include "cMtrlTex.h"


cMtrlTex::cMtrlTex()
	: m_pTexture(NULL)
{
	ZeroMemory(&m_stMtrl, sizeof(D3DMATERIAL9));
}



cMtrlTex::~cMtrlTex()
{
	SAFE_RELEASE(m_pTexture);
}
