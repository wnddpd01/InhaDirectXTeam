#include "stdafx.h"
#include "MouseInputManager.h"

BOOL MouseInputManager::PushLeft(POINT* const outPosition)
{
	if(GetKeyState(VK_LBUTTON) & 0x8000)
	{
		GetCursorPos(outPosition);
		return true;
	}

	return false;
}

BOOL MouseInputManager::PushRight(POINT* const outPosition)
{
	if (GetKeyState(VK_RBUTTON) & 0x8000)
	{
		GetCursorPos(outPosition);
		return true;
	}

	return false;
}

BOOL MouseInputManager::MoveMouse(POINT* const outPosition)
{
	static POINT privMousePosition;
	POINT curMousePosition;
	
	GetCursorPos(&curMousePosition);
	
	if(curMousePosition.x == privMousePosition.x && curMousePosition.y == privMousePosition.y)
	{
		return false;
	}
	
	else
	{
		*outPosition = curMousePosition;
	}
	
	return true;
}

