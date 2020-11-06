#include "stdafx.h"
#include "MouseInputManager.h"

extern HWND hWnd;

BOOL MouseInputManager::DownLeftButton(POINT* const outPosition)
{
	bool bCurMouseLButton = GetKeyState(VK_LBUTTON) & 0x8000;

	if (bCurMouseLButton)
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
	bool bCurMouseLButton = GetKeyState(VK_LBUTTON) & 0x8000;

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

BOOL MouseInputManager::DownRightButton(POINT* const outPosition)
{
	static bool bPrivMouseRButton;
	bool bCurMouseRButton = GetKeyState(VK_RBUTTON) & 0x8000;
	
	if (bCurMouseRButton)
	{
		GetCursorPos(outPosition);
		ScreenToClient(hWnd, outPosition);
		return true;
	}
	
	return false;
}

BOOL MouseInputManager::UpRightButton(POINT* const outPosition)
{
	static bool bPrivMouseRButton;
	bool bCurMouseRButton = GetKeyState(VK_LBUTTON) & 0x8000;

	if (bPrivMouseRButton == TRUE && bCurMouseRButton == FALSE)
	{
		GetCursorPos(outPosition);
		ScreenToClient(hWnd, outPosition);
		bPrivMouseRButton = bCurMouseRButton;
		return true;
	}

	bPrivMouseRButton = bCurMouseRButton;
	return false;
}

BOOL MouseInputManager::MoveMouse(POINT* const outPosition)
{
	static POINT privMousePosition;
	POINT curMousePosition;

	GetCursorPos(&curMousePosition);
	ScreenToClient(hWnd, &curMousePosition);
	
	if (privMousePosition.x != curMousePosition.x || privMousePosition.y != curMousePosition.y)
	{
		*outPosition = curMousePosition;

		return true;
	}

	return false;
}

void MouseInputManager::Update()
{
	static eEventName PrivMouseState = eEventName::MOUSE_STOP;
	
	POINT mousePosition = ChangeMouseState();

	if(PrivMouseState != mMouseState)
	{
		gEventManager->EventOccurred(mMouseState, &mousePosition);
	}
	
	PrivMouseState = mMouseState;
}

POINT MouseInputManager::ChangeMouseState()
{
	POINT mousePosition;
	
	if (gMouseInputManager->DownLeftButton(&mousePosition))
	{
		mMouseState = eEventName::MOUSE_L_DOWN;
	}
	if (gMouseInputManager->DownRightButton(&mousePosition))
	{
		mMouseState = eEventName::MOUSE_R_DOWN;
	}
	if (gMouseInputManager->UpLeftButton(&mousePosition))
	{
		mMouseState = eEventName::MOUSE_L_UP;
	}
	if (gMouseInputManager->UpRightButton(&mousePosition))
	{
		mMouseState = eEventName::MOUSE_R_UP;
	}
	if(gMouseInputManager->MoveMouse(&mousePosition))
	{
		mMouseState = eEventName::MOUSE_MOVE;
	}
	
	return mousePosition;
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
