#pragma once
class cCubePC;
class cCamera;
class cGrid;
class cCubeMan;
class cObject;

class cGroup;

class cLight;
class cBPath;
class cFrame;
class cMtlTex;

class cRay;

struct BoundingSphere
{
	D3DXVECTOR3 _center;
	float _radius;
	bool _check = false;
};


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

	cFrame* m_pRootFrame;
	
	LPD3DXFONT m_pFont;
	D3DXFONT_DESC fd;
	
	cRay* m_pRay;


	
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


// mesh
private:
	LPD3DXMESH m_pMeshTeapot;
	LPD3DXMESH m_pMeshSphere;

	
	D3DMATERIAL9 m_stMtlTeapot;
	D3DMATERIAL9 m_stMtlSphere;

	BoundingSphere bs[6];

	LPD3DXMESH m_pObjMesh;
	std::vector<cMtlTex*> m_vecObjMtlTex;

	
public:
	void Setup_MeshObject();
	void Mesh_Render();


public:
	
	
	struct Ray
	{
		D3DXVECTOR3 _origin;
		D3DXVECTOR3 _direction;
	};

	Ray CalcPickingRay(int x, int y);
	void TransformRay(Ray* ray, D3DXMATRIX* T);




	bool raySphereIntersectionTest(Ray* ray, BoundingSphere* sphere);




	
};

