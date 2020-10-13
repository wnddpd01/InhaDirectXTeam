#pragma once
#include "cCharacterT.h"
#include "tGroup.h"

class cCubeNode;

class cCubeMan :
	public cCharacterT
{
public:
	cCubeMan();
	//~cCubeMan();

protected:
	cCubeNode*			m_pRoot;
	D3DMATERIAL9		m_stMtl;
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXVECTOR3			m_prevPosition;
	
public:
	virtual ~cCubeMan();
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	bool MoveToUpdate(D3DXVECTOR3 dest);
	void objUpdate(std::vector<tGroup*>& vecSufGroup);
	
	
};

