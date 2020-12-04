#pragma once

#include "DeviceManager.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "UIBase.h"
#include "UIImage.h"
#include "SceneCenter.h"
#include "KeyboardInputManager.h"
//inline void PanelEventListen(eEventName eventName, void* parameter, UIBase* uiImage)
//{
//	static bool isClicked = false;
//	uiImage = (UIImage*)uiImage;
//	if(eventName == eEventName::MOUSE_L_DOWN)
//	{
//		POINT mousePt = *(POINT*)(parameter);
//		if (PtInRect(&uiImage->GetRectInViewPort(), mousePt))
//		{
//			isClicked = true;
//		}
//	}
//	else if(eventName == eEventName::MOUSE_L_UP)
//	{
//		POINT mousePt = *(POINT*)(parameter);
//		isClicked = false;
//		if (PtInRect(&uiImage->GetRectInViewPort(), mousePt))
//		{
//			uiImage->SetVisible(!uiImage->IsVisible());
//		}
//	}
//}

inline bool BtnStartEventListen(eEventName eventName, void * parameter, UIBase * uiImage)
{
	UIImage* uiImageConvert = (UIImage*)uiImage;
	static bool isClicked = false;
	switch (eventName)
	{
	case eEventName::MOUSE_L_DOWN:
	{
		POINT& mousePt = *(POINT*)(parameter);
		if (PtInRect(&uiImageConvert->GetRectInViewPort(), mousePt))
		{
			uiImageConvert->SetTexture("Resources/UI/Main/NewGame_Click.png");
			isClicked = true;
			return true;
		}
	}
	break;
	case eEventName::MOUSE_L_UP:
	{
		POINT& mousePt = *(POINT*)(parameter);
		isClicked = false;
		if (PtInRect(&uiImageConvert->GetRectInViewPort(), mousePt))
		{
			eSceneName sceneName = eSceneName::INGAME_SCENE;
			gSoundManager->Play("CLICK");
			gEventManager->EventOccurred(eEventName::SCENE_CHANGE, &(sceneName));
			uiImageConvert->SetTexture("Resources/UI/Main/NewGame.png");
			return true;
		}
		uiImageConvert->SetTexture("Resources/UI/Main/NewGame.png");
	}
	break;
	case eEventName::MOUSE_MOVE:
	{
		POINT& mousePt = *(POINT*)(parameter);
		if (isClicked == false)
		{
			if (PtInRect(&uiImageConvert->GetRectInViewPort(), mousePt))
			{
				uiImageConvert->SetTexture("Resources/UI/Main/NewGame_Click.png");
			}
			else
			{
				uiImageConvert->SetTexture("Resources/UI/Main/NewGame.png");
			}
		}
	}
	break;
	default:
		break;
	}
	return false;
}

inline bool BtnExitEventListen(eEventName eventName, void* parameter, UIBase* uiImage)
{
	UIImage* uiImageConvert = (UIImage*)uiImage;
	static bool isClicked = false;
	switch (eventName)
	{
	case eEventName::MOUSE_L_DOWN:
	{
		POINT mousePt = *(POINT*)(parameter);
		if (PtInRect(&uiImageConvert->GetRectInViewPort(), mousePt))
		{
			uiImageConvert->SetTexture("Resources/UI/Main/Quit_Click.png");
			isClicked = true;
			return true;
		}
	}
	break;
	case eEventName::MOUSE_L_UP:
	{
		POINT mousePt = *(POINT*)(parameter);
		isClicked = false;
		if (PtInRect(&uiImageConvert->GetRectInViewPort(), mousePt))
		{
			gSoundManager->Play("CLICK");
			uiImageConvert->SetTexture("Resources/UI/Main/Quit.png");
			return true;
		}
		uiImageConvert->SetTexture("Resources/UI/Main/Quit.png");
	}
	break;
	case eEventName::MOUSE_MOVE:
	{
		POINT mousePt = *(POINT*)(parameter);
		if (isClicked == false)
		{
			if (PtInRect(&uiImageConvert->GetRectInViewPort(), mousePt))
			{
				uiImageConvert->SetTexture("Resources/UI/Main/Quit_Click.png");
			}
			else
			{
				uiImageConvert->SetTexture("Resources/UI/Main/Quit.png");
			}
		}
	}
	break;
	default:
		break;
	}


	return false;
}

