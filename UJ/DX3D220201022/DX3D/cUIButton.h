#pragma once
#include "cUIImage.h"
class cUIButton :
	public cUIImage
{
	LPDIRECT3DTEXTURE9 m_pTextureBtn[3];
public:
	cUIButton();
	virtual ~cUIButton();

	void Update(MouseEvent mouseEvent) override;
};

