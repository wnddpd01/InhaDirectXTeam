#pragma once
#include "BaseObject.h"
#include "BaseObserver.h"
class UIBase :
	public BaseObject, public BaseObserver
{
public:
	UIBase();
	~UIBase();
};

