#pragma once

enum class eSceneName
{
	START_SCENE = 0, 
};

class Scene;

class SceneCenter
{
	void SceneLoad();
public :
	SceneCenter();
	~SceneCenter();
	void SceneChange(eSceneName sceneName);
	void RegisterAndMakeScene(eSceneName sceneName);
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

