#pragma once

class Scene;
class SceneCenter
{
private:
	Scene* mCurScene;
	std::map<std::wstring, Scene*> mSceneMap;
public :
	SceneCenter();
	~SceneCenter();
	void SceneChange(std::wstring sceneName);
	void RegisterScene(std::wstring sceneName);
	void InputProcess();
	void Update(float timeProgressRatio = 1.0f);
	void Render();
};

