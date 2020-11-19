#pragma once
#include "Singleton.h"

#define gCameraManager CameraManager::GetInstance()
#define gCurrentCamera CameraManager::GetInstance()->GetCurrentCamera()

class Camera;

class CameraManager : public Singleton<CameraManager>
{
private:
	Camera* mCurrentCamera;

public:
	void SetCamera(Camera* newCamera);
	Camera* GetCurrentCamera();
	
};

