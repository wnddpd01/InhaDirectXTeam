#pragma once

#define g_pDeviceManager cDeviceManager::GetInstance()
#define g_pD3DDevice cDeviceManager::GetInstance()->GetDevice()

class cDeviceManager
{
	Singletone(cDeviceManager);
	
private:
	LPDIRECT3D9		  m_pD3D; // 다이렉트 x 인터페이스 정보
	LPDIRECT3DDEVICE9 m_pD3DDevice; // 연결된 장치에 대한 설정
public:
	LPDIRECT3DDEVICE9 GetDevice();
	void Destroy();
	
};