inline bool BtnSettingEventListen(eEventName eventName, void* parameter, UIBase* uiImage)
{
	UIImage* uiImageConvert = (UIImage*)uiImage;
	static bool isClicked = false;
	static int isCalled = -1;

	switch (eventName)
	{
	case eEventName::KEY_UP:
	{
		eKeyName key = *(eKeyName*)parameter;
		if (key == eKeyName::KEY_ESC)
		{
			isCalled *= -1;	
		}	
	}
	break;
	case eEventName::MOUSE_L_DOWN:
	{
		POINT mousePt = *(POINT*)(parameter);
		if (PtInRect(&uiImageConvert->GetChildUI("ExitBtn")->GetRectInViewPort(), mousePt))
		{
			uiImageConvert->GetChildUI("ExitBtn")->SetTexture("Resources/UI/Setting/Exit_on.png");
			isClicked = true;
		}

		if (PtInRect(&uiImageConvert->GetChildUI("Control")->GetRectInViewPort(), mousePt))
		{
			uiImageConvert->GetChildUI("Control")->SetTexture("Resources/UI/Setting/Control_on.png");
			isClicked = true;
		}

		if (PtInRect(&uiImageConvert->GetChildUI("BGMLine")->GetChildUI("BGMBtn")->GetRectInViewPort(), mousePt))
		{
			uiImageConvert->GetChildUI("BGMLine")->GetChildUI("BGMBtn")->SetTexture("Resources/UI/Setting/Button_set.png");
			isClicked = true;
		}
			
			
	}
	break;
	case eEventName::MOUSE_L_UP:
	{
		POINT mousePt = *(POINT*)(parameter);
		isClicked = false;
		if (PtInRect(&uiImageConvert->GetChildUI("ExitBtn")->GetRectInViewPort(), mousePt))
		{
			uiImageConvert->GetChildUI("ExitBtn")->SetTexture("Resources/UI/Setting/Exit_off.png");
			isCalled = -1;
		}

		if (PtInRect(&uiImageConvert->GetChildUI("Control")->GetRectInViewPort(), mousePt))
		{
			
			uiImageConvert->GetChildUI("Control")->SetTexture("Resources/UI/Setting/Control_off.png");

			for(pair<string, UIImage*> child : uiImageConvert->GetChildUI() )
			{
				if(child.first == "ControlLayer")
				{
					child.second->SetVisible(true);
				}
				else
				{
					child.second->SetVisible(false);
				}
			}
			
		}

		if (PtInRect(&uiImageConvert->GetChildUI("BGMLine")->GetRectInViewPort(), mousePt))
		{
			UIImage*Line = uiImageConvert->GetChildUI("BGMLine");	
			UIImage*Btn = uiImageConvert->GetChildUI("BGMLine")->GetChildUI("BGMBtn");
			
			int num = (mousePt.x- Line->GetPos().x )/ (Line->GetWidth()*0.1f);
			LONG x = Line->GetPos().x + ((Line->GetWidth()*0.1)* num);
			
			Btn->SetPos(D3DXVECTOR3(x, Btn->GetPos().y, 0));
			gSoundManager->Volume("BGM", num*0.1f);
		}

	

	}
	break;
	case eEventName::MOUSE_MOVE:
	{
		POINT mousePt = *(POINT*)(parameter);
		if (isClicked == false)
		{
			if (PtInRect(&uiImageConvert->GetChildUI("ExitBtn")->GetRectInViewPort(), mousePt))
			{
				uiImageConvert->GetChildUI("ExitBtn")->SetTexture("Resources/UI/Setting/Exit_on.png");
			}
			else
			{
				uiImageConvert->GetChildUI("ExitBtn")->SetTexture("Resources/UI/Setting/Exit_off.png");
			}

			if (PtInRect(&uiImageConvert->GetChildUI("Control")->GetRectInViewPort(), mousePt))
			{
				uiImageConvert->GetChildUI("Control")->SetTexture("Resources/UI/Setting/Control_on.png");
			}
			else
			{
				uiImageConvert->GetChildUI("Control")->SetTexture("Resources/UI/Setting/Control_off.png");
			}

			if(PtInRect(&uiImageConvert->GetChildUI("BGMLine")->GetChildUI("BGMBtn")->GetRectInViewPort(), mousePt))
			{
				uiImageConvert->GetChildUI("BGMLine")->GetChildUI("BGMBtn")->SetTexture("Resources/UI/Setting/Button_click.png");
			}
			else
			{
				uiImageConvert->GetChildUI("BGMLine")->GetChildUI("BGMBtn")->SetTexture("Resources/UI/Setting/Button_set.png");
			}


			
		}
		else
		{

			if (PtInRect(&uiImageConvert->GetChildUI("BGMLine")->GetRectInViewPort(), mousePt))
			{
				UIImage*Line = uiImageConvert->GetChildUI("BGMLine");
				UIImage*Btn = uiImageConvert->GetChildUI("BGMLine")->GetChildUI("BGMBtn");

				int num = (mousePt.x - Line->GetPos().x) / (Line->GetWidth()*0.1f);
				LONG x = Line->GetPos().x + ((Line->GetWidth()*0.1)* num);

				Btn->SetPos(D3DXVECTOR3(x, Btn->GetPos().y, 0));
				gSoundManager->Volume("BGM", num*0.1f);
			}
		}
	}
	break;
	default:
		break;
	}


	
	if (isCalled == 1)
	{
		uiImageConvert->SetVisible(true);
		return true;
	}
	else
	{
		for (pair<string, UIImage*> child : uiImageConvert->GetChildUI())
		{
			if (child.first == "ControlLayer")
			{
				child.second->SetVisible(false);
			}
			else
			{
				child.second->SetVisible(true);
			}
		}
		uiImageConvert->SetVisible(false);
		return false;
	}
	
}
