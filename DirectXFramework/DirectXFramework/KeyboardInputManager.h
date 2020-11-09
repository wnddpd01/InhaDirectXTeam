#pragma once
#include "EventManager.h"
#include "Singleton.h"

#define gKeyboardInputManager KeyboardInputManager::GetInstance()

enum class eKeyName { KEY_LEFT_DOWN = 0, KEY_RIGHT_DOWN, KEY_FRONT_DOWN, KEY_BACK_DOWN, KEY_FRONTLEFT_DOWN, KEY_FRONTRIGHT_DOWN,KEY_BACKLEFT_DOWN, KEY_BACKRIGHT_DOWN,
	KEY_INTERACTION_DOWN,KEY_EQUIPCHAGELFFT_DOWN, KEY_EQUIPCHAGERIGHT_DOWN , KEY_RUN_DOWN};

struct KeyState
{
	bool bFrontKey;
	bool bBackKey;
	bool bLeftKey;
	bool bRightKey;
	bool bInteractionKey;
	bool bRunKey;
	bool bEquipmentChangeRight;
	bool bEquipmentChangeLeft;
	
	bool isAllFalse()
	{
		return (bFrontKey | bBackKey | bLeftKey | bRightKey | bInteractionKey | bRunKey | bEquipmentChangeRight | bEquipmentChangeLeft) == 0;
	}
};

class KeyboardInputManager : public Singleton<KeyboardInputManager>
{
private:
	KeyState mKeyState;
public:
	
	bool ChangeKeyState();
	void Update();
};
