#pragma once

#include "Base3DObject.h"

class SkinnedMesh;
class Static3DObject;
class ColliderSphere;

class CCTV :
	public Base3DObject
{
private :
	bool mbRotateRight;
	float mRotateProgressTime;
	SkinnedMesh* mSkinnedMesh;
	D3DXVECTOR3 mEyeDir;
	D3DXVECTOR3 mDetectSpherePos;
	D3DXVECTOR3 mDetectSphereRange[4];
	LPD3DXMESH mDetectRangeMesh;
	ColliderSphere* mDetectSphere;

	void RenderDetectRangeMesh();
	void Rotate();
public :
	CCTV(const LPD3DXMESH& floorMesh, D3DXVECTOR3 eyeDir, D3DXVECTOR3 pos);
	~CCTV();

	void Update() override;
	void Render() override;
};

