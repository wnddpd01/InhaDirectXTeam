#pragma once
#include "Object.h"
#include "cMtlTex.h" // << : 

class Group :
	public Object
{
public:
	Group();
	~Group();
private:
	Synthesize_Pass_by_Ref(std::vector<Vertex>, m_vecVertex, vertex);
	Synthesize_Add_Ref(cMtlTex*, m_pMtlTex, MtlTex);
	
public:
	void Render();
};

