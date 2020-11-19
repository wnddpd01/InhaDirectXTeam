#include "stdafx.h"
#include "CameraManager.h"
#include "Camera.h"

void CameraManager::SetCamera(Camera* newCamera)
{
	if(newCamera)
		mCurrentCamera = newCamera;
}

Camera* CameraManager::GetCurrentCamera()
{
	return mCurrentCamera;
}
