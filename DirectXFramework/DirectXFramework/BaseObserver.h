#pragma once

#include "EventManager.h"

class BaseObserver
{
public:
	BaseObserver();
	virtual ~BaseObserver();

	virtual void Update(eEventName eventName, void* parameter);
};
