#pragma once
#include "BaseObject.h"
#include "BaseObserver.h"

class UIBase :
	public BaseObject, public BaseObserver
{
protected:
	D3DXVECTOR3 mPos;
	float		mWidth;
	float		mHeight;
	bool		mbVisible;
public:
	D3DXVECTOR3 GetPos() const
	{
		return mPos;
	}

	void SetPos(const D3DXVECTOR3& m_pos)
	{
		mPos = m_pos;
	}


	float GetWidth() const
	{
		return mWidth;
	}

	void SetWidth(float m_width)
	{
		mWidth = m_width;
	}


	float GetHeight() const
	{
		return mHeight;
	}

	void SetHeight(float m_height)
	{
		mHeight = m_height;
	}


	bool IsVisible() const
	{
		return mbVisible;
	}

	void SetVisible(bool mb_visible)
	{
		mbVisible = mb_visible;
	}


	RECT GetRectInViewPort();
	
	UIBase();
	virtual ~UIBase();

	function<bool(eEventName, void*, UIBase *)> EventProcess;
	
	bool Update(eEventName eventName, void* parameter) override;
	virtual void Render() override;
};
