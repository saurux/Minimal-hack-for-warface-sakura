#pragma once
#include "CActorSystem.h"

class CSystem {public:};

class CGameFramework
{
public:
	static CGameFramework* Singleton() { return *(CGameFramework**)0x1421AB058; } // Failed to create the GameFramework
	CActorSystem* GetActorSystem() { return *(CActorSystem**)((uint64_t)this + 0x4E0);}
	CSystem* GetSystem() { return VirtualFunction<CSystem* (__thiscall*)(void*)>(this, 160 / 8)(this); }
	CActor* GetClientActor() { CActor* pNewActor = 0; if (VirtualFunction<bool(__thiscall*)(void*, CActor**)>(this, 1136 / 8)(this, &pNewActor)) { return pNewActor; } else { return 0; } }
};