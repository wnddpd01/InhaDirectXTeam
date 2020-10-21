#pragma once
class cCubePNT
{
public:
	cCubePNT();
protected:
public:
	std::vector<ST_PNT_VERTEX> m_vecVertex;
	virtual ~cCubePNT();
	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

