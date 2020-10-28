#include "stdafx.h"
#include "cFontManager.h"


cFontManager::cFontManager()
{
}


cFontManager::~cFontManager()
{
}

LPD3DXFONT cFontManager::GetFont(eFontType e)
{
	if(m_mapFont.find(e) != m_mapFont.end())
	{
		return m_mapFont[e];
	}
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	switch (e)
	{
	case E_DEFAULT:
	{
		fd.Height = 25;
		fd.Width = 12;
		fd.Weight = FW_BOLD;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;

		wcscpy_s(fd.FaceName, L"±¼¸²Ã¼");
	}
	break;
	case E_QUEST:
	{
		fd.Height = 50;
		fd.Width = 25;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;

		AddFontResource(L"Font/umberto.ttf");
		wcscpy_s(fd.FaceName, L"umberto");
	}
	break;
	}
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
	return m_mapFont[e];
}

void cFontManager::Destroy()
{
	for (auto font : m_mapFont)
	{
		SafeRelease(font.second);
	}
	m_mapFont.clear();
}
