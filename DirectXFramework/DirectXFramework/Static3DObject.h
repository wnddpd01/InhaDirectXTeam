#pragma once
#include "Base3DObject.h"

enum class eShaderName
{
	OUT_LINE = 0, TOON
};

class Static3DObject :
	public Base3DObject
{
private:
	LPD3DXMESH				mpMesh;
	D3DMATERIAL9*			mpMaterials;
	LPDIRECT3DTEXTURE9*		mpTextures;
	DWORD					mNumMaterials;
	
public:
	Static3DObject();
	virtual ~Static3DObject();

	void Setup(
		IN string	folder,
		IN string	fileName
	);

	void Update() override;
	void Render() override;

	void RenderMesh();

	LPD3DXEFFECT LoadShader(const char* filename);
};

