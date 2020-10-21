#pragma once
#include "cCubePNT.h"
#include "cMtlTex.h"

class cCubeNode :
	public cCubePNT
{
public:
	cCubeNode();
	virtual ~cCubeNode();
	virtual void AddChild(cCubeNode* pChild);
	virtual void Destroy();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	float m_fRotX;
	D3DXVECTOR3 m_vLocalPos;
	D3DXMATRIXA16 m_matLocalTM;
	D3DXMATRIXA16 m_matWorldTM;
	cMtlTex* m_pMtlTex;
	Synthesize(D3DXMATRIXA16 *, m_pParentWorldTM, ParentWorldTM);

protected:
	std::vector<cCubeNode*> m_vecChild;

	Synthesize(float, m_fRotDeltax, RotDeltaX);
};

