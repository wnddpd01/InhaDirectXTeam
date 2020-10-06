#pragma once

class cCubePC;
class cCamera;
class cGrid;
class cPyramid;
class cCharacter;
class cCubeMan;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	//vector<ST_PC_VERTEX>	m_vecLineVertex;
	//vector<ST_PC_VERTEX>	m_vecTriangleVertex;

	//vector<ST_PC_VERTEX>	m_vecGizmo;

	//vector<D3DXVECTOR3>		m_vecBoxVertex;
	//vector<DWORD>			m_vecBoxIndex;
	//vector<D3DXVECTOR3>		m_vecGridIndex;
	//vector<ST_PC_VERTEX>	m_vecGridVertex;		//���� ������
	//D3DXVECTOR3				m_vPosition;			//�ڽ� ��ġ

	//POINT				m_ptPrevMouse;				//���콺 ������ġ
	//bool				m_isLButtonDown;			//���콺�� ���ȴ���
	//float				m_fCameraDist;				//ī�޶� �Ÿ�

	//D3DXVECTOR3			m_vCamRotAngle;				//ī�޶� ȸ��
	//float				m_fBoxRotY;					//�ڽ� ȸ����
	//D3DXVECTOR3			m_vBoxDirection;			//�ڽ��� ����
	cCubePC * m_pCubePc;
	cCharacter * m_pCharacter;
	cCubeMan * m_pCubeMan;
	cCamera * m_pCamera;
	cGrid   * m_pGrid;

	/*LPDIRECT3DTEXTURE9 m_pTextrue;
	vector<ST_PT_VERTEX> m_vecVertex;*/

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();
	//void Setup_Line();
	//void Draw_Line();
	//void Setup_Triangle();
	//void Draw_Triangle();

	//void Setup_Box();
	//void Setup_Grid();
	//void Setup_Gzimo();
	//void Draw_Gzimo();
	//void Draw_Grid();
	//void Update_Move();
	//void Update_Rotation();
};

