#pragma once
#include "EventManager.h"
#include "Singleton.h"

#define gMouseInputManager MouseInputManager::GetInstance()

class MouseInputManager : public Singleton<MouseInputManager>
{
public:
	//BOOL DownLeftButton(POINT * const outPosition);
	//BOOL DownRightButton(POINT * const outPosition);
	//BOOL DownWheelButton(POINT * const outPosition);
	//BOOL UpRightButton(POINT * const outPosition);
	//BOOL UpLeftButton(POINT * const outPosition);
	//BOOL DragLeftButton(POINT * const outPosition);
	//BOOL DragRightButton(POINT * const outPosition);
	//BOOL MoveMouse(POINT * const outPosition);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//void Update();
private:
	//eEventName mMouseState;
	//POINT prevMousePosition;
	bool mbLButtonDown;
	bool mbRButtonDown;
};
