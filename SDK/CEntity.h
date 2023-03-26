#pragma once

class CEntity
{
private:
	char pad_0x0000[0x18]; //0x0000
	int dwEntityId; //0x0018 
public:
	int GetEntityId() { return this->dwEntityId; }
	const char* GetName() { return VirtualFunction<const char* (__thiscall*)(void*)>(this, 96 / 8)(this); }
	int GetFlags() {return VirtualFunction<int(__thiscall*)(void*)>(this, 0x30 / 8)(this);}

	template <typename T>
	inline void Set(DWORD64 dwOffset, T tValue) { *(T*)((DWORD64)this + dwOffset) = tValue; }
	template <typename T>
	inline T Get(DWORD64 dwOffset) { return *(T*)((DWORD64)this + dwOffset); }
};