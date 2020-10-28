#pragma once
#include "cUI.h"
class cUIImage : public cUI
{
protected:
	LPD3DXSPRITE		m_pSprite;
	LPDIRECT3DTEXTURE9	m_pTextureUI;
	RECT				m_drawRect;
	POINT m_prevPos;
	bool  m_bMouseClicked;
	RECT GetRectInViewPort();
public:
	cUIImage(wstring texture_path = L"");
	virtual ~cUIImage();

	void Update(MouseEvent mouseEvent) override;
	void Render(D3DXMATRIXA16* parentMat) override;
};

