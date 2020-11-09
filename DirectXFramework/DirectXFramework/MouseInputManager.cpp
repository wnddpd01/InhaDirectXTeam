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
	
	static bool bPrevMouseLButton = false;
	bool bCurMouseLButton = GetKeyState(VK_LBUTTON) & 0x8000;

	if (bPrevMouseLButton == TRUE && bCurMouseLButton == FALSE)
	{
		GetCursorPos(outPosition);
		ScreenToClient(hWnd, outPosition);
		bPrevMouseLButton = bCurMouseLButton;
		return true; 
	}

	bPrevMouseLButton = bCurMouseLButton;
	return false;
}

BOOL MouseInputManager::DownRightButton(POINT* const outPosition)
{
	static bool bPrevMouseRButton = false;
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
	static bool bPrevMouseRButton = false;
	bool bCurMouseRButton = GetKeyState(VK_RBUTTON) & 0x8000;

	if (bPrevMouseRButton == TRUE && bCurMouseRButton == FALSE)
	{
		GetCursorPos(outPosition);
		ScreenToClient(hWnd, outPosition);
		bPrevMouseRButton = bCurMouseRButton;
		return true;
	}

	bPrevMouseRButton = bCurMouseRButton;
	return false;
}

BOOL MouseInputManager::MoveMouse(POINT* const outPosition)
{
	static POINT prevMousePosition;
	POINT curMousePosition;

	GetCursorPos(&curMousePosition);
	ScreenToClient(hWnd, &curMousePosition);
	
	if (prevMousePosition.x != curMousePosition.x || prevMousePosition.y != curMousePosition.y)
	{
		*outPosition = curMousePosition;

		return true;
	}

	return false;
}

void MouseInputManager::Update()
{
	static eEventName prevMouseState = eEventName::MOUSE_STOP;
	
	POINT mousePosition = ChangeMouseState();

	if(prevMouseState != mMouseState)
	{
		gEventManager->EventOccurred(mMouseState, &mousePosition);
	}
	
	prevMouseState = mMouseState;
}

POINT MouseInputManager::ChangeMouseState()
{
	POINT mousePosition;
	
	if(gMouseInputManager->MoveMouse(&mousePosition))
	{
		mMouseState = eEventName::MOUSE_MOVE;
	}
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

	if (gMouseInputManager->UpRightButton(&mousePosition))
	{
		mMouseState = eEventName::MOUSE_R_UP;
	}
	
	return mousePosition;
}
