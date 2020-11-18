#pragma once
#include "Base3DObject.h"

class cMtlTex;

class MeshObject :
	public Base3DObject
{
	LPD3DXMESH mMesh;

	
	map<string, cMtlTex*>mMapMtltex;
	vector<cMtlTex*> mMtlTex;
public:
	MeshObject();
	virtual ~MeshObject() = default;

	void Setup(string filename);
	void Update() override;
	void Render() override;
	
	void LoadMesh(char* szFolder, char* szFile);
	void LoadMtlLib(char* filePath, char* szFile);
};

