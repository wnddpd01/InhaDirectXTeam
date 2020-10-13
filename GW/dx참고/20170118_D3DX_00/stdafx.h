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


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hWnd;

#define SAFE_DELETE(p) { if (p) delete (p); }
#define SAFE_RELEASE(p) { if (p) (p)->Release(); }
#define SAFE_ADDREF(p) { if(p) (p)->AddRef(); }

#define SINGLETON(class_name) \
private:\
	class_name();\
	~class_name();\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SYNTHESIZE(varType, varName, funName) \
private:\
	varType varName;\
public:\
	inline varType Get##funName()  { return varName; }\
	inline void Set##funName(varType var) { varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName) \
private:\
	varType varName;\
public:\
	inline varType& Get##funName() { return varName; }\
	inline void Set##funName(varType& var) { varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName) \
private:\
	varType varName;\
public:\
	inline varType Get##funName()  { return varName; }\
	inline void Set##funName(varType var)\
	{\
		if(varName != var)\
		{\
			SAFE_RELEASE(varName);\
			SAFE_ADDREF(var);\
			varName = var;\
		}\
	}

#include <vector>
#include <assert.h>
#include <time.h>
#include <map>
#include <list>
#include <set>

using namespace std;

#include "cDeviceManager.h"
#include "cTextureManager.h"
#include "cTimeManager.h"
#include "cObject.h"
#include "cObjectManager.h"
#include "cGameObject.h"
#include "cAutoReleasePool.h"
#include "D3DUtility.h"
#include "cMaterialManager.h"

using namespace D3DUTILITY;

#define MAX_CLIME_SIZE	1.0f
#define GRAVITY			-1.0f
#define EPSILON			0.0001f