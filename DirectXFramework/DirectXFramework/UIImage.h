#pragma once
#include "UIBase.h"
class UIImage :
	public UIBase
{
	LPDIRECT3DTEXTURE9	mTextureUI;
	LPD3DXSPRITE		mSprite;
	RECT				mDrawRect;

	vector<UIImage*>	mChildSprite;
public:
	D3DXMATRIXA16 mMatWorld;
	UIImage(string texturePath);
	virtual ~UIImage();

	void Render() override;

	void AddChild(UIImage* child);
	void Destory();
	
	void SetTexture(string newTexturePath)
	{
		D3DXIMAGE_INFO imageInfo;
		ZeroMemory(&imageInfo, sizeof(D3DXIMAGE_INFO));
		mTextureUI = gTextureManager->GetUITexture(newTexturePath, imageInfo);
	}
};

