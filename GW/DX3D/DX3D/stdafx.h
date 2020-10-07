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
#include <fstream>
#include <assert.h> //경고 관련




#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


extern HWND g_hWnd;

#define SafeRelease(p)	{if(p) p->Release() ; p =NULL;}   //인터페이스 해제

#define SafeDelete(p) {if(p) delete p; p=NULL;} // 메모리 삭제

// >> :
#define Singletone(class_name) \
	private : \
	class_name(void) ; \
	~class_name(void) ; \
	public : \
	static class_name* GetInstance() \
	{   \
		static class_name instance ; \
		return &instance ; \
	}
// << :

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR   c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};


struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3   n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
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
	enum { FVF = D3DFVF_XYZ| D3DFVF_TEX1 };

};


#define Synthesize(varType, varName, funName) \
	protected:varType varName; \
	public : inline varType Get##funName(void) const{return varName;} \
	public : inline void Set##funName(varType var){varName = var;}


#define Synthesize_pass_by_Ref(varType, varName, funName) \
	protected:varType varName; \
	public : inline varType& Get##funName(void) {return varName;} \
	public : inline void Set##funName(varType& var){varName = var;}


#include "cDeviceManager.h"

#define PI 3.141592f

// TODO: reference additional headers your program requires here
