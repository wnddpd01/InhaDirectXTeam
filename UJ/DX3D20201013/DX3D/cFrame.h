#pragma once
#include "cObject.h"
#include "cMtlTex.h"

class cFrame :
	public cObject
{
public:
	cFrame();
	~cFrame();
private :
	Synthesize_Pass_by_Ref(vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matLocalTM, LocalTM);
	Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matWorldTM, WorldTM);
	Synthesize_Add_Ref(cMtlTex*, m_pMtlTex, MtlTex);
	vector<cFrame*> m_vecChild;

	Synthesize_Pass_by_Ref(vector<ST_POS_SAMPLE>, m_vecPosTrack, PosTrack);
	Synthesize_Pass_by_Ref(vector<ST_ROT_SAMPLE>, m_vecRotTrack, RotTrack);
public:
	void Update(int nKeyFrame, D3DXMATRIXA16* pMatParent);
	void Render();
	void AddChild(cFrame * pChild);
	void Destroy();
	void CaclOriginLocalTM(D3DXMATRIXA16* pMatParent);
	void CalcLocalT(IN int nKeyFrame, OUT D3DXMATRIXA16& matT);
	void CalcLocalR(IN int nKeyFrame, OUT D3DXMATRIXA16& matT);
	int GetKeyFrame();
	DWORD	m_dwFirstFrame;
	DWORD	m_dwLastFrame;
	DWORD	m_dwFrameSpeed;
	DWORD	m_dwTicksPerFrame;

private :
	int	m_nNumTri;
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	LPD3DXMESH m_pObjMesh;
public :
	void BuildVB(vector<ST_PNT_VERTEX>& vecVertex);
	void BuildIB(vector<ST_PNT_VERTEX>& vecVertex);
	void BuildAB(vector<ST_PNT_VERTEX>& vecVertex);
};

