#include "stdafx.h"
#include "tObject.h"


tObject::tObject()
	: m_ulRefCount(1)
{
	g_pObjectManager->AddObject(this);
}


tObject::~tObject()
{
}

void tObject::AddRef()
{
	++m_ulRefCount;
}

void tObject::Release()
{
	--m_ulRefCount;
	if (m_ulRefCount == 0)
		delete this;
}
