#pragma once
#include "EventManager.h"
#include "Singleton.h"

#define gKeyboardInputManager KeyboardInputManager::GetInstance()

//struct KeyState
//{
//	bool bFrontKey;
//	bool bBackKey;
//	bool b
//	bool
//	bool
//	bool
//
//	
//};

class KeyboardInputManager : public Singleton<KeyboardInputManager>
{
public:
	int ReadKey();
};
