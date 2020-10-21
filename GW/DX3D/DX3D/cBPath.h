#pragma once
class cCubeMan;
class cPyramid;

class cBPath
{
public:
	cBPath();
	~cBPath();

private:
	std::vector<ST_PC_VERTEX> m_vecVertex;
	cCubeMan* m_pCubeMan;

public:
	void Setup();
	void Render();
	void resurlt();
};

