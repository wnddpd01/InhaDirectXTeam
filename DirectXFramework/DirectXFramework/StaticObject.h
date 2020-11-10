#pragma once
#include "BaseObject.h"
class cMtlTex;
class OBB;

class StaticObject :
	public BaseObject
{
private:
	D3DXMATRIXA16		mMatPos;
	D3DXMATRIXA16		mMatRot;
	D3DXMATRIXA16		mMatScale;
	
	LPD3DXMESH			mMesh;

	OBB*				mCollider;
	
	D3DMATERIAL9		mMaterial;
	LPDIRECT3DTEXTURE9	mTextrue;
	vector<cMtlTex*>    vecMtlTex;
	LPD3DXEFFECT		mShader;
	
public:
	OBB * GetOBB();
	StaticObject();
	virtual ~StaticObject();

	void Setup(char* szOBj, char* szTex, D3DXVECTOR3 pos);
	void Update() override;
	void Render() override;
};

