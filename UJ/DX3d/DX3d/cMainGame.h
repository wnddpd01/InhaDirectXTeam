#pragma once

class cCubeNode;
class cBox;
class cCubeAutoMan;
class cHexagon;
class cCubePC;
class cCamera;
class cGrid;
class cPyramid;
class cCharacter;
class cCubeMan;
class cGroup;
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
	//vector<ST_PC_VERTEX>	m_vecGridVertex;		//선의 정점들
	//D3DXVECTOR3				m_vPosition;			//박스 위치

	//POINT				m_ptPrevMouse;				//마우스 이전위치
	//bool				m_isLButtonDown;			//마우스가 눌렸는지
	//float				m_fCameraDist;				//카메라 거리

	//D3DXVECTOR3			m_vCamRotAngle;				//카메라 회전
	//float				m_fBoxRotY;					//박스 회전량
	//D3DXVECTOR3			m_vBoxDirection;			//박스의 방향
	cCubePC * m_pCubePc;
	cHexagon * m_hexagon;
	cCharacter * m_pCharacter;
	cCubeMan * m_pCubeMan;
	cCubeAutoMan * m_pCubeAutoMan;
	cCamera * m_pCamera;
	cGrid   * m_pGrid;
	cBox    * m_pBox;

	vector<cGroup *> m_vecMap;
	vector<cGroup *> m_vecMapSurface;
	cCubeNode * m_pCubeNode;
	/*LPDIRECT3DTEXTURE9 m_pTextrue;
	vector<ST_PT_VERTEX> m_vecVertex;*/

public:
	void Setup();
	void KeyInput();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void ObjectCreator(string obj_file_name = "./box.obj");
	void Set_Light();
	void Setup_Obj();
	void Setup_Ase();
	void Obj_Render();
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

