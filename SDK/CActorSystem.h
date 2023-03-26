#pragma once
#include <map>
#include "CActor.h"

class CActorSystem
{
public:
	CActor* GetActor(uint32_t iEntityId) { return VirtualFunction<CActor* (__thiscall*)(void*, uint32_t)>(this, 120 / 8)(this, iEntityId); }
	bool IsNotMyTeam(CActor* lActor, CActor* pActor){ return ((lActor->GetTeamId() != pActor->GetTeamId() || pActor->GetTeamId() == 0) && (pActor != lActor)); }
	bool IsMyTeam(CActor* lActor, CActor* pActor) {return ((lActor->GetTeamId() == pActor->GetTeamId() && lActor != pActor)); }

	std::map<unsigned int, CActor*, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, CActor*>>> GetActors() { return *(std::map<unsigned int, CActor*, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, CActor*>>>*)((DWORD64)this + 0x30); }
	
	template <typename T>
	inline T Get(DWORD64 dwOffset) { return *(T*)((DWORD64)this + dwOffset); }
};