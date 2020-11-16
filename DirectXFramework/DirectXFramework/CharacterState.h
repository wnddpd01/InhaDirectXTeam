#pragma once
enum class eKeyName;
class Player;

class CharacterState
{
public:
	CharacterState();
	virtual ~CharacterState() {}

	virtual void Enter(Player& player) {}
	virtual CharacterState* HandleInput(Player& player, eEventName eventName, eKeyName &key)
	{
		return nullptr;
	}
	virtual CharacterState* Update(Player& player) { return nullptr; }
};

