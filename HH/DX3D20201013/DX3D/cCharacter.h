#pragma once
class HeightMap;

class cCharacter
{
public:
	cCharacter();
	//~cCharacter();
protected :
	float			m_fRotY; 
	D3DXVECTOR3		m_vDirection; 
	D3DXVECTOR3		m_vPosition; 
	D3DXMATRIXA16	m_matWorld; 

	HeightMap*		m_pHeightMap;
	
public : 
	virtual ~cCharacter(void); 

	virtual void Setup(HeightMap* hMap);
	virtual void Update(); 
	virtual void Render(); 
	virtual D3DXVECTOR3& GetPosition();


};

