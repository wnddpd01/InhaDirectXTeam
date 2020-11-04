#pragma once
#include "EventManager.h"

class KeyboardInputManager : public EventManager
{
public:
	HRESULT CreateDevice(HWND hWnd);
	VOID	FreeDirectInput();
	void	OnActivate(WPARAM wParam); // ��Ʈ���� ������ Ű ������ �ش� ���α׷��� �ѱ�
	HRESULT	ReadData();
	BOOL	PressKey(BYTE key);

private:
	LPDIRECTINPUT8		 mDI;
	LPDIRECTINPUTDEVICE8 mKeyboard;
	HWND				 mHWnd;
	BYTE				 mKeys[256];
};

