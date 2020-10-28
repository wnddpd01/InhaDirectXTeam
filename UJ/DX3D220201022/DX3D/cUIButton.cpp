#include "stdafx.h"
#include "cUIButton.h"

#include <iostream>

cUIButton::cUIButton()
{
	D3DXIMAGE_INFO imageInfo;
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	ZeroMemory(&imageInfo, sizeof(D3DXIMAGE_INFO));
	D3DXCreateTextureFromFileEx(g_pD3DDevice, L"UI/btnIdle.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, &imageInfo, NULL, &m_pTextureBtn[0]);
	D3DXCreateTextureFromFileEx(g_pD3DDevice, L"UI/btnHovered.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, &imageInfo, NULL, &m_pTextureBtn[1]);
	D3DXCreateTextureFromFileEx(g_pD3DDevice, L"UI/btnClicked.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, &imageInfo, NULL, &m_pTextureBtn[2]);
	SetRect(&m_drawRect, 0, 0, imageInfo.Width, imageInfo.Height);
	m_width = imageInfo.Width;
	m_height = imageInfo.Height;
	m_pTextureUI = m_pTextureBtn[0];
}


cUIButton::~cUIButton()
{
}

void cUIButton::Update(MouseEvent mouseEvent)
{
	cout << mouseEvent.bClicked << endl;
	if(PtInRect(&GetRectInViewPort(), mouseEvent.mousePt))
	{
		if (mouseEvent.bClicked == true)
		{
			m_pTextureUI = m_pTextureBtn[2];
		}
		else
		{
			m_pTextureUI = m_pTextureBtn[1];
		}
	}
	else
	{
		m_pTextureUI = m_pTextureBtn[0];
	}
}

