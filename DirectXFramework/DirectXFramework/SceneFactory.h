#pragma once

enum class eSceneName;
class Scene;
class Group;

class SceneFactory
{
public:
	SceneFactory();
	~SceneFactory();

	Scene* CreateScene(eSceneName eSceneName);
private:
	vector<Group*> m_VecGroup;
	
};

