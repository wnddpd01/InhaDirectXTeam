#include "stdafx.h"
#include "UIImage.h"
#include "UIAnimation.h"


UIAnimation::UIAnimation(string texturePath, POINT pos, LONG width, LONG height, LONG srcNumRaw) 
	: UIImage(texturePath, pos, width, height)
	, mNumRaw(srcNumRaw)
{
	mLenOneRaw = GetDrawRect().bottom / mNumRaw;
	mCntTime = 0.f;
	mTimePerFrame = 1.f / mNumRaw;

	SetRect(&mAnimRect, 0, 0, GetDrawRect().right, mLenOneRaw);
}

UIAnimation::~UIAnimation()
{

}

void UIAnimation::Update()
{
	mCntTime += gDeltaTime;
	if (mCntTime > mTimePerFrame)
	{
		if (mAnimRect.bottom >= GetDrawRect().bottom)
		{
			SetRect(&mAnimRect, 0, 0, GetDrawRect().right, mLenOneRaw);
		}
		else 
		{
			mAnimRect.top += mLenOneRaw;
			mAnimRect.bottom += mLenOneRaw;
		}
		SetDrawRect(mAnimRect);
	}
}

void UIAnimation::Render()
{
	UIImage::Render();
}

