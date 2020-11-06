#include "stdafx.h"
#include "KeyboardInputManager.h"

bool KeyboardInputManager::ChangeKeyState()
{
	if (GetKeyState('W') & 0x8000)
	{
		mKeyState.bFrontKey = TRUE;
	}
	else
	{
		mKeyState.bFrontKey = FALSE;
	}
	
	if (GetKeyState('S') & 0x8000)
	{
		mKeyState.bBackKey = TRUE;
	}
	else
	{
		mKeyState.bBackKey = FALSE;
	}
	
	if (GetKeyState('A') & 0x8000)
	{
		mKeyState.bLeftKey = TRUE;
	}
	else
	{
		mKeyState.bLeftKey = FALSE;
	}
	
	if (GetKeyState('D') & 0x8000)
	{
		mKeyState.bRightKey = TRUE;
	}
	else
	{
		mKeyState.bRightKey = FALSE;
	}
	
	if (GetKeyState('Q') & 0x8000)
	{
		mKeyState.bEquipmentChangeLeft = TRUE;
	}
	else
	{
		mKeyState.bEquipmentChangeLeft = FALSE;
	}

	if (GetKeyState('E') & 0x8000)
	{
		mKeyState.bEquipmentChangeRight = TRUE;
	}
	else
	{
		mKeyState.bEquipmentChangeRight = FALSE;
	}

	if (GetKeyState(VK_ESCAPE) & 0x8000)
	{
		mKeyState.bInteractionKey = TRUE;
	}
	else
	{
		mKeyState.bInteractionKey = FALSE;
	}

	if (GetKeyState(VK_SHIFT) & 0x8000)
	{
		mKeyState.bRunKey = TRUE;
	}
	else
	{
		mKeyState.bRunKey = FALSE;
	}


	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		mKeyState.bInteractionKey = TRUE;
	}
	else
	{
		mKeyState.bInteractionKey = FALSE;
	}

	return mKeyState.isAllFalse();
}

void KeyboardInputManager::Update()
{
	if(ChangeKeyState())
	{
		return;
	}
	
	eKeyName keyName;
	
	if(mKeyState.bFrontKey == TRUE && mKeyState.bLeftKey == TRUE)
	{
		keyName = eKeyName::KEY_FRONTLEFT_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}
	else if (mKeyState.bFrontKey == TRUE && mKeyState.bRightKey == TRUE)
	{
		keyName = eKeyName::KEY_FRONTRIGHT_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}
	else if (mKeyState.bBackKey == TRUE && mKeyState.bLeftKey == TRUE)
	{
		keyName = eKeyName::KEY_BACKLEFT_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}
	else if (mKeyState.bBackKey == TRUE && mKeyState.bRightKey == TRUE)
	{
		keyName = eKeyName::KEY_BACKRIGHT_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}
	else if (mKeyState.bFrontKey == TRUE)
	{
		keyName = eKeyName::KEY_FRONT_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}
	else if (mKeyState.bBackKey == TRUE)
	{
		keyName = eKeyName::KEY_FRONT_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}
	else if (mKeyState.bRightKey == TRUE)
	{
		keyName = eKeyName::KEY_RIGHT_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}
	else if (mKeyState.bLeftKey == TRUE)
	{
		keyName = eKeyName::KEY_LEFT_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}

	if(mKeyState.bEquipmentChangeLeft == TRUE)
	{
		keyName = eKeyName::KEY_EQUIPCHAGELFFT_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}
	if (mKeyState.bEquipmentChangeRight == TRUE)
	{
		keyName = eKeyName::KEY_EQUIPCHAGERIGHT_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}
	if (mKeyState.bInteractionKey == TRUE)
	{
		keyName = eKeyName::KEY_INTERACTION_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}
	if (mKeyState.bRunKey == TRUE)
	{
		keyName = eKeyName::KEY_RUN_DOWN;
		gEventManager->EventOccurred(eEventName::KEY_DOWN, &keyName);
	}
}