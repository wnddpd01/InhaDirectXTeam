#pragma once
class cbodyCube;

class cCharactor
{
public:
	cCharactor();
	~cCharactor();

private:
	D3DXVECTOR3					m_vDirection;
	D3DXVECTOR3					m_vBody;
	D3DXMATRIXA16				m_matWorld;
	float						m_fRotY;
	std::vector<cBodyCube*>		parts;
	bool						m_Move = false;

public:
	void Update();
	void Setup();
	void Render();

	D3DXVECTOR3& GetPosition();
	void MoveOnOff(bool triger);
};

