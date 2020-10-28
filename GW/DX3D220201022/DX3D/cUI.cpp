#include "stdafx.h"
#include "cUI.h"


cUI::cUI()
	: m_pFont(NULL)
	, m_ifont(0)
	, m_pSprite(NULL)
	, m_stImageInfo(NULL)
	, m_pTextureUI(NULL)
	, m_rc(NULL)
	, m_isLButtonDown(false)
{
	m_box.x = 0;
	m_box.y = 0;
	temp.x = 0;
	temp.y = 0;
}


cUI::~cUI()
{
	Destroy();
}

void cUI::Setup_UI()
{
	
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	D3DXIMAGE_INFO temp_info;
	LPDIRECT3DTEXTURE9 temp_textureUI;
	
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		L"UI/panel-info.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&temp_info,
		NULL,
		&temp_textureUI);

	m_stImageInfo.push_back(temp_info);
	m_pTextureUI.push_back(temp_textureUI);

	
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		L"UI/btn-med-up.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&temp_info,
		NULL,
		&temp_textureUI);

	m_stImageInfo.push_back(temp_info);
	m_pTextureUI.push_back(temp_textureUI);

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		L"UI/btn-main-menu.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&temp_info,
		NULL,
		&temp_textureUI);


	m_stImageInfo.push_back(temp_info);
	m_pTextureUI.push_back(temp_textureUI);

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		L"UI/btn-med-down.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&temp_info,
		NULL,
		&temp_textureUI);


	m_stImageInfo.push_back(temp_info);
	m_pTextureUI.push_back(temp_textureUI);

	RECT rc;
	
	SetRect(&rc, 0, 0, m_stImageInfo[0].Width, m_stImageInfo[0].Height);
	m_rc.push_back(rc);
	SetRect(&rc, 0, 0, m_stImageInfo[1].Width, m_stImageInfo[1].Height);
	m_rc.push_back(rc);
	SetRect(&rc, 0, 0, m_stImageInfo[2].Width, m_stImageInfo[2].Height);
	m_rc.push_back(rc);
	
	m_click = m_pTextureUI[1];
	
}

