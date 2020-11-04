#include "stdafx.h"
#include "EventManager.h"
#include "BaseObserver.h"

void EventManager::EventOccurred(eEventName eventName, void* parameter)
{
	for (auto subscriber : m_mapSubscriber[eventName])
	{
		subscriber->Update(eventName, parameter);
	}
}
