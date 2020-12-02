#pragma once
class Camera : public BaseObserver
{
public:
	Camera();
	~Camera();
private:
	D3DXVECTOR3 mStartPos;
	D3DXVECTOR3 mEye;
	D3DXVECTOR3 mLookAt;
	D3DXVECTOR3 mUp;
	D3DXVECTOR3 mRight;
	D3DXVECTOR3 mCameraUp;
	D3DXVECTOR3* mTarget;

	float mCameraDistance;
	D3DXVECTOR3 mCamRotAngle;

	//�̺�Ʈ�� ī�޶� ����
	bool bEventCamera;
	float mLifeTime;
	float mMoveSpeed;

public:
	void SetTarget(D3DXVECTOR3 * target);
	void Setup();
	void SetupPre();
	void Update();

	bool Update(eEventName eventName, void* parameter) override;

	D3DXVECTOR3 GetPickingPosition(POINT& mousePos);

	//�̺�Ʈ�� ī�޶� ����
	void SetEventCamera(bool setEvent);
	bool GetEventCamera();

	void SetLifeTime(float lifeTime);
	float GetLifeTime();

	void SetYCamRotAngle(float CamRotAngle);
	float GetYCamRotAngle();

	void SetStartPos(D3DXVECTOR3 StartPos);
	D3DXVECTOR3 GetStartPos();

	void SetMoveSpeed(float MoveSpeed);
	float GetMoveSpeed();

	void SetCameraDistance(float CameraDistance);
	float GetCameraDistance();
};
