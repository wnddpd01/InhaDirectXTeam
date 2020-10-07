#pragma once
class cCubeMan;
class cPyramid;

class cBPath
{
public:
	cBPath();
	~cBPath();

private:
	std::vector<ST_PN_VERTEX> m_vecVertex;

public:
	void Setup();
	void Render();
	void resurlt();
};

