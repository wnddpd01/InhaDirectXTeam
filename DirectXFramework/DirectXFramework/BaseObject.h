#pragma once
class BaseObject
{
	string objectName;
public:
	BaseObject();
	~BaseObject();

	void Update();
	void Render();
	
	string GetObjectName()
	{
		return objectName;
	}
};

