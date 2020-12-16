#include "stdafx.h"
#include "UIAssemblyLine.h"
#include "Scene.h"

void UIAssemblyLine::MakeStartSceneUI(Scene* newScene)
{
	UIImage* uiImage = new UIImage("Resources/UI/Main/Title.png", { 20, 4 }, 24, 8);
	uiImage->SetObjectName("Title");
	uiImage->SetVisible(true);
	newScene->mGameUIs.insert(make_pair("Title", uiImage));

	uiImage = new UIImage("Resources/UI/Main/NewGame.png", { 26,20 }, 12, 4);
	uiImage->SetObjectName("BtnStart");
	uiImage->EventProcess = BtnStartEventListen;
	newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 9, uiImage);
	newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 9, uiImage);
	newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, uiImage);
	uiImage->SetVisible(true);
	newScene->mGameUIs.insert(make_pair("btnStart", uiImage));

	uiImage = new UIImage("Resources/UI/Main/Quit.png", { 26, 24 }, 12, 4);
	uiImage->SetObjectName("BtnExit");
	uiImage->EventProcess = BtnExitEventListen;
	newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 9, uiImage);
	newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 9, uiImage);
	newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 9, uiImage);
	uiImage->SetVisible(true);
	newScene->mGameUIs.insert(make_pair("btnExit", uiImage));
}

void UIAssemblyLine::MakeIngameSceneUI(Scene* newScene)
{
	UIImage* uiImage = new UIImage("Resources/UI/Setting/Layer.png", { 12, 6 }, 40, 24);
	uiImage->SetObjectName("SettingLayer");
	uiImage->EventProcess = BtnSettingEventListen;
	newScene->AddEventSubscriberList(eEventName::KEY_UP, 0, uiImage);
	newScene->AddEventSubscriberList(eEventName::KEY_DOWN, 0, uiImage);
	newScene->AddEventSubscriberList(eEventName::MOUSE_L_DOWN, 0, uiImage);
	newScene->AddEventSubscriberList(eEventName::MOUSE_L_UP, 0, uiImage);
	newScene->AddEventSubscriberList(eEventName::MOUSE_MOVE, 0, uiImage);
	newScene->AddEventSubscriberList(eEventName::MOUSE_L_DRAG, 0, uiImage);
	uiImage->SetVisible(false);
	newScene->mGameUIs.insert(make_pair("SettingLayer", uiImage));

	UIImage* childUI = new UIImage("Resources/UI/Setting/Exit_off.png", { 14, 28 }, 4, 1);
	childUI->SetObjectName("ExitBtn");
	childUI->SetUIPath("Resources/UI/Setting/Exit_off.png", eStateUI::off);
	childUI->SetUIPath("Resources/UI/Setting/Exit_on.png", eStateUI::on);
	childUI->SetVisible(true);
	uiImage->AddChild("ExitBtn", childUI);

	childUI = new UIImage("Resources/UI/Setting/BGM_off.png", { 16, 10 }, 6, 2);
	childUI->SetObjectName("BGMText");
	childUI->SetUIPath("Resources/UI/Setting/BGM_off.png", eStateUI::off);
	childUI->SetUIPath("Resources/UI/Setting/BGM_on.png", eStateUI::on);
	childUI->SetVisible(true);
	uiImage->AddChild("BGMText", childUI);

	childUI = new UIImage("Resources/UI/Setting/Line.png", { 24, 10 }, 16, 2);
	childUI->SetObjectName("BGMLine");
	childUI->SetVisible(true);
	uiImage->AddChild("BGMLine", childUI);

	childUI = new UIImage("Resources/UI/Setting/Button_set.png", { 30 , 10 }, 4, 2);
	childUI->SetObjectName("BGMBtn");
	childUI->SetUIPath("Resources/UI/Setting/Button_set.png", eStateUI::off);
	childUI->SetUIPath("Resources/UI/Setting/Button_click.png", eStateUI::on);
	childUI->SetVisible(true);
	uiImage->GetChildUI("BGMLine")->AddChild("BGMBtn", childUI);

	childUI = new UIImage("Resources/UI/Setting/Control_off.png", { 16, 14 }, 6, 2);
	childUI->SetObjectName("Control");
	childUI->SetUIPath("Resources/UI/Setting/Control_off.png", eStateUI::off);
	childUI->SetUIPath("Resources/UI/Setting/Control_on.png", eStateUI::on);
	childUI->SetVisible(true);
	uiImage->AddChild("Control", childUI);

	childUI = new UIImage("Resources/UI/Setting/OptionText.png", { 36, 26 }, 15, 2);
	childUI->SetObjectName("OptionText");
	childUI->SetVisible(true);
	uiImage->AddChild("OptionText", childUI);

	childUI = new UIImage("Resources/UI/Setting/Control.png", { 12, 6 }, 40, 24);
	childUI->SetObjectName("ControlLayer");
	childUI->SetVisible(false);
	uiImage->AddChild("ControlLayer", childUI);

	childUI = new UIImage("Resources/UI/Setting/Return_off.png", { 14, 28 }, 4, 1);
	childUI->SetObjectName("ReturnBtn");
	childUI->SetUIPath("Resources/UI/Setting/Return_off.png", eStateUI::off);
	childUI->SetUIPath("Resources/UI/Setting/Return_on.png", eStateUI::on);
	childUI->SetVisible(false);
	uiImage->AddChild("ReturnBtn", childUI);
}

void UIAssemblyLine::MakeSceneUI(Scene* newScene)
{
	D3DVIEWPORT9 viewPort;
	gD3Device->GetViewport(&viewPort);
	switch (newScene->GetSceneName())
	{
		case eSceneName::START_SCENE :
			{
				MakeStartSceneUI(newScene);
			}
			break;
		case eSceneName::INGAME_SCENE :
			{
				MakeIngameSceneUI(newScene);
			}
			break;
		default :
			{
				
			}
			break;
	}
}
