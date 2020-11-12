#include "stdafx.h"
#include "UIBase.h"


RECT UIBase::GetRectInViewPort()
{
	RECT ret = { mPos.x, mPos.y, mWidth + mPos.x, mHeight + mPos.y };
	return ret;
}

UIBase::UIBase()
	:mPos(0,0,0)
	,mWidth(0)
	,mHeight(0)
	,mbVisible(false)
{
}


UIBase::~UIBase()
{
}

bool UIBase::Update(eEventName eventName, void* parameter)
{
	return EventProcess(eventName, parameter, this);
}

