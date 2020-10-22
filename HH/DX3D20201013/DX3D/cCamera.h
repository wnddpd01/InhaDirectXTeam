#pragma once
class Ray;

class cCamera
{
public:
	cCamera();
	~cCamera();
private :
	D3DXVECTOR3		m_vEye; 
	D3DXVECTOR3		m_vLookAt; 
	D3DXVECTOR3		m_vUp; 
	D3DXVECTOR3*	m_pvTarget; 

	POINT			m_ptPrevMouse; 
	bool			m_isLButtonDown; 
	float			m_fCameraDistance; 
	D3DXVECTOR3		m_vCamRotAngle;

	D3DXMATRIXA16	m_matProjection;

	

public :
	void Setup(D3DXVECTOR3* pvTarget); 
	void Update(); 

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	D3DXMATRIXA16 GetProjectionMat();
	D3DXVECTOR3 GetvEye();
};

