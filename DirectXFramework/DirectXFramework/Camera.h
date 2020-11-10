#pragma once
class Camera : public BaseObserver
{
public:
	Camera();
	~Camera();
private:
	D3DXVECTOR3 mEye;
	D3DXVECTOR3 mLookAt;
	D3DXVECTOR3 mUp;
	D3DXVECTOR3* mTarget;

	float mCameraDistance;
	D3DXVECTOR3 mCamRotAngle;
public:
	void Setup(D3DXVECTOR3* target);
	void Update();

	bool Update(eEventName eventName, void* parameter) override;
};