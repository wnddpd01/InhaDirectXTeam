#include "stdafx.h"
#include "cXfileLoader.h"


cXfileLoader::cXfileLoader()
	: Mesh(NULL)
	, Mtrls(NULL)
	, Textures(NULL)
{
}


cXfileLoader::~cXfileLoader()
{
	SafeRelease(Mesh);
}

bool cXfileLoader::Setup()
{
	HRESULT hr = 0;

	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls = 0;

	hr = D3DXLoadMeshFromX( L"Zealot/zealot.x", 
		D3DXMESH_MANAGED, g_pD3DDevice, 
		&adjBuffer, 
		&mtrlBuffer, 
		0, &numMtrls, &Mesh );

	if(FAILED(hr))
	{
		return false;
	}


	if(mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for(int i = 0 ; i< numMtrls; i++)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			Mtrls.push_back(mtrls[i].MatD3D);


			if(mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(g_pD3DDevice, L"Zealot/Zealot_Diffuse.bmp", &tex);

				Textures.push_back(tex);
			}
			else
			{
				Textures.push_back(0);
			}
		}

		
	}

	

	return true;
}

bool cXfileLoader::Display(float timeDelta)
{
	if (g_pD3DDevice)
	{
		static float y = 0.0f;
		D3DXMATRIX yRot;
		D3DXMatrixRotationY(&yRot, y);
		y += timeDelta;

		if (y >= 6.28f)
			y = 0.0f;

		D3DXMATRIX World = yRot;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &World);


		for (int i = 0; i < Mtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&Mtrls[i]);
			g_pD3DDevice->SetTexture(0, Textures[i]);
			Mesh->DrawSubset(i);
		}


	}
	return true;
}
