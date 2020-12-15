#pragma once
#include "Base3DObject.h"
#include "Singleton.h"

#define gShader ShaderManager::GetInstance()


class ShaderManager : public Singleton<ShaderManager>
{
private:
	map<string, LPD3DXEFFECT>		mShaders;
	LPDIRECT3DTEXTURE9				mTexA1;
	LPDIRECT3DTEXTURE9				mTexRound;

public:
	void LoadAllShader();
	LPD3DXEFFECT LoadShader(const char* filename);
	LPDIRECT3DTEXTURE9 LoadTexture(const char * filename);
	
	void RenderWithToonShader(function<void()> FunctionPtr);
	void RenderWithFireShader(function<void()> FunctionPtr);
	void RenderWithWallShader(function<void()> FunctionPtr);
	void RenderWithItemShader(function<void()> FunctionPtr, eShaderPath eShaderPath);
	void RednerWithFlashShader(function<void()> FunctionPtr);
};

