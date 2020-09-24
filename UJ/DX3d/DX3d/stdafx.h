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

#include "cMainGame.h"
#include "cDeviceManager.h"