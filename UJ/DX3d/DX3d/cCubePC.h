#pragma once
class cCubePC
{
public:
	cCubePC();
	~cCubePC();
private :
	vector<ST_PC_VERTEX> m_vecVertex;
	float				 m_fRotY;
	float				 m_fRotX;
	D3DXVECTOR3          m_vScale;
	D3DXVECTOR3		     m_vDirection;
	D3DXVECTOR3			 m_vPosition;
	D3DXMATRIXA16		 m_matWorld;

public:
	void Setup(float width = 1.0f, float height = 1.0f, float depth = 1.0f);
	void Setup(D3DXVECTOR3& size);
	void Update();
	void Update(D3DXMATRIXA16& mat);
	void Render();
	void KeyCheck();
	D3DXVECTOR3&		GetPosition();
	float				GetRotY();
	float				GetRotX();
	D3DXVECTOR3		    GetDir();
	D3DXVECTOR3			GetScale();
	void				SetPosition(D3DXVECTOR3 pos);
	void				SetRotY(float rotY);
	void				SetRotX(float rotX);
};

