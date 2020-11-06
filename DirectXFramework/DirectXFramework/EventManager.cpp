#include "stdafx.h"
#include "EventManager.h"
#include "BaseObserver.h"

void EventManager::ClearSubscriber()
{
	for (auto subscriberMap : mMapSubscriber)
	{
		subscriberMap.second.clear();
	}
	mMapSubscriber.clear();
}

void EventManager::EventOccurred(eEventName eventName, void* parameter)
{
	for (auto subscriber : mMapSubscriber[eventName])
	{
		if (subscriber.second->Update(eventName, parameter))
		{
			break;
		}
	}
	
}
