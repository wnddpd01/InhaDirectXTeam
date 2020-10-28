#include "stdafx.h"
#include "cUIImage.h"

#include <iostream>


RECT cUIImage::GetRectInViewPort()
{
	RECT ret = { m_pos.x, m_pos.y, m_width + m_pos.x, m_height + m_pos.y };
	return ret;
}

cUIImage::cUIImage(wstring texture_path)
	: m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_prevPos({0,0})
	, m_bMouseClicked(false)
{
	if (texture_path.size() == 0)
		return;
	D3DXIMAGE_INFO imageInfo;
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	ZeroMemory(&imageInfo, sizeof(D3DXIMAGE_INFO));
	D3DXCreateTextureFromFileEx(g_pD3DDevice, texture_path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE,D3DX_DEFAULT, 0, &imageInfo, NULL, &m_pTextureUI);
	SetRect(&m_drawRect, 0, 0, imageInfo.Width, imageInfo.Height);
	m_width = imageInfo.Width;
	m_height = imageInfo.Height;
}

cUIImage::~cUIImage()
{
	SafeRelease(m_pTextureUI);
	SafeRelease(m_pSprite);
}

void cUIImage::Update(MouseEvent mouseEvent)
{
	if (m_bMouseClicked)
	{
		if (mouseEvent.bClicked == false)
		{
			m_bMouseClicked = false;
		}
		else if (mouseEvent.mousePt != m_prevPos)
		{
			D3DXMATRIXA16 matT;
			D3DXMatrixTranslation(&matT, mouseEvent.mousePt.x - m_prevPos.x, mouseEvent.mousePt.y - m_prevPos.y, 0);
			D3DXVec3TransformCoord(&m_pos, &m_pos, &matT);
			m_prevPos = mouseEvent.mousePt;
		}
	}
	
	
	if(PtInRect(&GetRectInViewPort(), mouseEvent.mousePt))
	{
		if(m_bMouseClicked == false && mouseEvent.bClicked == true)
		{
			m_prevPos = mouseEvent.mousePt;
			m_bMouseClicked = mouseEvent.bClicked;
		}
		mouseEvent.mousePt.x -= m_pos.x;
		mouseEvent.mousePt.y -= m_pos.y;
		for (auto child : m_vecChild)
		{
			child->Update(mouseEvent);
		}
	}

	
}

void cUIImage::Render(D3DXMATRIXA16* parentMat)
{
	D3DXMATRIXA16 matWorld = m_matWorld;
	if(parentMat != NULL)
	{
		matWorld *= *parentMat;
	}
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	matWorld *= matT;
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pTextureUI, &m_drawRect, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0,0,0),D3DCOLOR_ARGB(255,255, 255, 255));
	m_pSprite->End();
	string^ asd;
	for (auto child : m_vecChild)
	{
		child->Render(&matWorld);
	}
}
