#pragma once
class CFrustum
{
public:
	CFrustum();
	~CFrustum();

private:
	LPD3DXMESH m_pMeshSphere;
	vector<ST_SPHERE> m_vecSphere;
	D3DMATERIAL9 m_stMtlNone;

	D3DXVECTOR3 m_vecVertex;
	D3DXVECTOR3 m_vecVertex2;



	
	
public:
	void Setup_Object();
	void Render_Object();

	void Setup();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
};


