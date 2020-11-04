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


#define SafeRelease(p)		{ if(p) p->Release() ; p = NULL ; }
#define SafeDelete(p)	{ if( p) delete p ; p=NULL ; }



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

#include <unordered_map>

#include <dinput.h>

#pragma comment(lib, "dinput8")
#pragma comment(lib, "dxguid")

using namespace std;

#include "TimeManager.h"
#include "DeviceManager.h"
#include "TextureManager.h"