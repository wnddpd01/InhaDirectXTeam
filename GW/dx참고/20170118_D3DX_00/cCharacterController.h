#pragma once
#include "iMap.h"

#define Max_JumpAcc		3.0f

class cObjMap;
class cHSMyCharacter;

class cCharacterController : public cObject
{
private:
	cHSMyCharacter*	m_pCharacter;
	D3DXMATRIXA16	m_matWorld;
	D3DXVECTOR3		m_vPosition;
	float			m_fRotY;
	float			m_fSpeed;

	iMap *			m_pMap;

	bool			m_bJump;
	bool			m_bInAir;
	float			m_fJumpAcc;

private:
	void Jump();
	void InAir();
public:
	cCharacterController();
	~cCharacterController();

	void Setup(char* _szFilePath);
	void Update();
	void Render();

	void SetMap(iMap * _pMap) { m_pMap = _pMap; }
	D3DXMATRIXA16* GetWorldTM() { return &m_matWorld; }
	D3DXVECTOR3* GetPosition() { return &m_vPosition; }
};