#pragma once
#include "cObject.h"
#include "cMtlTex.h"

class cFrame :
	public cObject
{
	
public:
	cFrame();
	~cFrame();
private:
	Synthesize_Pass_by_Ref(vector <ST_PNT_VERTEX>, m_vecVertex, Vertex);
	Synthesize_Pass_by_Ref(vector <ST_PNT_VERTEX>, m_vecVertex4Index, Vertex4Index);
	
	Synthesize_Pass_by_Ref(vector <ST_ABC_INDEX>, m_vecIndex, Index);
	Synthesize_Pass_by_Ref(vector <DWORD>, m_vecAttrBuf, AttrBuf);
	
	Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matLocalTM, LocalTM);
	Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matWorldTM, WorldTM);

	Synthesize_Add_Ref(cMtlTex*, m_pMtlTex, MtlTex);
	vector<cFrame*>	m_vecChild;

	Synthesize_Pass_by_Ref(vector<ST_POS_SAMPLE>, m_vecPosTrack, PosTrack);
	Synthesize_Pass_by_Ref(vector<ST_ROT_SAMPLE>, m_vecRotTrack, RotTrack);

	LPD3DXMESH			m_pMesh;

public:
	void Update(int nKeyFrame, D3DXMATRIXA16* pmatParent);
	void Render();
	void RenderIndex();
	void RenderMesh();
	void AddChild(cFrame* pChild);
	void Destroy();
	void CalsOriginLocalTM(D3DXMATRIXA16* pmatParent);

	void CalcLocalT(IN int nKeyFrame, OUT D3DXMATRIXA16& matT);
	void CalcLocalR(IN int nKeyFrame, OUT D3DXMATRIXA16& matR);

	DWORD		m_dwFirstFrame;
	DWORD		m_dwLastFrame;
	DWORD		m_dwFrameSpeed;
	DWORD		m_dwTicksPerFrame;

	int			GetKeyFrame();

private:
	int							m_nNumTri;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	IDirect3DIndexBuffer9*		m_pIB;
	
	
	
public:
	void BuildVB(vector<ST_PNT_VERTEX>& vecVertex);
	void BuildIB();
	void BuildMesh();
};

