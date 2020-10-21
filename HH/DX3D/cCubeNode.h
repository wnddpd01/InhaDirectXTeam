#pragma once
#include "cCubePNT.h"
class cCubeNode :
	public cCubePNT
{
public:
	cCubeNode();
	//~cCubeNode();
protected:
	float			m_fRotX;
	D3DXVECTOR3		m_vLocalPos;
	D3DXMATRIXA16	m_matLocalTM;
	D3DXMATRIXA16	m_matWorldTM;
	std::vector<cCubeNode*>		m_vecChild;

	Synthesize(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	Synthesize(float, m_fRotDeltaX, RotDeltaX);

public:
	virtual ~cCubeNode(void);
	
	virtual void AddChild(cCubeNode* cChild);
	virtual void Destroy();
	virtual void SetMineCraftTexture(float left, float top, float width, float depth, float hight);

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	
	
};

