#pragma once

enum class eSceneName;
class Scene;

class SceneFactory
{
public:
	SceneFactory();
	~SceneFactory();

	Scene* CreateScene(eSceneName eSceneName);
};

