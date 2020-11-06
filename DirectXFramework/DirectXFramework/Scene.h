#pragma once
#include "Camera.h"
#include "SceneCenter.h"

class BaseObject;
class QuarterMap;

class Scene
{
	eSceneName mSceneName;
	
	Camera * mCamera;
	QuarterMap* mQuaterMap;

	map<eEventName, BaseObserver*> eventSubscriberList;
	
public:
	Scene();
	virtual ~Scene();

	map<string, BaseObject*> mGameObjects;
	map<string, BaseObject*> mGameUIs;

	eSceneName GetSceneName() const
	{
		return mSceneName;
	}

	void SetSceneName(const eSceneName& m_scene_name)
	{
		mSceneName = m_scene_name;
	}

	void AddEventSubscriberList(eEventName eventName, BaseObserver* baseObserver);
	void DetachAllSubscriberInEventManager();
	
	virtual void Update();
	virtual void Render();

private:
};
