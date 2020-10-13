#pragma once
#include "iMap.h"

class cObjMap : public cObject, public iMap
{
private:
	vector<D3DXVECTOR3> m_vecVertex;
	float		m_fDistance;

public:

private:
public:
	cObjMap();
	~cObjMap();

	virtual void Load(char* szFilePath, D3DXMATRIXA16* pMat);
	virtual bool GetHeight(IN const float& x, OUT float& y, IN const float& z);
	virtual float GetDistance() { return m_fDistance; }

};

