#pragma once

class CWorldQuery
{
public:
	char pad_0x0170[0x170];
	int m_lookAtEntityId;
};

class CGameObject
{
public:
	CWorldQuery* GetWorldQuery() { return VirtualFunction<CWorldQuery*(__thiscall*)(void*)>(this, 51)(this); }	
	int GetLookAtEntityId() { if (auto p = this->GetWorldQuery()) return p->m_lookAtEntityId; }
};