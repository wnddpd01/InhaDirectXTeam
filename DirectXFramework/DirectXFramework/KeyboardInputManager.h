#pragma once
#include "EventManager.h"
#include "Singleton.h"

#define gKeyboardInputManager KeyboardInputManager::GetInstance()

struct KeyState
{
	bool bFrontKey;
	bool bBackKey;
	bool bLeftKey;
	bool bRightKey;
	bool bSpaceKey;
	bool bInteractionKey;
};

class KeyboardInputManager : public Singleton<KeyboardInputManager>
{
public:
	int ReadKey();
};
