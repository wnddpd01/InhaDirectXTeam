#pragma once
class Ray
{
private:
	enum eRaySpace
	{
		E_NONE,
		E_VIEW,
		E_WORLD,
	};

	eRaySpace m_eRaySpace;
	D3DXVECTOR3 m_vOrg;
	D3DXVECTOR3 m_vDir;

public:
	Ray(void);
	~Ray(void);

	static Ray RayAtViewSpace(int x, int y);
	static Ray RayAtWorldSpace(int x, int y);
	Ray Transform(D3DXMATRIXA16& mat);
	bool IsPicked(D3DXVECTOR3& vSphereCenter, float fSphereRadius);
	bool IntersectTri(D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2, D3DXVECTOR3& vPickedPosition);
};

