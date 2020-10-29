#pragma once

#include <map>
#include <Windows.h>
#include <chrono>
#include <cassert>

//�̱��� ��ũ��
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