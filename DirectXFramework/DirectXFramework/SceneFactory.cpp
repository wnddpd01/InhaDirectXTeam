#include "stdafx.h"
#include "SceneFactory.h"
#include "SceneCenter.h"
#include "Scene.h"
#include "QuarterMap.h"


SceneFactory::SceneFactory()
{
}


SceneFactory::~SceneFactory()
{
}

Scene* SceneFactory::CreateScene(eSceneName eSceneName)
{
	Scene * newScene = new Scene;
	if (eSceneName == eSceneName::START_SCENE)
	{
		newScene->SetSceneName(eSceneName);
		D3DVIEWPORT9 viewPort;
		gD3Device->GetViewport(&viewPort);
		UIImage * uiImage = new UIImage("Resources/UI/BasePanel.png");
		uiImage->SetObjectName("BasePanel");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5,
			uiImage->GetPos().y + viewPort.Height * 0.5f - uiImage->GetHeight() * 0.5, 0.0f));
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("BasePanel", uiImage));

		uiImage = new UIImage("Resources/UI/BtnIdle.png");
		uiImage->SetObjectName("BtnStart");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5,
			uiImage->GetPos().y + viewPort.Height * 0.55f + uiImage->GetHeight() * 0.5, 0.0f));
		uiImage->EventProcess = BtnStartEventListen;
		gEventManager->AttachSubscriber(eEventName::MOUSE_L_DOWN, uiImage);
		gEventManager->AttachSubscriber(eEventName::MOUSE_L_UP, uiImage);
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("BtnStart", uiImage));

		uiImage = new UIImage("Resources/UI/BtnIdle.png");
		uiImage->SetObjectName("BtnExit");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5,
			uiImage->GetPos().y + viewPort.Height * 0.65f + uiImage->GetHeight() * 0.5, 0.0f));
		uiImage->EventProcess = BtnExitEventListen;
		gEventManager->AttachSubscriber(eEventName::MOUSE_L_DOWN, uiImage);
		gEventManager->AttachSubscriber(eEventName::MOUSE_L_UP, uiImage);
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("BtnExit", uiImage));

		gSoundManager->SoundSet();
	}
	else if(eSceneName == eSceneName::INGAME_SCENE)
	{
		QuarterMap * quarterMap = new QuarterMap;
		quarterMap->Setup("HeightMapData/", "HeightMap.raw", "StoneTiles.jpg");
		newScene->mGameObjects.insert({ "QuarterMap", quarterMap });
	}
	return newScene;	
}
