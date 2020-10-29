#include "stdafx.h"
#include "cUI.h"


RECT cUI::GetRectInViewPort()
{
	RECT ret = { m_pos.x, m_pos.y, m_width + m_pos.x, m_height + m_pos.y };
	return ret;
}

cUI::cUI()
	: isVisible(true)
{
	m_pos = { 0,0,0 };
	m_height = 0;
	m_width = 0;
	D3DXMatrixIdentity(&m_matWorld);
}


cUI::~cUI()
{
}



void cUI::AddChild(cUI* child)
{
	m_vecChild.push_back(child);
}

void cUI::Update(MouseEvent& mouseEvent)
{
	POINT prevMousePt = mouseEvent.mousePt;
	if(PtInRect(&GetRectInViewPort(), mouseEvent.mousePt))
	{
		for (auto ui : m_vecChild)
		{
			mouseEvent.mousePt.x -= m_pos.x;
			mouseEvent.mousePt.y -= m_pos.y;
			ui->Update(mouseEvent);
		}
	}
	mouseEvent.mousePt = prevMousePt;
}

void cUI::Render(D3DXMATRIXA16* parentMat)
{
	for (auto m_vec_child : m_vecChild)
	{
		m_vec_child->Render(&m_matWorld);
	}
}
