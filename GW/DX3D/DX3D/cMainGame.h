#pragma once
class cCubePC;
class cCamera;
class cGrid;
class cCubeMan;
class cObject;

class cGroup;

class cLight;
class cBPath;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();


private:

	std::vector<ST_PC_VERTEX> m_vecLineVertex;
	std::vector<ST_PC_VERTEX> m_vecTriangleVertex;


	cCubePC* m_pCubePC;
	cCamera* m_pCamera;
	cGrid* m_pGrid;
	
	cCubeMan* m_pCubeMan;
	
	cLight* m_pLight;
	cBPath* m_pBPath;

	std::vector<cGroup*> m_vecGroup;
	iMap* m_pMap;
	
public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Set_Light();

	void Draw_Texture();

	void Setup_Obj();
	void Obj_Render();

	void Load_Surface();
	
};

