#pragma once

class cPyramid;

class cGrid
{
public:
	cGrid();
	~cGrid();
private:
	std::vector<ST_PN_VERTEX>	m_vecVertex;
	std::vector<cPyramid*>		m_vecPyramid;
public:
	void Setup(int nNumHalfTile = 50, float fInterval = 0.4f);
	void Render();
};

