#pragma once
class tObject
{
public:
	tObject();
	//~tObject();
protected:
	ULONG m_ulRefCount;
public:
	virtual ~tObject(void);

	virtual void AddRef();
	virtual void Release();


	
};

