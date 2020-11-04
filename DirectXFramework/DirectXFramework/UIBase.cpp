#include "stdafx.h"
#include "UIBase.h"


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

void UIBase::Update(eEventName eventName, void* parameter)
{
	EventProcess(eventName, parameter, this);
}

void UIBase::Render()
{
}
