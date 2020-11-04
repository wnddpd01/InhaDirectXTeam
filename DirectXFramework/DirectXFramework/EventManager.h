#pragma once
#include <map>
#include <vector>
#include "BasicObserver.h"

using namespace std;

class EventManager
{
	EventManager();
	map<string, vector<BasicObserver*>> m_mapSubscriber;
public:
	static EventManager* GetInstance()
	{
		static EventManager ins;
		return &ins;
	}
	~EventManager();

	bool AddSubscriber(string eventName, BasicObserver* newSubscriber)
	{
		m_mapSubscriber[eventName].push_back(newSubscriber);
		return true;
	}

	bool SubtractSubscriber(string eventName, BasicObserver* newSubscriber)
	{
		for (auto it = m_mapSubscriber[eventName].begin(); it != m_mapSubscriber[eventName].end(); it++)
		{
			if (*it == newSubscriber)
			{
				m_mapSubscriber[eventName].erase(it);
				return true;
			}
		}
		return false;
	}

	bool SubtractSubscriber(BasicObserver* newSubscriber)
	{
		for (auto it_map = m_mapSubscriber.begin(); it_map != m_mapSubscriber.end(); it_map++)
		{
			for (auto it_mapVec = it_map->second.begin(); it_mapVec != it_map->second.end(); it_mapVec++)
			{
				if (*it_mapVec == newSubscriber)
				{
					it_map->second.erase(it_mapVec);
					return true;
				}
			}
		}
		return false;
	}

	void EventOccured(string eventName, void* parameter)
	{
		for (auto subscriber : m_mapSubscriber[eventName])
		{
			subscriber->Event(parameter);
		}
	}
};

