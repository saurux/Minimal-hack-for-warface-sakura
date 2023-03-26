#pragma once

#include "CEntity.h"
#include "CGameObject.h"
#include "CItemProxy.h"

class CActor
{
public:
	CEntity* GetEntity() { return *(CEntity**)((uint64_t)this + 0x10); }
	CGameObject* GetGameObject() { return *(CGameObject**)((uint64_t)this + 0x18); }
	int GetTeamId() { return *(uint32_t*)((uint64_t)this + 0x3E0); }
	int GetHealth() { return VirtualFunction<int(__thiscall*)(void*)>(this, 224 / 8)(this); }
	bool IsDead() { return GetHealth() <= 0; }
	CItemProxy* GetCurrentItem(bool includeVehicle = false) { return VirtualFunction<CItemProxy* (__thiscall*)(void*, bool)>(this, 464 / 8)(this, includeVehicle); }
	CWeapon* GetWeapon() { if (auto proxy = this->GetCurrentItem()) return proxy->GetWeapon(); }
	int GetLookAtEntityId() { if (auto g = GetGameObject()) return g->GetLookAtEntityId(); }

	template <class T>
	inline void Set(DWORD64 dwOffset, T tValue) { *(T*)((DWORD64)this + dwOffset) = tValue; }
};