#pragma once
#include "cGeometry.h"


class cMtrlTex;

class cAseLoader : public cObject
{
private:
	vector<cMtrlTex*> m_vecMtrlTex;
public:


private:

public:
	cAseLoader();
	~cAseLoader();

	void Load(IN const char* _szFilePath, OUT cGeometry*& _pGeometry, OUT ST_ASE_SCENE& _stScene);
};

