
#include "stdafx.h"

// 디버깅용
#include <iostream>

#include "SceneCenter.h"
#include "Scene.h"

using namespace std;

void SceneCenter::SceneLoad()
{
	Scene* startScene = new Scene(eSceneName::START_SCENE);
	RegisterScene(startScene);
	SceneChange(eSceneName::START_SCENE);
}

SceneCenter::SceneCenter() : mCurScene(NULL)
{
	SceneLoad();
}

SceneCenter::~SceneCenter()
{
	for (auto scene : mSceneMap)
	{
		delete scene.second;
	}
	mSceneMap.clear();
}

void SceneCenter::SceneChange(eSceneName sceneName)
{
	if(mSceneMap.find(sceneName) != mSceneMap.end())
	{
		mCurScene = mSceneMap.find(sceneName)->second;
	}
	else
	{
		//TODO Scene이 존재하지않을때 예외처리
	}
}

void SceneCenter::RegisterAndMakeScene(eSceneName sceneName)
{
	if (mSceneMap.find(sceneName) == mSceneMap.end())
	{
		mSceneMap.insert(make_pair(sceneName, new Scene(sceneName)));
	}
	else
	{
		//TODO Scene이 존재할때 예외처리
	}
}

void SceneCenter::RegisterScene(Scene* scene)
{
	if (mSceneMap.find(scene->GetSceneName()) == mSceneMap.end())
	{
		mSceneMap.insert(make_pair(scene->GetSceneName(), scene));
	}
	else
	{
		//TODO Scene이 존재할때 예외처리
	}
}

void SceneCenter::InputProcess()
{
	
}

void SceneCenter::Update()
{
	gTimeManager->Update();

	if(mCurScene != NULL)
	{
		mCurScene->Update();
	}
}

void SceneCenter::Render()
{
	if(mCurScene != NULL)
	{
		mCurScene->Render();
	}
}

void SceneCenter::MouseInput()
{
	POINT mousePrivPosition;
	
	
}

void SceneCenter::KeyBoardInput()
{
	if (mCurScene != NULL)
	{
	}

}