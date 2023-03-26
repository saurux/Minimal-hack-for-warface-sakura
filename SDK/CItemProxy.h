#pragma once
#include "CWeapon.h"

class CItemProxy
{
public:
	CWeapon* GetWeapon() { return VirtualFunction<CWeapon* (__thiscall*)(void*)>(this, 632 / 8)(this); }
};