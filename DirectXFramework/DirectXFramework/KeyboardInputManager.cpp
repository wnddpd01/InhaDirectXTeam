#include "stdafx.h"
#include "KeyboardInputManager.h"

HRESULT KeyboardInputManager::CreateDevice(HWND hWnd)
{
	HRESULT hr;

	mHWnd = hWnd;
	
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&mDI, NULL)))
	{
		return hr;
	}

	// Create Keyboard Instance
	if (FAILED(hr = mDI->CreateDevice(GUID_SysKeyboard, &mKeyboard, NULL)))
	{
		return hr;
	}

	// DirectInput device data struct c_dfDIKeyBoard
	// extern const DIDATAFORMAT c_dfDIKeyboard;�� directinput.h�� ���ǵǾ� �ִ�.
	if (FAILED(hr = mKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
		
	// Cooperative Level�̶� DirectInput�� ����ϴ� Application�� System���� Interaction�� ���� Set
	hr = mKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	if (FAILED(hr))
	{
		return hr;
	}

	// Ű���� ������� �Էºη� �������� �Լ�
	mKeyboard->Acquire(); 

	return S_OK;
}

void KeyboardInputManager::FreeDirectInput()
{
	// Unacquire the device one last time just in
	// the app tried to exit while the device
	if (mKeyboard)
		mKeyboard->Unacquire();
	
	SafeRelease(mKeyboard);
	SafeRelease(mDI);
	
}

void KeyboardInputManager::OnActivate(WPARAM wParam)
{
	if (WA_INACTIVE != wParam && mKeyboard)
	{
		// Make sure the device is acquired, if we are gain in
		mKeyboard->Acquire();
	}
}

HRESULT KeyboardInputManager::ReadData()
{
	HRESULT hr;

	if (NULL == mKeyboard)
	{
		return S_OK;
	}
		
	ZeroMemory(mKeys, sizeof(mKeys));
	hr = mKeyboard->GetDeviceState(sizeof(mKeys), mKeys);

	if (FAILED(hr))
	{
		hr = mKeyboard->Acquire();
		while (hr == DIERR_INPUTLOST)
		{
			hr = mKeyboard->Acquire();
		}
			
		return S_OK;
	}

	return S_OK;
}

BOOL KeyboardInputManager::PressKey(BYTE key)
{
	if (mKeys[key] & 0x80)
	{
		return TRUE;
	}
		
	return FALSE;
}


