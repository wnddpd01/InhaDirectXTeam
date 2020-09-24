// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <ctime>
#include <assert.h>


#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hwnd;

#define SafeRelease(p)	{ if(p)	p->Release(); p = NULL; }
#define SafeDelete(p)	{ if(p) delete p ; p = NULL; }

//싱글턴 매크로
#define Singletone(class_name) \
	private : \
		class_name(void) ; \
		~class_name(void) ;	\
	public : \
		static class_name* GetInstance() \
		{	\
			static class_name instance; \
			return &instance ; \
		}
// 싱글턴 매크로 끝
//

struct ST_PC_VERTEX
{
	D3DXVECTOR3		p;
	D3DCOLOR		c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_TRIANGLE
{
	int index[3];
};

enum SHAPE
{
	CUBE = 1,
	GRID = 2,
	GIZMO = 3
};

#include "Object.h"
#include "cDeviceManager.h";
// TODO: reference additional headers your program requires here
