#pragma once

class ST_BONE;

class cSkinnedMesh
{
public:
	cSkinnedMesh();
	~cSkinnedMesh();
	cSkinnedMesh(char * szFolder, char*szFilename);
	void Load(char* szFolder, char* szFilename);
	void Destroy();
	void UpdateAndRender();
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pMatWorld);
	void SetRandomTrackPosition();
	void SetTransform(D3DXMATRIXA16* pMat);
	D3DXMATRIXA16 m_matWorldTM;
	Synthesize(D3DXVECTOR3, m_vMin, Min);
	Synthesize(D3DXVECTOR3, m_vMax, Max);

protected:
	LPD3DXFRAME m_pRoot;
	LPD3DXANIMATIONCONTROLLER m_pAnimController;
	float		m_fBlendTime;
	float		m_fPassedBlendTime;
	UINT		m_animationStartTime;
	bool		m_isAnimBlend;
public :
	void Setup(char * szFolder, char * szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
};

