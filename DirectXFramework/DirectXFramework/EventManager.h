#pragma once

#include "Singleton.h"

#define gEventManager EventManager::GetInstance()

enum class eEventName
{
	SCENE_CHANGE = 0,MOUSE_STOP, MOUSE_L_DOWN, MOUSE_R_DOWN, MOUSE_R_UP, MOUSE_L_UP, MOUSE_MOVE, KEY_DOWN
};

class BaseObserver;

class EventManager : public Singleton<EventManager>
{
	map<eEventName, vector<BaseObserver*>> mMapSubscriber;
public:

	void ClearSubscriber();
	
	bool AttachSubscriber(eEventName eventName, BaseObserver* newSubscriber)
	{
		mMapSubscriber[eventName].push_back(newSubscriber);
		return true;
	}

	void DetachSubscriber(eEventName eventName, BaseObserver* detachedSubscriber)
	{
		for (auto it = mMapSubscriber[eventName].begin(); it != mMapSubscriber[eventName].end(); it++)
		{
			if (*it == detachedSubscriber)
			{
				mMapSubscriber[eventName].erase(it);
				break;
			}
		}
	}

	void DetachSubscriber(BaseObserver* detachedSubscriber)
	{
		for (auto it_map = mMapSubscriber.begin(); it_map != mMapSubscriber.end(); it_map++)
		{
			for (auto it_mapVec = it_map->second.begin(); it_mapVec != it_map->second.end(); it_mapVec++)
			{
				if (*it_mapVec == detachedSubscriber)
				{
					it_map->second.erase(it_mapVec);
					break;
				}
			}
		}
	}

	void EventOccurred(eEventName eventName, void* parameter);
};

