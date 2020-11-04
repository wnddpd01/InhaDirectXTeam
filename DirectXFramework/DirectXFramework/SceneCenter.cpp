
#include "stdafx.h"

// ������
#include <iostream>

#include "SceneCenter.h"
#include "Scene.h"

using namespace std;

SceneCenter::SceneCenter() : mCurScene(NULL)
{
}

SceneCenter::~SceneCenter()
{
	for (auto scene : mSceneMap)
	{
		delete scene.second;
	}
	mSceneMap.clear();
}

void SceneCenter::SceneChange(std::wstring sceneName)
{
	if(mSceneMap.find(sceneName) != mSceneMap.end())
	{
		mCurScene = mSceneMap.find(sceneName)->second;
	}
	else
	{
		//TODO Scene�� �������������� ����ó��
	}
}

void SceneCenter::RegisterScene(wstring sceneName)
{
	if (mSceneMap.find(sceneName) == mSceneMap.end())
	{
		mSceneMap.insert(make_pair(sceneName, new Scene(sceneName)));
	}
	else
	{
		//TODO Scene�� �����Ҷ� ����ó��
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
	}
}

void SceneCenter::Render()
{
	if(mCurScene != NULL)
	{
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