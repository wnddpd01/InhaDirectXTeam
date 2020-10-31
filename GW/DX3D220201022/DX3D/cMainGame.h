#pragma once
class cCubePC; 
class cCamera; 
class cGrid; 
class cCubeMan; 
class cGroup; 
class cFrame; 
class cMtlTex; 
class cXfileLoader;

class cSkinnedMesh;

class CFrustum;

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


	//cXfileLoader* m_pXfileLoader;

	cSkinnedMesh* m_pSkinnedMesh;

	//cUI* m_pUI;


	LPD3DXEFFECT m_pShader;

	bool LoadAssets();
	LPD3DXEFFECT LoadShader(const char * filename);
	
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


	//>>:
	LPD3DXMESH	m_pSphere;
	D3DMATERIAL9 m_stCullingMtl;
	vector<ST_SPHERE*> m_vecCullingSphere;
	CFrustum* m_pFrustum;

	//<<:

	cZealot* m_pHoldZealot;
	cZealot* m_pMoveZealot;


	vector<ST_PC_VERTEX> m_vecVertexParticle;

	int m_nType;
	LPDIRECT3DTEXTURE9 m_pTex0;
	LPDIRECT3DTEXTURE9 m_pTex1;
	LPDIRECT3DTEXTURE9 m_pTex2;
	LPDIRECT3DTEXTURE9 m_pTex3;
	vector<ST_PT_VERTEX> m_vecVertex_Multi;
	
	
	
public :

	void Setup_MultiTexture();
	void update_MultiTexture();
	void MultiTexture_Render();


	void MultiTexture_Render1();
	void MultiTexture_Render2();
	void MultiTexture_Render3();
	void MultiTexture_Render4();
	void MultiTexture_Render5();
	void MultiTexture_Render6();
	void MultiTexture_Render7();
	void MultiTexture_Render8();
	void MultiTexture_Render9();
	void MultiTexture_Render0();
	void MultiTexture_Render_default();


	
	
	void Setup_MeshObject(); 
	void Mesh_Render(); 

	void Setup_PickingObj(); 
	void PickingObj_Render();


	void SkinnedMesh_Render();

	void Setup_HeightMap();



	//>>:
	void Setup_Frustum();
	void Frustum_Render();
	//<<:

	void Setup_OBB();
	void OBB_Render();


	void Setup_Particle();
	void Update_Particle();
	void Particle_Render();

	void SetBillboard();
	
};

