#include "stdafx.h"
#include "Camera.h"


Camera::Camera() :
	mEye(0, 0, -5)
	, mLookAt(0, 0, 0)
	, mUp(0, 1, 0)
	, mTarget(nullptr)
	, mCameraDistance(15.0f)
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

	D3DXMATRIXA16 matProj;
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0F, viewPort.Width / (float)(viewPort.Height), 1.0f, 1000.0f); // 원근 투영
	D3DXMatrixOrthoLH(&matProj, 14.f, 14.f * viewPort.Height / viewPort.Width, 1, 100.f); // 직교 투영
	//D3DXMatrixIdentity(&matProj);
	gD3Device->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Camera::Update()
{
	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, mCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, mCamRotAngle.y);
	matR = matRX * matRY;

	mEye = D3DXVECTOR3(4, 5, -mCameraDistance);
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

bool Camera::Update(eEventName eventName, void* parameter)
{
	switch (eventName)
	{
		case eEventName::MOUSE_L_DRAG:
			{
				POINT mouseDeltaPosition = *(POINT*)parameter;

				mCamRotAngle.y += (mouseDeltaPosition.x / 100.0f);
				mCamRotAngle.x += (mouseDeltaPosition.y / 100.0f);

				if (mCamRotAngle.x < -D3DX_PI / 2.0f + 0.0001f)
				{
					mCamRotAngle.x = -D3DX_PI / 2.0f + 0.0001f;
				}

				if (mCamRotAngle.x > D3DX_PI / 2.0f - 0.0001f)
				{
					mCamRotAngle.x = D3DX_PI / 2.0f - 0.0001f;
				}
			}
			break;
		case eEventName::MOUSE_WHEEL_SCROLL:
			{
				mCameraDistance -= *(float*)parameter;
				if (mCameraDistance < 10.0f)
				{
					mCameraDistance = 10.0f;
				}	
			}
			break;
		default:
			break;
	}
	return true;
}
