#pragma once
#include "cCharacter.h"
class cCubeNode; 

class cCubeMan :
	public cCharacter
{
public:
	cCubeMan();
	//~cCubeMan();
protected :
	cCubeNode*			m_pRoot; 
	D3DMATERIAL9		m_stMtl; 
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXVECTOR3			m_LookAt;

public : 
	virtual ~cCubeMan(); 

	virtual void Setup(HeightMap* hMap) override;
	virtual void Update() override; 
	virtual void Render() override;
	void SetLookat(D3DXVECTOR3 lookAt);

};

