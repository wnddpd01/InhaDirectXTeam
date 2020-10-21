#pragma once
#include "CasteljouMove.h"

class cCube;
class cCamera;
class cGrid;
class cCharactor;
class CasteljouMove;
class tGroup;
class cGeomObject;
class cSeoGroup;

class cCubeMan;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	std::vector<ST_PC_VERTEX>	m_vecLineVertex;
	std::vector<ST_PC_VERTEX>	m_vecTriangleVertex;
	std::vector<Object*>		m_vecObject;
	float Fov;
	D3DXVECTOR3 vEye;
	D3DXVECTOR3 vLookAt;
	D3DXVECTOR3 vUp;
	float CameraDist;

	
	std::vector<ST_PC_VERTEX>	m_vecHex;
	CasteljouMove catelMove;
	
	
	cCube*		m_pCubePC;
	cCamera*	m_pCamera;
	cGrid*		m_pGrid;
	cCharactor*	m_pCharactor;
	cCubeMan*	m_pCubeMan;
	ObjParser*  m_pBox;



	std::vector<tGroup*>		m_vecGroup;
	std::vector<tGroup*>		m_vecSurfGroup;
	
	std::vector<cGeomObject*>	m_vecGeomObject;
	std::vector<cSeoGroup*>		m_vecSeoGroup;
	std::vector<ST_PT_VERTEX>	m_vecVertex;
	
	
public:
	void Setup();
	void Update();
	void Render();

	void SetupLine();
	void DrawLine();

	void SetupTriangle();
	void DrawTriangle();

	void UpdateMove();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//»ù
	void WndProcTeacher(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();
	void Draw_Textrue();

	void Setup_Obj();
	void Obj_Render();
	
};


