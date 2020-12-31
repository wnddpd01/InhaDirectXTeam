#pragma once
#include "ChaserState.h"

class IdleChaserState :
	public ChaserState
{
private :
	DWORD mIdleEnterTime;
public :
	IdleChaserState();
	virtual ~IdleChaserState();

	virtual void Enter(Chaser* chaser) override;
	ChaserState* Update(Chaser* chaser) override;
};

