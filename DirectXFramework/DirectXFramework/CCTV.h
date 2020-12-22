#pragma once

#include "Base3DObject.h"

class SkinnedMesh;
class Static3DObject;
class ColliderSphere;

class CCTV :
	public Base3DObject
{
private :
	SkinnedMesh* mSkinnedMesh;
	D3DXVECTOR3 mEyeDir;
	D3DXVECTOR3 mDetectSpherePos;
	ColliderSphere* mDetectSphere;
public :
	CCTV(const LPD3DXMESH& floorMesh, D3DXVECTOR3 eyeDir, D3DXVECTOR3 pos);
	~CCTV();

	void Update() override;
	void Render() override;
};

