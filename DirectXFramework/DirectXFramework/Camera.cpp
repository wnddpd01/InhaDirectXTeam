#include "stdafx.h"
#include "Camera.h"


Camera::Camera() :
	mEye(0, 0, -5)
	, mLookAt(0, 0, 0)
	, mUp(0, 1, 0)
	, mTarget(nullptr)
	, mCameraDistance(15.0f)
	, mCamRotAngle(0, 0, 0)
	, mbLButtonDown(false)
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
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0F, viewPort.Width / (float)(viewPort.Height), 1.0f, 1000.0f); // ���� ����
	//D3DXMatrixOrthoLH(&matProj, (float)(viewPort.Height) * (float)(viewPort.Height) / viewPort.Width, 1.f / tan(D3DX_PI / 8.0F ), 0, 10.f); // ���� ����

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
		case eEventName::MOUSE_L_DOWN:
			{
				mbLButtonDown = true;
			}
			break;
		case eEventName::MOUSE_L_UP:
			{
				mbLButtonDown = false;
			}
			break;
		case eEventName::MOUSE_L_DRAG:
			{
				POINT ptCurMouse = *(POINT*)parameter;
				float fDeltaX = (float)ptCurMouse.x - mPrevMousePos.x;
				float fDeltaY = (float)ptCurMouse.y - mPrevMousePos.y;
				mCamRotAngle.y += (fDeltaX / 100.0f);
				mCamRotAngle.x += (fDeltaY / 100.0f);

				if (mCamRotAngle.x < -D3DX_PI / 2.0f + 0.0001f)
					mCamRotAngle.x = -D3DX_PI / 2.0f + 0.0001f;

				if (mCamRotAngle.x > D3DX_PI / 2.0f - 0.0001f)
					mCamRotAngle.x = D3DX_PI / 2.0f - 0.0001f;

				mPrevMousePos = ptCurMouse;
			}
			break;
		default:
			break;
	}
	return true;
}
