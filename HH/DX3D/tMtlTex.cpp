#include "stdafx.h"
#include "tMtlTex.h"


tMtlTex::tMtlTex()
	: m_pTexture(NULL)
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
}


tMtlTex::~tMtlTex()
{
	SafeRelease(m_pTexture);
}
