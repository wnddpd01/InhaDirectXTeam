#pragma once

#include "targetver.h"

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


#include "cMainGame.h"
#include "cDeviceManager.h"