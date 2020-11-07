#pragma once
class cMtlTex;

class QuarterMap : public BaseObject
{
	// �⺻���� : Scene���� ���� �ı��ϸ鼭 ���
	//			 �����ʹ� ���������
	// raw�� ���� �ּҰ��� ������ �� ���� ���� == �ʹ��� ��
	// �浹ó���� ���� ���ϴ� ���� ���� ���̶� ������ �� ����

private:
	LPD3DXMESH			mMeshMap;
	LPD3DXMESH			mMeshWall;
	LPD3DXMESH			mMeshFloor;
	LPD3DXMESH			mMeshDoor;
	vector<D3DXVECTOR3>	mVertexContainer;
	D3DMATERIAL9		mMaterial;
	LPDIRECT3DTEXTURE9	mTextrue;
	LPDIRECT3DTEXTURE9	mTextrueFloor;
	vector<cMtlTex*>    vecMtlTex;
	LPD3DXEFFECT		mShader;

public:
	QuarterMap();
	virtual ~QuarterMap();

	void Setup(char* szFolder, char* szRaw , char* szTex, DWORD dwBytesPerPixel = 1);
	void Update() override; 
	void Render() override;
	
	void Destroy();
	float GetHeight(float posX, float posZ);
	
	//todo ������ ���� ���� �ν�
};

