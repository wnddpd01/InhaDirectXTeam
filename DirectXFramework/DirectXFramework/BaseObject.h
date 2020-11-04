#pragma once
class BaseObject
{
	string objectName;
public:
	BaseObject();
	virtual ~BaseObject();

	virtual void Update();
	virtual void Render();

	string GetObjectName()
	{
		return objectName;
	}
};
