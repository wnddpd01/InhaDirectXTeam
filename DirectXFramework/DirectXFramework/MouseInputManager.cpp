#include "stdafx.h"
#include "MouseInputManager.h"


HRESULT MouseInputManager::CreateDevice(HWND hWnd)
{
	HRESULT hr;

	mHWnd = hWnd;
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&mDI, NULL)))
	{
		return hr;
	}

	if(FAILED(hr = mDI->CreateDevice(GUID_SysMouse,&mMouse,NULL)))
	{
		return hr;
	}
	if (FAILED(hr = mMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return hr;
	}

	hr = mMouse->SetCooperativeLevel(mHWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	if(FAILED(hr))
	{
		return hr;
	}

	mMouse->Acquire();

	return S_OK;
}

HRESULT MouseInputManager::ReadDate()
{
	HRESULT hr;

	if (NULL == mMouse)
	{
		return S_OK;
	}
		
	ZeroMemory(&mMouseState2, sizeof(mMouseState2));
	
	hr = mMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &mMouseState2);

	if(FAILED(hr))
	{
		hr = mMouse->Acquire();
		while (hr == DIERR_INPUTLOST)
		{
			hr = mMouse->Acquire();
		}
	}

	mMouseFrameDistance.x = mMouseState2.lX;
	mMouseFrameDistance.y = mMouseState2.lY;

	return S_OK;
}

void MouseInputManager::FreeDirectInput()
{
	if (mMouse)
		mMouse->Unacquire();
	SafeRelease(mMouse);
	SafeRelease(mDI);
}

void MouseInputManager::OnActivate(WPARAM wParam)
{
	if(WA_INACTIVE != wParam && mMouse)
	{
		mMouse->Acquire();
	}
}

BOOL MouseInputManager::PushLeft()
{
	return (mMouseState2.rgbButtons[0] & 0x80) ? TRUE : FALSE;
}

BOOL MouseInputManager::PushRight()
{
	return (mMouseState2.rgbButtons[1] & 0x80) ? TRUE : FALSE;
}

BOOL MouseInputManager::PushMiddle()
{
	return (mMouseState2.rgbButtons[2] & 0X80) ? TRUE : FALSE;
}


