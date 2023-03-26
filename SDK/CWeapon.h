#pragma once

class CWeapon
{
public:
	void StartFire() { VirtualFunction<void(__thiscall*)(void*)>(this, 88 / 8)(this); }
	void StopFire() { VirtualFunction<void(__thiscall*)(void*)>(this, 96 / 8)(this); }

	void ClampFire()
	{
		if (Chrono::join(280))
		{
			StartFire();
			StopFire();
		}
	}
};