#include "stdafx.h"
#include "cBigShip.h"


cBigShip::cBigShip()
{
}


cBigShip::~cBigShip()
{
}

void cBigShip::Setup()
{
	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls = 0;

	D3DXLoadMeshFromX(L"bigship/bigship1.x", D3DXMESH_MANAGED, g_pD3DDevice, &adjBuffer, &mtrlBuffer, 0, &numMtrls, &Mesh);

	D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

	for (int i = 0; i < numMtrls; ++i)
	{
		mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

		Mtrls.push_back(mtrls[i].MatD3D);

		if(mtrls[i].pTextureFilename != 0)
		{
			IDirect3DTexture9* tex = 0;
			string sTexDir = "bigship/" + string(mtrls[i].pTextureFilename);
		 	tex =  g_pTextureManager->GetTexture(sTexDir);
			Textures.push_back(tex);
		}
		else
		{
			Textures.push_back(0);
		}
		SafeRelease(mtrlBuffer);
		
	}
}

void cBigShip::Render(float timeDelta)
{
	static float y = 0.0f;
	D3DXMATRIX yRot;
	D3DXMatrixRotationY(&yRot, y);
	y += timeDelta;
	if (y >= 6.28f)
		y = 0.f;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &yRot);
	for (int i = 0; i < Mtrls.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&Mtrls[i]);
		g_pD3DDevice->SetTexture(0, Textures[i]);
		Mesh->DrawSubset(i);
	}
}
