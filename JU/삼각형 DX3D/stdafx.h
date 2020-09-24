// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <d3dx9.h>
#include <d3d9.h>


#include <vector>
#include <string>
#include <map>
#include <set>
#include  <list>
#include <assert.h>



#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")



using namespace std;

extern HWND g_hWnd;

#define SafeRelease(p) { if(p) p->Release(); p = NULL;  }
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#define SafeDelete(p) { if(p) delete p; p = NULL; }

// >> :
#define Singletone(class_name) \
		private : \
			class_name(void) ; \
			~class_name(void) ; \
		public : \
			static class_name* GetInstance() \
			{	\
				static class_name instance ; \
				return &instance ; \
			}
// << :
#include "cDeviceManager.h"



struct ST_PC_VERTEX //POINT COLOR
{
	D3DXVECTOR3 p;
	D3DXCOLOR   c;
	enum {
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};