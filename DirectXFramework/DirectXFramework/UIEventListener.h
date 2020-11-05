#pragma once

#include "DeviceManager.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "UIBase.h"
#include "UIImage.h"


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

inline void BtnStartEventListen(eEventName eventName, void * parameter, UIBase * uiImage)
{
	UIImage* uiImageConvert = (UIImage*)uiImage;
	if(eventName == eEventName::MOUSE_L_DOWN)
	{
		POINT mousePt = *(POINT*)(parameter);
		if (PtInRect(&uiImageConvert->GetRectInViewPort(), mousePt))
		{
			uiImageConvert->SetTexture("Resources/UI/BtnSelected.png");
			gSoundManager->Play("BGM");
		}
	}
	if (eventName == eEventName::MOUSE_L_UP)
	{
		POINT mousePt = *(POINT*)(parameter);
		if (PtInRect(&uiImageConvert->GetRectInViewPort(), mousePt))
		{
		}
		uiImageConvert->SetTexture("Resources/UI/BtnIdle.png");
	}
}

inline void BtnExitEventListen(eEventName eventName, void * parameter, UIBase * uiImage)
{
	UIImage* uiImageConvert = (UIImage*)uiImage;
	if (eventName == eEventName::MOUSE_L_DOWN)
	{
		POINT mousePt = *(POINT*)(parameter);
		if (PtInRect(&uiImageConvert->GetRectInViewPort(), mousePt))
		{
			uiImageConvert->SetTexture("Resources/UI/BtnSelected.png");
		}
	}
	if (eventName == eEventName::MOUSE_L_UP)
	{
		POINT mousePt = *(POINT*)(parameter);
		if (PtInRect(&uiImageConvert->GetRectInViewPort(), mousePt))
		{
		}
		uiImageConvert->SetTexture("Resources/UI/BtnIdle.png");
	}
}