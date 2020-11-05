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
	
	void LoadUI();
	void LoadObject();
public:
	Scene(eSceneName SceneName);
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
	
	virtual void Update();
	virtual void Render();

private:
};
