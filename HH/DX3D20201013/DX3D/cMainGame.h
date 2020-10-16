#pragma once
#include "cMtlTex.h"
class cCubePC; 
class cCamera; 
class cGrid; 
class cCubeMan; 
class cGroup;
class cFrame;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private :
	cCubePC*		m_pCubePC; 
	cCamera*		m_pCamera; 
	cGrid*			m_pGrid; 

	cCubeMan*		m_pCubeMan; 

	// >> : for texture 
	LPDIRECT3DTEXTURE9		m_pTexture; 
	vector<ST_PT_VERTEX>	m_vecVertex; 
	// << :

	vector<cGroup*>			m_vecGroup; 
	iMap*					m_pMap;

	cFrame*					m_pRootFrame;
	cFrame*					m_pRootFrame2;

	LPD3DXFONT m_pFont;
public :
	void Setup(); 
	void Update(); 
	void Render(); 
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 

	void Set_Light(); 

	void Setup_Texture();
	void Draw_Texture(); 

	void Setup_Obj(); 
	void Obj_Render(); 

	void Load_Surface();

private:
	LPD3DXMESH		m_pMeshTeapot;
	LPD3DXMESH		m_pMeshSphere;
	D3DMATERIAL9	m_stMtlTeapot;
	D3DMATERIAL9	m_stMtlSphere;

	LPD3DXMESH			m_pObjMesh;
	vector<cMtlTex*>	m_vecObjMtlTex;
	
	LPD3DXMESH			m_pGirlMesh;
	vector<cMtlTex*>	m_vecGirlMtlTex;
	
public:
	void Setup_MeshObject();
	void Mesh_Render();


};

