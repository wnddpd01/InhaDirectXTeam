#pragma once
class cCubePC;
class cCamera;
class cGrid;
class cKids;
class cCubeMan;
class cLight;

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

	// >>: for texture
	//LPDIRECT3DTEXTURE9 m_pTexture;
	std::vector<ST_PT_VERTEX> m_vecVertx;
	// <<:
	
	
public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Set_Light();

	void Draw_Texture();
};

