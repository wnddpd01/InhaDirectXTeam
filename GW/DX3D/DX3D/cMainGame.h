#pragma once
class cMainGame
{
public:
	cMainGame();
	~cMainGame();


private:
	std::vector<ST_PC_VERTEX> m_vecVertex;
	std::vector<ST_PC_VERTEX> m_vecLineVertex;
	std::vector<ST_PC_VERTEX> m_vecTriangleVertex;
	std::vector<ST_PC_VERTEX> m_vecGizmosVertex;

	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR3 m_vBoxDirection;
	D3DXVECTOR3 m_vCamRotAngle;
	float m_fBoxRotY;
	float m_fCameraDistance;
	D3DXMATRIXA16 matR;

	POINT m_ptPrevMouse;
	bool m_isLButtonDown;
	
	
	
public:
	void Setup();
	void Update();
	void Render();

	void Setup_Line();
	void Draw_Line();

	void Setup_Gizmos();
	void Draw_Gizmos();
	
	
	void Setup_Cube();
	void Draw_Cube();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	void Update_Rotation();
	void Update_Move();
	
};

