#include "stdafx.h"
#include "cDeviceManager.h"


cDeviceManager::cDeviceManager()
	: m_pD3D(NULL)
	, m_pD3Device(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	int nVertexProcessing = 0;
	m_pD3D->GetDeviceCaps(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		&caps
	);
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	//stD3DPP.BackBufferWidth = 800;
	//stD3DPP.BackBufferHeight = 600;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.BackBufferCount = 1;
	//stD3DPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	//stD3DPP.MultiSampleQuality = 0;
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.hDeviceWindow = g_hwnd;
	stD3DPP.Windowed = TRUE;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;
	//stD3DPP.Flags = 0;
	//
	//stD3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	stD3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	m_pD3Device = 0;
	HRESULT hr = m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hwnd,
		nVertexProcessing,
		&stD3DPP,
		&m_pD3Device);

	if (FAILED(hr))
	{
		::MessageBox(0, L"CreateDevice() - FAILED", 0, 0);
		return;
	}
}


cDeviceManager::~cDeviceManager()
{
	SafeRelease(m_pD3D);
	SafeRelease(m_pD3Device);
}

LPDIRECT3DDEVICE9 cDeviceManager::GetDevice()
{
	return m_pD3Device;
}

void cDeviceManager::Destroy()
{
}
