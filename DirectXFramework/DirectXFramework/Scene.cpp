#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
	: Scene(std::wstring(L"NoNameScene"))
{
}

Scene::Scene(std::wstring SceneName)
{
	SetSceneName(SceneName);
}

Scene::~Scene()
{
}

void Scene::Update()
{
}

void Scene::Render()
{
}
