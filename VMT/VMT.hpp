#pragma once
#include <Windows.h>

#ifdef _WIN64
#define _pdword        PDWORD64
#define _dword        DWORD64
#else
#define _pdword        PDWORD
#define _dword        DWORD
#endif

class VMTHookManager
{
public:
	VMTHookManager(void)
	{
		memset(this, 0, sizeof(VMTHookManager));
	}
	VMTHookManager(_pdword* ppdwClassBase)
	{
		Initialize(ppdwClassBase);
	}
	~VMTHookManager(void)
	{
		UnHook();
	}
	bool Initialize(_pdword* uClassBase)
	{
		if (uClassBase == m_ppdwClassBase)
			return false;

		if (uClassBase && m_pdwNewVMT)
		{
			*uClassBase = m_pdwOldVMT;
			delete[] m_pdwNewVMT;
		}

		if (!uClassBase)
			return false;

		m_ppdwClassBase = uClassBase;
		m_pdwOldVMT = *uClassBase;
		m_dwVMTSize = dwGetVMTCount(*uClassBase);
		m_pdwNewVMT = new _dword[m_dwVMTSize];

		memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(_dword) * m_dwVMTSize);
		*uClassBase = m_pdwNewVMT;

		return true;
	}
	bool Initialize(_pdword** pppdwClassBase)
	{
		return Initialize(*pppdwClassBase);
	}
	void UnHook(void)
	{
		if (m_ppdwClassBase)
		{
			*m_ppdwClassBase = m_pdwOldVMT;
		}
	}
	void ReHook(void)
	{
		if (m_ppdwClassBase)
		{
			*m_ppdwClassBase = m_pdwNewVMT;
		}
	}
	int iGetFuncCount(void)
	{
		return (int)m_dwVMTSize;
	}
	_dword dwGetMethodAddress(int Index)
	{
		if (Index >= 0 && Index <= (int)m_dwVMTSize && m_pdwOldVMT != NULL)
		{
			return m_pdwOldVMT[Index];
		}
		return NULL;
	}
	_pdword pdwGetOldVMT(void)
	{
		return m_pdwOldVMT;
	}
	_dword dwHookMethod(_dword dwNewFunc, unsigned int iIndex)
	{
		if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
		{
			m_pdwNewVMT[iIndex] = dwNewFunc;
			return m_pdwOldVMT[iIndex];
		}

		return NULL;
	}
private:
	_dword dwGetVMTCount(_pdword pdwVMT)
	{
		_dword dwIndex = 0;

		for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
		{
			if (IsBadCodePtr((FARPROC)pdwVMT[dwIndex]))
			{
				break;
			}
		}
		return dwIndex;
	}
	_pdword* m_ppdwClassBase;
	_pdword    m_pdwNewVMT, m_pdwOldVMT;
	_dword    m_dwVMTSize;
};