#pragma once
#include "EventManager.h"
#include "Singleton.h"

#define gMouseInputManager MouseInputManager::GetInstance()

class MouseInputManager : public Singleton<MouseInputManager>
{
public:
	BOOL PushLeft(POINT* outPosition);
	BOOL PushRight(POINT* outPosition);
	BOOL MoveMouse(POINT* outPosition);
};
