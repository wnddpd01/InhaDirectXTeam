#pragma once
#include <functional>

#include "cUIImage.h"
class cUIButton :
	public cUIImage
{
	LPDIRECT3DTEXTURE9 m_pTextureBtn[3];
public:
	string name;
	cUIButton();
	std::function<void()> Clicked;
	void Update(MouseEvent mouseEvent) override;
};

