#pragma once
class cSkinnedMesh;

class OBB
{
public:
	OBB();
	~OBB();
private:
	D3DXVECTOR3 m_vOriCenterPos;
	D3DXVECTOR3 m_vOriAxisDir[3];
	vector<ST_PC_VERTEX> m_BoxDrawVertex;
	D3DXVECTOR3 m_vCenterPos;
	D3DXVECTOR3 m_vAxisDir[3];
	float m_fAxisLen[3];

	float m_fAxisHalfLen[3];

	D3DXMATRIXA16 m_matWorldTM;

public:
	void Setup(cSkinnedMesh* pSkinnedMesh);
	void Setup(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax);
	void Update(D3DXMATRIXA16* pmatWorld);
	static bool IsCollision(OBB* pOBB1, OBB* pOBB2);

	void OBBBOX_Render(D3DCOLOR c);
};
