#include "stdafx.h"

// 디버깅용
#include <iostream>

#include "SceneCenter.h"
#include "Scene.h"
#include "MouseInputManager.h"
#include "KeyboardInputManager.h"
#include "EventManager.h"

using namespace std;

void SceneCenter::SceneLoad(eSceneName sceneName)
{
	Scene* newScene = mSceneFactory.CreateScene(sceneName);
	RegisterScene(newScene);
}

SceneCenter::SceneCenter() : mCurScene(nullptr)
{
	SceneLoad(eSceneName::START_SCENE);
	SceneChange(eSceneName::START_SCENE);

	gEventManager->AttachSubscriber(eEventName::SCENE_CHANGE, this);
}

SceneCenter::~SceneCenter()
{
	for (auto scene : mSceneMap)
	{
		SafeDelete(scene.second);
	}
	mSceneMap.clear();
}

void SceneCenter::SceneChange(eSceneName sceneName)
{
	if (mSceneMap.find(sceneName) == mSceneMap.end())
	{
		SceneLoad(sceneName);
	}
	if (mCurScene != nullptr)
	{
		mCurScene->DetachAllSubscriberInEventManager();
	}
	mCurScene = mSceneMap.find(sceneName)->second;
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
	/*if ( gKeyboardInputManager->ReadKey() != static_cast<int>(eKeyButton::NON_KEY))
	{
	}*/

	gMouseInputManager->Update();
	gKeyboardInputManager->Update();
}

void SceneCenter::Update()
{
	gTimeManager->Update();

	if (mCurScene != nullptr)
	{
		mCurScene->Update();
	}

	gSoundManager->Update();
}

void SceneCenter::Update(eEventName eventName, void* parameter)
{
	if(eventName == eEventName::SCENE_CHANGE)
	{
		eSceneName * sceneName = static_cast<eSceneName *>(parameter);
		SceneChange(*sceneName);
	}
}

void SceneCenter::Render()
{
	if (mCurScene != nullptr)
	{
		mCurScene->Render();
	}
}
