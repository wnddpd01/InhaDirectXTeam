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

#include <map>
#include <string>
#include <mmsystem.h>
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


struct ST_POS_SAMPLE
{
	int 		n;
	D3DXVECTOR3 v;
	ST_POS_SAMPLE()
		:n(0)
	,v(0,0,0)
	{}
};

struct ST_ROT_SAMPLE
{
	int 		n;
	D3DXQUATERNION q;
	ST_ROT_SAMPLE()
		:n(0)
	{
		D3DXQuaternionIdentity(&q);
	}
};



struct ST_SPHERE
{
	float fRadius;
	D3DXVECTOR3 vCenter;
	bool isPicked;
	ST_SPHERE() : fRadius(0.0f), vCenter(0,0,0){}
};



#define Synthesize(varType, varName, funName) \
	protected:varType varName; \
	public : inline varType Get##funName(void) const{return varName;} \
	public : inline void Set##funName(varType var){varName = var;}


#define Synthesize_Pass_by_Ref(varType, varName, funName) \
	protected:varType varName; \
	public : inline varType& Get##funName(void) {return varName;} \
	public : inline void Set##funName(varType& var){varName = var;}




#define  SafeAddRef(p) {if(p) p->AddRef();}



#define Synthesize_Add_Ref(varType, varName, funName) \
   protected : varType varName; \
   public: virtual varType Get##funName(void)const{return varName;}\
   public: virtual void Set##funName(varType var ){ \
   if(varName != var)\
   {\
    SafeAddRef(var); \
    SafeRelease(varName);\
    varName = var;\
   }\
}

#include "iMap.h"



#include "cDeviceManager.h"

#define PI 3.141592f



#include "cDeviceManager.h"
#include "cObject.h"
#include "cObjectManager.h"
#include "cTextureManager.h"



// TODO: reference additional headers your program requires here