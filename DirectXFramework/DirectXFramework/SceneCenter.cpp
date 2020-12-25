#include "stdafx.h"

// 디버깅용
#include <iostream>

#include "SceneCenter.h"
#include "Scene.h"
#include "MouseInputManager.h"
#include "KeyboardInputManager.h"
#include "EventManager.h"

using namespace std;

void SceneCenter::LoadScene(eSceneName sceneName)
{
	Scene* newScene = mSceneFactory.CreateScene(sceneName);
	RegisterScene(newScene);
}

void SceneCenter::EnterScene(eSceneName sceneName)
{
	switch (sceneName)
	{
		case eSceneName::START_SCENE :
			{
				gSoundManager->Play("Menu_BGM");
			}
			break;
		case eSceneName::INGAME_SCENE :
			{
				gSoundManager->Stop("Menu_BGM");
				gSoundManager->Play("PartA_BGM");
			}
			break;
		default :
			{
				
			}
			break;
	}
}

SceneCenter::SceneCenter()
	: mCurScene(nullptr)
{
	gSoundManager->SoundSet();
	gShader->LoadAllShader();
	
	ChangeScene(eSceneName::START_SCENE);
	gEventManager->AttachSubscriber(eEventName::SCENE_CHANGE, 0, this);
}

SceneCenter::~SceneCenter()
{
	for (auto scene : mSceneMap)
	{
		SAFE_DELETE(scene.second);
	}
	mSceneMap.clear();
}

void SceneCenter::ChangeScene(eSceneName sceneName)
{
	if (mSceneMap.find(sceneName) == mSceneMap.end())
	{
		LoadScene(sceneName);
	}
	if (mCurScene != nullptr)
	{
		mCurScene->DetachAllSubscriberInSubscriberList();
	}
	mCurScene = mSceneMap.find(sceneName)->second;
	mCurScene->AttachAllSubscriberInSubscriberList();
	EnterScene(mCurScene->GetSceneName());
	gCameraManager->SetCamera(mSceneMap.find(sceneName)->second->GetCamera());
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

bool SceneCenter::Update(eEventName eventName, void* parameter)
{
	if(eventName == eEventName::SCENE_CHANGE)
	{
		eSceneName * sceneName = static_cast<eSceneName *>(parameter);
		ChangeScene(*sceneName);
	}
	return true;
}

void SceneCenter::Render()
{
	if (mCurScene != nullptr)
	{
		mCurScene->Render();
	}
}
