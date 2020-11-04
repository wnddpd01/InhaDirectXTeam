#pragma once
#include "EventManager.h"
#include "Singleton.h"

#define gMouseInputManager MouseInputManager::GetInstance()

class MouseInputManager : public Singleton<MouseInputManager>
{
public:
	BOOL DownLeftButton(POINT * const outPosition);
	BOOL DownRightButton(POINT * const outPosition);
	BOOL UpLeftButton(POINT * const outPosition);
	
private:
	bool bMouseLbuttonDown;

};
