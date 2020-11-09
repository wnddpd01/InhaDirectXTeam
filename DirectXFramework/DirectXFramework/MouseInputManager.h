#pragma once
#include "EventManager.h"
#include "Singleton.h"

#define gMouseInputManager MouseInputManager::GetInstance()

class MouseInputManager : public Singleton<MouseInputManager>
{
public:
	BOOL DownLeftButton(POINT * const outPosition);
	BOOL DownRightButton(POINT * const outPosition);
	BOOL UpRightButton(POINT * const outPosition);
	BOOL UpLeftButton(POINT * const outPosition);
	POINT ChangeMouseState();
	BOOL MoveMouse(POINT * const outPosition);
	BOOL DragMouse(POINT * const outPosition);
	void Update();
private:
	eEventName mMouseState;
};
