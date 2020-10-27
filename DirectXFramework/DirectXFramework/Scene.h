#pragma once

class Scene
{
	std::wstring mSceneName;
public:
	Scene();
	Scene(std::wstring SceneName);
	~Scene();
	std::wstring GetSceneName() const
	{
		return mSceneName;
	}
	void SetSceneName(const std::wstring& m_scene_name)
	{
		mSceneName = m_scene_name;
	}

	virtual void Update();
	virtual void Render();
private:

};

