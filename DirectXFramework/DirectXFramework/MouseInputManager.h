#pragma once
#include "EventManager.h"

class MouseInputManager : public EventManager
{
public:

	
private:

	BOOL PushLeft( POINT* const outPosition);
	BOOL PushRight( POINT* const outPosition);
	BOOL MoveMouse( POINT* const outPosition);

};

