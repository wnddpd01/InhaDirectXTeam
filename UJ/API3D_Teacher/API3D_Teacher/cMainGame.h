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
	vector<cVector3>	m_vecLineVertex;	//���� ������
	cVector3			m_vPosition;	//�ڽ� ��ġ
	POINT				m_ptPrevMouse;	//���콺 ������ġ
	bool				m_isLButtonDown;	//���콺�� ���ȴ���
	float				m_fCameraDist;	//ī�޶� �Ÿ�

	cVector3			m_vCamRotAngle;		//ī�޶� ȸ��
	cVector3			m_vAxisXTextPosition;	//���ڿ� �����ġ
	cVector3			m_vAxisZTextPosition;

	float				m_fBoxRotY;			//�ڽ� ȸ����
	cVector3			m_vBoxDirection;	//�ڽ��� ����
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

