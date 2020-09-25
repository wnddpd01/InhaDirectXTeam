#pragma once

class cCubePC;

class cCharacter
{
	vector<cCubePC *> character_body_vector_;
	float				 m_fRotY;
	float				 m_fRotX;
	D3DXVECTOR3		     m_vDirection;
	D3DXVECTOR3			 m_vPosition;
	D3DXMATRIXA16		 m_matWorld;
	vector<float> animation_dir;
	bool isMoved;
public:
	cCharacter();
	~cCharacter();

public :
	void KeyInput();
	void Setup();
	void Update();
	void UpdateIdle();
	void UpdateSwing();
	void Render();
	D3DXVECTOR3& GetPosition();
};

