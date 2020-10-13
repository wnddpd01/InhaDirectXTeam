#pragma once
#include "cGeometry.h"

class cCharacterController;

class cHSMyCharacter : public cGameObject
{
private:
	ST_ASE_SCENE				m_stScene;
	cGeometry*					m_pModel;

public:

private:
public:
	cHSMyCharacter();
	~cHSMyCharacter();

	void Setup(char* _szFilePath, D3DXVECTOR3 _vScale = D3DXVECTOR3(1.f,1.f,1.f));
	void Update(D3DXMATRIXA16* _matParent);
	void Render();


};

