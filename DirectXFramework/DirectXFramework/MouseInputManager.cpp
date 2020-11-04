#include "stdafx.h"
#include "MouseInputManager.h"

extern HWND hWnd;

BOOL MouseInputManager::DownLeftButton(POINT* const outPosition)
{
	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		GetCursorPos(outPosition);
		ScreenToClient(hWnd, outPosition);
		bMouseLbuttonDown = true;
		return true;
	}
	else
	{
		bMouseLbuttonDown = false;
		return false;
	}
	
}


BOOL MouseInputManager::DownRightButton(POINT* const outPosition)
{
	if (GetKeyState(VK_RBUTTON) & 0x8000)
	{
		GetCursorPos(outPosition);
		ScreenToClient(hWnd, outPosition);
		return true;
	}
	
	return false;
}

BOOL MouseInputManager::UpLeftButton(POINT* const outPosition)
{
	
	static bool bPrivMouseLButton;
	bool bCurMouseLButton;

	bCurMouseLButton = GetKeyState(VK_LBUTTON) & 0x8000;
	
	if (bPrivMouseLButton == TRUE && bCurMouseLButton == FALSE)
	{
		GetCursorPos(outPosition);
		ScreenToClient(hWnd, outPosition);
		bPrivMouseLButton = bCurMouseLButton;
		return true; 
	}

	bPrivMouseLButton = bCurMouseLButton;
	return false;
}

//BOOL MouseInputManager::MoveMouse(POINT* const outPosition)
//{
//	static POINT privMousePosition;
//	POINT curMousePosition;
//
//	GetCursorPos(&curMousePosition);
//
//	
//	if (curMousePosition.x == privMousePosition.x && curMousePosition.y == privMousePosition.y)
//	{
//		return false;
//	}
//	
//	
//
//	return true;
//}
