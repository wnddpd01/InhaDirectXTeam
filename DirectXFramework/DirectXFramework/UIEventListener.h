#pragma once

#include "EventManager.h"
#include "UIBase.h"
#include "UIImage.h"


inline void PanelEventListen(eEventName eventName, void* parameter, UIBase* uiImage)
{
	static bool isClicked = false;
	uiImage = (UIImage*)uiImage;
	if(eventName == eEventName::MOUSE_L_DOWN)
	{
		POINT mousePt = *(POINT*)(parameter);
		cout << mousePt.x << " " << mousePt.y << endl;
		if (PtInRect(&uiImage->GetRectInViewPort(), mousePt))
		{
			isClicked = true;
		}
	}
	else if(eventName == eEventName::MOUSE_L_UP)
	{
		POINT mousePt = *(POINT*)(parameter);
		isClicked = false;
		if (PtInRect(&uiImage->GetRectInViewPort(), mousePt))
		{
			uiImage->SetVisible(!uiImage->IsVisible());
		}
	}
}