#pragma once
#include "iMap.h"

class cCamera;
class cHSMyCharacter;
class cGrid;
class cCharacterController;
class cGeometry;

class cMainGame
{
private:
	cCamera*				m_pCamera;
	cGrid*					m_pGrid;
	cCharacterController*	m_pCharacterController;

	vector<cGeometry*>		m_vecMap;
	iMap*					m_pMapSerface;

	LPD3DXFONT				m_pFont;

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

