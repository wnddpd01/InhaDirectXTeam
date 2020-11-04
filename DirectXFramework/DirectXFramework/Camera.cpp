#include "stdafx.h"
#include "Camera.h"


Camera::Camera() :
	mEye(0, 0, -5)
	, mLookAt(0, 0, 0)
	, mUp(0, 1, 0)
	, mTarget(nullptr)
	, mCameraDistance(5.0f)
	, mCamRotAngle(0, 0, 0)
{
}


Camera::~Camera()
{
}

void Camera::Setup(D3DXVECTOR3* target)
{
	mTarget = target;

	D3DVIEWPORT9 viewPort;
	gD3Device->GetViewport(&viewPort);
	
	D3DXMATRIXA16   matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0F,
		viewPort.Width / (float)viewPort.Height, 1.0f, 1000.0f);

	gD3Device->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Camera::Update()
{
	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, mCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, mCamRotAngle.y);
	matR = matRX* matRY;

	mEye = D3DXVECTOR3(0, 0, -mCameraDistance);
	D3DXVec3TransformCoord(&mEye, &mEye, &matR);
	if (mTarget)
	{
		mLookAt = *mTarget;
		mEye += *mTarget;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &mEye, &mLookAt, &mUp);

	gD3Device->SetTransform(D3DTS_VIEW, &matView);
}
