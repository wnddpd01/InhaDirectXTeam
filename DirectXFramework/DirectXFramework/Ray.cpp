#include "stdafx.h"
#include "Ray.h"

Ray::Ray(void)
	: m_eRaySpace(E_NONE)
	, m_vOrg(0, 0, 0)
	, m_vDir(0, 0, 0)
{
}


Ray::~Ray(void)
{
}

Ray Ray::RayAtViewSpace(int x, int y)
{
	D3DVIEWPORT9 vp;
	gD3Device->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	gD3Device->GetTransform(D3DTS_PROJECTION, &matProj);

	Ray r;
	r.m_vDir.x = ((2.0f * x) / vp.Width - 1.0f) / matProj._11;
	r.m_vDir.y = ((-2.0f * y) / vp.Height + 1.0f) / matProj._22;
	r.m_vDir.z = 1.0f;

	r.m_eRaySpace = E_VIEW;

	D3DXVec3Normalize(&r.m_vDir, &r.m_vDir);

	return r;
}

Ray Ray::RayAtWorldSpace(int x, int y)
{
	D3DXMATRIXA16 matView, matInvView;
	gD3Device->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, nullptr, &matView);

	Ray r = RayAtViewSpace(x, y);

	D3DXVec3Normalize(&r.m_vDir, &r.m_vDir);

	r.m_eRaySpace = E_WORLD;

	return r.Transform(matInvView);
}

Ray Ray::Transform(D3DXMATRIXA16& mat)
{
	Ray r = (*this);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &mat);
	D3DXVec3TransformCoord(&r.m_vOrg, &r.m_vOrg, &mat);
	D3DXVec3Normalize(&r.m_vDir, &r.m_vDir);
	return r;
}

bool Ray::IsPicked(D3DXVECTOR3& vSphereCenter, float fSphereRadius)
{
	assert(m_eRaySpace == E_WORLD);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixTranslation(&matInvWorld, -vSphereCenter.x, -vSphereCenter.y, -vSphereCenter.z);
	Ray r = Transform(matInvWorld);

	// (V.Q)^2 - V.V * (Q.Q - r.r) >= 0
	float vv = D3DXVec3Dot(&r.m_vDir, &r.m_vDir);
	float qq = D3DXVec3Dot(&r.m_vOrg, &r.m_vOrg);
	float vq = D3DXVec3Dot(&r.m_vOrg, &r.m_vDir);
	float rr = fSphereRadius * fSphereRadius;

	return (vq * vq - vv * (qq - rr)) >= 0;
}

bool Ray::IntersectTri(IN D3DXVECTOR3& v0, IN D3DXVECTOR3& v1, IN D3DXVECTOR3& v2, OUT D3DXVECTOR3& vPickedPosition)
{
	Ray r = (*this);
	float u, v, t;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &r.m_vOrg, &r.m_vDir, &u, &v, &t);
	vPickedPosition = r.m_vOrg + (t * r.m_vDir);

	return b;
}