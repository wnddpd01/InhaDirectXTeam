#pragma once

#include "targetver.h"
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#define WIN32_LEAN_AND_MEAN
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here
#include <d3dx9.h>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <assert.h>
#include <iostream>
#include <time.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace std;
extern HWND g_hWnd;

#define SafeRelease(p)		{ if(p) p->Release();	p = NULL; }
#define SafeDelete(p) { if(p) delete p; p = NULL; }

#define  Singleton(class_name) \
	private : \
		class_name(void); \
		~class_name(void); \
	public : \
		static class_name* GetInstance() \
		{ \
			static class_name instance; \
			return &instance; \
		}

struct ST_PC_VERTEX	//포인트, 컬러
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL};
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	enum {FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1};
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};
#define Synthesize(varType, varName, funName) \
protected : varType varName ; \
public	  : inline varType Get##funName(void) const { return varName;} \
public	  : inline void Set##funName(varType var)   { varName = var;}

#define Synthesize_pass_by_Ref(varType, varName, funName) \
protected : varType varName ; \
public	  : inline varType& Get##funName(void)  { return varName;} \
public	  : inline void Set##funName(varType& var)   { varName = var;}

inline float factorial(int n)
{
	float ret = 1;
	for (int i = 2; i <= n; ++i)
	{
		ret *= i;
	}
	return ret;
}
inline float binomial_coefficient(int n, int k) {
	return factorial(n) / (factorial(k) * factorial(n - k));
}


#include "cMainGame.h"
#include "cDeviceManager.h"