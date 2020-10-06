#pragma once



class cLight
{
public:
	cLight();
	~cLight();
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	D3DLIGHT9 stLight[3];
	float temp_range;

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

