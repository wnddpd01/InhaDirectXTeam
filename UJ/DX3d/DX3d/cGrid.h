#pragma once

class cPyramid;

class cGrid
{
public:
	cGrid();
	~cGrid();
private:
	vector<ST_PN_VERTEX>	m_vecVertex;
	vector<cPyramid *>		m_vecPyramid;
	D3DMATERIAL9 m_stMtl;
public :
	void Setup(int nNumHalfTime = 15, float fInterval = 1.0f);
	void Render();
};

