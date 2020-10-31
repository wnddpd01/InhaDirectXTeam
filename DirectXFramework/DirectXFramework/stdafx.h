#pragma once
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#include <map>
#include <Windows.h>
#include <chrono>
#include <cassert>

#include "DirectX9SDK/Include/d3d9.h"
#include "DirectX9SDK/Include/d3dx9.h"
#pragma comment(lib, "DirectX9SDK/Lib/x86/d3d9.lib")
#pragma comment(lib, "DirectX9SDK/Lib/x86/d3dx9.lib")

#include "TimeManager.h"
#include "DeviceManager.h"
