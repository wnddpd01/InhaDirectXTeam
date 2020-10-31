#pragma once

#include "Singleton.h"

class DeviceManager : public Singleton<DeviceManager>
{
private :
	LPDIRECT3D9			mD3D;
	LPDIRECT3DDEVICE9	mD3DDevice;
	DeviceManager();

public :
	LPDIRECT3DDEVICE9	GetDevice(); 
	void Destroy(); 
};

