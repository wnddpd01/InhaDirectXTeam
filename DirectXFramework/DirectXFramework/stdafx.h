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

#include "TimeManager.h"