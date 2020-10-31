#pragma once

#include "Singleton.h"

class DeviceManager : public Singleton<DeviceManager>
{

private :
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;

public :
	LPDIRECT3DDEVICE9	GetDevice(); 
	void Destroy(); 
};

