#pragma once
class cUI
{
public:
	cUI();
	~cUI();

private:
	LPD3DXSPRITE	m_pSprite;

	
	vector<D3DXIMAGE_INFO>m_stImageInfo;

	
	vector<LPDIRECT3DTEXTURE9> m_pTextureUI;


	LPDIRECT3DTEXTURE9 m_click;

	vector<RECT> m_rc;


	LPD3DXFONT	m_pFont;

	int m_ifont;

	bool m_isLButtonDown;

	POINT m_box;
	POINT temp;
	
public:
	void Setup_UI();
	void UI_Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Create_Font();
	void Text_Render();

	void Destroy();
	
};

