#pragma once

#include "cMtrlTex.h"

struct ST_POS_SAMPLE
{
	int				n;
	D3DXVECTOR3		v;
};

struct ST_ROT_SAMPLE
{
	int				n;
	D3DXQUATERNION	q;
};

struct ST_ASE_SCENE
{
	int nFirstFrame;
	int nLastFrame;
	int nFrameSpeed;
	int nTicksPerFrame;
};


class cGeometry : public cObject
{
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, MatWorld);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matLocal, MatLocal);
	SYNTHESIZE_PASS_BY_REF(vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	SYNTHESIZE_ADD_REF(cMtrlTex*, m_pMtrlTex, MtrlTex);

private:
	vector<cGeometry*>			m_vecChild;
	string						m_sMyName;

	SYNTHESIZE_PASS_BY_REF(vector<ST_POS_SAMPLE>, m_vecPosTrack, PosTrack);
	SYNTHESIZE_PASS_BY_REF(vector<ST_ROT_SAMPLE>, m_vecRotTrack, RotTrack);

public:


private:
public:
	cGeometry();
	~cGeometry();

	void Update(int _nKeyFrame, D3DXMATRIXA16* _pParentsMat = NULL);
	void Render();


	cGeometry*		GetMyParents(string _sParentsName);
	bool			AddMyChild(cGeometry* _pChild);
	void			SetMyName(char * _pName);


	void CalcLocalTM(cGeometry* pParent);
	void CalcLocalTranslationMatrix(IN int _nKeyFrame, OUT D3DXMATRIXA16& _mat);
	void CalcLocalRotationMatrix(IN int _nKeyFrame, OUT D3DXMATRIXA16& _mat);
};

