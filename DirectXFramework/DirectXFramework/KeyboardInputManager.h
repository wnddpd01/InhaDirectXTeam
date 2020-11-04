#pragma once
#include "EventManager.h"

class KeyboardInputManager : public EventManager
{
public:	
	
	
private:
	LPDIRECTINPUT8		 mDI;
	LPDIRECTINPUTDEVICE8 mKeyboard;
	HWND				 mHWnd;
	BYTE				 mKeys[256];
	
	bool PressUpKey();
	bool PressDownKey();
	bool PressLeftKey();
	bool PressRightKey();
};

