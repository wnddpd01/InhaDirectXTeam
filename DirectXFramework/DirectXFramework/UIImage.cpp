#include "stdafx.h"
#include "UIImage.h"


UIImage::UIImage(string texturePath, POINT pos, LONG width, LONG height)
	: mTextureUI(nullptr)
	, mSprite(nullptr)
{
	if (texturePath.size() == 0)
		return;
	static float cellSize = 0;
	if (cellSize == 0.f)
	{
		D3DVIEWPORT9 viewPort;
		gD3Device->GetViewport(&viewPort);
		cellSize = (float)viewPort.Width / HORIZONTAL_CELL_NUM;
	}
	D3DXCreateSprite(gD3Device, &mSprite);
	D3DXIMAGE_INFO imageInfo;
	ZeroMemory(&imageInfo, sizeof(D3DXIMAGE_INFO));
	mTextureUI = gTextureManager->GetUITexture(texturePath, imageInfo);
	SetRect(&mDrawRect, 0, 0, imageInfo.Width, imageInfo.Height);
	mWidth = cellSize * width;
	mHeight = cellSize * height;
	mPos.x = cellSize * pos.x;
	mPos.y = cellSize * pos.y;
	D3DXMatrixIdentity(&mMatWorld);
}

UIImage::~UIImage()
{
	mSprite->Release();
	
	for (pair<string, UIImage*> child : mChildSprite)
	{
		SAFE_DELETE(child.second);
	}


}

void UIImage::Render()
{
	if (mbVisible == false)
		return;
	
	D3DXMATRIXA16 matWorld = mMatWorld;
	D3DXMATRIXA16 matS, matT;
	D3DXMatrixScaling(&matS, (float)mWidth / (mDrawRect.right - mDrawRect.left), float(mHeight) / (mDrawRect.bottom - mDrawRect.top), 0);
	D3DXMatrixTranslation(&matT, mPos.x, mPos.y, 0);
	matWorld = matS * matT;
	mSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	mSprite->SetTransform(&matWorld);
	mSprite->Draw(mTextureUI, &mDrawRect, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	mSprite->End();

	for(pair<string, UIImage*> child : mChildSprite)
	{
		child.second->Render();
	}

}

void UIImage::AddChild(string UIname, UIImage* child)
{
	mChildSprite.insert(make_pair(UIname, child));
}


