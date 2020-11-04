#pragma once

enum class eKeyButton { LEFT_KEY, RIGHT_KEY, DOWN_KEY, UP_KEY };
        
enum class eSceneName
{
	START_SCENE = 0,
	GAME_SCENE,
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

	void MouseInput();
	void KeyBoardInput();

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

