#include "stdafx.h"

// 디버깅용
#include <iostream>

#include "SceneCenter.h"
#include "Scene.h"
#include "MouseInputManager.h"
#include "KeyboardInputManager.h"
#include "EventManager.h"

using namespace std;

void SceneCenter::SceneLoad()
{
	Scene* startScene = new Scene(eSceneName::START_SCENE);
	RegisterScene(startScene);
	SceneChange(eSceneName::START_SCENE);
}

SceneCenter::SceneCenter() : mCurScene(nullptr)
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
	if (mSceneMap.find(sceneName) != mSceneMap.end())
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
	/*if ( gKeyboardInputManager->ReadKey() != static_cast<int>(eKeyButton::NON_KEY))
	{
		
	}*/

	POINT mousePosition;
	
	if( gMouseInputManager->DownLeftButton(&mousePosition))
	{
		gEventManager->EventOccurred(eEventName::MOUSE_L_DOWN,&mousePosition);
	}

	if(gMouseInputManager->DownRightButton(&mousePosition))
	{
		gEventManager->EventOccurred(eEventName::MOUSE_R_DOWN, &mousePosition);
	}

	if (gMouseInputManager->UpLeftButton(&mousePosition))
	{
		gEventManager->EventOccurred(eEventName::MOUSE_L_UP, &mousePosition);
	}


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

void SceneCenter::Render()
{
	if (mCurScene != nullptr)
	{
		mCurScene->Render();
	}
}
