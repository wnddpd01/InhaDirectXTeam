#include "stdafx.h"
#include "KeyboardInputManager.h"

bool KeyboardInputManager::PressUpKey()
{
	if (GetKeyState('W') & 0x8000)
	{
		return true;
	}
	
	return false;
}

bool KeyboardInputManager::PressDownKey()
{
	if (GetKeyState('S') & 0x8000)
	{
		return true;
	}

	return false;
}

bool KeyboardInputManager::PressLeftKey()
{
	if (GetKeyState('A') & 0x8000)
	{
		return true;
	}

	return false;
}

bool KeyboardInputManager::PressRightKey()
{
	if (GetKeyState('D') & 0x8000)
	{
		return true;
	}

	return false;

}