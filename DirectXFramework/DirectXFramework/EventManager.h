#pragma once

#include "Singleton.h"

#define gEventManager EventManager::GetInstance()

enum class eEventName
{
	MOUSE_STOP = 0, MOUSE_L_DOWN, MOUSE_R_DOWN, MOUSE_R_UP, MOUSE_L_UP, MOUSE_MOVE, KEY_DOWN
};

class BaseObserver;

class EventManager : public Singleton<EventManager>
{
	map<eEventName, vector<BaseObserver*>> m_mapSubscriber;
public:

	bool AttachSubscriber(eEventName eventName, BaseObserver* newSubscriber)
	{
		m_mapSubscriber[eventName].push_back(newSubscriber);
		return true;
	}

	bool DetachSubscriber(eEventName eventName, BaseObserver* detachedSubscriber)
	{
		for (auto it = m_mapSubscriber[eventName].begin(); it != m_mapSubscriber[eventName].end(); it++)
		{
			if (*it == detachedSubscriber)
			{
				m_mapSubscriber[eventName].erase(it);
				return true;
			}
		}
		return false;
	}

	bool DetachSubscriber(BaseObserver* detachedSubscriber)
	{
		for (auto it_map = m_mapSubscriber.begin(); it_map != m_mapSubscriber.end(); it_map++)
		{
			for (auto it_mapVec = it_map->second.begin(); it_mapVec != it_map->second.end(); it_mapVec++)
			{
				if (*it_mapVec == detachedSubscriber)
				{
					it_map->second.erase(it_mapVec);
					return true;
				}
			}
		}
		return false;
	}

	void EventOccurred(eEventName eventName, void* parameter);
};

