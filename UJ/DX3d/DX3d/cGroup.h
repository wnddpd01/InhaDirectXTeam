#pragma once

#include "cMtlTex.h"
#include "cObject.h"
class cGroup :
	public cObject
{
public:
	cGroup();
	~cGroup();
	Synthesize_pass_by_Ref(std::vector<ST_PNT_VERTEX>, m_vecVertex, VerTex);
	Synthesize_Add_Ref(cMtlTex*, m_pMtlTex, MtlTex);
private :

public :
	void Render();
};

