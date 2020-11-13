#include "stdafx.h"
#include "ModelLoader.h"


ModelLoader::ModelLoader()
{
	
}


ModelLoader::~ModelLoader()
{
}

void ModelLoader::LoadXfile(
	string folder, string fileName, LPD3DXMESH& mpMesh, D3DMATERIAL9** mpMaterials,
	LPDIRECT3DTEXTURE9** mpTextures, DWORD& mNumMaterials)
{
	string fullPath = folder + "/" + fileName;
	LPD3DXBUFFER pMtlBuffer;

	D3DXLoadMeshFromXA(
		fullPath.c_str(),
		D3DXMESH_MANAGED,
		gD3Device,
		NULL,
		&pMtlBuffer,
		NULL,
		&mNumMaterials,
		&mpMesh
	);

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pMtlBuffer->GetBufferPointer();


	*mpMaterials = new D3DMATERIAL9[mNumMaterials];
	*mpTextures = new LPDIRECT3DTEXTURE9[mNumMaterials];

	for (DWORD i = 0; i < mNumMaterials; ++i)
	{
		(*mpMaterials)[i] = d3dxMaterials[i].MatD3D;

		(*mpMaterials)[i].Ambient = (*mpMaterials)[i].Diffuse;

		(*mpTextures)[i] = NULL;
		if ((d3dxMaterials[i].pTextureFilename != NULL) &&
			(strlen(d3dxMaterials[i].pTextureFilename) > 0))
		{
			string path = folder + "/" + string(d3dxMaterials[i].pTextureFilename);
			d3dxMaterials[i].pTextureFilename = const_cast<char *>(path.c_str());
			 
			D3DXCreateTextureFromFileA(gD3Device,
				d3dxMaterials[i].pTextureFilename,
				&((*mpTextures)[i]));
		}
	}

	pMtlBuffer->Release();
}

