#include "stdafx.h"
#include "cLight.h"


cLight::cLight()
{
	temp_range = 1.0f;
}


cLight::~cLight()
{
}

void cLight::Setup()
{
	ZeroMemory(&stLight[0], sizeof(D3DLIGHT9));
	stLight[0].Type = D3DLIGHT_DIRECTIONAL;
	stLight[0].Ambient = D3DXCOLOR(0.1F, 0.1F, 0.1F, 1.0F);
	stLight[0].Diffuse = D3DXCOLOR(0.5f, 0.5F, 0.5F, 1.0F);
	stLight[0].Specular = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);

	D3DXVECTOR3 vDir(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight[0].Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight[0]);
	g_pD3DDevice->LightEnable(0, true);


	ZeroMemory(&stLight[1], sizeof(D3DLIGHT9));
	stLight[1].Type = D3DLIGHT_POINT;
	stLight[1].Ambient = D3DXCOLOR(0.0F, 0.0F, 0.8F, 1.0F);
	stLight[1].Diffuse = D3DXCOLOR(0.0F, 0.0F, 0.8F, 1.0F);
	stLight[1].Specular = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);

	stLight[1].Attenuation0 = 0.01f;

	stLight[1].Range = temp_range;

	stLight[1].Position.x = -5.0f;
	stLight[1].Position.y = 0.0f;
	stLight[1].Position.z = 0.0f;
	g_pD3DDevice->SetLight(1, &stLight[1]);
	g_pD3DDevice->LightEnable(1, true);


	ZeroMemory(&stLight[2], sizeof(D3DLIGHT9));
	stLight[2].Type = D3DLIGHT_SPOT;
	stLight[2].Ambient = D3DXCOLOR(0.0F, 1.0F, 0.0F, 1.0F);
	stLight[2].Diffuse = D3DXCOLOR(0.0F, 1.0F, 0.0F, 1.0F);
	stLight[2].Specular = D3DXCOLOR(0.0F, 0.8F, 0.0F, 1.0F);

	stLight[2].Attenuation0 = 0.01f;
	stLight[2].Attenuation1 = 0.01f;
	stLight[2].Attenuation2 = 0.01f;
	stLight[2].Range = 10.0f;

	stLight[2].Position.x = 1.0f;
	stLight[2].Position.y = 2.0f;
	stLight[2].Position.z = 1.0f;

	stLight[2].Falloff = 1.0f;
	stLight[2].Theta = D3DX_PI / 4.5f;
	stLight[2].Phi = D3DX_PI / 4.0f;

	D3DXVECTOR3 vDir2(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir2, &vDir2);
	stLight[2].Direction = vDir2;

	g_pD3DDevice->SetLight(2, &stLight[2]);
	g_pD3DDevice->LightEnable(2, true);



}

void cLight::Update()
{

}

void cLight::Render()
{


}

void cLight::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	

	
}

