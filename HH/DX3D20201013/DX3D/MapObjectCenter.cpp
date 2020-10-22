#include "stdafx.h"
#include "MapObjectCenter.h"
#include "MapObject.h"


MapObjectCenter::MapObjectCenter()
{
}


MapObjectCenter::~MapObjectCenter()
{
	for (auto p : m_pVecMapObj)
	{
		delete p;
	}
}

vector<MapObject*>& MapObjectCenter::GetVecMapObj()
{
	return m_pVecMapObj;
}

void MapObjectCenter::AddMapObj(MapObject* p)
{
	m_pVecMapObj.push_back(p);
}

void MapObjectCenter::Setup()
{
	for (auto p : m_pVecMapObj)
	{
		p->Setup();
	}
}

void MapObjectCenter::Update()
{
	for (auto p : m_pVecMapObj)
	{
		p->Update();
	}
}

void MapObjectCenter::Render()
{
	for (auto p : m_pVecMapObj)
	{
		p->Render();
	}
}