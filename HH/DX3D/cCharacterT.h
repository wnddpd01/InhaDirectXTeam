#pragma once
class cCharacterT
{
public:
	cCharacterT();
	//~cCharacterT();
protected:
	float			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;

public:
	virtual ~cCharacterT(void);

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual D3DXVECTOR3& GetPosition();
};

