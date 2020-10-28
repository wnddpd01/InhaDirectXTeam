#pragma once
class cBigShip;
class cCubePC; 
class cCamera; 
class cGrid; 
class cCubeMan; 
class cGroup; 
class cFrame; 
class cMtlTex;
class cSkinnedMesh;
class cZealot;
class cUI;

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

	cZealot*				m_pHoldZealot;
	cZealot*				m_pMoveZealot;
	
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

private :
	LPD3DXMESH		m_pMeshTeapot; 
	LPD3DXMESH		m_pMeshSphere; 
	D3DMATERIAL9	m_stMtlTeapot; 
	D3DMATERIAL9	m_stMtlSphere; 

	LPD3DXMESH			m_pObjMesh; 
	vector<cMtlTex*>	m_vecObjMtlTex; 

	vector<ST_SPHERE>	m_vecSphere; 
	D3DMATERIAL9		m_stMtlNone;
	D3DMATERIAL9		m_stMtlPicked; 
	D3DMATERIAL9		m_stMtlPlane; 
	vector<ST_PN_VERTEX>	m_vecPlaneVertex; 
	D3DXVECTOR3			m_vPickedPosition; 
	cBigShip*			m_pBigShip;
	cSkinnedMesh*		m_pSkinnedMesh;

	LPD3DXFONT			m_font;
	ID3DXMesh*			m_p3DText;
	LPD3DXSPRITE		m_pSprite;
	D3DXIMAGE_INFO		m_stImageInfo;
	LPDIRECT3DTEXTURE9	m_pTextureUI;
	vector<cUI*>		m_vecUI;
public :
	void Setup_MeshObject(); 
	void Mesh_Render(); 

	void Setup_PickingObj(); 
	void PickingObj_Render(); 

	void SkinnedMesh_Render();
	void Setup_HeightMap();

	void Setup_OBB();
	void OBB_Render();

	void Create_Font();
	void Text_Render();

	void Setup_UI();
	void UI_Render();
};

