#pragma once
class cCube
{
public:
	cCube();
	~cCube();

private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	float						m_fRotY;
	D3DXVECTOR3					m_vDirection;
	D3DXVECTOR3					m_vPosition;

	D3DXMATRIXA16				m_matWorld;

public:
	void Setup();
	void Update();
	void Render();
	D3DXVECTOR3&				GetPosition();


};

