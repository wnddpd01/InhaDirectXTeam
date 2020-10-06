#pragma once

class cCubePC;

class cLight
{
public:
	cLight();
	~cLight();
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	D3DLIGHT9 m_Light[3];

	cCubePC* m_pSLC;
	cCubePC* m_pPLC;

public:
	void Setup();
	void Update();
	void Render();

};

