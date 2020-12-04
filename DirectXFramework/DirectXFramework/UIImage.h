#pragma once
#include "UIBase.h"
class UIImage :
	public UIBase
{
	LPDIRECT3DTEXTURE9	mTextureUI;
	LPD3DXSPRITE		mSprite;
	RECT				mDrawRect;

	//vector<UIImage*>	mChildSprite;
	map<string, UIImage*> mChildSprite;
public:
	D3DXMATRIXA16 mMatWorld;
	UIImage(string texturePath);
	virtual ~UIImage();

	RECT GetDrawRect() const { return mDrawRect; }
	void SetDrawRect(RECT drawRect) { mDrawRect = drawRect; }

	void Render() override;

	void AddChild(string UIname, UIImage* child);

	UIImage* GetChildUI(string UIname)
	{	
		return mChildSprite.find(UIname)->second;
	}
	
	
	void SetTexture(string newTexturePath)
	{
		D3DXIMAGE_INFO imageInfo;
		ZeroMemory(&imageInfo, sizeof(D3DXIMAGE_INFO));
		mTextureUI = gTextureManager->GetUITexture(newTexturePath, imageInfo);
	}
};

