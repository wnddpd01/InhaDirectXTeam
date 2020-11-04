#pragma once
#include "EventManager.h"

class MouseInputManager : public EventManager
{
public:
	HRESULT CreateDevice(HWND hWnd);
	HRESULT ReadDate();
	VOID FreeDirectInput();
	void OnActivate(WPARAM wParam);
	BOOL PushLeft();
	BOOL PushRight();
	BOOL PushMiddle();
	
private:
	LPDIRECTINPUT8 mDI;
	LPDIRECTINPUTDEVICE8 mMouse;
	DIMOUSESTATE2 mMouseState2;
	HWND mHWnd;
	POINT mMouseFrameDistance;
};

