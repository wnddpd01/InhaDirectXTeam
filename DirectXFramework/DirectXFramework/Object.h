#pragma once

class Object
{
public:
	Object();
protected:
	ULONG m_ulRefCount;
public:
	virtual ~Object(void);

	virtual void AddRef();
	virtual void Release();
};