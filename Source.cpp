#include <Windows.h>
#include <CALL.hpp>
#include <CGameFramework.h>

using fnUpdate = bool(__stdcall*)(CSystem*, int, int);
fnUpdate oUpdate;
VMTHookManager* pVirtualTableHook = new VMTHookManager();

void SetVisionParams(CEntity* pEntity, Color_tpl<float>* color, EHUDSilhouetteVisibility type, bool bDisableAtMin = false, float nearDist = 1000.f)
{
    CallFunction<void* (__fastcall*)(DWORD64, int, Color_tpl<float>*, bool, float)>(0x1415558D0)(0, pEntity->GetEntityId(), color, bDisableAtMin, nearDist);
} // need to update

std::map<unsigned int, CActor*, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, CActor*>>> m_actors;
Color_tpl<float> color;
bool Shots = false;

bool __stdcall Update(CSystem* pSystem, int updateFlags, int nPauseMode)
{
    if (GetAsyncKeyState(0x70) & 1) Shots = !Shots;

    color.r = 1.f;
    color.g = 0.f;
    color.b = 0.5f;
    color.a = 1.f;

    m_actors.clear();

    CGameFramework* pGameFramework = CGameFramework::Singleton();
    if (pGameFramework)
    {
        CActorSystem* pActorSystem = pGameFramework->GetActorSystem();
        CActor* pActor = pGameFramework->GetClientActor();

        if (pActor)
        {
            pActor->Set<float>(0xEAC, 3.5f); // need to update

            if (Shots)
            {
                if (CActor* pEntityActor = pActorSystem->GetActor(pActor->GetLookAtEntityId()))
                {
                    if (!pEntityActor->IsDead() && pActorSystem->IsNotMyTeam(pActor, pEntityActor))
                    {
                        pActor->GetWeapon()->ClampFire();
                    }
                }
            }

            m_actors = pActorSystem->GetActors();

            if (!m_actors.empty())
            {
                for (auto it = m_actors.begin(); it != m_actors.end(); ++it)
                {
                    if (it->second->IsDead())continue;

                    if (pActorSystem->IsNotMyTeam(pActor, it->second))
                    {
                        SetVisionParams(it->second->GetEntity(), &color, EHUDSilhouetteVisibility::Blocked);
                    }
                }
            }
        }
    }

    return oUpdate(pSystem, updateFlags, nPauseMode);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (0x1 == dwReason)
    {
        pVirtualTableHook->Initialize((PDWORD64*)CGameFramework::Singleton()->GetSystem()); // need to update
        oUpdate = (fnUpdate)pVirtualTableHook->dwHookMethod((DWORD64)Update, 4);
    }

    return TRUE;
}

