#pragma once
#include "EventManager.h"
#include "Singleton.h"

#define gMouseInputManager MouseInputManager::GetInstance()

class MouseInputManager : public Singleton<MouseInputManager>
{
public:
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	bool mbLButtonDown;
	bool mbRButtonDown;
};
