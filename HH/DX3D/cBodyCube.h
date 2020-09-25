#pragma once
class cBodyCube
{
public:
	cBodyCube(D3DXMATRIXA16* BodyWorld, 
		D3DXVECTOR3 Position2Body, 
		D3DXVECTOR3 Scale,
		D3DXVECTOR3 moveCenter = D3DXVECTOR3(0.f, 0.f, 0.f),
		bool moveReverse = false
	);
	~cBodyCube();

private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	float						m_fRotY;
	//D3DXVECTOR3*				m_vDirection;
	//D3DXVECTOR3*				m_v_pBodyPosition;
	D3DXMATRIXA16				m_matScale;
	D3DXMATRIXA16				m_matChageCenter;
	D3DXVECTOR3					m_vPosition2Body;
	//D3DXVECTOR3				m_vRotateCenter;
	D3DXMATRIXA16*				m_matWorld;
	bool						m_move = false;
	bool						m_moveReverse = false;

public:
	
	void Setup();
	void Update();
	void Render();

	void MoveCenter(D3DXVECTOR3 move);
	void OnMove(bool move);
};

