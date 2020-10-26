#pragma once
#include "iMap.h"
class cObjMap :
	public iMap
{
private :
	vector<D3DXVECTOR3> m_vecSurface; 
public:
	cObjMap(IN char * szFolder, IN char* szFile, IN D3DXMATRIXA16* pmat = NULL); 
	~cObjMap();

	void Load(IN char* szFolder , IN char* szFile , IN D3DXMATRIXA16* pmat = NULL);

	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override; 

};

