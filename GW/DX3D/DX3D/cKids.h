#pragma once
class cCubePC;

class cKids
{
public:
	cKids();
	~cKids();
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	float						m_fRotY;
	D3DXVECTOR3					m_vDirection;
	D3DXVECTOR3					m_vPosition;
	D3DXMATRIXA16				m_matWorld;

	std::vector<cCubePC*> m_vecKids;

	cCubePC* m_pBody;
	cCubePC* m_pHead;
	cCubePC* m_prLeg;
	cCubePC* m_plLeg;
	cCubePC* m_prArm;
	cCubePC* m_plArm;

public:
	void Setup();
	void Update();
	void Render();
	D3DXVECTOR3& GetPosition();

};

