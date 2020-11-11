#include "stdafx.h"
#include "SceneFactory.h"
#include "SceneCenter.h"
#include "Scene.h"
#include "QuarterMap.h"
#include "PlayerCharacter.h"
#include "StaticObject.h"
#include "cObjLoader.h"
#include "Group.h"

SceneFactory::SceneFactory()
{
}


SceneFactory::~SceneFactory()
{
}

Scene* SceneFactory::CreateScene(eSceneName eSceneName)
{
	Scene * newScene = new Scene;
	newScene->SetSceneName(eSceneName);
	if (eSceneName == eSceneName::START_SCENE)
	{
		D3DVIEWPORT9 viewPort;
		gD3Device->GetViewport(&viewPort);
		UIImage * uiImage = new UIImage("Resources/UI/BasePanel.png");
		uiImage->SetObjectName("BasePanel");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5f,
			uiImage->GetPos().y + viewPort.Height * 0.5f - uiImage->GetHeight() * 0.5f, 0.0f));
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("BasePanel", uiImage));

		uiImage = new UIImage("Resources/UI/BtnIdle.png");
		uiImage->SetObjectName("BtnStart");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5f,
			uiImage->GetPos().y + viewPort.Height * 0.55f + uiImage->GetHeight() * 0.5, 0.0f));
		uiImage->EventProcess = BtnStartEventListen;
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, uiImage);
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("BtnStart", uiImage));

		uiImage = new UIImage("Resources/UI/BtnIdle.png");
		uiImage->SetObjectName("BtnExit");
		uiImage->SetPos(D3DXVECTOR3(uiImage->GetPos().x + viewPort.Width * 0.5f - uiImage->GetWidth() * 0.5f,
			uiImage->GetPos().y + viewPort.Height * 0.65f + uiImage->GetHeight() * 0.5f, 0.0f));
		uiImage->EventProcess = BtnExitEventListen;
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 9, uiImage);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, uiImage);
		uiImage->SetVisible(true);
		newScene->mGameUIs.insert(make_pair("BtnExit", uiImage));

		gSoundManager->SoundSet();
	}
	else if(eSceneName == eSceneName::INGAME_SCENE)
	{



		
			D3DLIGHT9	stLight;
			ZeroMemory(&stLight, sizeof(D3DLIGHT9));
			stLight.Type = D3DLIGHT_DIRECTIONAL;
			stLight.Ambient = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);
			stLight.Diffuse = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);
			stLight.Specular = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);

			D3DXVECTOR3  vDir(1.0f, -1.0f, 1.0f);
			D3DXVec3Normalize(&vDir, &vDir);
			stLight.Direction = vDir;
			gD3Device->SetLight(0, &stLight);
			gD3Device->LightEnable(0, true);
	









		
		QuarterMap * quarterMap = new QuarterMap;
		quarterMap->Setup("HeightMapData/", "QuarterHeightMap.raw", "StoneTiles.jpg");
		newScene->mGameObjects.insert({ "QuarterMap", quarterMap });

		StaticObject* desk = new StaticObject;
		desk->Setup("desk.obj", "Texture/DeskWood.png", { 9.f, 0.5f, 2.f });
		newScene->mGameObjects.insert({ "Desk", desk });
		
		StaticObject* door = new StaticObject;
		door->Setup("door.obj", "Texture/DoorWood.jpg", { 9.f, 1.5f, 14.f });
		newScene->mGameObjects.insert({ "Door", door });
		
		PlayerCharacter* player = new PlayerCharacter;
		player->Setup();
		newScene->AddEventSubscriberList(eEventName::KEY_DOWN, 9, player);
		newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, player);
		newScene->mGameObjects.insert(make_pair("player", player));
		newScene->mCamera->Setup(&player->GetPosition());
	}
	return newScene;
}
