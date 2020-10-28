#include "stdafx.h"
#include "cUI.h"


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

void cUI::Update(MouseEvent mouseEvent)
{
	RECT rectInViewport = { m_pos.x, m_pos.y, m_width + m_pos.x, m_height + m_pos.y };

	if(PtInRect(&rectInViewport, mouseEvent.mousePt))
	{
		for (auto ui : m_vecChild)
		{
			ui->Update(mouseEvent);
		}
	}
}

void cUI::Render(D3DXMATRIXA16* parentMat)
{
	for (auto m_vec_child : m_vecChild)
	{
		m_vec_child->Render(&m_matWorld);
	}
}