void cUI::UI_Render()
{
	m_pSprite->Begin((D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE));
	
	Text_Render();

	D3DXMATRIXA16 matT, matS, matR, mat;
	D3DXMatrixTranslation(&matT, 0, 0, 0);

	mat = matT;

	//static float fAngle = 0.0f;
	//fAngle += 0.05f;
	//D3DXMatrixRotationZ(&matR, fAngle);
	//mat = matR * matT;

	m_pSprite->SetTransform(&mat);

	
	temp.x = (m_rc[0].left - m_rc[0].right) / 2;
	temp.y = (m_rc[0].top - m_rc[0].bottom) / 2;
	if (m_box.x == 0)
	{
		m_pSprite->Draw(m_pTextureUI[0], &m_rc[0], &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(190, 255, 255, 255));
		m_pSprite->Draw(m_click, &m_rc[1], &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(m_stImageInfo[0].Width / 4, m_stImageInfo[0].Height / 1.5, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pSprite->Draw(m_pTextureUI[2], &m_rc[2], &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(m_stImageInfo[0].Width / 1.3, m_stImageInfo[0].Height / 7, 0), D3DCOLOR_ARGB(255, 255, 255, 255));

	}
	else
	{
		m_pSprite->Draw(m_pTextureUI[0], &m_rc[0], &D3DXVECTOR3(-m_box.x - temp.x, -m_box.y - temp.y, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(190, 255, 255, 255));
		m_pSprite->Draw(m_click, &m_rc[1], &D3DXVECTOR3(-m_box.x - temp.x, -m_box.y - temp.y, 0), &D3DXVECTOR3(m_stImageInfo[0].Width/4, m_stImageInfo[0].Height/1.5, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pSprite->Draw(m_pTextureUI[2], &m_rc[2], &D3DXVECTOR3(-m_box.x - temp.x, -m_box.y - temp.y, 0), &D3DXVECTOR3(m_stImageInfo[0].Width / 1.3, m_stImageInfo[0].Height / 7, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	}


	
	
	
	m_pSprite->End();
}

void cUI::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


		switch (message)
		{
		case WM_LBUTTONDOWN:
			if (m_click == m_pTextureUI[3])
			{
				m_ifont = 1;
			}
			else
			{
				m_click = m_pTextureUI[2];
			}

			m_isLButtonDown = true;
			break;
		case WM_LBUTTONUP:
			m_isLButtonDown = false;
			break;
		case WM_MOUSEMOVE:
			

			if (m_isLButtonDown)
			{
				m_box.x = LOWORD(lParam);
				m_box.y = HIWORD(lParam);

			}

			
			
				POINT ptCurMouse;
				ptCurMouse.x = LOWORD(lParam);
				ptCurMouse.y = HIWORD(lParam);
				if ((-m_box.x - temp.x+m_rc[1].right > ptCurMouse.x &&  -m_box.x - temp.x+m_rc[1].left < ptCurMouse.x) &&
					(-m_box.y - temp.y+m_rc[1].bottom > ptCurMouse.y &&  -m_box.y - temp.y+m_rc[1].top < ptCurMouse.y))
				{
					m_click = m_pTextureUI[3];
				}
				else
				{
					m_click = m_pTextureUI[1];
				}


			
			

			break;
		}
	
	
}

void cUI::Create_Font()
{
	/*D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 50;
	fd.Width = 25;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;

	wcscpy_s(fd.FaceName, L"±¼¸²Ã¼");

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);*/



	//HDC hdc = CreateCompatibleDC(0);
	//LOGFONT lf;
	//ZeroMemory(&lf, sizeof(LOGFONT));
	//lf.lfHeight = 25;
	//lf.lfWidth = 12;
	//lf.lfWeight = 500;
	//lf.lfItalic = false;
	//lf.lfUnderline = false;
	//lf.lfStrikeOut = false;
	//lf.lfCharSet = DEFAULT_CHARSET;
	//wcscpy_s(lf.lfFaceName, L"±¼¸²Ã¼");
	//AddFontResourceA("font/umberto.ttf");
	//wcscpy_s(lf.lfFaceName, L"umberto");

	//HFONT hFont;
	//HFONT hFontOld;

	//hFont = CreateFontIndirect(&lf);
	//hFontOld = (HFONT)SelectObject(hdc, hFont);

	//D3DXCreateText(g_pD3DDevice, hdc, L"Direct3D", 0.001f, 0.01f, &m_p3DText, 0, 0);

	//SelectObject(hdc, hFontOld);
	//DeleteObject(hFont);
	//DeleteDC(hdc);
}

void cUI::Text_Render()
{
	string sText[3];
	sText[0] = ("Å»Ãâ?");
	sText[1] = ("Å»ÃâÇÏ¿´½À´Ï´Ù.");
	sText[2] = ("°ÔÀÓ¿À¹ö");
	
	
	RECT rctemp;

	if (temp.x == 0)
	{
		SetRect(&rctemp, m_stImageInfo[0].Width / 4,
			m_stImageInfo[0].Height / 4,
			m_stImageInfo[0].Width / 4,
			m_stImageInfo[0].Height / 4);
	}
	else
	{
		SetRect(&rctemp, m_stImageInfo[0].Width / 4 + m_rc[0].left + m_box.x + temp.x,
			m_stImageInfo[0].Height / 4 + m_rc[0].top + m_box.y + temp.y,
			m_stImageInfo[0].Width / 4 + m_rc[0].right + m_box.x + temp.x,
			m_stImageInfo[0].Height / 4 + m_rc[0].bottom + m_box.y + temp.y);
	}
	LPD3DXFONT pFont = g_pFontManager->GetFont(cFontManager::E_DEFAULT);


	pFont->DrawTextA(NULL,
		sText[m_ifont].c_str(),
		sText[m_ifont].length(),
		&rctemp,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));



	/*D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 50.0f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 4.0f);
	D3DXMatrixTranslation(&matT, -2.0f, 1.0f, 0.0f);
	matWorld = matS* matR*matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_p3DText->DrawSubset(0);*/
}

void cUI::Destroy()
{

	SafeRelease(m_pFont);
	SafeRelease(m_click);
	SafeRelease(m_pSprite);

	for each(auto p in m_pTextureUI)
		SafeRelease(p);
	m_pTextureUI.clear();

	m_stImageInfo.clear();

	
}
