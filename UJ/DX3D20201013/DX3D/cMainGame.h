#pragma once
class cMtlTex;
class cFrame;
class cCubePC; 
class cCamera; 
class cGrid; 
class cCubeMan; 
class cGroup;
class cMesh;
class cTerrain;

struct BasicObject
{
	D3DMATERIAL9 m_mtl;
	LPD3DXMESH	 m_pMesh;
	D3DXVECTOR3  m_pos;
	float		 m_fScale;
	D3DXMATRIXA16 m_matWorld;

	BasicObject()
	{
		ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
		m_pos = { 0, 0, 0 };
		m_fScale = 1;
		D3DXMatrixIdentity(&m_matWorld);
	}
};


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
	D3DXVECTOR3				m_vecPos;
	D3DXVECTOR3				m_vecDir;
	D3DXVECTOR3*            m_pVecTargetPos;
	vector<cFrame*>			m_vecPFrame;
	LPD3DXFONT				m_font;
	cTerrain*				m_pTerrain;
public :
	void Setup();
	void InputProcess();
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
	LPD3DXMESH	 m_pMeshTeapot;
	LPD3DXMESH	 m_pMeshSphere;
	D3DMATERIAL9 m_stMtlTeapot;
	D3DMATERIAL9 m_stMtlSphere;
	D3DMATERIAL9 m_stMtlSelectedSphere;
	LPD3DXMESH	 m_pObjMesh;
	vector<cMtlTex*> m_vecObjMtlTex;
	vector<BasicObject*>	m_vecObject;
	vector<ST_SPHERE> m_vecSphere;
	D3DMATERIAL9	  m_stMtlNone;
	D3DMATERIAL9	  m_stMtlPicked;
	D3DMATERIAL9	  m_stMtlPlane;
	vector<ST_PN_VERTEX> m_vecPlaneVertex;
	D3DXVECTOR3		  m_vPickedPosition;
public :
	void Setup_MeshObject();
	void Mesh_Render();

	void Setup_PickingObj();
	void PickingObj_Render();
};

