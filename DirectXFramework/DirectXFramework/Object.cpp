#include "stdafx.h"
#include "Object.h"


Object::Object()
	: m_ulRefCount(1)
{
	g_pObjectManager->AddObject(this);
}

Object::~Object()
{
	g_pObjectManager->RemoveObject(this);
}

void Object::AddRef()
{
	++m_ulRefCount;
}

void Object::Release()
{
	--m_ulRefCount;
	if (m_ulRefCount == 0)
		delete this;
}