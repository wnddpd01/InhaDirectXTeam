#pragma once

enum class eKeyButton { LEFT_KEY, RIGHT_KEY, DOWN_KEY, UP_KEY };
        
class Scene;
class SceneCenter
{
public :
	SceneCenter();
	~SceneCenter();
	void SceneChange(std::wstring sceneName);
	void RegisterScene(std::wstring sceneName);
	void InputProcess();
	void Update();
	void Render();

	void MouseInput();

	void KeyBoardInput();
	
private:
	Scene* mCurScene;
	std::map<std::wstring, Scene*> mSceneMap;
};

