#pragma once
class QuarterMap
{
	// �⺻���� : Scene���� ���� �ı��ϸ鼭 ���
	//			 �����ʹ� ���������
	// raw�� ���� �ּҰ��� ������ �� ���� ���� == �ʹ��� ��
	// �浹ó���� ���� ���ϴ� ���� ���� ���̶� ������ �� ����

private:
	LPD3DXMESH			mMesh;
	vector<D3DXVECTOR3>	mVertexContainer;
	D3DMATERIAL9		mMaterial;
	LPDIRECT3DTEXTURE9	mTextrue;
	LPD3DXEFFECT		mShader;
	int					mTileN;

public:
	QuarterMap();
	virtual ~QuarterMap();
	void Setup(char* szFolder, char* szRaw , char* szTex, DWORD dwBytesPerPixel = 1);
	void Update();
	void Render();
	void Destroy();

	//todo ������ ���� ���� �ν�
};

