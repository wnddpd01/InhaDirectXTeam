#include "stdafx.h"
#include "UIImage.h"


UIImage::UIImage(string texturePath)
	: mTextureUI(nullptr)
	, mSprite(nullptr)
{
	if (texturePath.size() == 0)
		return;
	D3DXCreateSprite(gD3Device, &mSprite);
	D3DXIMAGE_INFO imageInfo;
	ZeroMemory(&imageInfo, sizeof(D3DXIMAGE_INFO));
	mTextureUI = gTextureManager->GetUITexture(texturePath, imageInfo);
	SetRect(&mDrawRect, 0, 0, imageInfo.Width, imageInfo.Height);
	mWidth = imageInfo.Width;
	mHeight = imageInfo.Height;
	D3DXMatrixIdentity(&mMatWorld);
}

UIImage::~UIImage()
{
}

void UIImage::Render()
{
	if (mbVisible == false)
		return;
	D3DXMATRIXA16 matWorld = mMatWorld;
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, mPos.x, mPos.y, mPos.z);
	matWorld *= matT;
	mSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	mSprite->SetTransform(&matWorld);
	mSprite->Draw(mTextureUI, &mDrawRect, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	mSprite->End();
}
