#pragma once
enum class eKeyName;
class cZealot;

class CharacterState
{
public:
	CharacterState();
	virtual ~CharacterState() {}

	virtual void Enter(cZealot& zealot) {}
	virtual CharacterState* HandleInput(cZealot& zealot, eEventName eventName, eKeyName &key)
	{
		return nullptr;
	}
	virtual CharacterState* Update(cZealot& zealot) { return nullptr; }
};

