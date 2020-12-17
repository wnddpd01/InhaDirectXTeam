#pragma once

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <algorithm>
#include <map>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <cassert>
#include <vector>
#include <string>
#include <queue>
#include <functional>

#include "DirectX9SDK/Include/d3d9.h"
#include "DirectX9SDK/Include/d3dx9.h"

#ifdef _WIN64
#pragma comment(lib, "DirectX9SDK/Lib/x64/d3d9.lib")
#pragma comment(lib, "DirectX9SDK/Lib/x64/d3dx9.lib")
# elif _WIN32
#pragma comment(lib, "DirectX9SDK/Lib/x86/d3d9.lib")
#pragma comment(lib, "DirectX9SDK/Lib/x86/d3dx9.lib")
#endif

#ifndef SAFE_DELETE
namespace  std
{
	template<class T>
	void SAFE_DELETE(T& item)
	{
		if (item)
		{
			delete item;
			item = nullptr;
		}
	}
}

#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif

#define ORTHO_WIDTH 40.f

enum class eDir
{
	UP = 0,
	DOWN,
	RIGHT,
	LEFT
};

enum class eShaderPath
{
	ALL_PATH = 0,
	PATH0 = 1,
	PATH1 = 2,
	PATH2 = 4,
	PATH3 = 8
};
struct Vertex
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Normal;
	D3DXVECTOR2 TexUV;

	bool operator==(const Vertex& other) const
	{
		if (Pos.x != other.Pos.x || Pos.y != other.Pos.y || Pos.z != other.Pos.z)
			return false;

		if (Normal.x != other.Normal.x || Normal.y != other.Normal.y || Normal.z != other.Normal.z)
			return false;

		if (TexUV.x != other.TexUV.x || TexUV.y != other.TexUV.y)
			return false;

		return true;
	}
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct CharacterVertex : Vertex
{
	D3DXVECTOR3 BoneWeights;
	BYTE BoneIndices[4];

	uint16_t MaterialIndex;
};

struct UIVertex : Vertex
{
	float Row;
};


namespace std
{
	template <>
	struct hash<D3DXVECTOR2>
	{
		std::size_t operator()(const D3DXVECTOR2& k) const
		{
			using std::size_t;
			using std::hash;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<float>()(k.x)
				^ (hash<float>()(k.y) << 1)));
		}
	};

	template <>
	struct hash<D3DXVECTOR3>
	{
		std::size_t operator()(const D3DXVECTOR3& k) const
		{
			using std::size_t;
			using std::hash;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<float>()(k.x)
					^ (hash<float>()(k.y) << 1)) >> 1)
				^ (hash<float>()(k.z) << 1);
		}
	};

	template <>
	struct hash<Vertex>
	{
		std::size_t operator()(const Vertex& k) const
		{
			using std::size_t;
			using std::hash;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<D3DXVECTOR3>()(k.Pos)
					^ (hash<D3DXVECTOR3>()(k.Normal) << 1)) >> 1)
				^ (hash<D3DXVECTOR2>()(k.TexUV) << 1);
		}
	};
}


#define SafeAddRef(p)	{if(p) p->AddRef() ; }

#define Synthesize(varType , varName , funName) \
protected : varType varName ; \
public : inline varType Get##funName(void) const { return varName ; } \
public : inline void Set##funName(varType var) { varName = var ; }

#define Synthesize_Add_Ref(varType , varName , funName) \
protected : varType varName ; \
public : virtual varType Get##funName(void) const { return varName ; } \
public : virtual void Set##funName(varType var ) { \
	if( varName != var ) \
	{ \
		SafeAddRef(var) ; \
		SAFE_RELEASE(varName) ; \
		varName = var ; \
	} \
}

#define Synthesize_Pass_by_Ref(varType , varName , funName) \
protected : varType varName ; \
public : inline varType& Get##funName(void)  { return varName ; } \
public : inline void Set##funName(varType& var) { varName = var ; }

#include <unordered_map>

#include <dinput.h>

#pragma comment(lib, "dinput8")
#pragma comment(lib, "dxguid")

using namespace std;

#include "fmod/fmod.hpp"
#pragma comment(lib, "fmod/fmodex_vc.lib")


#include "UIEventListener.h"
#include "TimeManager.h"
#include "DeviceManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "JSON.h"
#include "ModelLoader.h"

inline string to_string(D3DXVECTOR3 & vec3)
{
	string ret = "x : " + to_string(vec3.x) +
		",y : " + to_string(vec3.y) +
		",z : " + to_string(vec3.z);
	return ret;
}


#include "Base3DObject.h"
struct CollisionEvent
{
	Base3DObject * obj1;
	string obj1ColliderTag;
	Base3DObject * obj2;
	string obj2ColliderTag;
};
