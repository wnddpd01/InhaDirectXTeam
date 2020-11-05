#pragma once
#include "SceneFactory.h"

enum class eSceneName
{
	START_SCENE = 0, INGAME_SCENE
};

class Scene;

class SceneCenter
{
	SceneFactory mSceneFactory;
	void SceneLoad(eSceneName sceneName);
public :
	SceneCenter();
	~SceneCenter();
	void SceneChange(eSceneName sceneName);
	void RegisterScene(Scene* scene);
	void InputProcess();
	void Update();
	void Render();

	Scene* GetScene(eSceneName sceneName)
	{
		return mSceneMap[sceneName];
	}

	Scene* GetCurScene()
	{
		return mCurScene;
	}


private:
	Scene* mCurScene;
	std::map<eSceneName, Scene*> mSceneMap;
};
