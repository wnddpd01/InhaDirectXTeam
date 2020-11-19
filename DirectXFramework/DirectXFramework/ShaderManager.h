#pragma once
#include "Base3DObject.h"
#include "Singleton.h"

#define gShader ShaderManager::GetInstance()

class ShaderManager : public Singleton<ShaderManager>
{
private:
	map<string, LPD3DXEFFECT>		mShaders;
	
public:
	void LoadAllShader();
	LPD3DXEFFECT LoadShader(const char* filename);
	LPDIRECT3DTEXTURE9 LoadTexture(const char * filename);
	
	void RenderWithToonShader(function<void()> FunctionPtr);
	void RenderWithOutLineShader(function<void()> FunctionPtr);
	void RenderWithPointLightShader(function<void()> FunctionPtr);
	void RenderWithSpotLightShader(function<void()> FunctionPtr);
	void RenderWithItemShader(function<void()> FunctionPtr);
};

