#include "Lazy/lazy_importer.h"

#pragma data_seg()
#pragma comment(linker,"/MERGE:.rdata=.text")

#define _CRT_SECURE_NO_WARNINGS 1

#include <Windows.h>
#include <map>
#include <iostream>
#include <chrono>
#include <VMT.hpp>

using namespace std;

namespace Chrono
{
	using Clock = std::chrono::steady_clock;
	std::chrono::time_point<std::chrono::steady_clock> start = Clock::now(), now;
	std::chrono::milliseconds duration;

	bool join(int ms)
	{
		while (true)
		{
			now = Clock::now();
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);

			if (duration.count() >= ms)
			{
				start = Clock::now();
				return true;
			}

			return false;
		}
	}
}

enum EHUDSilhouetteVisibility
{
	Blocked = 0x0,
	NonBlocked = 0x1,
	DependingOnAlpha = 0x2,
	Always = 0x3,
};

template <typename T>
struct Color_tpl
{
	T r;
	T g;
	T b;
	T a;
};

template <typename T>
T VirtualFunction(void* base, __int32 index) { return (*(T**)base)[index]; }

template <typename V>
V CallFunction(DWORD64 dwPointer) { return (V)(dwPointer); }