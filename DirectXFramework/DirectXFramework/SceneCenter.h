#pragma once

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
	
private:
	Scene* mCurScene;
	std::map<std::wstring, Scene*> mSceneMap;
};

