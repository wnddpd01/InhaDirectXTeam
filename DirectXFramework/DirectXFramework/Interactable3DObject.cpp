#include "stdafx.h"
#include "Interactable3DObject.h"

bool Interactable3DObject::CheckCondition()
{
	for (vector<function<bool()>>::value_type condition : mInteractionCondition)
	{
		if (!condition())
		{
			return false;
		}
	}
	return true;
}

void Interactable3DObject::DoBehavior()
{
	for (function<void()> behavior : mInteractionBehavior)
	{
		behavior();
	}
	cout << GetObjectName() << " : " << " interaction Behavior" << endl;
}

Interactable3DObject::Interactable3DObject()
	: mbTryInteractionCalled(false)
{
	mObjectTag = eObjTag::INTERACTABLE_OBJECT;
	mShaderPath = eShaderPath::PATH1;
}

Interactable3DObject::~Interactable3DObject()
{
}

void Interactable3DObject::Update()
{
	if(CheckCondition())
	{
		DoBehavior();
	}

	if(mbTryInteractionCalled == true)
	{
		mbTryInteractionCalled = false;
	}
	
	Static3DObject::Update();
}

bool Interactable3DObject::TryInteraction()
{
	mbTryInteractionCalled = true;
	return CheckCondition();
}

void Interactable3DObject::ChangeToStaticObject()
{
	mShaderPath = eShaderPath::PATH1;
	mObjectTag = eObjTag::STATIC_OBJECT;
}
