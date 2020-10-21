#pragma once
#include "cCharacterSam.h"
class cCubeNode;

class cCubeMan :
	public cCharacterSam
{
public:
	cCubeMan();
	cCubeNode*	m_pRoot;
	D3DMATERIAL9	m_stMtl;
	LPDIRECT3DTEXTURE9 m_pTextrue;
protected:
public :
	virtual ~cCubeMan();
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	void Command(WPARAM key);
	
};

