#pragma once
#include "UIBase.h"
class UIImage :
	public UIBase
{
	LPDIRECT3DTEXTURE9	mTextureUI;
	LPD3DXSPRITE		mSprite;
	RECT				mDrawRect;
public:
	D3DXMATRIXA16 mMatWorld;
	UIImage(string texturePath);
	virtual ~UIImage();

	void Render() override;

	void SetTexture(string newTexturePath)
	{
		D3DXIMAGE_INFO imageInfo;
		ZeroMemory(&imageInfo, sizeof(D3DXIMAGE_INFO));
		mTextureUI = gTextureManager->GetUITexture(newTexturePath, imageInfo);
	}
};

