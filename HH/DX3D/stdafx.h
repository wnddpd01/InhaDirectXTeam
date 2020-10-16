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
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>


#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hwnd;

#define RENDERTIME 0.02f
#define GAMETIME 0.02f
#define TEXTURESIZE 64.f

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

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct CheckPoint
{
	//D3DXVECTOR3 DestPoint;
	std::vector<D3DXVECTOR3> SplinePoint;
};


struct Scene
{
	std::string		FileName;
	int				FirstFrame;
	int				LastFrame;
	int				FrameSpeed;
	int				TickSperFrame;
	D3DXVECTOR3		BackGraound_Static;
	D3DXVECTOR3		Ambient_Static;
};

struct MapDiffuse
{
	std::string		MapName;
	std::string		MapClass;
	int				SubNo;
	float			MapAmount;
	std::string		Bitmap;
	std::string		MapType;
	float			UVW_U_Offset;
	float			UVW_V_Offset;
	float			UVW_U_Tiling;
	float			UVW_V_Tiling;
	float			UVW_Angel;
	float			UVW_Blur;
	float			UVW_Blur_Offset;
	float			UVW_Nouse_Amt;
	float			UVW_Noise_Size;
	int				UVW_Noise_Level;
	float			UVW_Noise_Phase;
	std::string		Bitmap_Filter;
};

struct Material
{
	std::string		Name;
	std::string		Class;
	D3DXVECTOR3		Ambient;
	D3DXVECTOR3		Diffuse;
	D3DXVECTOR3		Specular;
	float			Shine;
	float			ShineStrength;
	float			Transparency;
	float			WireSize;
	std::string		Shading;
	float			Xp_Falloff;
	float			SelfIllum;
	std::string		Falloff;
	std::string		XP_Type;
	MapDiffuse		structDiffuse;
};


struct GeoNodeTm
{
	std::string		nodeName;
	D3DXVECTOR3		inheritPos;
	D3DXVECTOR3		inheritRot;
	D3DXVECTOR3		inheritScl;
	D3DXMATRIXA16	tmMat;
	D3DXVECTOR3		tmPos;
	D3DXVECTOR3		tmRotAxis;
	float			tmRotAngle;
	D3DXVECTOR3		tmScale;
	D3DXVECTOR3		tmScaleAxis;
	float			tmScaleAxisAng;
};

struct GeoMesh
{
	int timeValue;
	int NumVertex;
	int NumFaces;
	int NumTVertex;
	int NumTFace;
	std::vector<ST_PNT_VERTEX> vecVertex;
};

struct GeoAnimation
{
	std::map<int, D3DXVECTOR3> ControlPos;
	std::map<int, D3DXVECTOR3> ControlRot;
};


#define Synthesize(varType, varName, funName) \
	protected : varType varName ; \
	public : inline varType Get##funName(void) const {return varName;} \
	public : inline void Set##funName(varType var) { varName = var; }

#define Synthesize_pass_by_Ref(varType, varName, funName) \
	protected : varType varName ; \
	public : inline varType& Get##funName(void) {return varName;} \
	public : inline void Set##funName(varType& var) { varName = var; }


#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

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
#define SafeAddRef(p) { if(p) p->AddRef() ; }

/*
#define Synthesize_Add_Ref(varType, varName, funName) \
	protected : varType varName ; \
	public : virtual varType Get##funName(void) const { return varName ; } \
	public : virtual void Set##funName(varType var) { \
		if( varName != var ) \
		{ \
			SafeAddRef(var); \
			SafeRelease(varName) \
			varName = var; \
		} \
	}
	*/

#define Synthesize_Add_Ref(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const {return varName;}\
public:virtual void Set##funName(varType var){\
   if(varName != var)\
   {\
      SafeAddRef(var);\
      SafeRelease(varName);\
      varName = var;\
   }\
}

#include "iMap.h"
#include "Object.h"
#include "cDeviceManager.h";
#include "cBodyCube.h"
#include "ObjParser.h"

#include "tObject.h"
#include "tObjectManager.h"
#include "tTextureManager.h"


// TODO: reference additional headers your program requires here
