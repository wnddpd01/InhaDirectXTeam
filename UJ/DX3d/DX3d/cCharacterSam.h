#pragma once
class cCharacterSam
{
public:
	cCharacterSam();
protected:
	float m_fRotY;
	D3DXVECTOR3 m_vDirection;
	D3DXVECTOR3 m_vPosition;
	D3DXMATRIXA16 m_matWorld;
public :
	virtual  ~cCharacterSam();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void SetPosition(D3DXVECTOR3& newPos);
	virtual D3DXVECTOR3& GetPosition();
	
};

