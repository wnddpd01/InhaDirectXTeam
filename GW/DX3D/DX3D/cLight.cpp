#include "stdafx.h"
#include "cLight.h"
#include "cCubePC.h"

cLight::cLight()
	:m_pPLC(NULL), m_pSLC(NULL)
{
}


cLight::~cLight()
{
	SafeDelete(m_pPLC);
	SafeDelete(m_pSLC);
}

void cLight::Setup()
{
	ZeroMemory(&m_Light[0], sizeof(D3DLIGHT9));
	m_Light[0].Type = D3DLIGHT_DIRECTIONAL;
	m_Light[0].Ambient = D3DXCOLOR(0.1F, 0.1F, 0.1F, 1.0F);
	m_Light[0].Diffuse = D3DXCOLOR(0.5f, 0.5F, 0.5F, 1.0F);
	m_Light[0].Specular = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);

	D3DXVECTOR3 vDir(1.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	m_Light[0].Direction = vDir;
	g_pD3DDevice->SetLight(0, &m_Light[0]);
	g_pD3DDevice->LightEnable(0, true);


	ZeroMemory(&m_Light[1], sizeof(D3DLIGHT9));
	m_Light[1].Type = D3DLIGHT_POINT;
	m_Light[1].Ambient = D3DXCOLOR(0.0F, 0.0F, 0.8F, 1.0F);
	m_Light[1].Diffuse = D3DXCOLOR(0.0F, 0.0F, 0.8F, 1.0F);
	m_Light[1].Specular = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);

	m_Light[1].Attenuation0 = 0.01f;

	m_Light[1].Range = 0.1f;

	m_Light[1].Position.x = -5.0f;
	m_Light[1].Position.y = 0.0f;
	m_Light[1].Position.z = 0.0f;
	//g_pD3DDevice->SetLight(1, &m_Light[1]);
	//g_pD3DDevice->LightEnable(1, true);


	ZeroMemory(&m_Light[2], sizeof(D3DLIGHT9));
	m_Light[2].Type = D3DLIGHT_SPOT;
	m_Light[2].Ambient = D3DXCOLOR(0.0F, 1.0F, 0.0F, 1.0F);
	m_Light[2].Diffuse = D3DXCOLOR(0.0F, 1.0F, 0.0F, 1.0F);
	m_Light[2].Specular = D3DXCOLOR(0.0F, 0.8F, 0.0F, 1.0F);

	m_Light[2].Attenuation0 = 0.01f;
	m_Light[2].Attenuation1 = 0.01f;
	m_Light[2].Attenuation2 = 0.01f;
	m_Light[2].Range = 15.0f;

	m_Light[2].Position.x = 1.0f;
	m_Light[2].Position.y = 10.0f;
	m_Light[2].Position.z = 1.0f;

	m_Light[2].Falloff = 1.0f;
	m_Light[2].Theta = D3DX_PI / 4.5f;
	m_Light[2].Phi = D3DX_PI / 0.5f;

	D3DXVECTOR3 vDir2(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir2, &vDir2);
	m_Light[2].Direction = vDir2;

	//g_pD3DDevice->SetLight(2, &m_Light[2]);
	//g_pD3DDevice->LightEnable(2, true);

	/*m_pPLC = new cCubePC;
	m_pPLC->Setup();

	m_pSLC = new cCubePC;
	m_pSLC->Setup();*/

}

void cLight::Update()
{


	D3DXMATRIXA16 matR;
	D3DXMatrixRotationZ(&matR, 0.05f);
	D3DXVec3TransformNormal((D3DXVECTOR3*)&m_Light[0].Direction, (D3DXVECTOR3*)&m_Light[0].Direction, &matR);

	g_pD3DDevice->SetLight(0, &m_Light[0]);


	if (GetKeyState('Q') & 0x8000)
	{
		if(m_Light[1].Range<=15.0f)
			m_Light[1].Range += 0.1f;
	}
	if (GetKeyState('E') & 0x8000)
	{
		if (m_Light[1].Range >= 0.5f)
			m_Light[1].Range -= 0.1f;
	}
	g_pD3DDevice->SetLight(1, &m_Light[1]);


	if (GetKeyState('I') & 0x8000)
	{
		if(m_Light[2].Position.z <=20.0f)
			m_Light[2].Position.z += 0.1f;
	}
	if (GetKeyState('K') & 0x8000)
	{
		if (m_Light[2].Position.z >= -20.0f)
			m_Light[2].Position.z -= 0.1f;
	}
	if (GetKeyState('J') & 0x8000)
	{
		if (m_Light[2].Position.x >= -20.0f)
			m_Light[2].Position.x -= 0.1f;
	}
	if (GetKeyState('L') & 0x8000)
	{
		if (m_Light[2].Position.x <= 20.0f)
			m_Light[2].Position.x += 0.1f;
	}
	g_pD3DDevice->SetLight(2, &m_Light[2]);


}

void cLight::Render()
{
	/*m_pPLC->Render();
	m_pSLC->Render();*/
}




