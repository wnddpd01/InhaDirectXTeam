#pragma once

enum animation_state
{
	animation_idle, animation_run, animation_naruto
};

class cCubePC;

class cCharacter
{
	vector<cCubePC *> character_body_vector_;
	float				 m_fRotY;
	float				 m_fRotX;
	float				 m_spd;
	D3DXVECTOR3		     m_vDirection;
	D3DXVECTOR3			 m_vPosition;
	D3DXMATRIXA16		 m_matWorld;
	animation_state animation_state_;
public:
	cCharacter();
	~cCharacter();

public :
	void KeyInput();
	void Setup();
	void Update();
	void UpdateIdle();
	void UpdateSwing();
	void UpdateNarutoRun();
	void Render();
	void ChangeAnimation(animation_state animation_state);
	D3DXVECTOR3& GetPosition();
};

