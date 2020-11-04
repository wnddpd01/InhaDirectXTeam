#pragma once

#include "EventManager.h"

class BaseObserver
{
public:
	BaseObserver();
	~BaseObserver();

	void Update(eEventName eventName ,void* parameter);
};

