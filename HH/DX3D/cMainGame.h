#pragma once
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
};

