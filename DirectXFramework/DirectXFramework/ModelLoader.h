#pragma once
class ModelLoader
{
public:
	ModelLoader();
	virtual ~ModelLoader();

	void LoadXfile(
		IN string					folder,
		IN string					fileName,
		OUT LPD3DXMESH&				mpMesh,
		OUT D3DMATERIAL9**			mpMaterials,
		OUT LPDIRECT3DTEXTURE9**	mpTextures,
		OUT DWORD&					mNumMaterials
	);
};

