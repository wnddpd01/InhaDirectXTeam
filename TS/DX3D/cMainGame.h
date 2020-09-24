#pragma once
class cMainGame
{
public:
	cMainGame();
	~cMainGame();
private:
	vector<ST_PC_VERTEX> m_vecLineVertex;
	vector<D3DXVECTOR3> m_vecLineVertexP;
	vector<ST_PC_VERTEX> m_vecGizmo;
	vector<D3DXVECTOR3> m_vecGizmoP;
	vector<ST_PC_VERTEX> m_vecTriangleVertex;
	vector<D3DXVECTOR3> m_vecVertex;
	vector<DWORD> m_GizmoIndex;
	vector<DWORD> m_vecIndex;
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vDirection;
	D3DXVECTOR3 vEye;
	D3DXVECTOR3 vLookAt;
	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matTrans;
	
	D3DXVECTOR3 m_vCamRotAngle;
	POINT m_ptPrevMouse; // 이전 위치
	bool m_isLButtonDown;// 마우스가 눌렸냐
	float m_fCameraDistance; // 카메라의 거리
	
	float Angle = 0;
	
public:
	void Setup();
	void Update();
	void Render();
	void Cleanup();

	void Setup_Line();
	void Draw_Line();

	void Setup_Triangle();
	void Draw_Triangle();
	
	void Update_Move();
	void Update_Rotation();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	
};

