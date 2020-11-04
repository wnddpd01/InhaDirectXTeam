#pragma once
#include "EventManager.h"

class KeyboardInputManager : public EventManager
{
public:
	HRESULT CreateDevice(HWND hWnd);
	VOID	FreeDirectInput();
	void	OnActivate(WPARAM wParam); // 알트탭이 눌릴시 키 권한을 해당 프로그램에 넘김
	HRESULT	ReadData();
	BOOL	PressKey(BYTE key);

private:
	LPDIRECTINPUT8		 mDI;
	LPDIRECTINPUTDEVICE8 mKeyboard;
	HWND				 mHWnd;
	BYTE				 mKeys[256];
};

