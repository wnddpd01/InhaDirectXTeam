#pragma once
class cVector3;
class cMatrix;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	HDC m_MemDc;
	HBITMAP m_hOldBitmap, m_hBitmap;

	vector<cVector3> m_vecVertex;
	vector<cVector3> m_gridVertex;
	
	vector<DWORD>	m_vecIndex;
	vector<cVector3> m_gridIndex;

	cMatrix			m_matWorld;
	cMatrix			m_matView;
	cMatrix			m_matProj;
	cMatrix			m_matViewport;

	cMatrix			m_matRotationY;
	cMatrix			m_matTranslation;

	cVector3		m_vEye;
	cVector3		m_vLookat;
	cVector3		m_vUp;

	cVector3		m_translate;
	cVector3		m_rotate;
	cVector3		m_vecFront;

	//>>
	vector<cVector3>	m_vecLineVertex;	//선의 정점들
	cVector3			m_vPosition;	//박스 위치
	POINT				m_ptPrevMouse;	//마우스 이전위치
	bool				m_isLButtonDown;	//마우스가 눌렸는지
	float				m_fCameraDist;	//카메라 거리

	cVector3			m_vCamRotAngle;		//카메라 회전
	cVector3			m_vAxisXTextPosition;	//문자열 출력위치
	cVector3			m_vAxisZTextPosition;

	float				m_fBoxRotY;			//박스 회전량
	cVector3			m_vBoxDirection;	//박스의 방향
	//<<
	
public:
	void SetUp();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetGrid();
	void DrawGrid();
	void Update_Move();
	void Update_Rotation();
};

