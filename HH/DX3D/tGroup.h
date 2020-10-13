#pragma once
#include "tObject.h"
#include "tMtlTex.h"
//class tMtlTex;

class tGroup :
	public tObject
{
public:
	tGroup();
	~tGroup();

private:
	Synthesize_pass_by_Ref(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	Synthesize_Add_Ref(tMtlTex*, m_pMtlTex, MtlTex);
	
public:
	void Render();
};

