// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
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
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
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